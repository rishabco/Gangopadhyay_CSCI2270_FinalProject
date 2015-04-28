#include "Travel.h"
#include <vector>
#include <queue>
#include <climits>
using namespace std;

Travel::Travel()
{
    //initializes that the districts are not already set
    districtIsSet == false;
}

Travel::~Travel()
{
    //dtor
}

/*
Function Prototype:

void addCity(std::string);

Function Description:

This function is used to initialize the graph. We pass in the values from the text file one by one into this function to make the graph. First the function checks to see if the city being added is already in the vector; if it is, then the function sets the found boolean to true, so that the city isn't added twice. If the city isn't already in the vector, then it creates a new vertex, sets the name and districtID, then adds it to the vector.

Example:
Travel tGraph;
tGraph->addCity(std::string);

Pre-conditions:

The string being passed in must be a string.


Post Conditions:

The graph will have vertices.

*/
void Travel::addCity(std::string cityName)
//Creates vertices in the vertices vector
{
    bool found = false;

    //Checks to see if the city is already in the vector.
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i].name == cityName)
        {
            //Sets to true, so vertex is not duplicated
            found = true;
        }
    }
    if(found == false)
    {
        //Creates a new vertex for the city
        vertex v;
        v.name = cityName;
        v.districtID = 0;
        //Adds to the vertices vector
        vertices.push_back(v);
    }

}

/*
Funciton prototype:
void addHub(std::string);

Function description:
This function is used to fifnd the "hub" or airport cities. We pass in the values from the text file one by one into this function to make a second graph. First the function checks to see if the city being added is already in the vector; if it is, then the function sets the found boolean to true, so that the city isn't added twice. If the city isn't already in the vector, then it creates a new vertex, sets the name and districtID, then adds it to the vector.

Example:
Travel tGraph;
tGraph->addCity(std::string);

Pre-conditions:

The string being passed in must be a string.


Post Conditions:

The graph will have vertices.

*/
void Travel::addHub(std::string cityName)
//Creates vertices in the hubCityVertices vector
{
    bool found = false;

    //Checks to see if the city is already in the vector.
    for(int i = 0; i < hubCityVertices.size(); i++)
    {
        if(hubCityVertices[i].name == cityName)
        {
            //Sets to true, so vertex is not duplicated.
            found = true;
        }
    }
    if(found == false)
    {
        //Creates a new vertex for the city
        vertex v;
        v.name = cityName;
        v.districtID = 0;
        //Adds to the hubCityVertices vector
        hubCityVertices.push_back(v);
    }

}

