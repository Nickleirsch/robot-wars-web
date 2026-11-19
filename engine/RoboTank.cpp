#include "RoboTank.h"
#include "Map.h"

void RoboTank::turn(ostream& COUT)
{
    cout << robotName << " - " << robotInitial << " (" << robotType << "):" << endl;
    COUT << robotName << " - " << robotInitial << " (" << robotType << "):" << endl;
    fire(COUT);
}

void RoboTank::fire(ostream& COUT)  //random firing
{
    int targetX, targetY;
    do
    {
        targetX = rand() % map->M;
        targetY = rand() % map->N;
    } while(targetX == X && targetY == Y);

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
