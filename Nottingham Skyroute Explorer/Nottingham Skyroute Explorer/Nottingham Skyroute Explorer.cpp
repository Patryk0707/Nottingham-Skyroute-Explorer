#include <iostream>
#include <fstream> //enables file handling

class CSVFile{
public:
	static int readCSV(); //creates a static method that returns a integer
};
int CSVFile::readCSV() {
	std::ifstream airports("../airports.csv"); //opens the CSV file and uses ../ to check for the file a folder before the x64 folder
	if (airports.is_open()) {
		std::cout << "File read successfully";
	}
	else {
		std::cout << "Error opening the file";
		return 1;
	}
}

class Menu {
public:
	static void displayMainMenu();
	static void displayAdditonalMenu();
};

void Menu::displayMainMenu(){
	int userChoice;
	while(true) {
		std::cout << "====== Nottingham SkyRoute Explorer ======" << std::endl;
		std::cout << "1. Search airports by country" << std::endl;
		std::cout << "2. Search airports by name" << std::endl;
		std::cout << "3. Search by IATA code" << std::endl;
		std::cout << "4. Count airports by type" << std::endl;
		std::cout << "5. Add a new airport" << std::endl;
		std::cout << "6. Save changes" << std::endl;
		std::cout << "7. Advanced options(radius search, nearest airport, high / low elevation,sort etc.)" << std::endl;
		std::cout << "8. Exit" << std::endl;
		std::cout<< "Enter a number:";
		std::cin >> userChoice;
		while (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(1000,'\n');
			std::cout<<"Invalid input, Please input a number:";
			std::cin >> userChoice;
		}
		while (userChoice > 8 or userChoice<1) {
			std::cin.ignore();
			std::cout << "Please enter a number within 1-8";
			std::cin >> userChoice;
		}
		
	switch (userChoice) {
		case 7:
			Menu::displayAdditonalMenu();
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
	Menu::displayMainMenu();
	CSVFile::readCSV();
	void displayMenu(); {
		
	}
	return 0;

}