#pragma once
#ifndef AIRPORTAPP_H
#define AIRPORTAPP_H

#include "airportRepository.h"

class AirportApp {
public:
    void displayMainMenu();//function to display the main menu
    void displayAdditonalMenu(airportRepository& repo);//function to display the additional features menu
    void displayAirportDetails(const airport& a);
};

#endif