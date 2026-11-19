#ifndef MADBOT_H
#define MADBOT_H

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
#include "BlueThunder.h"

class Madbot : public BlueThunder
{
public:
    Madbot(string& x, string& y, char& initial, string& name) : Robot(x, y, initial, name)
    { robotType = "Madbot"; }
    Madbot(int x, int y, char& initial, string& name) : Robot(x, y, initial, name)
    { robotType = "Madbot"; }
    Madbot(const Robot& other) : Robot(other)
    { robotType = "Madbot"; }
    Madbot() { }
   void turn(ostream& COUT) override;
   void fire(ostream& COUT) override;
};

#endif