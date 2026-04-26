#ifndef AIRPORTREPOSITORY_H
#define AIRPORTREPOSITORY_H

#include "airport.h"
#include <vector>
#include <map>
#include <string>
class airportRepository {
public://Declaration of all the functions that will be used in the airportRepository.cpp file including parameters and return types
	void loadFromCSV();
	std::multimap<std::string, airport> searchAirportByCountry(const std::string& country) const;
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
	std::vector<airport> getSortedAirports(int criteria, int orderChoice) const;
private://Declaration of the vector that will be used to store all the airports
	std::vector<airport>airports;
};
#endif