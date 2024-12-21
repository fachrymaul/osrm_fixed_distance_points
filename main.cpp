#include <curlpp/Exception.hpp>
#include <iomanip>
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
#include <cmath>

const int CHUNK_ADDER = 63;
const int EARTH_DIAMETER = 6371000;
const std::string OSRM_DATA = "{\"code\":\"Ok\",\"routes\":[{\"legs\":[{\"steps\":[{\"geometry\":\"l_ce@wm_kSC?iDVa@B}@FUBa@@gADE@sADk@@WBu@@g@B{@B_@@o@?w@@E?Q?\",\"maneuver\":{\"bearing_after\":350,\"bearing_before\":0,\"location\":[106.82604,-6.246465],\"type\":\"depart\"},\"mode\":\"driving\",\"driving_side\":\"right\",\"name\":\"Jalan Mampang Prapatan Raya\",\"intersections\":[{\"out\":0,\"entry\":[true],\"bearings\":[350],\"location\":[106.82604,-6.246465]},{\"out\":2,\"in\":0,\"entry\":[false,true,true],\"bearings\":[165,270,345],\"location\":[106.825924,-6.245596]},{\"out\":0,\"in\":1,\"entry\":[true,false,true],\"bearings\":[0,180,270],\"location\":[106.825795,-6.244479]},{\"out\":0,\"in\":1,\"entry\":[true,false,true],\"bearings\":[0,180,270],\"location\":[106.825732,-6.243688]}],\"weight\":26.900000000,\"duration\":26.900000000,\"distance\":483.2},{\"geometry\":\"fdbe@kk_kSi@EeA?aAAgDEa@AkAMGC{@OgAWcEkAg@SUKe@U{@i@[QcAe@k@[o@@}@g@g@Wq@c@w@q@y@y@KGMI\",\"maneuver\":{\"bearing_after\":1,\"bearing_before\":358,\"location\":[106.825664,-6.242116],\"modifier\":\"slight right\",\"type\":\"fork\"},\"mode\":\"driving\",\"destinations\":\"Menteng, Setiabudi\",\"driving_side\":\"right\",\"name\":\"Terowongan Mampang-Kuningan\",\"intersections\":[{\"out\":0,\"in\":1,\"entry\":[true,false,true],\"bearings\":[0,180,345],\"location\":[106.825664,-6.242116]},{\"out\":0,\"classes\":[\"tunnel\"],\"in\":1,\"entry\":[true,false],\"bearings\":[0,180],\"location\":[106.825727,-6.240385]},{\"out\":0,\"in\":1,\"entry\":[true,false],\"bearings\":[15,195],\"location\":[106.825812,-6.239839]},{\"out\":1,\"in\":2,\"entry\":[true,true,false],\"bearings\":[0,15,195],\"location\":[106.825826,-6.239796]},{\"out\":0,\"classes\":[\"tunnel\"],\"in\":1,\"entry\":[true,false],\"bearings\":[30,210],\"location\":[106.82698,-6.237218]},{\"out\":0,\"in\":1,\"entry\":[true,false],\"bearings\":[30,210],\"location\":[106.827469,-6.236421]}],\"weight\":48.8,\"duration\":48.8,\"distance\":880.4},{\"geometry\":\"nw`e@w}_kSeAcBEIUm@[}@c@mASg@[o@Wc@k@_AOQi@s@e@g@e@a@MMYU@Wo@a@e@Uo@[MG]Mq@UmA]UEi@MmAUw@Ke@CWCO?@@c@?e@@a@Bc@@M?k@Bg@@[@U?{@BM?I@I?U@Y@S@oABS@qABgFLs@B_DLeAP{B^gARaANeDp@QB_BR{@TSJ]JmDfAiEx@@Hu@LIBiAL]Dy@HmALu@Hm@FgBHQ@iBF}BJO@gBDyBHkCDE?sA?K@uE?o@@qG\\\\}@Ja@Fu@Nw@Nm@Ny@Tu@Rw@Xw@Z_ChAIFGB]TWJaCnA\",\"maneuver\":{\"bearing_after\":54,\"bearing_before\":30,\"location\":[106.828595,-6.234961],\"modifier\":\"straight\",\"type\":\"turn\"},\"mode\":\"driving\",\"driving_side\":\"right\",\"name\":\"Jalan Hajjah R. Rasuna Said\",\"intersections\":[{\"out\":0,\"in\":1,\"entry\":[true,false,false],\"bearings\":[60,210,240],\"location\":[106.828595,-6.234961]},{\"out\":0,\"in\":1,\"entry\":[true,false,true],\"bearings\":[60,240,330],\"location\":[106.829099,-6.234607]},{\"out\":0,\"in\":1,\"entry\":[true,false,false],\"bearings\":[60,240,330],\"location\":[106.829153,-6.234575]},{\"out\":0,\"in\":1,\"entry\":[true,false,true],\"bearings\":[45,240,315],\"location\":[106.831018,-6.233567]},{\"out\":0,\"in\":1,\"entry\":[true,false,false],\"bearings\":[45,225,315],\"location\":[106.831106,-6.233494]},{\"out\":0,\"in\":2,\"entry\":[true,false,false],\"bearings\":[30,165,210],\"location\":[106.832497,-6.231797]},{\"out\":0,\"in\":2,\"entry\":[true,true,false],\"bearings\":[0,90,180],\"location\":[106.833018,-6.227536]},{\"out\":0,\"in\":1,\"entry\":[true,false,true],\"bearings\":[0,180,345],\"location\":[106.832961,-6.226699]},{\"out\":2,\"in\":0,\"entry\":[false,false,true],\"bearings\":[176,185,355],\"location\":[106.832867,-6.225134]},{\"out\":0,\"in\":2,\"entry\":[true,false,false],\"bearings\":[0,90,180],\"location\":[106.832845,-6.224874]},{\"out\":2,\"in\":0,\"entry\":[false,true,true],\"bearings\":[165,255,330],\"location\":[106.831868,-6.22071]},{\"out\":2,\"in\":0,\"entry\":[false,false,true],\"bearings\":[150,210,345],\"location\":[106.831808,-6.220612]},{\"out\":2,\"in\":1,\"entry\":[true,false,true],\"bearings\":[45,165,345],\"location\":[106.830889,-6.217732]},{\"out\":2,\"in\":0,\"entry\":[false,true,true],\"bearings\":[165,270,345],\"location\":[106.830739,-6.216896]},{\"out\":0,\"in\":1,\"entry\":[true,false,true],\"bearings\":[0,180,315],\"location\":[106.830454,-6.214034]},{\"out\":0,\"in\":2,\"entry\":[true,true,false],\"bearings\":[0,90,180],\"location\":[106.830366,-6.21227]},{\"out\":0,\"in\":2,\"entry\":[true,false,false],\"bearings\":[0,75,180],\"location\":[106.83036,-6.212205]},{\"out\":2,\"in\":0,\"entry\":[false,true,true],\"bearings\":[165,300,345],\"location\":[106.830138,-6.209218]},{\"out\":2,\"in\":0,\"entry\":[false,false,true],\"bearings\":[165,225,345],\"location\":[106.830095,-6.209051]},{\"out\":2,\"in\":0,\"entry\":[false,false,true],\"bearings\":[150,180,330],\"location\":[106.828972,-6.206456]}],\"weight\":197.600000000,\"duration\":197.600000000,\"distance\":3573.1},{\"geometry\":\"j_{d@k|kS[NsAj@_AZiAPq@BgAAy@Aq@C{AE\",\"maneuver\":{\"bearing_after\":330,\"bearing_before\":327,\"location\":[106.828376,-6.2055],\"modifier\":\"straight\",\"type\":\"new name\"},\"mode\":\"driving\",\"driving_side\":\"right\",\"name\":\"Jalan Kuningan Flyover\",\"intersections\":[{\"out\":1,\"in\":0,\"entry\":[false,true],\"bearings\":[150,330],\"location\":[106.828376,-6.2055]}],\"weight\":18.2,\"duration\":18.2,\"distance\":329.3},{\"geometry\":\"nmzd@ky_kSE?q@Eo@G}@GsEI_EY]EYEmBMq@Ea@Ec@C}@GwGe@cBKcAKoAKE?c@AEAsCBSAoDAoDCoBA]AMC\",\"maneuver\":{\"bearing_after\":1,\"bearing_before\":2,\"location\":[106.8279,-6.202639],\"modifier\":\"straight\",\"type\":\"new name\"},\"mode\":\"driving\",\"driving_side\":\"right\",\"name\":\"Jalan Haji Oemar Said Cokroaminoto\",\"intersections\":[{\"out\":0,\"in\":1,\"entry\":[true,false],\"bearings\":[0,180],\"location\":[106.8279,-6.202639]},{\"out\":0,\"in\":1,\"entry\":[true,false,true],\"bearings\":[0,180,345],\"location\":[106.827901,-6.202605]},{\"out\":0,\"in\":1,\"entry\":[true,false,false],\"bearings\":[0,195,225],\"location\":[106.828012,-6.201814]},{\"out\":0,\"in\":1,\"entry\":[true,false,true],\"bearings\":[15,180,270],\"location\":[106.828055,-6.200748]},{\"out\":0,\"in\":2,\"entry\":[true,false,false,true],\"bearings\":[15,105,195,285],\"location\":[106.82822,-6.199638]},{\"out\":0,\"in\":2,\"entry\":[true,true,false,false],\"bearings\":[15,90,195,285],\"location\":[106.828245,-6.199507]},{\"out\":0,\"in\":1,\"entry\":[true,false,true],\"bearings\":[0,195,285],\"location\":[106.828403,-6.198363]},{\"out\":0,\"in\":1,\"entry\":[true,false,true],\"bearings\":[15,195,270],\"location\":[106.828693,-6.196151]},{\"out\":0,\"in\":2,\"entry\":[true,false,false,true],\"bearings\":[0,90,195,285],\"location\":[106.828808,-6.195407]},{\"out\":0,\"in\":2,\"entry\":[true,true,false,false],\"bearings\":[0,90,180,285],\"location\":[106.828826,-6.195169]},{\"out\":0,\"in\":1,\"entry\":[true,false,true],\"bearings\":[15,180,330],\"location\":[106.828867,-6.191856]}],\"weight\":68.9,\"duration\":68.9,\"distance\":1207},{\"geometry\":\"tixd@qkSIECEGCYYCEm@o@sByBKKCGGCOO_BeBYYgBmBEE{A_Bg@i@GGSS}AeBKIq@w@GCI?GD]PA@i@XMBG@IE\",\"maneuver\":{\"bearing_after\":36,\"bearing_before\":16,\"location\":[106.828887,-6.191792],\"modifier\":\"slight right\",\"type\":\"turn\"},\"mode\":\"driving\",\"driving_side\":\"right\",\"name\":\"Jalan Dokter Sam Ratulangi\",\"intersections\":[{\"out\":1,\"in\":2,\"entry\":[true,true,false],\"bearings\":[0,45,195],\"location\":[106.828887,-6.191792]},{\"out\":0,\"in\":2,\"entry\":[true,false,false,true],\"bearings\":[45,90,225,270],\"location\":[106.828973,-6.19168]},{\"out\":0,\"in\":1,\"entry\":[true,false,false],\"bearings\":[45,225,255],\"location\":[106.829104,-6.191553]},{\"out\":0,\"in\":2,\"entry\":[true,true,false,false],\"bearings\":[45,150,225,330],\"location\":[106.83008,-6.190637]},{\"out\":0,\"in\":2,\"entry\":[true,true,false],\"bearings\":[45,135,225],\"location\":[106.830816,-6.189914]},{\"out\":0,\"in\":2,\"entry\":[true,true,false],\"bearings\":[45,135,225],\"location\":[106.832131,-6.188658]},{\"out\":0,\"in\":1,\"entry\":[true,false],\"bearings\":[30,225],\"location\":[106.833069,-6.187775]},{\"out\":0,\"in\":1,\"entry\":[true,false,true],\"bearings\":[15,150,285],\"location\":[106.832827,-6.187279]}],\"weight\":47,\"duration\":47,\"distance\":724.2},{\"geometry\":\"nlwd@ex`kSGOEQGQUmAKcAC[A]AM?i@@o@@SBy@@Q@{@BkBCKCGKIIGGAYM\",\"maneuver\":{\"bearing_after\":66,\"bearing_before\":1,\"location\":[106.832827,-6.187121],\"modifier\":\"right\",\"type\":\"turn\"},\"mode\":\"driving\",\"driving_side\":\"right\",\"name\":\"Jalan Cut Meutia\",\"intersections\":[{\"out\":0,\"in\":1,\"entry\":[true,false,true,false],\"bearings\":[60,180,240,345],\"location\":[106.832827,-6.187121]},{\"out\":1,\"in\":2,\"entry\":[true,true,false],\"bearings\":[0,90,255],\"location\":[106.83382,-6.186838]},{\"out\":1,\"in\":2,\"entry\":[true,true,false],\"bearings\":[0,90,270],\"location\":[106.834106,-6.186806]},{\"out\":0,\"in\":2,\"entry\":[true,false,false],\"bearings\":[90,255,270],\"location\":[106.835016,-6.186843]},{\"out\":0,\"in\":2,\"entry\":[true,true,false],\"bearings\":[75,180,270],\"location\":[106.835945,-6.186884]}],\"weight\":22.4,\"duration\":22.4,\"distance\":398.8},{\"geometry\":\"~hwd@kmakSQ@_@HWHIDg@VSLe@Vy@f@QLa@TEDy@@{@d@CBOHm@Za@To@\\\\a@TMHk@ZWNC@SDYVGJIJGPQd@CHCJ\",\"maneuver\":{\"bearing_after\":352,\"bearing_before\":26,\"location\":[106.836216,-6.186564],\"modifier\":\"slight left\",\"type\":\"new name\"},\"mode\":\"driving\",\"driving_side\":\"right\",\"name\":\"Jalan Menteng Raya\",\"intersections\":[{\"out\":0,\"in\":2,\"entry\":[true,false,false],\"bearings\":[0,180,210],\"location\":[106.836216,-6.186564]},{\"out\":2,\"in\":0,\"entry\":[false,true,true],\"bearings\":[150,240,330],\"location\":[106.834417,-6.183567]},{\"out\":2,\"in\":0,\"entry\":[false,false,true],\"bearings\":[150,225,330],\"location\":[106.834373,-6.183503]},{\"out\":2,\"in\":0,\"entry\":[false,true,true],\"bearings\":[150,255,330],\"location\":[106.834225,-6.183278]},{\"out\":2,\"in\":1,\"entry\":[false,false,true],\"bearings\":[120,150,315],\"location\":[106.834107,-6.183043]}],\"weight\":32.000000000,\"duration\":32.000000000,\"distance\":539.7},{\"geometry\":\"ppvd@g|`kSQRGHKLWV[RKFMF_@Ra@Na@Ni@PODgD~@\",\"maneuver\":{\"bearing_after\":309,\"bearing_before\":289,\"location\":[106.83348,-6.182646],\"modifier\":\"straight\",\"type\":\"new name\"},\"mode\":\"driving\",\"driving_side\":\"right\",\"name\":\"Jalan Mohammad Ihwan Ridwan Rais\",\"intersections\":[{\"out\":3,\"in\":1,\"entry\":[false,false,false,true],\"bearings\":[60,105,255,315],\"location\":[106.83348,-6.182646]},{\"out\":3,\"in\":1,\"entry\":[false,false,false,true],\"bearings\":[45,135,255,315],\"location\":[106.833378,-6.182562]},{\"out\":2,\"in\":0,\"entry\":[false,false,true],\"bearings\":[135,165,330],\"location\":[106.833139,-6.182343]}],\"weight\":17.8,\"duration\":17.8,\"distance\":283.3},{\"geometry\":\"vbvd@st`kSI?I@aEz@YJMBmATo@JKB\",\"maneuver\":{\"bearing_after\":341,\"bearing_before\":338,\"location\":[106.832259,-6.180439],\"modifier\":\"straight\",\"type\":\"new name\"},\"mode\":\"driving\",\"driving_side\":\"right\",\"name\":\"Jalan Medan Merdeka Timur\",\"intersections\":[{\"out\":2,\"in\":0,\"entry\":[false,true,true],\"bearings\":[165,285,345],\"location\":[106.832259,-6.180439]},{\"out\":3,\"in\":1,\"entry\":[true,false,false,true],\"bearings\":[105,165,270,345],\"location\":[106.831894,-6.179239]},{\"out\":2,\"in\":0,\"entry\":[false,false,true],\"bearings\":[165,180,345],\"location\":[106.831758,-6.178777]}],\"weight\":18.2,\"duration\":18.2,\"distance\":226.2},{\"geometry\":\"nvud@q`kS@J?@ABUVABGHGFIJAH?XDTALAHAD\",\"maneuver\":{\"bearing_after\":267,\"bearing_before\":344,\"location\":[106.831677,-6.178483],\"modifier\":\"left\",\"type\":\"turn\"},\"mode\":\"driving\",\"driving_side\":\"right\",\"name\":\"\",\"intersections\":[{\"out\":1,\"in\":0,\"entry\":[false,true,true],\"bearings\":[165,270,345],\"location\":[106.831677,-6.178483]},{\"out\":1,\"classes\":[\"restricted\"],\"in\":0,\"entry\":[false,true],\"bearings\":[90,285],\"location\":[106.831613,-6.178486]},{\"out\":1,\"classes\":[\"restricted\"],\"in\":0,\"entry\":[false,true,true],\"bearings\":[135,315,330],\"location\":[106.831453,-6.178355]},{\"out\":2,\"classes\":[\"restricted\"],\"in\":0,\"entry\":[false,true,true],\"bearings\":[135,180,270],\"location\":[106.831303,-6.17823]},{\"out\":2,\"classes\":[\"restricted\"],\"in\":1,\"entry\":[true,false,true],\"bearings\":[45,90,255],\"location\":[106.831122,-6.178223]}],\"weight\":3301.600000000,\"duration\":24.9,\"distance\":101.5},{\"geometry\":\"ztud@{k`kSQBgATuBb@\",\"maneuver\":{\"bearing_after\":345,\"bearing_before\":278,\"location\":[106.83086,-6.178223],\"modifier\":\"right\",\"type\":\"turn\"},\"mode\":\"driving\",\"driving_side\":\"right\",\"name\":\"\",\"intersections\":[{\"out\":3,\"classes\":[\"restricted\"],\"in\":0,\"entry\":[false,true,true,true],\"bearings\":[105,195,270,345],\"location\":[106.83086,-6.178223]},{\"out\":2,\"classes\":[\"restricted\"],\"in\":0,\"entry\":[false,true,true],\"bearings\":[165,255,345],\"location\":[106.830726,-6.177774]}],\"weight\":34.3,\"duration\":34.3,\"distance\":120.8},{\"geometry\":\"jnud@}i`kS\",\"maneuver\":{\"bearing_after\":0,\"bearing_before\":341,\"location\":[106.830545,-6.177177],\"modifier\":\"straight\",\"type\":\"arrive\"},\"mode\":\"driving\",\"driving_side\":\"right\",\"name\":\"\",\"intersections\":[{\"in\":0,\"entry\":[true],\"bearings\":[165],\"location\":[106.830545,-6.177177]}],\"weight\":0,\"duration\":0,\"distance\":0}],\"summary\":\"Jalan Hajjah R. Rasuna Said, Jalan Haji Oemar Said Cokroaminoto\",\"weight\":3833.7,\"duration\":557,\"distance\":8867.3}],\"weight_name\":\"routability\",\"weight\":3833.7,\"duration\":557,\"distance\":8867.3}],\"waypoints\":[{\"hint\":\"1ReBgP__38BAAAAAgAAAAAAAAAAAAAA-SMWQJNc9D8AAAAAAAAAAAEAAAACAAAAAAAAAAAAAAAcCQAAOAleBr-voP8nCV4GvK-g_wAA_xUZ8WqN\",\"distance\":1.910375105,\"name\":\"Jalan Mampang Prapatan Raya\",\"location\":[106.82604,-6.246465]},{\"hint\":\"rc-DgEPQg4AAAAAAHwAAAAAAAAAAAAAAAAAAAFPATkEAAAAAAAAAAAAAAAAfAAAAAAAAAAAAAAAcCQAA0RpeBme-of93G14G1b-h_wAA3w8Z8WqN\",\"distance\":44.449594213,\"name\":\"\",\"location\":[106.830545,-6.177177]}]}";

