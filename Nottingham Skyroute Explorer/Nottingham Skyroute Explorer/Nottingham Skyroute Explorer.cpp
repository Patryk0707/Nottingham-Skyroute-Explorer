#include <iostream>
#include <fstream> //enables file handling
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath> // required for Haversine formula to calculate distance between two coordinates
class airport {	
	private:
		std::string identifier;
		std::string type;
		std::string name;
		int elevationInFeet;
		std::string continent;
		std::string isoCountry;
		std::string isoRegion;
		std::string municipality;
		std::string icaoCode;
		std::string iataCode;
		std::string gpsCode;
		std::string localCode;
		double latitude;
		double longitude;

	public:
		std::string getIdentifier() const;
		std::string getType() const;
		std::string getName() const;
		int getElevationInFeet() const;
		std::string getContinent() const;
		std::string getIsoCountry() const;
		std::string getIsoRegion() const;
		std::string getMunicipality() const;
		std::string getIcaoCode() const;
		std::string getIataCode() const;
		std::string getGpsCode() const;
		std::string getLocalCode() const;
		double getLatitude() const; 
		double getLongitude() const; 
		void set(std::string id, std::string typ, std::string nme, int elev, std::string cont, std::string isoC, std::string isoR,
			std::string muni, std::string icao, std::string iata, std::string gps, std::string local,double lat,double lon);
};
void airport::set(std::string id,std::string typ,std::string nme,int elev,std::string cont,std::string isoC,std::string isoR,
	std::string muni,std::string icao,std::string iata,std::string gps,std::string local,double lat,double lon)
{
	identifier = id;
	type = typ;
	name = nme;
	elevationInFeet = elev;
	continent = cont;
	isoCountry = isoC;
	isoRegion = isoR;
	municipality = muni;
	icaoCode = icao;
	iataCode = iata;
	gpsCode = gps;
	localCode = local;
	latitude = lat;
	longitude = lon;

};


std::string airport::getName() const { return name; }
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
double airport::getLongitude() const {return longitude;}


