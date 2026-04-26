#include "airportRepository.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <iostream>
void airport::set(std::string id, std::string typ, std::string nme, int elev, std::string cont, std::string isoC, std::string isoR,
	std::string muni, std::string icao, std::string iata, std::string gps, std::string local, double lat, double lon) {
	identifier = id; type = typ; name = nme; elevationInFeet = elev; continent = cont;
	isoCountry = isoC; isoRegion = isoR; municipality = muni; icaoCode = icao;
	iataCode = iata; gpsCode = gps; localCode = local; latitude = lat; longitude = lon; //sets all the variables of the airport class to the values that are passed in as parameters
}
std::string airport::getName() const { return name; }//getter methods to access the return the value of the variables of the airport class
std::string airport::getType() const { return type; }
std::string airport::getIdentifier() const { return identifier; }
int airport::getElevationInFeet() const { return elevationInFeet; }
std::string airport::getContinent() const { return continent; }
std::string airport::getIsoCountry() const { return isoCountry; }
std::string airport::getIsoRegion() const { return isoRegion; }
std::string airport::getMunicipality() const { return municipality; }
std::string airport::getIcaoCode() const { return icaoCode; }
std::string airport::getIataCode() const { return iataCode; }
std::string airport::getGpsCode() const { return gpsCode; }
std::string airport::getLocalCode() const { return localCode; }
double airport::getLatitude() const { return latitude; }
double airport::getLongitude() const { return longitude; }

