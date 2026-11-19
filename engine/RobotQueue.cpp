#include "RobotQueue.h"
#include "Sentinel.h"
#include "PrimeSentinel.h"
#include "RoboCop.h"
#include "Terminator.h"
#include "TerminatorRoboCop.h"
#include "BlueThunder.h"
#include "Madbot.h"
#include "RoboTank.h"
#include "UltimateRobot.h"

shared_ptr<Robot> cloneRobot(int X, int Y, string name, string type)
{
    //cout << "Creating " << type << " of name " << name << " at " << X << " x " << Y <<
    //" with initial " << initial << endl;
    char initial = name[0];
    shared_ptr<Robot> robot;
    if (type == "RoboCop")
    {
        robot = make_shared<RoboCop>(X, Y, initial, name);
    }
    else if (type == "Terminator")
    {
        robot = make_shared<Terminator>(X, Y, initial, name);
    }
    else if (type == "T-RoboCop")
    {
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
        cout << "Unable to make a clone. The may be a robot type that has been mispelt. Please recheck and rerun the program." << endl;
        exit(1);
    }

    return robot;
}



RobotQueue::RobotQueue() //default constructor
{
    first = 0;
    last = 0;
    size = 0;
    R = 52; //52 possible robots in one game
    robots = new shared_ptr<Robot>[R];
}

RobotQueue::RobotQueue(int r) //constructor with parameter
{
    first = 0;
    last = 0;
    size = 0;
    R = r;
    robots = new shared_ptr<Robot>[R];
}

// copy constructor
RobotQueue::RobotQueue(const RobotQueue& copy)
{
    first = copy.first;
    last = copy.last;
    R = copy.R;
    size = copy.size;
    robots = new shared_ptr<Robot>[R];
    for (int i = 0; i < size; i++) {
        int index = (copy.first + i) % R; //circular queue
        int X = copy.robots[index]->getX();
        int Y = copy.robots[index]->getY();
        string name = copy.robots[index]->getName();
        string type = copy.robots[index]->getType();
        robots[index] = cloneRobot(X, Y, name, type);
    }
}

// overloaded assignment operator
RobotQueue& RobotQueue::operator=(const RobotQueue& operand)
{
    if (this != &operand) 
    {
        first = operand.first;
        last = operand.last;
        R = operand.R;
        size = operand.size;
        robots = new shared_ptr<Robot>[R];
        for (int i = 0; i < size; i++) {
            int index = (operand.first + i) % R; //circular queue
            int X = operand.robots[index]->getX();
            int Y = operand.robots[index]->getY();
            string name = operand.robots[index]->getName();
            string type = operand.robots[index]->getType();
            robots[index] = cloneRobot(X, Y, name, type);
        }
    }
    return *this;
}

bool RobotQueue::isEmpty() const {
    return size == 0;
}

bool RobotQueue::isFull() const {
    return size == R;
}

bool RobotQueue::enqueue(shared_ptr<Robot>& robot) {
    if (isInQueue(robot)) 
    {
        //cout << robot->getName() << " is already in the queue." << endl;
        return false;
    }
    if (isFull()) 
    {
        cout << "Queue is full" << endl;
        return false;
    }
    if (robot->deathCount >= 2)
    {
        //cout << robot->getName() << " won't enter queue as it's died thrice" << endl;
        robot->incrementDeath();
        return false;
    }
    else
    {
        robots[last] = robot;
        last = (last + 1) % R;
        size++;
        return true;
    }
}

void RobotQueue::dequeue(ostream& COUT) 
{
    if (isEmpty()) 
    {
        return;
    }
    robots[first]->revive(COUT);
    first = (first + 1) % R;
    size--;
}

bool RobotQueue::isInQueue(const shared_ptr<Robot>& robot) const {
    for (int i = 0; i < size; i++) {
        int index = (first + i) % R;
        if (robots[index] == robot) {
            return true;
        }
    }
    return false;
}

vector<string> RobotQueue::getNames() const {
    vector<string> names;
    for (int i = 0; i < size; i++) {
        int index = (first + i) % R;
        names.push_back(robots[index]->getName());
    }
    return names;
}

void RobotQueue::display(ostream& COUT) const {
    COUT << "Queue: ";
    for (int i = 0; i < size; i++) {
        int index = (first + i) % R;
        COUT << robots[index]->getName() << " ";
    }
    COUT << endl << endl;
}
