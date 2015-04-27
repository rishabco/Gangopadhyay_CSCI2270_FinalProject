
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
    }
}


void Travel::printPlanePaths()
{

}

void Travel::printDistricts()
{

}

void Travel::printCities()
{

}

int Travel::calculateCost(string starting, string destination)
{

}

int Travel::calculateTime(string starting, string destination)
{
//    cout << travelDistance << endl;
}

void Travel::shortestDistance(std::string starting, std::string destination)
{

}

void Travel::findDistricts() //Based on isAirport BOOl
{


}

