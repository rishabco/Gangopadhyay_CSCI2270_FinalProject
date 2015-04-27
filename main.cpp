#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "Travel.h"

using namespace std;

void welcomeMenu()
{
    cout << "------------------------------" << endl;
    cout << "Welcome to Travel Planner" << endl;
    cout << "------------------------------" << endl;
    cout << "To Begin, ";
}

void plannerMenu()
{
    cout << "" << endl;
    cout << "   Please make a selection" << endl;
    cout << "   1. Plan fastest route" << endl;
    cout << "   2. Plan cheapest route" << endl;

}

void printMenu()
{
    cout <<  "Please Make A Selection" << endl;
    cout << "------------------------------" << endl;
    cout << "1. Print All City Options" << endl;
    cout << "2. View Options for Ground Travel" << endl;
    cout << "3. View Options for Air Travel" << endl;
    cout << "4. Begin Planning Trip" << endl;
    cout << "5. Quit" << endl;

}

int main()
{
vector <string> cities;
    Travel* tGraph = new Travel;

    //Read in file
    //string fileName = argc[1];
    string fileName = "cities.txt";
    ifstream fn;
    fn.open(fileName);
    if (!fn)
    {
        cout << "Could not open file\n";
    }


    //read in the thing to the vector
    string line;
    int lineCount = 0;

    while(getline(fn, line))
    {
        stringstream ss(line);
        vector <string> data;
        int vectIndex = 0;


        while(ss.good())
        {
            string info;
            getline(ss, info, ',');
            data.push_back(info);
            vectIndex++;

        }
            //Read in first line.
            if(lineCount == 0)
            {
                cities = data;
                for(int i  = 1; i < cities.size(); i++)
                {

                    tGraph->addCity(cities[i]);
                    tGraph->addHub(cities[i]);
                }

            }
            else
            {
                string currentCity = data[0];
                for(int i = 1; i < cities.size(); i++)
                {
                    if(stoi(data[i]) != -1)
                    {
                        if(stoi(data[i])<=1000)
                        {
                            tGraph->addRoad(currentCity, cities[i], stoi(data[i]));
                        }
                        else
                        {
                            //tGraph->addHub(currentCity);
                            tGraph->addPlanePath(currentCity, cities[i], stoi(data[i]));
                        }

                    }

                }

            }
            lineCount++;
        }

    fn.close();

    tGraph->findDistricts();

    string input;
    welcomeMenu();

    string startCity;
    string destCity;

    while(input != "5")
    {
        printMenu();
        getline(cin, input);

        //Print Cities
        if(input=="1"){
            cout << "These are the cities currently available:" << endl << endl;
            tGraph->printCities();
            cout << endl;

        }
        //Ground Travel Options
        else if(input=="2")
        {
            cout << endl;
            cout << "You can travel on ground within each Travel District. ";
            cout << "Here are all Ground Travel Districts in your Network: " << endl;
            tGraph->printDistricts();
            cout << endl;
        }
        //Air Travel Options
        else if(input=="3")
        {
            cout << endl;
            cout << "You can travel between districts via Plane. ";
            cout << "Here are all airports in your District" << endl;
            tGraph->printPlanePaths();
            cout << endl;

        }
        //Plan Trip
        else if(input=="4")
        {

            plannerMenu();


            //Plan Fastest Route
            //Plan Cheapest Route

        }
        else if(input =="5")
        {
            cout << "Thank you, enjoy your trip!" << endl;
        }
        else
        {
            cout << "Invalid Input" <<endl;
        }
    }


}