std::multimap<std::string, airport> airportRepository::searchAirportByCountry(const std::string& country) const {
	std::multimap<std::string, airport> result;

	for (const auto& a : airports) {//iterates through all the airports in the vector and adds matching airports by country to the result multimap
		if (a.getIsoCountry() == country) {
			result.insert({ a.getIsoCountry(), a });
		}
	}
	return result;
}
std::multimap<std::string, airport> airportRepository::searchAirportByName(const std::string& name) const {
	std::multimap<std::string, airport> result;

	for (const auto& a : airports) {//iterates through all the airports in the vector and adds matching airports by name to the result multimap
		if (a.getName().find(name) != std::string::npos) {
			result.insert({ a.getName(), a });
		}
	}
	return result;
}
std::multimap<std::string, airport> airportRepository::searchAirportByIataCode(const std::string& iataCode) const {
	std::multimap<std::string, airport> result;

	for (const auto& a : airports) {//iterates through all the airports in the vector and adds matching airports by IATA code to the result multimap
		if (a.getIataCode() == iataCode) {
			result.insert({ a.getIataCode(), a });
		}
	}
	return result;
}
std::map<std::string, int> airportRepository::countAirportsByType() const {
	std::map<std::string, int> count;

	for (const auto& a : airports) {//iterates through all the airports in the vector and counts the number of airports by type
		count[a.getType()]++;
	}
	return count;
}
void airportRepository::addAirport(const airport& a) {//adds the new airport the user has created to the vector of airports
	airports.push_back(a);
}
void airportRepository::loadFromCSV() {
	std::ifstream airportsFile("../airports.csv"); //opens the CSV file and uses ../ to check for the file a folder before the x64 folder
	std::string line;
	if (airportsFile.is_open()) {
		std::cout << "Loading..." << std::endl;
	}
	else {
		std::cout << "Error opening the file";
		return;
	}

	getline(airportsFile, line);

	while (getline(airportsFile, line)) {
		std::stringstream ss(line);
		std::string temp, latStr, lonStr;
		airport a;
		int elevationInFeet;
		std::string identifier, type, name, continent, isoCountry, isoRegion, municipality, icaoCode, iataCode, gpsCode, localCode;

		try {
			std::getline(ss, identifier, ',');//Reads the lines from the CSV file and stores the information to the variables used below
			std::getline(ss, type, ',');
			std::getline(ss, name, ',');
			std::getline(ss, temp, ','); elevationInFeet = std::stoi(temp);
			std::getline(ss, continent, ',');
			std::getline(ss, isoCountry, ',');
			std::getline(ss, isoRegion, ',');
			std::getline(ss, municipality, ',');
			std::getline(ss, icaoCode, ',');
			std::getline(ss, iataCode, ',');
			std::getline(ss, gpsCode, ',');
			std::getline(ss, localCode, ',');
			std::getline(ss, latStr, ',');
			std::getline(ss, lonStr, ',');
			double lat = std::stod(latStr);//Converts the latitude and longitude from string to double using std::stod
			double lon = std::stod(lonStr);
			a.set(identifier, type, name, elevationInFeet, continent, isoCountry, isoRegion, municipality, icaoCode, iataCode, gpsCode, localCode, lat, lon);

			airports.push_back(a);

		}
		catch (...) {
		}
	}
	std::cout << "CSV File read successfully!" << std::endl;//if no errors occur while reading the file, this will be outputted to the user
};
void airportRepository::saveToCsv() const {
	std::ofstream file("../airports.csv"); //opens the CSV file for writing
	if (!file.is_open()) {
		std::cout << "Error:Could not open airports.csv for writing.\n";
		return;
	}
	file << "ident,type,name,elevation_ft,continent,iso_country,iso_region,municipality,icao_code,iata_code,gps_code,local_code,coordinates\n";

	for (const auto& a : airports) {
		file << a.getIdentifier() << ","
			<< a.getType() << ","
			<< a.getName() << ","
			<< a.getElevationInFeet() << ","
			<< a.getContinent() << ","
			<< a.getIsoCountry() << ","
			<< a.getIsoRegion() << ","
			<< a.getMunicipality() << ","
			<< a.getIcaoCode() << ","
			<< a.getIataCode() << ","
			<< a.getGpsCode() << ","
			<< a.getLocalCode() << ","
			<< a.getLatitude() << ","
			<< a.getLongitude() << "\n";//saves all the information of airports from the vector back to the CSV file
	}
}
double airportRepository::calculateAirportDistance(double lat1, double lon1, double lat2, double lon2) {
	double earthRadiusKm = 6371.0;
	double M_PI = 3.14159265358979323846;

	double lat1InRadians = lat1 * M_PI / 180.0;
	double lat2InRadians = lat2 * M_PI / 180.0;
	double differenceInLatitude = (lat2 - lat1) * M_PI / 180.0;
	double differenceInLongitude = (lon2 - lon1) * M_PI / 180.0;

	// Haversine formula
	double a = std::sin(differenceInLatitude / 2) * std::sin(differenceInLatitude / 2) +
		std::cos(lat1InRadians) * std::cos(lat2InRadians) * std::sin(differenceInLongitude / 2) * std::sin(differenceInLongitude / 2); //distance between two airports in a straight line

	double c = 2 * std::asin(std::sqrt(a)); //calculate the curve

	return earthRadiusKm * c;


}
airport* airportRepository::findByIdentifier(const std::string& ident) {
	for (auto& a : airports) {
		if (a.getIdentifier() == ident) {
			return &a; //Returns memory address of the airport that has been found by identifier
		}
	}
	return nullptr; // Returns null pointer if there is no matches
}
airport* airportRepository::findNearestAirport(const std::string& ident) {
	airport* airportInput = findByIdentifier(ident);
	if (!airportInput) return nullptr;//if there isnt an airport found that the user has inputted, return a null pointer

	airport* nearestAirport = nullptr;
	double minDistance = -1.0;

	for (auto& otherAirport : airports) {
		// Don't calculate distance to itself
		if (otherAirport.getIdentifier() == ident) continue;

		double dist = calculateAirportDistance(
			airportInput->getLatitude(), airportInput->getLongitude(),
			otherAirport.getLatitude(), otherAirport.getLongitude()//calculate the distance between each airport to the airport that the user has entered and output the closest airport
		);

		if (minDistance < 0 or dist < minDistance) {
			minDistance = dist;
			nearestAirport = &otherAirport;
		}
	}
	return nearestAirport;
}
std::vector<airport> airportRepository::findAirportsInRadius(const std::string& ident, double radiusKm) {
	std::vector<airport> result;
	airport* centerAirport = findByIdentifier(ident);

	if (!centerAirport) return result; // returns empty if airport found by user not found

	for (const auto& nearestAirportInRadius : airports) {
		// Skip the airport that the user has chosen
		if (nearestAirportInRadius.getIdentifier() == ident) continue;

		double dist = calculateAirportDistance(//show the distance of airports within the radius to the airport that the user has entered
			centerAirport->getLatitude(), centerAirport->getLongitude(),
			nearestAirportInRadius.getLatitude(), nearestAirportInRadius.getLongitude()
		);

		if (dist <= radiusKm) {
			result.push_back(nearestAirportInRadius);//if the distance is within the radius, add the airport to the result vector
		}
	}
	return result;
}
std::vector<airport> airportRepository::getTop10LowestElevation() const {
	std::vector<airport> lowestElevationVector = airports;

	//Sort in ascending order (lowest elevation first)
	std::sort(lowestElevationVector.begin(), lowestElevationVector.end(), [](const airport& a, const airport& b) {
		return a.getElevationInFeet() < b.getElevationInFeet();
		});

	//Only keep the top 10
	if (lowestElevationVector.size() > 10) lowestElevationVector.resize(10);
	return lowestElevationVector;
}