/*
Function Prototype:
void addRoad(std::string, std::string, int);

Function description:
This function is used to add edges to the vertices. We pass in the values from the text file. First the function checks where the cities being added are in the vector, then the function adds the edge to the adjacentcy vector.

Example:
Travel tGraph;
tGraph->addRoad(std::string, std::string, int);

Pre-conditions:

The strings being passed in must be strings. int must be an int. Function won't do anything if cityOne doesn't exist in the vector.


Post Conditions:

The graph will have edges.

*/
void Travel::addRoad(std::string cityOne, std::string cityTwo, int distance)
//Adds a "road" path between cities
{
    //Loops through vertices vector
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i].name == cityOne)
        {
            //Loops through "cityOne" adjacency vector
            for(int j = 0; j < vertices.size(); j++)
            {
                if(vertices[j].name == cityTwo && i != j)
                {
                    //Adds a new vertex to the "cityOne" adjacency vector
                    adjVertex av;
                    av.v = &vertices[j];
                    av.weight = distance;
                    vertices[i].adj.push_back(av);
                }
            }
        }
    }
}
/*
Function prototype:

void addPlanePath(std::string, std::string, int);


Function description:

This function is used to add edges to the vertices. We pass in the values from the text file. First the function checks where the cities being added are in the vector, then the function adds the edge to the adjacentcy vector.
Also sets each city's isAirport boolean to true, so we know which cities are our hub cities.

Example:

Travel tGraph;
tGraph->addPlanePath(std::string, std::string, int);

Pre-conditions:

The strings being passed in must be strings. int must be an int. Function won't do anything if cityOne doesn't exist in the vector.


Post Conditions:

The graph will have edges.

*/
void Travel::addPlanePath(std::string cityOne, std::string cityTwo, int distance)
//Adds a path between "hub" cities
{

    int cityOneIndex;
    int cityTwoIndex;

    //Find Index of cityOne
    for(int i = 0; i < vertices.size(); i++)
    {
        if(cityOne == vertices[i].name)
        {
            cityOneIndex=i;
        }
    }

    //Find Index of cityTwo
    for(int i = 0; i < vertices.size(); i++)
    {
        if(cityTwo ==  vertices[i].name)
        {
            cityTwoIndex=i;
        }
    }

    //Distinguishes these cities as "hub" cities
    vertices[cityOneIndex].isAirport = true;
    vertices[cityTwoIndex].isAirport = true;

    //Loops through hubCityVertices
    for(int i = 0; i < hubCityVertices.size(); i++)
    {
        if(hubCityVertices[i].name == cityOne)
        {
            //Loops through cityOne adjacency vector
            for(int j = 0; j < hubCityVertices.size(); j++)
            {
                if(hubCityVertices[j].name == cityTwo && i != j)
                {
                    //Adds new city to cityOne adjacency vector
                    adjVertex av;
                    av.v = &hubCityVertices[j];
                    av.weight = distance;
                    hubCityVertices[i].adj.push_back(av);
                }
            }
        }
    }
}


/*
Function prototype:

void findDistricts();


Function description:

This function is used to set districtID's for each city in the vertices vector. First it checks to see if the districtID is set, if it hasn't been set it's 0.
Example:

Travel tGraph;
tGraph->findDistricts();

Pre-conditions:

Must call this function after addCity/addHub and addRoad/addPlanePath have been called, and the graph has been fully generated. 


Post Conditions:

All vertices in the graph will be given districtIDs to identify which part of the graph they are in

*/
void Travel::findDistricts()
//Sets the districts
{
    districtIsSet = true;
    //Starts count at 1 for district number
    int districtCounter = 1;
    
    //Loops through vertices vector
    for(int j = 0; j < vertices.size(); j++)
    {
    
        if(vertices[j].districtID == 0)
        {

            queue <vertex*> districtQueue;
            vertex v;
            int i = 0;
            for(i=0; i<vertices.size();i++)
            {
                if (vertices[j].name == vertices[i].name)
                {
                    v = vertices[i];
                    break;
                }
            }
            
            //Sets District
            vertices[i].visited = true;
            vertices[i].districtID = districtCounter;
            districtQueue.push(&vertices[i]);

            while (!districtQueue.empty())
            {
                v = *districtQueue.front();
                districtQueue.pop();
                for(i=0;i<v.adj.size();i++)
                {
                    if (v.adj[i].v->visited==false)
                    {
                        v.adj[i].v->visited = true;
                        v.adj[i].v->districtID = districtCounter;
                        districtQueue.push(v.adj[i].v);
                    }
                }
            }

        }

        if(vertices[j+1].districtID == 0)
        {
            districtCounter++;
        }

    }
    numDistricts = districtCounter;

}

/*
Function prototype:

void printCities();


Function description:

This function is used to print all the cities in the vertices vector.
Just iterates through the vertices vector, printing the name as well as the adjacent vectors to each cities' names.

Example:

Travel tGraph;
tGraph->printCities();

Pre-conditions:

Graph existing would be nice, otherwise there's nothing to print.


Post Conditions:

The graph will be printed.

*/
void Travel::printCities()
//Prints out all cities and paths between
{
    for(int i = 0 ; i < vertices.size(); i++)
    {
        cout <<vertices[i].name << "-->";
        for(int j = 0; j < vertices[i].adj.size(); j++)
        {
            cout << vertices[i].adj[j].v->name;
            if(j != vertices[i].adj.size()-1)
            {
                cout << "---";
            }
        }
        cout << endl;
    }
    cout<< endl;
}

