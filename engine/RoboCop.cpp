#include "RoboCop.h"
#include "Map.h"

void RoboCop::turn(ostream& COUT)
{
    cout << robotName << " - " << robotInitial << " (" << robotType << "):" << endl;
    COUT << robotName << " - " << robotInitial << " (" << robotType << "):" << endl;
    move(COUT);
    fire(COUT);
    fire(COUT);
    fire(COUT);
}

void RoboCop::fire(ostream& COUT)
{
    int targetX, targetY;
    do
    {
        targetX = rand() % map->M;
        targetY = rand() % map->N;
    } while (targetX + targetY > 10 || (targetX == X && targetY == Y));

    if (map->battlefield[targetX][targetY] == '.')
    {
        cout << "Fired at " << targetX << " x " << targetY << " but missed." << endl;
        COUT << "Fired at " << targetX << " x " << targetY << " but missed." << endl;
        return;
        //cout << "RoboCop missed it's shot" << endl; //fired at an empty cell
    }
    else
    {
        cout << "Fired at " << targetX << " x " << targetY << " killing " << map->battlefield[targetX][targetY] << endl;
        COUT << "Fired at " << targetX << " x " << targetY << " killing " << map->battlefield[targetX][targetY] << endl;
        map->battlefield[targetX][targetY] = '.'; // indicate hit
        killCount = killCount + 1;
        return;
    }
        
}

bool RoboCop::look(int& newX, int& newY)
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
            newX = X - lookX[index];
            newY = Y - lookY[index];
            return true;
        }
    }
    return false;
}

void RoboCop::move(ostream& COUT)
{
    int newX, newY;
    int moveX[8] = { 1, 1, 1, 0, 0, -1, -1, -1 };
    int moveY[8] = { 1, 0, -1, 1, -1, 1, 0, -1 };
    if (look(newX, newY))
    {
        do
        {
            newX = X + moveX[rand() % 8];
            newY = Y + moveY[rand() % 8];
        } while (map->withinBattlefield(newX, newY) == false);

        map->battlefield[newX][newY] = map->battlefield[X][Y];
        map->battlefield[X][Y] = '.';
        X = newX;
        Y = newY;
    }
    else //no robot
    {
        do
        {
            newX = X + moveX[rand() % 8];
            newY = Y + moveY[rand() % 8];
        } while (map->robotPresent(newX, newY) == true || map->withinBattlefield(newX, newY) == false);

        map->battlefield[newX][newY] = map->battlefield[X][Y];
        map->battlefield[X][Y] = '.';
        X = newX;
        Y = newY;
    }

    cout << "Moved to " << X << " x " << Y << endl;
    COUT << "Moved to " << X << " x " << Y << endl;
}
