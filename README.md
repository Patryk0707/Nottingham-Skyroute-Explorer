# Nottingham Skyroute Explorer
This application will allow the user to seach for airports using a variety of ways. Display full airport details for search results and save all airports including new airport entries that the user can create allowing them to be viewed in the future. This program will have a simple console interface and handle any errors the user may come across

Project is called Nottingham Skyroute explorer. It helps the user add airports, search airports, list airports or filter through airports. It has a simple interface that uses a range of numbers to continue through different parts of the features. The CSV file is read every time the program is ran. I used instances such as airport to store each row of the CSV and the repo instance to store the whole thing in a vector.
The program runs in the window console and does not use any additional libraries
Key features
Main Features
The menu that the user can access allows the user to:
1. Search airports by country
2. Search airports by name
3. Search by IATA code
4. Count airports by type
5. Add a new airport
6. Save changes to the airport CSV
Advanced Features:
1. Calculate distance between airports
2. Find nearest airport to a given location
3. List all airports within a radius
4. List highest or lowest elevation airports
5. List airports with missing IATA codes
6. Group airports by municipality
7. Sort airports
How to use:
1.Run the project in visual studio
2.Use the menu interface to use the simple features by pressing 1-8 to search for airports, count airports by type or add airports and save them to the CSV file.
3. press 7 to go to the additional features menu to access the more advanced features. Advanced features include calculating distance between airports, listing airports within a radius. List highest or lowest elevation airports, list airports with missing IATA codes,group airports by municipality or sort airports.
4.Press 8 twice to close the program once your finished
Classes:
airport
airportRepository
File structure:
--------//Nottingham Skyroute Explorer
airports.csv
Nottingham Skyroute Explorer.slnx
------// Nottingham Skyroute Explorer
	airport.h
	AirportApp.cpp
	airportApp.h
	AirportRepository.cpp
	airportRepository.h
	main.cpp
	Nottingham Skyroute Explorer.vcxproj
	Nottingham Skyroute Explorer.vcxproj.filters
	Nottingham Skyroute Explorer.vcxproj.user
