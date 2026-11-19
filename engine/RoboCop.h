#ifndef ROBOCOP_H
#define ROBOCOP_H

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

class RoboCop : public MovingRobot, public ShootingRobot, public SeeingRobot
{
public:
    RoboCop(string& x, string& y, char& initial, string& name) : Robot(x, y, initial, name)
    { robotType = "RoboCop"; }
    RoboCop(int x, int y, char& initial, string& name) : Robot(x, y, initial, name)
    { robotType = "RoboCop"; }
    RoboCop(const Robot& other) : Robot(other)
    { robotType = "RoboCop"; }
    RoboCop() { }
    void turn(ostream& COUT) override;
    void fire(ostream& COUT) override;
    bool look(int& newX, int& newY) override;
    void move(ostream& COUT) override;
};

#endif