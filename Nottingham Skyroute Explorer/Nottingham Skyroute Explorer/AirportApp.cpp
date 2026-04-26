#include "AirportApp.h"
#include <iostream>
#include <string>


void AirportApp::displayMainMenu(airportRepository& repo) {
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
		case 1: {
			std::string countryInput;
			std::cout << "Enter country code such as 'US' to find airports within that country: ";
			while (true) {
				std::cin >> countryInput;
				if (countryInput == "exit")
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
		case 2: {
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
		case 3: {
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
		case 4: {
			auto count = repo.countAirportsByType();

			std::cout << "Airport count by type:\n";

			for (const auto& entry : count) {
				std::cout << entry.first << ": " << entry.second << "\n";
			}

			break;
		}
		case 5: {
			airport a;
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
			while (name.empty()) {
				std::cout << "Name cannot be empty:  ";
				std::getline(std::cin, name);
			}
			std::string elevationStr;
			std::cout << "Enter elevation in feet: ";
			std::getline(std::cin, elevationStr);
			while (elevationStr.empty() or elevationStr.find_first_not_of("0123456789") != std::string::npos) {
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

		case 6: {
			repo.saveToCsv();
			std::cout << "Changes saved.\n";
			break;
		}
		case 7: {
			Menu::displayAdditonalMenu(repo);
			break;
		}
		case 8: {
			exit(0);
		}


		}
	}
}

void AirportApp::displayAdditonalMenu(airportRepository& repo) {
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

			std::vector<airport> sorted = repo.getSortedAirports(sortChoice, orderChoice);

			std::cout << "\n--- Sorted Results ---\n";
			for (const auto& a : sorted) {
				std::cout << a.getName() << " (" << a.getIsoCountry() << ") - "
					<< a.getElevationInFeet() << " ft\n";
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