#include "Robots.h"

Map* Robot::map = nullptr;

Robot::Robot(string& x, string& y, char& initial, string& name)
{
    if (x != "random")
        X = stoi(x);
    else
        X = rand() % map->M;

    if (y != "random")
        Y = stoi(y);
    else
        Y = rand() % map->N;

    while (map->robotPresent(X, Y))
    {
        X = rand() % map->M;
        Y = rand() % map->N;
    }
    robotInitial = initial;
    robotName = name;
    map->battlefield[X][Y] = robotInitial;
    deathCount = 0;
    killCount = 0;
}

Robot::Robot(int x, int y, char& initial, string& name)
{
    X = x;
    Y = y;
    robotInitial = initial;
    robotName = name;
    map->battlefield[X][Y] = robotInitial;
    deathCount = 0;
    killCount = 0;
}

Robot::Robot(const Robot& other)
{
    alive = other.alive;
    robotInitial = other.robotInitial;
    robotType = other.robotType;
    robotName = other.robotName;
    killCount = other.killCount;
    X = other.X;
    Y = other.Y;
}

int Robot::getKills() { return this->killCount; }
int Robot::getDeaths() { return this->deathCount; }

void Robot::setMap(Map* Map)
{
    map = Map;
}

char Robot::getInitial() { return robotInitial; }
string Robot::getType() { return robotType; }
int Robot::getX() { return X; }
int Robot::getY() { return Y; }
string Robot::getName() { return robotName; }

void Robot::incrementDeath()
{
    deathCount = deathCount + 1;
}

void Robot::revive(ostream& COUT)
{
    do
    {
        X = rand() % map->M;
        Y = rand() % map->N;
    }while(map->robotPresent(X, Y));
    map->battlefield[X][Y] = robotInitial;
    cout << robotName << " - " << robotInitial << " (" << robotType << ") " << "is being revived at " << X << " x " << Y << endl << endl;
    COUT << robotName << " - " << robotInitial << " (" << robotType << ") " << "is being revived at " << X << " x " << Y << endl << endl;
}

bool Robot::checkStatus()
{
    if (map->battlefield[X][Y] == robotInitial)
        return true;
    else
    {
        return false;
    }
}

