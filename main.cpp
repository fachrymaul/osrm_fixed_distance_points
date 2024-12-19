#include <curlpp/Exception.hpp>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <curlpp/Easy.hpp>
#include <curlpp/Option.hpp>
#include <curlpp/Options.hpp>
#include "include/json.hpp"

void performGetRequest(const std::string& url) {
	try {
		std::cout << "url = " << url << std::endl;
		std::ostringstream response;

		curlpp::Easy request;

		request.setOpt(curlpp::options::Url(url));
		request.setOpt(curlpp::options::WriteStream(&response));
		request.perform();
		// std::cout << "GET response: " << response.str() << std::endl;


		nlohmann::json root = nlohmann::json::parse(response.str());

		// std::cout << "Routes: " << root["routes"] << std::endl;
		// auto routes = root["routes"];
		auto steps = root["routes"][0]["legs"][0]["steps"];
		
		// std::cout << "legs: " << legs << std::endl;
		for(const auto& step : steps) {
		 std::cout << "legs: " << step["geometry"] << std::endl;
		}

		// nlohmann::json routes = nlohmann::json::parse(root["routes"]);

		// std::cout << "legs: " << routes["legs"] << std::endl;

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
