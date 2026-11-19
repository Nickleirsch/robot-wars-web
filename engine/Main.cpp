#include "RobotList.h"
#include "RobotQueue.h"
#include "Robots.h"
#include "Map.h"
#include "Sentinel.h"
#include "PrimeSentinel.h"
#include "RoboCop.h"
#include "Terminator.h"
#include "TerminatorRoboCop.h"
#include "BlueThunder.h"
#include "Madbot.h"
#include "RoboTank.h"
#include "UltimateRobot.h"

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <memory>
#include <sstream>
using namespace std;

shared_ptr<Robot> interpretLine(string& type, string name, string X, string Y, char initial);

int main()
{
    srand(time(0)); //seed rand generator
    string m, n, t, r, filename; 
    cout << "Enter the filename you want the simulator to access: " << endl;
    cin >> filename;
    ifstream txtFile(filename);

    if (!txtFile.is_open())
    {
        cout << "Error opening the .txt file" << endl;
        exit(1);
    }

    //first Line, matrix dimensions
    string matrixLine;
    getline(txtFile, matrixLine);
    matrixLine.erase(0,9);
    //now matrix has string "M N"
    istringstream MatrixString(matrixLine);
    MatrixString >> m >> n;

    Map* map = new Map(stoi(m), stoi(n));
    Robot::setMap(map); //set the map for all the robots

    //second line, steps
    string stepsLine;
    getline(txtFile, stepsLine);
    stepsLine.erase(0,7);
    istringstream StepsString(stepsLine);
    StepsString >> t;

    //third line, robots
    string robotsLine;
    getline(txtFile, robotsLine);
    robotsLine.erase(0,8);
    istringstream RobotsString(robotsLine);
    RobotsString >> r;

    RobotList list;
    RobotQueue queue;

    string line, type, name, X, Y;
    for (int i = 0; i < stoi(r); i++) //for whatever amount of robots
    {
        getline(txtFile, line);
        istringstream PlayersString(line);
        PlayersString >> type >> name >> X >> Y;
        shared_ptr<Robot> robot = interpretLine(type, name, X, Y, name[0]); 
        //interpret line creates a shared ptr of a robot that matches the type
        list.insert(robot); //that robot is then inserted into the list
    }
    txtFile.close();

    ofstream outFile("battlefield.txt");
    if (!outFile.is_open())
    {
        cout << "Error opening the output .txt file" << endl;
        exit(1);
    }

    outFile << "Initial battlefield" << endl;
    outFile << map;

    cout << "Initial battlefield" << endl;
    cout << map;

    for(int turn = 0; turn < stoi(t); turn++)
    {
        ofstream outFile("battlefield.txt", ios::app); //append the output file
        if (!outFile.is_open()) 
        {
            cout << "Error opening the output .txt file" << std::endl;
            exit(1);
        } 

        cout << "Turn " << turn + 1 << endl << endl;
        outFile << "Turn " << turn + 1 << endl << endl;
        
        //traverse calls the turns of each robot
        list.traverse(queue, outFile);
        cout << endl;
        outFile << endl;
        cout << map;
        outFile << map;
        //display the robots in the queue
        queue.display(cout);
        queue.display(outFile);
        //display the robots in the list
        list.displayList(cout);
        list.displayList(outFile);
        //display the stats of each robot
        list.displayStats(cout);
        list.displayStats(outFile);
        //dequeue a robot in the queue, if any are there
        queue.dequeue(outFile);

        if (list.getListSize() <= 1) //check if only one robot is left standing
        {
            break;
        }
    }

    outFile.close();
    delete map; //delete the map
    cout << "End of simulation" << endl;
    return 0;
}

shared_ptr<Robot> interpretLine(string& type, string name, string X, string Y, char initial)
{
        //cout << "Creating " << type << " of name " << name << " at " << X << " x " << Y <<
        //" with initial " << initial << endl;

        shared_ptr<Robot> robot;

        if (type == "RoboCop")
        {
            robot = make_shared<RoboCop>(X, Y, initial, name);
        }
        else if (type == "Terminator")
        {
            robot = make_shared<Terminator>(X, Y, initial, name);
        }
        else if (type == "TerminatorRoboCop")
        {
            type = "T-RoboCop"; //shorten the name for display purposes
            robot = make_shared<TerminatorRoboCop>(X, Y, initial, name);
        }
        else if (type == "BlueThunder")
        {
            robot = make_shared<BlueThunder>(X, Y, initial, name);
        }
        else if (type == "Madbot")
        {
            robot = make_shared<Madbot>(X, Y, initial, name);
        }
        else if (type == "RoboTank")
        {
            robot = make_shared<RoboTank>(X, Y, initial, name);
        }
        else if (type == "UltimateRobot")
        {
            robot = make_shared<UltimateRobot>(X, Y, initial, name);
        }
        else if (type == "Sentinel")
        {
            robot = make_shared<Sentinel>(X, Y, initial, name);
        }
        else if (type == "PrimeSentinel")
        {
            robot = make_shared<PrimeSentinel>(X, Y, initial, name);
        }
        else
        {
            cout << "The may be a robot type that has been mispelt. Please recheck and rerun the program." << endl;
            exit(1);
        }

    return robot;
}