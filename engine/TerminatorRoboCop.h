#ifndef TERMINATORROBOCOP_H
#define TERMINATORROBOCOP_H

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
#include "RoboCop.h"
#include "Terminator.h"

class TerminatorRoboCop : public RoboCop, public Terminator
{
public:
    TerminatorRoboCop(string& x, string& y, char& initial, string& name) : Robot(x, y, initial, name)
    { robotType = "T-RoboCop"; }
    TerminatorRoboCop(int x, int y, char& initial, string& name) : Robot(x, y, initial, name)
    { robotType = "T-RoboCop"; }
    TerminatorRoboCop(const Robot& other) : Robot(other)
    { robotType = "T-RoboCop"; }
    TerminatorRoboCop() { }
    void turn(ostream& COUT) override;
    void fire(ostream& COUT) override;
    bool look(int& newX, int& newY) override;
    void move(ostream& COUT) override;
    void step(int& newX, int& newY, ostream& COUT) override;
};

#endif