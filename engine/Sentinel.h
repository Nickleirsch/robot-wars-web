#ifndef SENTINEL_H
#define SENTINEL_H

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

class Sentinel : public MovingRobot, public ShootingRobot
{
public:
    Sentinel(string& x, string& y, char& initial, string& name) : Robot(x, y, initial, name)
    { robotType = "Sentinel"; }
    Sentinel(int x, int y, char& initial, string& name) : Robot(x, y, initial, name)
    { robotType = "Sentinel"; }
    Sentinel(const Robot& other) : Robot(other)
    { robotType = "Sentinel"; }
    Sentinel() { }
    void turn(ostream& COUT) override;
    void move(ostream& COUT) override;
    void fire(ostream& COUT) override;
};

#endif