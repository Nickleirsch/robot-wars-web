#ifndef ROBOTANK_H
#define ROBOTANK_H

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
#include "Madbot.h"

class RoboTank : public Madbot
{
public:
    RoboTank(string& x, string& y, char& initial, string& name) : Robot(x, y, initial, name)
    { robotType = "RoboTank"; }
    RoboTank(int x, int y, char& initial, string& name) : Robot(x, y, initial, name)
    { robotType = "RoboTank"; }
    RoboTank(const Robot& other) : Robot(other)
    { robotType = "RoboTank"; }
    RoboTank() { }
    void turn(ostream& COUT) override;
    void fire(ostream& COUT) override;
};

#endif