class airportRepository {
	public:
		void loadFromCSV();
		std::multimap<std::string,airport> searchAirportByCountry(const std::string& country) const;
		std::multimap<std::string, airport> searchAirportByName(const std::string& name) const;
		std::multimap<std::string, airport> searchAirportByIataCode(const std::string& iataCode) const;
		std::map<std::string, int> countAirportsByType() const;
		void addAirport(const airport& a);
		void saveToCsv() const;
		airport* findByIdentifier(const std::string& ident);
		double calculateAirportDistance(double lat1, double lon1, double lat2, double lon2);
		airport* findNearestAirport(const std::string& ident);
		std::vector<airport> findAirportsInRadius(const std::string& ident, double radiusKm);
		std::vector<airport> getTop10LowestElevation() const;
		std::vector<airport> getTop10HighestElevation() const;
		std::vector<airport> getAirportsWithMissingIata() const;
		std::vector<airport> getAirportsByMunicipality(const std::string& municipalities) const;
	private:
		std::vector<airport>airports;
};
std::multimap<std::string, airport> airportRepository::searchAirportByCountry(const std::string& country) const {
    std::multimap<std::string, airport> result;

    for (const auto& a : airports) {
        if (a.getIsoCountry() == country) {
            result.insert({ a.getIsoCountry(), a });
        }
    }
	return result;
}
std::multimap<std::string, airport> airportRepository::searchAirportByName(const std::string& name) const {
    std::multimap<std::string, airport> result;

    for (const auto& a : airports) {
		if (a.getName().find(name) != std::string::npos){
			result.insert({ a.getName(), a });
        }
    }
    return result;
}
std::multimap<std::string, airport> airportRepository::searchAirportByIataCode(const std::string& iataCode) const {
	std::multimap<std::string, airport> result;

	for (const auto& a : airports) {
		if (a.getIataCode() == iataCode) {
			result.insert({ a.getIataCode(), a });
		}
	}
	return result;
}
std::map<std::string, int> airportRepository::countAirportsByType() const {
	std::map<std::string, int> count;

	for (const auto& a : airports) {
		count[a.getType()]++;
	}
	return count;
}
void airportRepository::addAirport(const airport& a) {
	airports.push_back(a);
}
void airportRepository::loadFromCSV(){
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
		std::string identifier,type,name,continent,isoCountry, isoRegion, municipality, icaoCode, iataCode, gpsCode, localCode;

		try {
			std::getline(ss, identifier, ',');
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
			double lat = std::stod(latStr);
			double lon = std::stod(lonStr);
			a.set(identifier,type,name,elevationInFeet,continent,isoCountry,isoRegion,municipality,icaoCode,iataCode,gpsCode,localCode,lat,lon);

			airports.push_back(a);

		}
		catch (...) {
		}
	}
	std::cout << "File read successfully!" << std::endl;
};
void airportRepository::saveToCsv() const {
	std::ofstream file("../airports.csv");
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
			<< a.getLongitude() << "\n"; 
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
			return &a; // Return memory address of the airport
		}
	}
	return nullptr; // Returns null pointer if not found
}
airport* airportRepository::findNearestAirport(const std::string& ident) {
	airport* airportInput = findByIdentifier(ident);
	if (!airportInput) return nullptr;

	airport* nearestAirport = nullptr;
	double minDistance = -1.0;

	for (auto& otherAirport : airports) {
		// Don't calculate distance to itself
		if (otherAirport.getIdentifier() == ident) continue;

		double dist = calculateAirportDistance(
			airportInput->getLatitude(), airportInput->getLongitude(),
			otherAirport.getLatitude(), otherAirport.getLongitude()
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

		double dist = calculateAirportDistance(
			centerAirport->getLatitude(), centerAirport->getLongitude(),
			nearestAirportInRadius.getLatitude(), nearestAirportInRadius.getLongitude()
		);

		if (dist <= radiusKm) {
			result.push_back(nearestAirportInRadius);
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
		if (a.getIataCode().empty()) {
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
class Menu {
public:
	static void displayMainMenu(airportRepository& repo);
	static void displayAdditonalMenu(airportRepository& repo);
};

void Menu::displayMainMenu(airportRepository& repo) {
	int userChoice;
	while (true) {
		std::cout << "====== Nottingham SkyRoute Explorer ======" << std::endl;
		std::cout << "1. Search airports by country" << std::endl;
		std::cout << "2. Search airports by name" << std::endl;
		std::cout << "3. Search by IATA code" << std::endl;
		std::cout << "4. Count airports by type" << std::endl;
		std::cout << "5. Add a new airport" << std::endl;
		std::cout << "6. Save changes" << std::endl;
		std::cout << "7. Advanced options" << std::endl;
		std::cout << "8. Exit" << std::endl;
		std::cout << "Enter a number:";
		std::cin >> userChoice;
		while (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << "Invalid input, Please input a number:";
			std::cin >> userChoice;
		}
		while (userChoice > 8 or userChoice < 1) {
			std::cin.ignore();
			std::cout << "Please enter a number within 1-8";
			std::cin >> userChoice;
		}

		switch (userChoice) {
		case 1:{
			std::string countryInput;
			std::cout << "Enter country code such as 'US' to find airports within that country: ";
			while (true){
				std::cin>>countryInput;
				if(countryInput=="exit")
					break;
				auto results = repo.searchAirportByCountry(countryInput);
				if (results.empty()) {
					std::cout << "No airports matching the country code. Try again or type 'exit' to return to the main menu.";
					continue;
				}
				for (const auto& entry : results) {
					std::cout << entry.second.getName() << "\n";
				}
				break;
			}
			break;
		}
		case 2:{
			std::string nameInput;
			std::cout << "Enter a airport name to find any matches: ";
			while (true) {
				std::cin >> nameInput;
				if (nameInput == "exit")
					break;
				auto results = repo.searchAirportByName(nameInput);
				if (results.empty()) {
					std::cout << "No airports matching that name. Try again or type 'exit' to return to the main menu.";
					continue;
				}
				for (const auto& entry : results) {
					std::cout << entry.second.getName() << "\n";
				}
				break;
			}
			break;
			}
		case 3:{
			std::string iataInput;
			std::cout << "Enter a IATA code to find any matches: ";
			while (true) {
				std::cin >> iataInput;
				if (iataInput == "exit")
					break;
				auto results = repo.searchAirportByIataCode(iataInput);
				if (results.empty()) {
					std::cout << "No airports matching that IATA Code. Try again or type 'exit' to return to the main menu.";
					continue;
				}
				for (const auto& entry : results) {
					std::cout << entry.second.getName() << "\n";
				}
				break;
			}
			break;
		}
		case 4:{
			auto count = repo.countAirportsByType();

			std::cout << "Airport count by type:\n";

			for (const auto& entry : count) {
				std::cout << entry.first << ": " << entry.second << "\n";
			}

			break;
		}
		case 5: {
			airport a;
			std::string identifier,type,name,continent,isoCountry,isoRegion,municipality,icaoCode,iataCode,gpsCode,localCode,latStr, lonStr;
			int elevation;
			std::cout << "Enter identifier: ";
			std::getline(std::cin,identifier);
			while (identifier.empty()) {
				std::cout << "Identifier cannot be empty:  ";
				std::getline(std::cin,identifier);
			}
			std::cout << "Enter type: ";
			std::getline(std::cin, type);
			while (type.empty()) {
				std::cout << "Type cannot be empty:  ";
				std::getline(std::cin, type);
			}
			std::cout << "Enter name: ";
			std::getline(std::cin, name);
			while (name.empty()) {
				std::cout << "Name cannot be empty:  ";
				std::getline(std::cin, name);
			}
			std::string elevationStr;
			std::cout << "Enter elevation in feet: ";
			std::getline(std::cin, elevationStr);
			while (elevationStr.empty() or elevationStr.find_first_not_of("0123456789") != std::string::npos){
				std::cout << "Elevation cannot be empty and has to be a integer:  ";
				std::getline(std::cin, elevationStr);
			}
			elevation = std::stoi(elevationStr);
			std::cout << "Enter continent: ";
			std::getline(std::cin, continent);
			while (continent.empty()) {
				std::cout << "Continent cannot be empty:  ";
				std::getline(std::cin, continent);
			}
			std::cout << "Enter ISO country code: ";
			std::getline(std::cin, isoCountry);
			while (isoCountry.empty()) {
				std::cout << "ISO Country cannot be empty:  ";
				std::getline(std::cin, isoCountry);
			}
			std::cout << "Enter ISO region: ";
			std::getline(std::cin, isoRegion);
			while (isoRegion.empty()) {
				std::cout << "ISO Region cannot be empty:  ";
				std::getline(std::cin, isoRegion);
			}
			std::cout << "Enter municipality: ";
			std::getline(std::cin, municipality);
			while (municipality.empty()) {
				std::cout << "Municipality cannot be empty:  ";
				std::getline(std::cin, municipality);
			}
			std::cout << "Enter ICAO code(Can be empty): ";
			std::getline(std::cin, icaoCode);
			std::cout << "Enter IATA code(Can be empty): ";
			std::getline(std::cin, iataCode);
			std::cout << "Enter GPS code(Can be empty): ";
			std::getline(std::cin, gpsCode);
			std::cout << "Enter local code(Can be empty): ";
			std::getline(std::cin, localCode);
			std::cout << "Enter latitude: ";
			std::getline(std::cin, latStr);
			while (latStr.empty() or latStr.find_first_not_of("0123456789,") != std::string::npos) {
				std::cout << "latitude cannot be empty and must be integers:  ";
				std::getline(std::cin, latStr);
			}
			std::cout << "Enter longitude: ";
			std::getline(std::cin, lonStr);
			while (lonStr.empty() or lonStr.find_first_not_of("0123456789,") != std::string::npos) {
				std::cout << "longitude cannot be empty and must be integers:  ";
				std::getline(std::cin, lonStr);
			}

			try {
				double latitude = std::stod(latStr);
				double longitude = std::stod(lonStr);

				a.set(identifier, type, name, elevation, continent, isoCountry, isoRegion,
					municipality, icaoCode, iataCode, gpsCode, localCode, latitude, longitude);

				repo.addAirport(a);

				std::cout << "Airport added successfully.\n";
			}
			catch (...) {
				std::cout << "Error: Could not convert latitude or longitude to a number. Airport has not been added.\n";
			}
			break;
		}

		case 6:{
			repo.saveToCsv();
			std::cout << "Changes saved.\n";
			break;
			}
		case 7:{
			Menu::displayAdditonalMenu(repo);
			break;
			}
		case 8:{
			exit(0);
			}


		}
	}
}

void Menu::displayAdditonalMenu(airportRepository& repo) {
	int userChoice;
	while (true) {
		std::cout << "====== Advanced Features ======" << std::endl;
		std::cout << "1. Calculate distance between airports" << std::endl;
		std::cout << "2. Find nearest airport to a given location" << std::endl;
		std::cout << "3. List all airports within a radius" << std::endl;
		std::cout << "4. List highest or lowest elevation airports" << std::endl;
		std::cout << "5. List airports with missing IATA codes" << std::endl;
		std::cout << "6. Group airports by municipality" << std::endl;
		std::cout << "7. Sort airports" << std::endl;
		std::cout << "8. Exit" << std::endl;
		std::cin >> userChoice;
		while (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << "Invalid input, Please input a number:";
			std::cin >> userChoice;
		}
		while (userChoice > 8 or userChoice < 1) {
			std::cin.ignore();
			std::cout << "Please enter a number within 1-8";
			std::cin >> userChoice;
		}

		switch (userChoice) {
		case 1: {
			std::string id1, id2;
			std::cout << "Enter first airport identifier (e.g., EGLL): ";
			std::cin >> id1;
			std::cout << "Enter second airport identifier: ";
			std::cin >> id2;

			airport* a1 = repo.findByIdentifier(id1);
			airport* a2 = repo.findByIdentifier(id2);

			if (a1 && a2) {
				double dist = repo.calculateAirportDistance(
					a1->getLatitude(), a1->getLongitude(),
					a2->getLatitude(), a2->getLongitude()
				);
				std::cout << "Distance between " << a1->getName()
					<< " and " << a2->getName() << " is: "
					<< dist << " km\n";
			}
			else {
				std::cout << "Error: One or both identifiers were not found.\n";
			}
			break;
		}
		case 2: {
			std::string airportId;
			std::cout << "Enter a airport identifier to search the nearest airport from: ";
			std::cin >> airportId;

			airport* nearestAirport = repo.findNearestAirport(airportId);
			airport* airportChosen = repo.findByIdentifier(airportId);

			if (nearestAirport && airportChosen) {
				double distance = repo.calculateAirportDistance(
					airportChosen->getLatitude(), airportChosen->getLongitude(),
					nearestAirport->getLatitude(), nearestAirport->getLongitude()
				);
				std::cout << "The nearest airport to " << airportChosen->getName() << " (" << airportId << ") is:\n";
				std::cout << "Name: " << nearestAirport->getName() << " (" << nearestAirport->getIdentifier() << ")\n";
				std::cout << "Distance: " << distance << " km\n";
			}
			else {
				std::cout << "Error: Identifier not found\n";
			}
			break;
		}
		case 3: {
			std::string ident;
			double radius;

			std::cout << "Enter the reference airport identifier: ";
			std::cin >> ident;
			std::cout << "Enter the radius in kilometers: ";
			std::cin >> radius;

			// validates radius input
			if (std::cin.fail() || radius < 0) {
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				std::cout << "Invalid radius entered.\n";
				break;
			}

			std::vector<airport> nearbyAirports = repo.findAirportsInRadius(ident, radius);

			if (nearbyAirports.empty()) {
				// This happens because either the identifier is wrong or theres no airports within the radius
				if (repo.findByIdentifier(ident) == nullptr) {
					std::cout << "Error: Reference airport identifier '" << ident << "' not found.\n";
				}
				else {
					std::cout << "No other airports found within " << radius << " km.\n";
				}
			}
			else {
				std::cout << "\nFound " << nearbyAirports.size() << " airports within " << radius << " km:\n";
				std::cout << "--------------------------------------------------\n";
				for (const auto& a : nearbyAirports) {
					airport* chosenAirport = repo.findByIdentifier(ident);
					double d = repo.calculateAirportDistance(chosenAirport->getLatitude(), chosenAirport->getLongitude(),
						a.getLatitude(), a.getLongitude());

					std::cout << "[" << a.getIdentifier() << "] " << a.getName()
						<< " | Distance: " << d << " km\n";
				}
				std::cout << "--------------------------------------------------\n";
			}
			break;
		}
		case 4: {
			int elevationChoice;
			std::cout << "\nWhich elevation of airports would you like to see?" << std::endl;
			std::cout << "1. Show 10 Highest Airports" << std::endl;
			std::cout << "2. Show 10 Lowest Airports" << std::endl;
			std::cout << "Enter choice: ";
			std::cin >> elevationChoice;

			std::vector<airport> results;
			if (elevationChoice == 1) {
				results = repo.getTop10HighestElevation();
				std::cout << "\nTop 10 Highest Elevation Airports:\n";
			}
			else if (elevationChoice == 2) {
				results = repo.getTop10LowestElevation();
				std::cout << "\nTop 10 Lowest Elevation Airports:\n";
			}
			else {
				std::cout << "Invalid choice.\n";
				break;
			}

			std::cout << "--------------------------------------------------\n";
			for (const auto& a : results) {
				std::cout << a.getElevationInFeet() << " ft | "
					 << a.getName() << " (" << a.getIsoCountry() << ")\n";
			}
			std::cout << "--------------------------------------------------\n";
			break;
		}
		case 5: {
			std::vector<airport> missingIata = repo.getAirportsWithMissingIata();

			if (missingIata.empty()) {
				std::cout << "No airports have missing IATA codes.\n";
			}
			else {
				std::cout << "--------------------------------------------------------------------------------\n";

				// Loop through the vector and print every airport without a IATA Code
				for (const auto& a : missingIata) {
					std::cout << "[" << a.getIdentifier() << "] "
						<< a.getName() << " | "
						<< "Country: " << a.getIsoCountry() << " | "
						<< "Municipality: " << a.getMunicipality() << "\n";
				}

				std::cout << "--------------------------------------------------------------------------------\n";
				std::cout << "\nFound " << missingIata.size() << " airports with missing IATA codes\n";
			}
			break;
		}
		case 6: {
			std::string municipalitySearch;
			std::cout << "\nEnter the Municipality name to search: ";
			std::cin.ignore(1000, '\n');
			std::getline(std::cin, municipalitySearch);

			std::vector<airport> results = repo.getAirportsByMunicipality(municipalitySearch);

			if (results.empty()) {
				std::cout << "No airports found for municipality: '" << municipalitySearch << "'\n";
			}
			else {
				std::cout << "\nFound " << results.size() << " airport in " << municipalitySearch << ":\n";
				std::cout << "--------------------------------------------------\n";
				for (const auto& a : results) {
					std::cout << "- " << a.getName() << " (" << a.getIdentifier() << ")\n";
				}
				std::cout << "--------------------------------------------------\n";
			}
			break;
		}
		case 8:
			return; 
		default:
			std::cout << "Invalid choice.\n";
			break;
		} 
	} 
} 
	
int main() {
	airportRepository repo;
	repo.loadFromCSV();
	Menu::displayMainMenu(repo);
	return 0;

}