/*
Function prototype:

void printDistricts();


Function description:

This function is used to print all the cities in the each district.
Just iterates through the vertices vector, printing the name as well as the adjacent vectors to each cities' names.

Example:

Travel tGraph;
tGraph->printDistricts();

Pre-conditions:

Graph existing would be nice, also need to run findDistricts before you call this.


Post Conditions:

The graph will be printed, seperated by district.

*/

void Travel::printDistricts()
//Prints out all cities in each district
{

    int currentDistrictID = 1;
    //Loops through all district numbers
    for(int l = 0; l <= numDistricts-2; l++)
    {
        cout << "Travel District " << currentDistrictID << ":" << endl;
        //Loops through vertices vector
        for(int i = 0 ; i < vertices.size(); i++)
        {
            //If the district of the vertex is the same as districtID -> prints vertex name
            if (vertices[i].districtID == currentDistrictID)
            {
                cout << vertices[i].name;
                cout << endl;
            }
        }

        cout << endl;
        //Move to next district
        currentDistrictID++;
    }

}
/*
Function prototype:

void printPlanePaths();


Function description:

This function is used to print all the cities in the hubCitiyVertices vector.
Just iterates through the hubCityVertices vector, printing the name as well as the adjacent vectors to each cities' names.

Example:

Travel tGraph;
tGraph->printPlanePaths();

Pre-conditions:

Graph existing would be nice, otherwise there's nothing to print.


Post Conditions:

The hubCity graph will be printed.

*/

void Travel::printPlanePaths()
//Prints out paths between "hub" cities
{

    for(int i = 0 ; i < hubCityVertices.size(); i++)
    {
        if(!hubCityVertices[i].adj.empty())
        {
            cout << hubCityVertices[i].name << "-->";
            for(int j = 0; j < hubCityVertices[i].adj.size(); j++)
            {
                cout << hubCityVertices[i].adj[j].v->name;
                if(j != hubCityVertices[i].adj.size() - 1)
                {
                    cout << "---";
                }
            }
            cout << endl;
        }

    }
}

/*
Function prototype:

void findNearestAirport(std::string);


Function description:

This function is used to find the nearest hub city to the starting city that is passed in. It checks first to see if the starting city is a hub city, and if that's true then it returns the address of that vertice. If it's not, then it iterates through the vertices looking for the vertex that has a matching districtID & isAirport = true. When it finds that, it returns the address of that vertice.

Example:

Travel tGraph;
tGraph->findNearestAirport(std::string);

Pre-conditions:

Graph existing would be nice, otherwise there's nothing to search in.
Strings being passed in must be strings.
addHubCity needs to be run, or the isAirport bool would not be set.
Need to run findDistricts, or there's no way to distinguish which hub city is accessible by road.


Post Conditions:

The function returns the closest hub city to the entered city, or, if the starting city isn't in the vertices vector, it returns NULL.

*/
vertex* Travel::findNearestAirport(string startingCity)
//Finds the airport in a district
{
    vertex* airportCity;

    int startIndex;
    //Find district ID of city

    //Search through all vertices
    for(int i =0; i < vertices.size();i++)
    {   //Check if it is the starting city
        if(startingCity == vertices[i].name)
        {
            if(vertices[i].isAirport == true)
            {   //If the starting city is an airport return that index
                return &vertices[i];
            }
            //Else return the start index
            startIndex = i;
        }
    }

    //This is the district of the city you must search through
    int cityDistrict = vertices[startIndex].districtID;

    //Search through vertices vector
    for(int i = 0 ; i < vertices.size(); i++)
    {
        //If you find a vertex with the same district
        if (vertices[i].districtID == cityDistrict)
        {
            //And if the vertex is an airport
            if(vertices[i].isAirport == true)
            {
                //Return that city as the "airport city"
                airportCity = &vertices[i];
                return airportCity;
            }
        }
    }

    return NULL;
}

