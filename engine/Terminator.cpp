#include "Terminator.h"
#include "Map.h"

void Terminator::turn(ostream& COUT)
{
    cout << robotName << " - " << robotInitial << " (" << robotType << "):" << endl;
    COUT << robotName << " - " << robotInitial << " (" << robotType << "):" << endl;
    move(COUT);
}

void Terminator::move(ostream& COUT)
{
    int moveX[8] = { 1, 1, 1, 0, 0, -1, -1, -1 };
    int moveY[8] = { 1, 0, -1, 1, -1, 1, 0, -1 };
    int newX, newY;
    if (look(newX, newY) == false) //no robots
    {
        do
        {
            int index = rand() % 8;
            newX = X + moveX[index];
            newY = Y + moveY[index];
        } while (map->robotPresent(newX, newY) == true || map->withinBattlefield(newX, newY) == false); //change the condition

        map->battlefield[newX][newY] = map->battlefield[X][Y];
        map->battlefield[X][Y] = '.';
        X = newX;
        Y = newY;
        cout << "Moved to " << X << " x " << Y << endl;
        COUT << "Moved to " << X << " x " << Y << endl;
    }

    else if (look(newX, newY) == true) //got robot, and position in newX and newY
        step(newX, newY, COUT);

    return;
}

bool Terminator::look(int& newX, int& newY)
{
    int lookX[8] = { 1, 1, 1, 0, 0, -1, -1, -1 };
    int lookY[8] = { 1, 0, -1, 1, -1, 1, 0, -1 };
    int enemyX, enemyY;

    for (int index = 0; index < 8; ++index)
    {
        enemyX = X + lookX[index];
        enemyY = Y + lookY[index];
        if (map->robotPresent(enemyX, enemyY))
        {
            newX = enemyX;
            newY = enemyY;
            return true;
        }
    }
    return false;
}

void Terminator::step(int& newX, int& newY, ostream& COUT)
{
    cout << "Stepped on " << map->battlefield[newX][newY] << " at "<< newX << " x " << newY << endl;
    COUT << "Stepped on " << map->battlefield[newX][newY] << " at "<< newX << " x " << newY << endl;
    map->battlefield[newX][newY] = map->battlefield[X][Y];
    map->battlefield[X][Y] = '.';
    X = newX;
    Y = newY;
    killCount = killCount + 1;
}
