#ifndef ROBOTS_H
#define ROBOTS_H

#include "RobotList.h"
#include "RobotQueue.h"
#include "Map.h"
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <memory>
#include <sstream>
using namespace std;

class Map;

class Robot
{
protected:
    bool alive; //to see if robot is alive
    char robotInitial;
    int killCount, X, Y;
    string robotType, robotName;
    static Map* map; //all robots share one map
public:
    int deathCount;
    virtual void turn(ostream& COUT) = 0; //pure virtual function
    Robot(string& x, string& y, char& initial, string& name); //constructor w parameters
    Robot(int x, int y, char& initial, string& name); //constructor w parameters(doesnt put in map)
    Robot(const Robot& other); //copy constructor 
    Robot() { } //default constructor
    ~Robot() { } //destructor
    static void setMap(Map* Map); //set static map
    int getKills();
    int getDeaths();
    char getInitial();
    string getType();
    int getX();
    int getY();
    string getName();
    void revive(ostream& COUT); //revive the robot, put in rand location
    bool checkStatus(); //check if alive
    void incrementDeath(); 
};


class MovingRobot : virtual public Robot 
{
public:
    MovingRobot() { }
    MovingRobot(const Robot& other) : Robot(other) { }
    virtual void move(ostream& COUT) = 0;
    virtual void turn(ostream& COUT) = 0;
};

class SeeingRobot : virtual public Robot 
{
public:
    SeeingRobot() { }
    SeeingRobot(const Robot& other) : Robot(other) { }
    virtual bool look(int& newX, int& newY) = 0;
    virtual void turn(ostream& COUT) = 0;
};

class SteppingRobot : virtual public Robot 
{
public:
    SteppingRobot() { }
    SteppingRobot(const Robot& other) : Robot(other) { }
    virtual void step(int& newX, int& newY, ostream& COUT) = 0;
    virtual void turn(ostream& COUT) = 0;
};

class ShootingRobot : virtual public Robot 
{
public:
    ShootingRobot() { }
    ShootingRobot(const Robot& other) : Robot(other) { }
    virtual void fire(ostream& COUT) = 0;
    virtual void turn(ostream& COUT) = 0;
};

#endif