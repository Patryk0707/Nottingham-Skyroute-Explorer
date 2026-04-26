#include "AirportApp.h"
#include <iostream> //imported for input and outputs to work
#include <string> 


void AirportApp::displayMainMenu() {
	airportRepository repo; //creates new instance called repo
	repo.loadFromCSV(); //loads the CSV file into the repo instance
	int userChoice;//variable to store the user's menu choice
	while (true) { //while loop until the user exits the program
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
		while (std::cin.fail()) {//input validation to make sure the user enters a number and not letters or symbols
			std::cin.clear();
			std::cin.ignore(1000, '\n');//ignores whitespace
			std::cout << "Invalid input, Please input a number:";//repeats until the user enters a valid number
			std::cin >> userChoice;
		}
		while (userChoice > 8 or userChoice < 1) {//more input validation to make sure the user enters a number between 1 and 8
			std::cin.ignore();
			std::cout << "Please enter a number within 1-8";
			std::cin >> userChoice;
		}

		switch (userChoice) {//switch case for different user inputs
		case 1: {
			std::string countryInput;
			std::cout << "Enter country code such as 'US' to find airports within that country: ";
			while (true) {//while loop that allows the user to try again or type exit to go back to the main menu
				std::cin >> countryInput;
				if (countryInput == "exit")//if they type exit, it will end the loop bringing them back to the main menu
					break;
				auto results = repo.searchAirportByCountry(countryInput);//stores the results of the search in results
				if (results.empty()) {//if there are no airports found with the country code it will notify the user
					std::cout << "No airports matching the country code. Try again or type 'exit' to return to the main menu.";
					continue;
				}
				for (const auto& entry : results) {
					displayAirportDetails(entry.second);
				}
				break;
			}
			break;
		}
		case 2: {
			std::string nameInput;
			std::cout << "Enter a airport name to find any matches: ";
			while (true) {// same loop as for case 1. 
				std::cin >> nameInput;
				if (nameInput == "exit")
					break;
				auto results = repo.searchAirportByName(nameInput);//uses the searchAirportByName method to search for airports with matching names
				if (results.empty()) {
					std::cout << "No airports matching that name. Try again or type 'exit' to return to the main menu.";
					continue;
				}
				for (const auto& entry : results) {
					displayAirportDetails(entry.second);
				}
				break;
			}
			break;
		}
		case 3: {
			std::string iataInput;
			std::cout << "Enter a IATA code to find any matches: ";
			while (true) {//same loop and instead airports are found by searching with IATA codes
				std::cin >> iataInput;
				if (iataInput == "exit")
					break;
				auto results = repo.searchAirportByIataCode(iataInput);//uses method to search for airports with matching IATA code
				if (results.empty()) {
					std::cout << "No airports matching that IATA Code. Try again or type 'exit' to return to the main menu.";
					continue;
				}
				for (const auto& entry : results) {
					displayAirportDetails(entry.second);
				}
				break;
			}
			break;
		}
		case 4: {
			auto count = repo.countAirportsByType();//user inputs a airport type and the method displays all the airports with the matching type

			std::cout << "Airport count by type:\n";

			for (const auto& entry : count) {
				std::cout << entry.first << ": " << entry.second << "\n";
			}

			break;
		}
		case 5: {
			airport a;//creates a new instance of the airport class called a to store the new airport's data
			std::string identifier, type, name, continent, isoCountry, isoRegion, municipality, icaoCode, iataCode, gpsCode, localCode, latStr, lonStr;
			int elevation;
			std::cout << "Enter identifier: ";
			std::getline(std::cin, identifier);
			while (identifier.empty()) {
				std::cout << "Identifier cannot be empty:  ";
				std::getline(std::cin, identifier);
			}
			std::cout << "Enter type: ";
			std::getline(std::cin, type);
			while (type.empty()) {
				std::cout << "Type cannot be empty:  ";
				std::getline(std::cin, type);
			}
			std::cout << "Enter name: ";
			std::getline(std::cin, name);
			while (name.empty()) {// if input is empty the user is prompted to enter the data again until it is valid
				std::cout << "Name cannot be empty:  ";
				std::getline(std::cin, name);
			}
			std::string elevationStr;
			std::cout << "Enter elevation in feet: ";
			std::getline(std::cin, elevationStr);
			while (elevationStr.empty() or elevationStr.find_first_not_of("0123456789") != std::string::npos) {// each input is valdidated to make sure the data is valid, this includes making sure the elevation is numbers only and not empty
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
			while (latStr.empty() or latStr.find_first_not_of("0123456789.-") != std::string::npos) {//the latiutude and longitude are validated to make sure they arent empty and are numbers
				std::cout << "latitude cannot be empty and must be a number:  ";
				std::getline(std::cin, latStr);
			}
			std::cout << "Enter longitude: ";
			std::getline(std::cin, lonStr);
			while (lonStr.empty() or lonStr.find_first_not_of("0123456789.-") != std::string::npos) {
				std::cout << "longitude cannot be empty and must be a number:  ";
				std::getline(std::cin, lonStr);
			}

			try {//adds the inputted data into the main vector holding all the airport data to then be saved
				double latitude = std::stod(latStr);
				double longitude = std::stod(lonStr);

				a.set(identifier, type, name, elevation, continent, isoCountry, isoRegion,
					municipality, icaoCode, iataCode, gpsCode, localCode, latitude, longitude);

				repo.addAirport(a);

				std::cout << "Airport added successfully.\n";//if there arent any issues with the data inputted, the aiport is added.
			}
			catch (...) {
				std::cout << "Error: Could not convert latitude or longitude to a number. Airport has not been added.\n";//if there are any issues with the input, the user is notified
			}
			break;
		}

		case 6: {
			repo.saveToCsv();//saves any changes made to the vector back to the CSV file including any new airports added by the user
			std::cout << "Changes saved.\n";
			break;
		}
		case 7: {
			displayAdditonalMenu(repo);//calls the method to display the additional menu with more advanced features
			break;
		}
		case 8: {
			exit(0);//ends the program when the user chooses to exit
		}


		}
	}
}

void AirportApp::displayAdditonalMenu(airportRepository& repo) {//displays the additional menu with advanced features, it takes the repo parameter so that it can use the methods that require access to the airport data
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
		while (std::cin.fail()) {//user validation to make sure the user enters a number and not letters or symbols
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << "Invalid input, Please input a number:";
			std::cin >> userChoice;
		}
		while (userChoice > 8 or userChoice < 1) {// more input validation to make sure the user enters a number between 1 and 8
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

			airport* a1 = repo.findByIdentifier(id1);//finds the two airports with matching identifiers using the findByIdentifier method
			airport* a2 = repo.findByIdentifier(id2);

			if (a1 && a2) {
				double dist = repo.calculateAirportDistance(//calculates the distance between the two airports using the calculateAirportDistance method
					a1->getLatitude(), a1->getLongitude(),
					a2->getLatitude(), a2->getLongitude()
				);
				std::cout << "Distance between " << a1->getName()//displays the distance between the two airports if they are both found
					<< " and " << a2->getName() << " is: "
					<< dist << " km\n";
			}
			else {
				std::cout << "Error: One or both identifiers were not found.\n";//if either of the airports arent found, the user is notified
			}
			break;
		}
		case 2: {
			std::string airportId;
			std::cout << "Enter a airport identifier to search the nearest airport from: ";
			std::cin >> airportId;

			airport* nearestAirport = repo.findNearestAirport(airportId);//finds nearest airport using findNearestAirport method which calculates the distance to all other airports and outputs the nearest airport
			airport* airportChosen = repo.findByIdentifier(airportId);

			if (nearestAirport && airportChosen) {//if the airport chosen by the user and the nearest airport are both found, it calculates the distance between them and outputs the name of the nearest airport and the distance between them
				double distance = repo.calculateAirportDistance(
					airportChosen->getLatitude(), airportChosen->getLongitude(),
					nearestAirport->getLatitude(), nearestAirport->getLongitude()
				);
				std::cout << "The nearest airport to " << airportChosen->getName() << " (" << airportId << ") is:\n";
				std::cout << "Name: " << nearestAirport->getName() << " (" << nearestAirport->getIdentifier() << ")\n";
				std::cout << "Distance: " << distance << " km\n";//displays airport information and distance
			}
			else {
				std::cout << "Error: Identifier not found\n";//if there is an issue with the identifier entered by the user, they are notified
			}
			break;
		}
		case 3: {
			std::string ident;
			double radius;

			std::cout << "Enter the reference airport identifier: ";
			std::cin >> ident;
			std::cout << "Enter the radius in kilometers: ";//finds airports within a certain radius of a airport chosen by the user
			std::cin >> radius;

			// validates radius input
			if (std::cin.fail() || radius < 0) {//if the radius entered is below 0 or not a nummber the user is told it is invalid
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				std::cout << "Invalid radius entered.\n";
				break;
			}

			std::vector<airport> nearbyAirports = repo.findAirportsInRadius(ident, radius);//method finds airports within a certain radius of the airport chosen by the user and stores them in a vector

			if (nearbyAirports.empty()) {
				// This happens because either the identifier is wrong or theres no airports within the radius
				if (repo.findByIdentifier(ident) == nullptr) {
					std::cout << "Error: Reference airport identifier '" << ident << "' not found.\n";//if reference airport is not found
				}
				else {
					std::cout << "No other airports found within " << radius << " km.\n";//if there arent any airports within the radius entered by the user
				}
			}
			else {
				std::cout << "\nFound " << nearbyAirports.size() << " airports within " << radius << " km:\n";
				std::cout << "--------------------------------------------------\n";
				for (const auto& a : nearbyAirports) {
					airport* chosenAirport = repo.findByIdentifier(ident);
					double d = repo.calculateAirportDistance(chosenAirport->getLatitude(), chosenAirport->getLongitude(),
						a.getLatitude(), a.getLongitude());//calculates the distance between the airport chosen by the user and each of the nearby airports to display it to the user

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
			std::cout << "1. Show 10 Highest Airports" << std::endl;//asks the user if they want to see 10 highest or lowest elevation airports
			std::cout << "2. Show 10 Lowest Airports" << std::endl;
			std::cout << "Enter choice: ";
			std::cin >> elevationChoice;

			std::vector<airport> results;
			if (elevationChoice == 1) {
				results = repo.getTop10HighestElevation();//if 1 it shows top 10 highest, if its 2 it shows top 10 lowest, if its enters anything else the user is told its an invalid choice
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
					<< a.getName() << " (" << a.getIsoCountry() << ")\n";//gets the details of the airports
			}
			std::cout << "--------------------------------------------------\n";
			break;
		}
		case 5: {
			std::vector<airport> missingIata = repo.getAirportsWithMissingIata();//gets all airports with missing IATA codes and displays them to the user

			if (missingIata.empty()) {
				std::cout << "No airports have missing IATA codes.\n";//if there arent any airports with missing IATA codes
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

			std::vector<airport> results = repo.getAirportsByMunicipality(municipalitySearch);//finds all airports with a matching municipality and displays them to the user

			if (results.empty()) {
				std::cout << "No airports found for municipality: '" << municipalitySearch << "'\n";
			}
			else {
				std::cout << "\nFound " << results.size() << " airport in " << municipalitySearch << ":\n";//displays how many airports were found with the matching municipality and then lists them
				std::cout << "--------------------------------------------------\n";
				for (const auto& a : results) {
					std::cout << "- " << a.getName() << " (" << a.getIdentifier() << ")\n";// gets the airports name and identifier to display to the user
				}
				std::cout << "--------------------------------------------------\n";
			}
			break;
		}
		case 7: {
			int sortChoice, orderChoice;

			std::cout << "\nSort airports by:\n";
			std::cout << "1. Name\n2. Country\n3. Type\n4. Latitude\n5. Elevation\n";
			std::cout << "Enter choice(1-5): ";
			std::cin >> sortChoice;

			std::cout << "\nOrder:\n";
			std::cout << "1. Ascending (A-Z)\n2. Descending (Z-A)\n";
			std::cout << "Enter choice(1 or 2): ";
			std::cin >> orderChoice;

			std::vector<airport> sorted = repo.getSortedAirports(sortChoice, orderChoice);//sorts airports using different filters and in ascending or descending order depending on the user input and then displays the sorted list to the user

			std::cout << "\n--- Sorted Results ---\n";
			for (const auto& a : sorted) {
				std::cout << a.getName() << " | Country: " << a.getIsoCountry() << " | Type: " << a.getType() << " | "
					<< a.getElevationInFeet() << " ft\n" << "| Latitude: " << a.getLatitude() << "\n";//displays the name, country, elevation, type and latitude of the airports in the sorted list
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
void AirportApp::displayAirportDetails(const airport& a) {//method to display all the details of an airport
	std::cout << "------------------------------------------" << std::endl;
	std::cout << "Name: " << a.getName() << std::endl;
	std::cout << "ID: " << a.getIdentifier() << " |Type: " << a.getType() << std::endl;
	std::cout << "IATA: " << (a.getIataCode().empty() ? "N/A" : a.getIataCode()) << " |ICAO: " << (a.getIcaoCode().empty() ? "N/A" : a.getIcaoCode()) << std::endl;
	std::cout << "Location: " << a.getMunicipality() << ", " << a.getIsoCountry() << " (" << a.getContinent() << ")" << std::endl;
	std::cout << "Elevation: " << a.getElevationInFeet() << "ft" << "|Coordinates: " << a.getLatitude() << ", " << a.getLongitude() << std::endl; 
	std::cout << "------------------------------------------" << std::endl;
}