std::vector<airport> airportRepository::getTop10HighestElevation() const {
	std::vector<airport> highestElevationVector = airports;

	//Sort it in descending order (Highest elevation first)
	std::sort(highestElevationVector.begin(), highestElevationVector.end(), [](const airport& a, const airport& b) {
		return a.getElevationInFeet() > b.getElevationInFeet();
		});

	//Only keep the top 10
	if (highestElevationVector.size() > 10) highestElevationVector.resize(10);
	return highestElevationVector;
}
std::vector<airport> airportRepository::getAirportsWithMissingIata() const {
	std::vector<airport> result;
	for (const auto& a : airports) {
		if (a.getIataCode().empty()) {//add all airports without an IATA code to the result vector
			result.push_back(a);
		}
	}
	return result;
}
std::vector<airport> airportRepository::getAirportsByMunicipality(const std::string& municipalities) const {
	std::vector<airport> result;

	//Uppercase version of what the user typed
	std::string municipalitiesInput = municipalities;
	std::transform(municipalitiesInput.begin(), municipalitiesInput.end(), municipalitiesInput.begin(), ::toupper);

	for (const auto& a : airports) {
		//Uppercase version of the current airport's municipality
		std::string municipalitiesUpperCase = a.getMunicipality();
		std::transform(municipalitiesUpperCase.begin(), municipalitiesUpperCase.end(), municipalitiesUpperCase.begin(), ::toupper);

		//Compare input to the current airport's municipality, if they match add the airport to the result vector
		if (municipalitiesUpperCase == municipalitiesInput) {
			result.push_back(a);
		}
	}
	return result;
}
std::vector<airport> airportRepository::getSortedAirports(int criteria, int orderChoice) const {
	std::vector<airport> sortedData = airports;

	std::sort(sortedData.begin(), sortedData.end(), [criteria, orderChoice](const airport& a, const airport& b) {
		//Ascending 
		if (orderChoice == 1) {
			if (criteria == 1) return a.getName() < b.getName();//sort airports by name in ascending order
			if (criteria == 2) return a.getIsoCountry() < b.getIsoCountry();//sort airports by country in ascending order
			if (criteria == 3) return a.getType() < b.getType();//sort airports by type in ascending order
			if (criteria == 4) return a.getLatitude() < b.getLatitude();//sort airports by latitude in ascending order
				if (criteria == 5) return a.getElevationInFeet() < b.getElevationInFeet();//sort airports by elevation in ascending order
		}
		//Descending
		else {
			if (criteria == 1) return a.getName() > b.getName();//sort airports by name in descending order
			if (criteria == 2) return a.getIsoCountry() > b.getIsoCountry();//sort airports by country in descending order
			if (criteria == 3) return a.getType() > b.getType();//sort airports by type in descending order
			if (criteria == 4) return a.getLatitude() > b.getLatitude();//sort airports by latitude in descending order
			if (criteria == 5) return a.getElevationInFeet() > b.getElevationInFeet();//sort airports by elevation in descending order
		}
		return false;
		});

	return sortedData;//returns the sorted data
}