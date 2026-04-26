#pragma once
#ifndef AIRPORT_H
#define AIRPORT_H

#include <string>
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
		std::string muni, std::string icao, std::string iata, std::string gps, std::string local, double lat, double lon);
};
#endif