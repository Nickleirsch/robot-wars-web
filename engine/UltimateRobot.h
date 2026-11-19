#ifndef ULTIMATEROBOT_H
#define ULTIMATEROBOT_H

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <memory>
#include <sstream>
using namespace std;

#include "Robots.h"
#include "TerminatorRoboCop.h"
#include "RoboTank.h"

class UltimateRobot : public RoboTank, public TerminatorRoboCop
{
public:
    UltimateRobot(string& x, string& y, char& initial, string& name) : Robot(x, y, initial, name)
    { robotType = "UltimateRobot"; }
    UltimateRobot(int x, int y, char& initial, string& name) : Robot(x, y, initial, name)
    { robotType = "UltimateRobot"; }
    UltimateRobot(const Robot& other) : Robot(other)
    { robotType = "UltimateRobot"; }
    UltimateRobot() { }
    void turn(ostream& COUT) override;
    void fire(ostream& COUT) override;
    bool look(int& newX, int& newY) override;
    void move(ostream& COUT) override;
    void step(int& newX, int& newY, ostream& COUT) override;
};

#endif