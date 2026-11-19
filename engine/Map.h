#ifndef MAP_H
#define MAP_H

#include "RobotList.h"
#include "RobotQueue.h"
#include "Robots.h"
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <memory>
#include <sstream>
using namespace std;

class Map
{
public:
    int M, N;
    char** battlefield;

    void displayBattlefield();
    Map(int m, int n);
    bool withinBattlefield(int X, int Y);
    bool robotPresent(int X, int Y);
    ~Map();
    friend ostream& operator<<(ostream& COUT, Map& map);
};
//note that everything in the class being public is not an oversight
//the map class was originally a structure but changed to a class to better reflect the criteria of the assignment

ostream& operator<<(ostream& COUT, Map*& map);

#endif