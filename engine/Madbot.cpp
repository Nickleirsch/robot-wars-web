#include "Madbot.h"
#include "Map.h"

void Madbot::turn(ostream& COUT)
{
    cout << robotName << " - " << robotInitial << " (" << robotType << "):" << endl;
    COUT << robotName << " - " << robotInitial << " (" << robotType << "):" << endl;
    fire(COUT);
}

void Madbot::fire(ostream& COUT)  //random firing
{
    int fireX[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
    int fireY[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
    int targetX, targetY, index;
    do
    {
    index = rand() % 8;
    targetX = X + fireX[index];
    targetY = Y + fireY[index];
    } while (map->withinBattlefield(targetX, targetY) == false);

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