/*
Function prototype:

void shortestDistance(std::string, std::string);


Function description:

This function is used to find the shortest path between 2 cities. It uses a modified Djikstra's Algorithm to find the shortest path. The modifications are for the restrictions caused by the districts, as you can only travel between districts from hub cities.

Example:

Travel tGraph;
tGraph->shortestDistance(std::string, std::string);

Pre-conditions:

Graph existing would be nice, no graph = nothing to figure out what the shortest distance between the 2 cities. 
strings being passed in must be strings.
findDistricts needs to be run before as well. This function calls on shortestDistance recursively, as well as findNearestAirport and travelBetweenDistricts.


Post Conditions:

The function finds the shortest distance between the 2 cities if they both exist, and prints the air routes, ground routes, and total distance traveled.

*/

int Travel::shortestDistance(std::string starting, std::string destination)
{
    //Djikstra's Algorithm w/Modifications

    //Makes sure both cities are in the graph
    int totalDistance = 0;
    bool startFound = false;
    bool destFound = false;

    for(int i = 0; i < vertices.size(); i++)
    {
        if(starting == vertices[i].name)
        {
            startFound = true;
        }
    }

    for(int i = 0; i < vertices.size(); i++)
    {
        if(destination == vertices[i].name)
        {
            destFound = true;
        }
    }

    //If not in the Graph, don't continue
    if(destFound == false || startFound == false)
    {
        cout << "One or more cities not in network" << endl;
        return 0;
    }


    vertex* start;
    vertex* dest;

    vector <vertex*> peth;

    for(int i = 0; i < vertices.size(); i++)
    {
        vertices[i].visited = false;
        vertices[i].previous = NULL;
        vertices[i].distance= INT_MAX;
        if (vertices[i].name == starting)
        {
            vertices[i].visited = true;
            vertices[i].distance = 0;
            start = &vertices[i];
        }
        else if(vertices[i].name == destination)
        {
            dest = &vertices[i];
        }
    }



    //Different Districts
    //If in different districts: Find the district the other city is in;
    if(dest->districtID != start->districtID)
    {
        //sets the airport in each district to find travel path between
        vertex* startingAirport = findNearestAirport(starting);
        vertex* destinationAirport = findNearestAirport(destination);

        //Travel from starting city to final city
        //Does shortest distance from starting to airport, airport to airport, airport to destination
        //Checks for airport to airport travel


        if(starting == startingAirport->name && destinationAirport->name == destination)
        {
             totalDistance = totalDistance + travelBetweenDistricts(startingAirport->name, destinationAirport->name);
             return totalDistance;

        }
        //Checks for airport to city travel
        else if(starting == startingAirport->name)
        {
            totalDistance = totalDistance + travelBetweenDistricts(startingAirport->name, destinationAirport->name);
            totalDistance = totalDistance + shortestDistance(destinationAirport->name, destination);
            return totalDistance;

        }
        //Checks for city to Airport travel
        else if(destination == destinationAirport->name)
        {
                    totalDistance = totalDistance + shortestDistance(starting, startingAirport->name);
        totalDistance = totalDistance + travelBetweenDistricts(startingAirport->name, destinationAirport->name);
        return totalDistance;

        }
        else
        {
            totalDistance = totalDistance + shortestDistance(starting, startingAirport->name);
            totalDistance = totalDistance + travelBetweenDistricts(startingAirport->name, destinationAirport->name);
            totalDistance = totalDistance + shortestDistance(destinationAirport->name, destination);
            return totalDistance;

        }

    }


    peth.push_back(start);
    int minDistance;

    
    while(dest->visited == false)
    {
        minDistance = INT_MAX;
        int distance = 0;
        vertex* minVert = NULL;
        vertex* minPrevious;

        for(int j = 0; j < peth.size(); j++)
        {
            peth[j]->visited = true;

            for( int l = 0; l < peth[j]->adj.size(); l++)
            {
                if(peth[j]->adj[l].v->visited == false)
                {
                    distance = peth[j]->distance + peth[j]->adj[l].weight;
                    if(distance < minDistance)
                    {
                        peth[j]->adj[l].v->distance = distance;

                        minDistance = distance;
                        minVert = peth[j]->adj[l].v;
                        minPrevious = peth[j];
                    }
                }
            }
        }

        minVert->previous = minPrevious;
        peth.push_back(minVert);

    }


    vector <string> path;
    vertex* destiNation = dest;

    //Stores path
    while(destiNation != NULL)
    {
        path.push_back(destiNation->name);
        destiNation = destiNation->previous;
    }

    //Prints Path
    cout << "Drive from: ";

    cout << path[path.size()-1];
    for (int i = path.size()-2; i > -1; i--)
    {
        cout << " to " << path[i];
    }

    cout << endl;

    return minDistance;

}