std::vector<std::string> parseGeometry(nlohmann::json osrmResp) {
	std::vector<std::string> res;
	auto steps = osrmResp["routes"][0]["legs"][0]["steps"];

	for(const auto& step : steps) {
		res.push_back(step["geometry"]);
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
std::vector<std::string> splitPolyline(std::string input) {
	std::vector<std::string> polylineString;
	int curStart = 0;

	for(int i = 0; i < input.length(); i++) {
		if(((int)input[i]) < 95) {
			polylineString.push_back(input.substr(curStart, i - curStart + 1));
			curStart = i + 1;
		}
	}

	return polylineString;
}

std::vector<std::pair<double, double>> constructPolylineCoordinate(std::vector<int> &input) {
	std::vector<std::pair<double, double>> coordinates;
	std::pair<double, double> current = std::make_pair(0,0);
	int longitude = 0;
	int latitude = 0;
	

	for(int i = 0; i < input.size() / 2; i++) {
		int index = i << 1;
		if(longitude == 0 || latitude == 0) {
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

double degToRad(double deg) {
	return (deg * M_PI) / 180;
}

double radToDeg(double rad) {
	return (rad * 180) / M_PI;
}

double latLongDistance(std::pair<double, double> start, std::pair<double, double> end) {
	double a = 
		std::pow(std::sin((end.first - start.first) / 2), 2) + 
		std::cos(start.first) *
		std::cos(end.first) *
		std::pow(std::sin((end.second - start.second) / 2), 2);
	double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));

	return EARTH_DIAMETER * c;
}


std::vector<double> getCoordinatesDistance(std::vector<std::pair<double, double>> coordinates) {
	std::vector<double> res;

	for(int i = 0; i < coordinates.size() - 1; i++) {
		std::pair<double, double> start = std::make_pair(degToRad(coordinates[i].first), degToRad(coordinates[i].second));
		std::pair<double, double> end = std::make_pair(degToRad(coordinates[i].first), degToRad(coordinates[i + 1].second));

		double distance = latLongDistance(start, end);

		std::cout << std::fixed << std::setprecision(5) << 
			radToDeg(start.first) << ", " << radToDeg(start.second) << " -> " <<
			radToDeg(end.first)   << ", " << radToDeg(end.second)   << "=" <<
			distance << std::endl;
		res.push_back(distance);
	}

	return res;
}

void performGetRequest(const std::string& url) {
	try {
		std::cout << "url = " << url << std::endl;
		std::ostringstream response;

		curlpp::Easy request;

		// request.setOpt(curlpp::options::Url(url));
		// request.setOpt(curlpp::options::WriteStream(&response));
		// request.perform();


		// nlohmann::json root = nlohmann::json::parse(response.str());
		nlohmann::json root = nlohmann::json::parse(OSRM_DATA);
		auto geometries = parseGeometry(root);
		std::vector<std::pair<double, double>> coordinatesCollection;
		for(const auto& geometry : geometries) {
			std::vector<std::string> polylines = splitPolyline(geometry);
			std::vector<int> parsed;
			for(const auto& polyline : polylines) {
				int temp = parsePolyline(polyline);
				parsed.push_back(temp);
			}
			std::vector<std::pair<double, double>> coordinates = constructPolylineCoordinate(parsed);

			for(const auto& coordinate: coordinates) {
				coordinatesCollection.push_back(coordinate);
			}

		}

		getCoordinatesDistance(coordinatesCollection);
		
//		for(const auto& coordinate: coordinatesCollection) {
//			std::cout << "[" << std::fixed << std::setprecision(5) << coordinate.second << ", " << coordinate.first  << "]," << std::endl;
//		}
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
