#ifndef TERMINATOR_H
#define TERMINATOR_H

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

class Terminator : public MovingRobot, public SeeingRobot, public SteppingRobot
{
public:
    Terminator(string& x, string& y, char& initial, string& name) : Robot(x, y, initial, name)
    { robotType = "Terminator"; }
    Terminator(int x, int y, char& initial, string& name) : Robot(x, y, initial, name)
    { robotType = "Terminator"; }
    Terminator(const Robot& other) : Robot(other)
    { robotType = "Terminator"; }
   Terminator() { }

    void turn(ostream& COUT) override;
    void move(ostream& COUT) override;
    bool look(int& newX, int& newY) override;
    void step(int& newX, int& newY, ostream& COUT) override;
};

#endif