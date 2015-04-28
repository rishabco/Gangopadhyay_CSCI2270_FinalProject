#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "Travel.h"

using namespace std;

//Initial menu
void welcomeMenu()
{
    cout << "------------------------------" << endl;
    cout << "Welcome to Travel Planner" << endl;
    cout << "------------------------------" << endl;
    cout << "To Begin, ";
}


//Function to simplify printing the menu out each time
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

//main loop
int main()
{

    vector <string> cities;
    Travel* tGraph = new Travel;

    //Read in file
    //string fileName = argc[1];  //If ever need to convert to take in command line arguments
    string fileName = "cities.txt";
    ifstream fn;
    fn.open(fileName);
    if (!fn)
    {
        cout << "Could not open file\n";
    }


    //Read in line to a vector
    string line;
    int lineCount = 0;

    while(getline(fn, line))
    {
        stringstream ss(line);
        vector <string> data;
        int vectIndex = 0;

        //Use string stream to add individual info to the vector
        while(ss.good())
        {
            string info;
            getline(ss, info, ',');
            data.push_back(info);
            vectIndex++;

        }
            //Read in first line.
            //First line has names of cities
            if(lineCount == 0)
            {
                cities = data;
                for(int i  = 1; i < cities.size(); i++)
                {
                    //Add the cities to the graph
                    tGraph->addCity(cities[i]);
                    tGraph->addHub(cities[i]);
                }

            }
            else
            {
                string currentCity = data[0];
                for(int i = 1; i < cities.size(); i++)
                {
                    //Check if there is a connection
                    if(stoi(data[i]) != -1)
                    {
                        if(stoi(data[i])<=1000)
                        {
                            //If distance is less than 1000 miles points can be reached by car
                            tGraph->addRoad(currentCity, cities[i], stoi(data[i]));
                        }
                        else
                        {
                            //If distance is greater than 1000 miles an airplane is required to reach it
                            tGraph->addPlanePath(currentCity, cities[i], stoi(data[i]));
                        }

                    }

                }

            }
            //Increase the line count.
            lineCount++;
        }

    //Close the file
    fn.close();

    //Establish the districts
    tGraph->findDistricts();

    string input;
    welcomeMenu();

    string startCity;
    string destCity;

    //main loop
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

                //Get starting city and destination information
                cout << "Please enter a starting city" << endl;
                getline(cin, startCity);
                cout << "Please enter a destination" << endl;
                getline(cin, destCity);

                cout << endl;
                cout << "Travel Summary" << endl;
                cout << "------------------------------" << endl;
                int distanceTraveled = tGraph->shortestDistance(startCity, destCity);
                //Call of function prints out path
                //Print out total distance traveled
                cout << "The total distance of your trip is: ";
                cout <<  distanceTraveled << " miles." << endl;
                cout << "------------------------------" << endl<<endl;



        }
        else if(input =="5")
        {
            //Ending message
            cout << "Thank you, enjoy your trip!" << endl;
        }
        else
        {
            cout << "Invalid Input" <<endl;
        }


    }


}
