#ifndef ROBOTLIST_H
#define ROBOTLIST_H

#include "Robots.h"
#include "RobotQueue.h"
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
class RobotQueue;

struct Node 
{
    shared_ptr<Robot> robot; 
    shared_ptr<Node> next;
    Node() : robot(nullptr), next(nullptr) {}
    Node(shared_ptr<Robot>& r) : robot(r), next(nullptr) {}
};

class RobotList 
{
private:
   shared_ptr<Node> head; //ptr to the first node
   int size;
public:
    RobotList(); //default constructor
    RobotList(const RobotList& copy); // copy constructor
    RobotList& operator=(const RobotList& operand); // overloaded assignment operator
    ~RobotList() { } //destructor
    int getListSize();
    void insert(shared_ptr<Robot>& robot); //inserts a robot into the back of the list
    void remove(); //removes a robot if deaths = 3
    void traverse(RobotQueue& queue, ostream& COUT); //calls each robot's turn
    void upgrade(shared_ptr<Robot>& robot, ostream& COUT); //upgrades robot if kill count = 3
    void displayStats(ostream& COUT);
    void displayList(ostream& COUT);
    vector<shared_ptr<Robot>> getRobots() const; //read-only snapshot of the list, for the web view
};

#endif