/*
Function prototype:

void travelBetweenDistricts(std::string, std::string);


Function description:

This function is used to find the shortest path between 2 hub cities. It uses a modified Djikstra's Algorithm to find the shortest path. The modifications are for the restrictions caused by the districts.

Example:

Travel tGraph;
tGraph->travelBetweenDistricts();

Pre-conditions:

Strings should be strings.
Graph existing would be nice, otherwise there's nothing to print.


Post Conditions:

Returns the int distance between 2 hub cities, the first in the starting district and the second in teh destination district to add to the total distance traveled.

*/
int Travel::travelBetweenDistricts(string starting, string destination)
{
    //Djikstra's Algorithm w/ Modifications
    //Searches through the hubCityVertices vector, to determine shortest path between hub cities
    vertex* start;
    vertex* dest;

    vector <vertex*> visitedVertices;

    for(int i = 0; i < hubCityVertices.size(); i++)
    {
        //Initializes all
        hubCityVertices[i].visited = false;
        hubCityVertices[i].previous = NULL;
        hubCityVertices[i].distance= INT_MAX;

        if (hubCityVertices[i].name == starting)
        {
            hubCityVertices[i].visited = true;
            hubCityVertices[i].distance = 0;
            start = &hubCityVertices[i];
        }
        else if(hubCityVertices[i].name == destination)
        {
            dest = &hubCityVertices[i];
        }

    }


    visitedVertices.push_back(start);
    int minDistance;


    while(dest->visited == false)
    {
        minDistance = INT_MAX;
        int distance = 0;
        vertex* minVert = NULL;
        vertex* minPrevious;

        for(int j = 0; j < visitedVertices.size(); j++)
        {
            visitedVertices[j]->visited = true;

            for( int l = 0; l < visitedVertices[j]->adj.size(); l++)
            {
                if(visitedVertices[j]->adj[l].v->visited == false)
                {
                    distance = visitedVertices[j]->distance + visitedVertices[j]->adj[l].weight;
                    if(distance < minDistance)
                    {
                        visitedVertices[j]->adj[l].v->distance = distance;

                        minDistance = distance;
                        minVert = visitedVertices[j]->adj[l].v;
                        minPrevious = visitedVertices[j];
                    }
                }
            }
        }

        minVert->previous = minPrevious;
        visitedVertices.push_back(minVert);

    }


    vector <string> path;
    vertex* destiNation = dest;

    //Adds path
    while(destiNation != NULL)
    {
        path.push_back(destiNation->name);
        destiNation = destiNation->previous;
    }

    travelDistance = minDistance;

    //Prints path
    cout << "Fly from: ";

    cout << path[path.size()-1];
    for (int i = path.size()-2; i > -1; i--)
    {
        cout << " to " << path[i];
    }

    cout << endl;

    //returns path distance
    return minDistance;

}
