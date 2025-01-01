#include "include/json.hpp"
#include <cmath>
#include <curlpp/Easy.hpp>
#include <curlpp/Exception.hpp>
#include <curlpp/Option.hpp>
#include <curlpp/Options.hpp>
#include <iomanip>
#include <ios>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

const int CHUNK_ADDER = 63;
const int EARTH_DIAMETER = 6371000;

std::vector<std::string> parseGeometry(nlohmann::json osrmResp) {
  std::vector<std::string> res;
  auto steps = osrmResp["routes"][0]["legs"][0]["steps"];

  for (const auto &step : steps) {
    res.push_back(step["geometry"]);
  }

  return res;
}

int parsePolyline(std::string polyline) {
  char const *polylineBytes = polyline.c_str();
  int res = 0;
  std::cout << "tempe" << std::endl;

  bool neg = false;
  for (int i = 0; i < polyline.length(); i++) {

    char chunk0x20 = polylineBytes[i] - CHUNK_ADDER;
    char chunk5bit = chunk0x20 & 0b011111;
    res |= ((int)chunk5bit) << (5 * i);

    if (i == 0) {
      neg = (chunk5bit & 0x01) == 1;
    }
  }

  res = res >> 1;
  if (neg) {
    res = res * -1;
  }

  return res;
}

std::vector<std::string> splitPolyline(std::string input) {
  std::vector<std::string> polylineString;
  int curStart = 0;

  for (int i = 0; i < input.length(); i++) {
    if (((int)input[i]) < 95) {
      polylineString.push_back(input.substr(curStart, i - curStart + 1));
      curStart = i + 1;
    }
  }

  return polylineString;
}

std::vector<std::pair<double, double>>
constructPolylineCoordinate(std::vector<int> &input) {
  std::vector<std::pair<double, double>> coordinates;
  std::pair<double, double> current = std::make_pair(0, 0);
  int longitude = 0;
  int latitude = 0;

  for (int i = 0; i < input.size() / 2; i++) {
    int index = i << 1;
    if (longitude == 0 || latitude == 0) {
      latitude = input[index];
      longitude = input[index + 1];
    } else {
      latitude += input[index];
      longitude += input[index + 1];
    }
    current.first = static_cast<double>(latitude) / 100000.0;
    current.second = static_cast<double>(longitude) / 100000.0;

    coordinates.push_back(current);
  }

  return coordinates;
}

double degToRad(double deg) { return (deg * M_PI) / 180; }

double radToDeg(double rad) { return (rad * 180) / M_PI; }

double latLongDistance(std::pair<double, double> start,
                       std::pair<double, double> end) {
  double a = std::pow(std::sin((end.first - start.first) / 2), 2) +
             std::cos(start.first) * std::cos(end.first) *
                 std::pow(std::sin((end.second - start.second) / 2), 2);
  double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));

  return EARTH_DIAMETER * c;
}

std::vector<double>
getCoordinatesDistance(std::vector<std::pair<double, double>> coordinates) {
  std::vector<double> res;

  for (int i = 0; i < coordinates.size() - 1; i++) {
    std::pair<double, double> start = std::make_pair(
        degToRad(coordinates[i].first), degToRad(coordinates[i].second));
    std::pair<double, double> end =
        std::make_pair(degToRad(coordinates[i + 1].first),
                       degToRad(coordinates[i + 1].second));

    double distance = latLongDistance(start, end);
    res.push_back(distance);
  }

  return res;
}

std::vector<std::pair<double, double>>
calculateDistancedPoints(std::vector<std::pair<double, double>> routes,
                         std::vector<double> distances, double fixedDistance) {
  std::vector<std::pair<double, double>> res;

  double distance = 0;
  std::vector<std::pair<double, double>> points;
  for (int i = 0; i < routes.size(); i++) {
    double temp = distance - distances[i];
    if (temp <= 0) {
      res.push_back(routes[i]);
      distance = fixedDistance + temp;
    } else {
      distance -= distances[i];
    }
  }

  return res;
}

std::string performGetRequest(const std::string &url) {
  try {
    std::cout << "url = " << url << std::endl;
    std::ostringstream response;

    curlpp::Easy request;

    request.setOpt(curlpp::options::Url(url));
    request.setOpt(curlpp::options::WriteStream(&response));
    request.perform();

    return response.str();
  } catch (const curlpp::RuntimeError &e) {
    std::cout << "GET Request Runtime Error: " << e.what() << std::endl;
  } catch (const curlpp::LogicError &e) {
    std::cout << "GET Request Logic Error: " << e.what() << std::endl;
  }
  return "";
}

std::vector<std::pair<double, double>> calculatePoints(std::string input) {
  nlohmann::json root = nlohmann::json::parse(input);
  auto geometries = parseGeometry(root);
  std::vector<std::pair<double, double>> coordinatesCollection;
  for (const auto &geometry : geometries) {
    std::vector<std::string> polylines = splitPolyline(geometry);
    std::vector<int> parsed;
    for (const auto &polyline : polylines) {
      int temp = parsePolyline(polyline);
      parsed.push_back(temp);
    }
    std::vector<std::pair<double, double>> coordinates =
        constructPolylineCoordinate(parsed);

    for (const auto &coordinate : coordinates) {
      coordinatesCollection.push_back(coordinate);
    }
  }

  std::vector<double> distances = getCoordinatesDistance(coordinatesCollection);

  auto points = calculateDistancedPoints(coordinatesCollection, distances, 100);

  return points;
}

std::vector<std::pair<double, double>>
getPoints(std::pair<double, double> start, std::pair<double, double> end) {
  std::stringstream ss;
  ss << "http://devmaps.gcp.bluebird.id/route/v1/driving/" << start.second
     << "," << start.first << ";" << end.second << "," << end.first
     << "?overview=false&alternatives=false&steps=true&annotations=false";

  const std::string url = ss.str();
  std::cout << "Performing GET request" << std::endl;
  std::string response = performGetRequest(url);
  return calculatePoints(response);
}

int main() {
  auto points = getPoints(std::make_pair(-6.22367, 106.8061675),
                          std::make_pair(-6.1766575, 106.8177421));

  for (const auto &point : points) {
    std::cout << std::fixed << std::setprecision(5) << point.second << ","
              << point.first << std::endl;
  }

  return 0;
}
