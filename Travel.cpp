#include "Travel.h"
#include <vector>
#include <queue>
#include <climits>
using namespace std;
 
Travel::Travel()
{
    districtIsSet == false;
}
 
Travel::~Travel()
{
    //dtor
}
 
void Travel::addRoad(std::string cityOne, std::string cityTwo, int distance)
{
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i].name == cityOne)
        {
            for(int j = 0; j < vertices.size(); j++)
            {
                if(vertices[j].name == cityTwo && i != j)
                {
                    adjVertex av;
                    av.v = &vertices[j];
                    av.weight = distance;
                    vertices[i].adj.push_back(av);
                }
            }
        }
    }
}
 
void Travel::addCity(std::string cityName)
{
    bool found = false;
    //Checks to see if the city is already in the vector.
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i].name == cityName)
        {
            found = true;
        }
    }
    if(found == false)
    {
        vertex v;
        v.name = cityName;
        v.districtID = 0;
        vertices.push_back(v);
    }
 
}
 
void Travel::addHub(std::string cityName)  //GET RID OF THIS ONE?
{
    bool found = false;
    for(int i = 0; i < hubCityVertices.size(); i++)
    {
        if(hubCityVertices[i].name == cityName)
        {
            found = true;
        }
    }
    if(found == false)
    {
        vertex v;
        v.name = cityName;
        v.districtID = 0;
        hubCityVertices.push_back(v);
    }
 
}
 
void Travel::addPlanePath(std::string cityOne, std::string cityTwo, int distance)
{
    //SET cityOne, cityTwo AS PLANE PATHS
    //find indexes
    int cityOneIndex;
    int cityTwoIndex;
 
    for(int i = 0; i < vertices.size(); i++)
    {
        if(cityOne == vertices[i].name)
        {
            cityOneIndex=i;
        }
    }
 
    for(int i = 0; i < vertices.size(); i++)
    {
        if(cityTwo ==  vertices[i].name)
        {
            cityTwoIndex=i;
        }
    }
 
    vertices[cityOneIndex].isAirport = true;
    vertices[cityTwoIndex].isAirport = true;
 
    for(int i = 0; i < hubCityVertices.size(); i++)
    {
        if(hubCityVertices[i].name == cityOne)
        {
            for(int j = 0; j < hubCityVertices.size(); j++)
            {
                if(hubCityVertices[j].name == cityTwo && i != j)
                {
                    adjVertex av;
                    av.v = &hubCityVertices[j];
                    av.weight = distance;
                    hubCityVertices[i].adj.push_back(av);
                }
            }
        }
    }
}
 
void Travel::printPlanePaths()
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
 
void Travel::printDistricts()
{
 
    int currentDistrictID = 1;
    for(int l = 0; l <= numDistricts-2; l++)
    {
        cout << "Travel District " << currentDistrictID << ":" << endl;
        for(int i = 0 ; i < vertices.size(); i++)
        {
            if (vertices[i].districtID == currentDistrictID)
            {
                cout << vertices[i].name;
                cout << endl;
            }
        }
 
        cout << endl;
        currentDistrictID++;
    }
 
}
 
void Travel::printCities()
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
 
vertex* Travel::findNearestAirport(string startingCity)
{
    vertex* airportCity;
 
 
    int startIndex;
    //Find district ID of city
    for(int i =0; i < vertices.size();i++)
    {
        if(startingCity == vertices[i].name)
        {
            if(vertices[i].isAirport == true)
            {
                return &vertices[i];
            }
            startIndex = i;
        }
    }
 
    int cityDistrict = vertices[startIndex].districtID;
    //Search through all cities in district
    for(int i = 0 ; i < vertices.size(); i++)
    {
        if (vertices[i].districtID == cityDistrict)
        {

            if(vertices[i].isAirport == true)
            {
                airportCity = &vertices[i];
                return airportCity;
            }
        }
    }

    return NULL;
}
 
int Travel::travelBetweenDistricts(string starting, string destination)
{
    vertex* start;
    vertex* dest;
 
    vector <vertex*> peth;
 
    for(int i = 0; i < hubCityVertices.size(); i++)
    {
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
 
    while(x != NULL)
    {
        path.push_back(x->name);
        destiNation = destiNation->previous;
    }
 
    travelDistance = minDistance;
 
    cout << "Fly from: ";
 
    cout << path[path.size()-1];
    for (int i = path.size()-2; i > -1; i--)
    {
        cout << " to " << path[i];
    }
 
    cout << endl;
 
    return minDistance;
 
}
 
int Travel::shortestDistance(std::string starting, std::string destination)
{
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
        vertex* startingAirport = findNearestAirport(starting);
        vertex* destinationAirport = findNearestAirport(destination);
 
        //Travel from starting city to final city
        //Do shortest distance from starting to airport, airport to airport, airport to destination
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
 
    while(destiNation != NULL)
    {
        path.push_back(destiNation->name);
        destiNation = destiNation->previous;
    }
 
    cout << "Drive from: ";
 
    cout << path[path.size()-1];
    for (int i = path.size()-2; i > -1; i--)
    {
        cout << " to " << path[i];
    }
 
    cout << endl;
 
    return minDistance;
 
}
 
void Travel::findDistricts() //Based on isAirport BOOl
{
    districtIsSet = true;
    int districtCounter = 1;
    for(int j = 0; j < vertices.size(); j++)
    {
        if(vertices[j].districtID == 0)
        {
 
            queue <vertex*> quething;
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
            vertices[i].visited = true;
            vertices[i].districtID = districtCounter;
            quething.push(&vertices[i]);
 
            while (!quething.empty())
            {
                v = *quething.front();
                quething.pop();
                for(i=0;i<v.adj.size();i++) 
                {
                    if (v.adj[i].v->visited==false)
                    {
                        v.adj[i].v->visited = true;
                        v.adj[i].v->districtID = districtCounter;
                        quething.push(v.adj[i].v);
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