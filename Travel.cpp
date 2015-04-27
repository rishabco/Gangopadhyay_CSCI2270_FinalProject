#include "Travel.h"
#include <vector>
#include <queue>
#include <climits>
using namespace std;

Travel::Travel()
{
	//ctor
	 districtIsSet = false;
}

Travel::~Travel()
{
    //dtor
}

void Travel::addRoad(std::string v1, std::string v2, int weight)
{
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i].name == v1)
        {
            for(int j = 0; j < vertices.size(); j++)
            {
                if(vertices[j].name == v2 && i != j)
                {
                    adjVertex av;
                    av.v = &vertices[j];
                    av.weight = weight;
                    vertices[i].adj.push_back(av);
                }
            }
        }
    }
}

void Travel::addCity(std::string cityName)
{
	bool found = false;
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i].name == cityName)
        {
            found = true;
            cout<<vertices[i].name<<" found."<<endl;
        }
    }
    if(found == false)
    {
        vertex v;
        v.name = cityName;
        v.districtID = 0;
        vertices.push_back(v);
        //cout << "Added: " << v.name << endl;
    }

}

void Travel::addHub(std::string cityName)  //GET RID OF THIS ONE
{
	bool found = false;
    for(int i = 0; i < hubCityVertices.size(); i++)
    {
        if(hubCityVertices[i].name == cityName)
        {
            found = true;
            cout<<hubCityVertices[i].name<<" found."<<endl;
        }
    }
    if(found == false)
    {
        vertex v;
        v.name = cityName;
        v.districtID = 0;
       // v.isAirport = true;
        hubCityVertices.push_back(v);
        //cout << "Added: " << v.name << endl;
    }
}

void Travel::addPlanePath(std::string v1, std::string v2, int weight)
{
	//SET V1, V2 AS PLANE PATHS
    //find indexes
    int v1Index;
    int v2Index;

    for(int i=0; i<hubCityVertices.size(); i++)
    {
        if(v1 == hubCityVertices[i].name)
        {
            v1Index=i;
        }
    }

    for(int i=0; i<hubCityVertices.size(); i++)
    {
        if(v2 == hubCityVertices[i].name)
        {
            v2Index=i;
        }
    }

    hubCityVertices[v1Index].isAirport = true;
    hubCityVertices[v2Index].isAirport = true;

        for(int i = 0; i < hubCityVertices.size(); i++)
        {
        //cout << hubCityVertices[i].name << endl;
        if(hubCityVertices[i].name == v1)
        {
            for(int j = 0; j < hubCityVertices.size(); j++)
            {
                if(hubCityVertices[j].name == v2 && i != j)
                {
                    adjVertex av;
                    av.v = &hubCityVertices[j];
                    av.weight = weight;
                    hubCityVertices[i].adj.push_back(av);
                }
            }
        }
        int k = 0;
    }
}

void Travel::printPlanePaths()
{

    for(int i = 0 ; i < hubCityVertices.size(); i++)
    {
        if(!hubCityVertices[i].adj.empty())
        {
            cout <<hubCityVertices[i].name << "-->";
            for(int j = 0; j < hubCityVertices[i].adj.size(); j++)
            {
                cout << hubCityVertices[i].adj[j].v->name;
                if(j != hubCityVertices[i].adj.size()-1)
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
                cout <<vertices[i].name;
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

    for(int i= 0; i < hubCityVertices.size(); i++)
    {
        if(hubCityVertices[i].isAirport == true)
        cout << hubCityVertices[i].name << " has an airport." << endl;
    }
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

    vector <vertex*> solved;

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
        totalDistance = totalDistance + shortestDistance(starting, startingAirport->name);
        totalDistance = totalDistance + travelBetweenDistricts(startingAirport->name, destinationAirport->name);
        totalDistance = totalDistance + shortestDistance(destinationAirport->name, destination);
        //Find where Other thing is
        return totalDistance;
    }


    solved.push_back(start);
    int minDistance;


    while(dest->visited == false)
    {
        minDistance = INT_MAX;
        int distance = 0;
        vertex* minVert = NULL;
        vertex* minPrevious;

        for(int j = 0; j < solved.size(); j++)
        {
            solved[j]->visited = true;

            for( int l = 0; l < solved[j]->adj.size(); l++)
            {
                if(solved[j]->adj[l].v->visited == false)
                {
                    distance = solved[j]->distance + solved[j]->adj[l].weight;
                    if(distance < minDistance)
                    {
                        solved[j]->adj[l].v->distance = distance;

                        minDistance = distance;
                        minVert = solved[j]->adj[l].v;
                        minPrevious = solved[j];
                    }
                }
            }
        }

        minVert->previous = minPrevious;
        solved.push_back(minVert);

    }

    vector <string> path;
    vertex* x = dest;

    while(x != NULL)
    {
        path.push_back(x->name);
        x = x->previous;
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

void Travel::findDistricts()
{
    districtIsSet = true;
    int districtCounter = 1;
    for(int j = 0; j < vertices.size(); j++)
    {
        //cout << districtCounter<<endl;
        if(vertices[j].districtID == 0)
        {

            queue<vertex*> bfq;
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
            //cout<<v.name<<endl;
            vertices[i].visited = true;
            vertices[i].districtID = districtCounter;
            bfq.push(&vertices[i]);

            while (!bfq.empty())
            {
                v = *bfq.front();
                bfq.pop();
                for(i=0;i<v.adj.size();i++) {
                    if (v.adj[i].v->visited==false)
                    {
                        v.adj[i].v->visited = true;
                        v.adj[i].v->districtID = districtCounter;
                        bfq.push(v.adj[i].v);
                        //cout<<v.adj[i].v->name<<endl;
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

vertex* Travel::findNearestAirport(std::string startingCity)
{
    vertex* airportCity;


    int startIndex;
    //Find district ID of city
    for(int i =0; i < vertices.size();i++)
    {
        if(startingCity == vertices[i].name)
        {
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

int Travel::travelBetweenDistricts(std::string starting, std::string destination)
{
    vertex* start;
    vertex* dest;

    vector <vertex*> solved;

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


    solved.push_back(start);
    int minDistance;


    while(dest->visited == false)
    {
        minDistance = INT_MAX;
        int distance = 0;
        vertex* minVert = NULL;
        vertex* minPrevious;

        for(int j = 0; j < solved.size(); j++)
        {
            solved[j]->visited = true;

            for( int l = 0; l < solved[j]->adj.size(); l++)
            {
                if(solved[j]->adj[l].v->visited == false)
                {
                    distance = solved[j]->distance + solved[j]->adj[l].weight;
                    if(distance < minDistance)
                    {
                        solved[j]->adj[l].v->distance = distance;

                        minDistance = distance;
                        minVert = solved[j]->adj[l].v;
                        minPrevious = solved[j];
                    }
                }
            }
        }

        minVert->previous = minPrevious;
        solved.push_back(minVert);

    }
    vector <string> path;
    vertex* x = dest;

    while(x != NULL)
    {
        path.push_back(x->name);
        x = x->previous;
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
