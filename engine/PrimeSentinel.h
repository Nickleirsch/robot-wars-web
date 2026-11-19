#ifndef PRIMESENTINEL_H
#define PRIMESENTINEL_H

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
#include "Sentinel.h"

class PrimeSentinel : public Sentinel, public SteppingRobot
{
   public:
    PrimeSentinel(string& x, string& y, char& initial, string& name) : Robot(x, y, initial, name)
    { robotType = "PrimeSentinel"; }
    PrimeSentinel(int x, int y, char& initial, string& name) : Robot(x, y, initial, name)
    { robotType = "PrimeSentinel"; }
    PrimeSentinel(const Robot& other) : Robot(other)
    { robotType = "PrimeSentinel"; }
    PrimeSentinel() { }
    void turn(ostream& COUT) override;
    void move(ostream& COUT) override;
    void fire(ostream& COUT) override;
    void step(int& newX, int& newY, ostream& COUT) override;
};

#endif