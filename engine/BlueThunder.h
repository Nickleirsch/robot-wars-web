#ifndef BLUETHUNDER_H
#define BLUETHUNDER_H

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

class BlueThunder : public ShootingRobot
{
private:
    int index; //index to keep track of which position its firing
public:
    BlueThunder(string& x, string& y, char& initial, string& name) : Robot(x, y, initial, name)
    { robotType = "BlueThunder"; index = 0; } //start facing up, per spec
    BlueThunder(int x, int y, char& initial, string& name) : Robot(x, y, initial, name)
    { robotType = "BlueThunder"; index = 0; } //start facing up, per spec
    BlueThunder(const Robot& other) : Robot(other)
    { robotType = "BlueThunder"; index = 0; } //start facing up, per spec
    BlueThunder() { }
   void turn(ostream& COUT) override;
   void fire(ostream& COUT) override;
};

#endif