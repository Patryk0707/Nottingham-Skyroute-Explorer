#include <iostream>
#include <fstream> //enables file handling
#include <string>
#include <map>
#include <vector>
#include <sstream>
class airport {					//new start
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
		std::string coordinates;

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
		std::string getCoordinates() const;
		void set(std::string id, std::string typ, std::string nme, int elev, std::string cont, std::string isoC, std::string isoR,
			std::string muni, std::string icao, std::string iata, std::string gps, std::string local, std::string coord);
		
};
void airport::set(std::string id,std::string typ,std::string nme,int elev,std::string cont,std::string isoC,std::string isoR,
	std::string muni,std::string icao,std::string iata,std::string gps,std::string local,std::string coord)
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
	coordinates = coord;

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
std::string airport::getCoordinates() const { return coordinates; }

class airportRepository {
	public:
		void loadFromCSV();
		std::multimap<std::string,airport> searchAirportByCountry(const std::string& country) const;
		std::multimap<std::string, airport> searchAirportByName(const std::string& name) const;
		std::multimap<std::string, airport> searchAirportByIataCode(const std::string& iataCode) const;
		std::map<std::string, int> countAirportsByType() const;
		void addAirport(const airport& a);
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
		std::string temp;
		airport a;
		int elevationInFeet;
		std::string identifier,type,name,continent,isoCountry, isoRegion, municipality, icaoCode, iataCode, gpsCode, localCode, coordinates;

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
			std::getline(ss, coordinates, ',');;

			a.set(identifier, type, name, elevationInFeet, continent,isoCountry, isoRegion, municipality, icaoCode,iataCode, gpsCode, localCode, coordinates);

			airports.push_back(a);

		}
		catch (...) {
		}
	}
};
//new end
class Menu {
public:
	static void displayMainMenu(airportRepository& repo);
	static void displayAdditonalMenu();
};

void Menu::displayMainMenu(airportRepository& repo) {
	int userChoice;
	while (true) {
		std::cout << "File read successfully!" << std::endl;
		std::cout << "====== Nottingham SkyRoute Explorer ======" << std::endl;
		std::cout << "1. Search airports by country" << std::endl;
		std::cout << "2. Search airports by name" << std::endl;
		std::cout << "3. Search by IATA code" << std::endl;
		std::cout << "4. Count airports by type" << std::endl;
		std::cout << "5. Add a new airport" << std::endl;
		std::cout << "6. Save changes" << std::endl;
		std::cout << "7. Advanced options(radius search, nearest airport, high / low elevation,sort etc.)" << std::endl;
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
			std::string identifier,type,name,continent,isoCountry,isoRegion,municipality,icaoCode,iataCode,gpsCode,localCode,coordinates;
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
			std::cout << "Enter coordinates(format=x,y): ";
			std::getline(std::cin, coordinates);
			int commaCount = std::count(coordinates.begin(), coordinates.end(), ',');
			while (coordinates.empty() or coordinates.find_first_not_of("0123456789,") != std::string::npos or commaCount!=1) {
				std::cout << "Coordinates cannot be empty,must be integers and in the correct format:  ";
				std::getline(std::cin, coordinates);
				commaCount = std::count(coordinates.begin(), coordinates.end(), ',');
			}

			a.set(identifier, type, name, elevation, continent, isoCountry, isoRegion,
				municipality, icaoCode, iataCode, gpsCode, localCode, coordinates);

			repo.addAirport(a);

			std::cout << "Airport added successfully.\n";
			break;
		}

		case 6:{
			break;
			}
		case 7:{
			Menu::displayAdditonalMenu();
			break;
			}
		case 8:{
			exit(0);
			}


		}
	}
}

void Menu::displayAdditonalMenu() {
	int userChoice;
	std::cout << "====== Nottingham SkyRoute Explorer ======" << std::endl;
	std::cout << "1. radius search" << std::endl;
	std::cout << "2. nearest airport" << std::endl;
	std::cout << "3. sort airports" << std::endl;
	std::cin >> userChoice;
}

int main() {
	airportRepository repo;
	repo.loadFromCSV();
	Menu::displayMainMenu(repo);
	return 0;

}