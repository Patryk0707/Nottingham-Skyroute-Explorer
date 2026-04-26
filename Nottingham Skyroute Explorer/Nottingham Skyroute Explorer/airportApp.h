#pragma once
#ifndef AIRPORTAPP_H
#define AIRPORTAPP_H

#include "airportRepository.h"

class AirportApp {
public:
    void displayMainMenu();

private:
    void displayAdditonalMenu(airportRepository& repo);
};

#endif