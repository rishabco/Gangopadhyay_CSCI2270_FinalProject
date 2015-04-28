#ifndef TRAVEL_H
#define TRAVEL_H
 
#include<vector>
#include<iostream>
 
struct vertex;
 
struct adjVertex
{
    vertex* v;
    int weight;
};
 
struct vertex
{
    vertex* previous;
    std::string name;
    std::vector<adjVertex> adj;
    bool visited;
    bool isAirport = false;
    int distance;
    int districtID;
};
 
class Travel
{
    public:
        Travel();
        ~Travel();
        void addRoad(std::string cityOne, std::string cityTwo, int distance);
        void addCity(std::string cityName);
        void addHub(std::string cityName);
        void addPlanePath(std::string cityOne, std::string cityTwo, int distance);
        void printDistricts();
        void printCities();
        void printPlanePaths();
        vertex* findNearestAirport(std::string city);
        int travelBetweenDistricts(std::string starting, std::string destination);
        int shortestDistance(std::string starting, std::string destination);
        void findDistricts();
 
 
    protected:
    private:
        std::vector<vertex> vertices;
        std::vector<vertex> hubCityVertices;
        bool districtIsSet;
        int numDistricts;
        int travelDistance;
};
 
 
#endif // TRAVEL_H