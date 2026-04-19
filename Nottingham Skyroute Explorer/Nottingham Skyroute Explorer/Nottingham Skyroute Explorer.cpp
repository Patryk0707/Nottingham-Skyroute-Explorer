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
		std::multimap<std::string,airport> searchAirportByCountry() const;
	private:
		std::vector<airport>airports;
};
std::multimap<std::string, airport> airportRepository::searchAirportByCountry() const {
	return{};
}
void airportRepository::loadFromCSV(){
	std::ifstream airportsFile("../airports.csv"); //opens the CSV file and uses ../ to check for the file a folder before the x64 folder
	std::string line;
	if (airportsFile.is_open()) {
		std::cout << "File read successfully";
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
	static void displayMainMenu(airportRepository& repo);//new
	static void displayAdditonalMenu();
};

void Menu::displayMainMenu(airportRepository& repo) {//new
	int userChoice;
	while (true) {
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
		case 1:
			repo.searchAirportByCountry();//new and breaks
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			Menu::displayAdditonalMenu();
			break;
		case 8:
			exit(0);



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
	airportRepository repo;//new
	repo.loadFromCSV();
	Menu::displayMainMenu(repo);//new in brackets
	return 0;

}