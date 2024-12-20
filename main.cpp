#include <curlpp/Exception.hpp>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <curlpp/Easy.hpp>
#include <curlpp/Option.hpp>
#include <curlpp/Options.hpp>
#include <utility>
#include <vector>
#include "include/json.hpp"

const int CHUNK_ADDER = 63;

std::vector<std::string> *parseGeometry(nlohmann::json osrmResp) {
	std::vector<std::string> *res = new std::vector<std::string>;
	auto steps = osrmResp["routes"][0]["legs"][0]["steps"];

	for(const auto& step : steps) {
		res->push_back(step["geometry"]);
	}
	
	return res;
}

int parsePolyline(std::string polyline) {
	char const *polylineBytes = polyline.c_str();
	int res = 0;

	bool neg = false;
	for(int i = 0; i < polyline.length(); i++) {
		
		char chunk0x20 =  polylineBytes[i] - CHUNK_ADDER;
		char chunk5bit = chunk0x20 & 0b011111;
		res |= ((int)chunk5bit) << (5 * i);

		if(i == 0) {
			neg = (chunk5bit & 0x01) == 1;
		}
	}

	res = res >> 1;
	if(neg) {
		res = res * -1;
	}

	return res;
}

// std::vector<std::pair<double, double>> parseGeometryPolyline(std::string polyline) {
// 	std::vector<std::pair<double, double>> res;
// 
// 
// 	
// 	return res;
// }
std::vector<std::string> *splitPolyline(std::string input) {
	std::vector<std::string> *polylineString = new std::vector<std::string>;
	int curStart = 0;

	for(int i = 0; i < input.length(); i++) {
		if(((int)input[i]) < 95) {
			polylineString->push_back(input.substr(curStart, i - curStart + 1));
			curStart = i + 1;
		}
	}

	return polylineString;
}

std::vector<std::pair<double, double>> constructPolylineCoordinate(std::vector<int> &input) {
	std::vector<std::pair<double, double>> coordinates;
	std::pair<int, int> current = std::make_pair(0,0);

	for(int i = 0; i < input.size() / 2; i++) {
		int index = i << 1;
		if(current.first == 0 || current.second == 0 || input[index] <= -6 || input[index + 1] >= 106) {
			current.first = input[index];
			current.second = input[index + 1];
		} else {
			current.first += input[index];
			current.second += input[index + 1];
		}
		std::cout << "[" << current.second/100000 << "." << current.second%100000<< ", " << current.first/100000 << "." << (current.first*-1)%100000 << "]," << std::endl;
		
		coordinates.push_back(current);
	}

	return coordinates;
}

void performGetRequest(const std::string& url) {
	try {
		std::cout << "url = " << url << std::endl;
		std::ostringstream response;

		curlpp::Easy request;

		request.setOpt(curlpp::options::Url(url));
		request.setOpt(curlpp::options::WriteStream(&response));
		request.perform();


		nlohmann::json root = nlohmann::json::parse(response.str());
		auto geometries = parseGeometry(root);
		for(const auto& geometry : *geometries) {
			std::vector<std::string> *polylines = splitPolyline(geometry);
			std::vector<int> parsed;
			for(const auto& polyline : *polylines) {
				int temp = parsePolyline(polyline);
				parsed.push_back(temp);
				// std::cout << temp << ", ";
			}
			// std::cout << std::endl;
			std::vector<std::pair<double, double>> coordinates = constructPolylineCoordinate(parsed);

			// for(const auto& coordinate: coordinates) {
			// 	std::cout << coordinate.first << ", " << coordinate.second << std::endl;
			// }

		}

		std::free(geometries);

	} catch (const curlpp::RuntimeError& e) {
		std::cout << "GET Request Runtime Error: " << e.what() << std::endl;
	} catch (const curlpp::LogicError& e) {
		std::cout << "GET Request Logic Error: " << e.what() << std::endl;
	}
}


int main() {
	const std::string url = "http://devmaps.gcp.bluebird.id/route/v1/driving/106.82602254957169,-6.246468326576988;106.8307105339486,-6.176810978147785?overview=false&alternatives=false&steps=true&annotations=false";
	std::cout << "Performing GET request" << std::endl;
	performGetRequest(url);

	return 0;
}
