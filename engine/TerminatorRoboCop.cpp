#include "TerminatorRoboCop.h"
#include "Map.h"

void TerminatorRoboCop::turn(ostream& COUT)
{
    cout << robotName << " - " << robotInitial << " (" << robotType << "):" << endl;
    COUT << robotName << " - " << robotInitial << " (" << robotType << "):" << endl;
    move(COUT);
    fire(COUT);
    fire(COUT);
    fire(COUT);
}

void TerminatorRoboCop::fire(ostream& COUT)
{
    int targetX, targetY;
    do
    {
        targetX = rand() % map->M;
        targetY = rand() % map->N;
    } while (targetX + targetY > 10);

    if (map->battlefield[targetX][targetY] == '.')
    {
        cout << "Fired at " << targetX << " x " << targetY << " but missed." << endl;
        COUT << "Fired at " << targetX << " x " << targetY << " but missed." << endl;
        return;
    }
    else
    {
        cout << "Fired at " << targetX << " x " << targetY << " killing " << map->battlefield[targetX][targetY] << endl;
        COUT << "Fired at " << targetX << " x " << targetY << " killing " << map->battlefield[targetX][targetY] << endl;
        map->battlefield[targetX][targetY] = '.'; // Indicate hit
        killCount = killCount + 1;
    }
}

bool TerminatorRoboCop::look(int& newX, int& newY)
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

void TerminatorRoboCop::move(ostream& COUT)
{
    int newX, newY;
    if (look(newX, newY) == true)
    { 
    step(newX, newY, COUT);  
    }
    else 
    { 
        int moveX[8] = { 1, 1, 1, 0, 0, -1, -1, -1 };
        int moveY[8] = { 1, 0, -1, 1, -1, 1, 0, -1 };
        do
        {
            int index = rand() % 8;
            newX = X + moveX[index];
            newY = Y + moveY[index];
        } while (map->robotPresent(newX, newY) == true || map->withinBattlefield(newX, newY) == false); 

        map->battlefield[newX][newY] = map->battlefield[X][Y];
        map->battlefield[X][Y] = '.';
        X = newX;
        Y = newY;
        cout << "Moved to " << X << " x " << Y << endl;
        COUT << "Moved to " << X << " x " << Y << endl;
    }
}

void TerminatorRoboCop::step(int& newX, int& newY, ostream& COUT)
{
    cout << "Stepped on " << map->battlefield[newX][newY] << " at "<< newX << " x " << newY << endl;
    COUT << "Stepped on " << map->battlefield[newX][newY] << " at "<< newX << " x " << newY << endl;
    map->battlefield[newX][newY] = map->battlefield[X][Y];
    map->battlefield[X][Y] = '.';
    X = newX;
    Y = newY;
    killCount = killCount + 1;
}
