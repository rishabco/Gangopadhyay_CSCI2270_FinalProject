# Gangopadhyay_CSCI2270_FinalProject

*****UPDATE***** Program now runs on command line, see how to run.

CSCI 2270 Final Project 

Project Summary 

Our project is a Trip Route Planner. 

Our project will serve as a travel route planner for cities in the United States. The program will allow you to input a starting and ending city city and provide information on how to get there. The unique aspect of our program is that there are different districts located across the country, to which you can travel. This means, for example, if your starting city and destination are in different cities, the program will inform you how to travel to your nearest "hub city" (where there is an airport), to take a flight from that airport to the next airport, and then directions on how to get from the airport to your destination city. 

How to Run

UPDATE: This Program now runs on terminal. To run go to the cloned repository and enter:
 
 g++ -std=c++11 *.cpp
 
 ./a.out cities.txt

When the user starts the program, they pass in the name of a .txt file from which the program's graph will be built. A sample .txt has been provided as an example, it is called cities.txt. The program automatically generates two graphs, one normal graph, with different districts, and one with "hub" cities that contain airports, that allow for movement between districts. 


Once the graphs are made, the program begins. 


A menu is then displayed and provides the user with the following options:

1. Print All City Options
2. View Options for Ground Travel
3. View Options for Air Travel
4. Begin Planning Trip
5. Quit


Print All City Options: Displays all cities in the graph, and all of the cities to which they connect. 

View Options for Ground Travel: Prints all districts in the graph by district. 

View Options for Air Travel: Displays all "hub" cities and airports to which they connect.

Begin Planning Trip: Given two cities, this option finds the shortest path between the cities. In situations where the cities are in different districts, another function allows for travel between districts. The total distance is displayed at the end, along with your path, and the type of travel used, plane or car. 

Dependencies

Standard C++ libraries:

Here are the libraries that must be included for this program to function
Main:
-  iostream
- fstream
-  string
-  vector
-  sstream
-  "Travel.h"
Travel.h
-  vector
-  iostream
Travel.cpp
-  "Travel.h"
-   vector
-   queue
-   climit




Rishab Gangopadhyay, Francesca Figueroa, Kevin Prabhu

