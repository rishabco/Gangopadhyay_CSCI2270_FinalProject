#ifndef TRAVEL_H
#define TRAVEL_H

#include<vector>
#include<iostream>

struct vertex;

struct adjVertex{
    vertex* v;
    int weight;
};

struct vertex{
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
        void addRoad(std::string v1, std::string v2, int weight);
        void addCity(std::string name);
        void addHub(std::string name);
        void addPlanePath(std::string v1, std::string v2, int weight);
        void printDistricts();
        void printCities();
        void printPlanePaths();
        vertex* findNearestAirport(std::string city);
        void shortestDistance(std::string starting, std::string destination);
        void findDistricts();

    protected:
    private:
        //vector<edge> edges;
        std::vector<vertex> vertices;
        std::vector<vertex> hubCityVertices;
        bool districtIsSet;
        int numDistricts;
        int travelDistance;
        int planeSpeed = 600;
        int carSpeed = 60;

};


#endif // TRAVEL_H
