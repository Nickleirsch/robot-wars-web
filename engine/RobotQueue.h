#ifndef ROBOTQUEUE_H
#define ROBOTQUEUE_H

#include "Robots.h"
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <memory>
#include <sstream>
#include <vector>
using namespace std;

class Robot;

shared_ptr<Robot> cloneRobot(int X, int Y, string name, string type);

class RobotQueue
{
private: 
    int first;
    int last;
    shared_ptr<Robot>* robots; //array
    int R; //number of robots
    int size;
public:
    RobotQueue(); //default constructor
    RobotQueue(int r); //constructor with parameter
    RobotQueue(const RobotQueue& copy);  //copy constructor
    RobotQueue& operator=(const RobotQueue& operand); //assignment operator
    ~RobotQueue() { } //destructor
    bool isEmpty() const;
    bool isFull() const;
    bool enqueue(shared_ptr<Robot>& robot);
    void dequeue(ostream& COUT);
    bool isInQueue(const shared_ptr<Robot>& robot) const;
    void display(ostream& COUT) const;
    vector<string> getNames() const; //queue contents in order, for the web view
};

#endif