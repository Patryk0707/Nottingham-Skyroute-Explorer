#include <iostream>
#include <fstream>
class CSVFile{
public:
	static int readCSV();
};
int CSVFile::readCSV() {
	std::ifstream airports("airports.csv");
	if (airports.is_open()) {
		std::cout << "File read successfully";
	}
	else {
		std::cout << "Error opening the file";
		return 1;
	}
}

int main() {
	CSVFile::readCSV();
	return 0;

}