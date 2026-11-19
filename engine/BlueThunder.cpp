#include "BlueThunder.h"
#include "Map.h"

void BlueThunder::turn(ostream& COUT)
{
    cout << robotName << " - " << robotInitial << " (" << robotType << "):" << endl;
    COUT << robotName << " - " << robotInitial << " (" << robotType << "):" << endl;
    fire(COUT);
}

void BlueThunder::fire(ostream& COUT)
{
    int fireX[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
    int fireY[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
    int targetX = X + fireX[index];
    int targetY = Y + fireY[index];

    if (map->withinBattlefield(targetX, targetY))
    {
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
    index = (index + 1) % 8; // move to the next direction, loop the 8 cells
}

