#include "Sentinel.h"
#include "Map.h"

void Sentinel::turn(ostream& COUT)
{
    cout << robotName << " - " << robotInitial << " (" << robotType << "):" << endl;
    COUT << robotName << " - " << robotInitial << " (" << robotType << "):" << endl;
    move(COUT);
    fire(COUT);
    fire(COUT);
}

void Sentinel::move(ostream& COUT)
{
    int newX, newY;
    int moveX[8] = { 1, 1, 1, 0, 0, -1, -1, -1 };
    int moveY[8] = { 1, 0, -1, 1, -1, 1, 0, -1 };
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

void Sentinel::fire(ostream& COUT)  //random firing
{
    int targetX, targetY;
    do
    {
        //do
        //{
            targetX = rand() % map->M;
            targetY = rand() % map->N;
        //} while(targetX == X && targetY == Y);
    } while (targetX + targetY > 10 || (targetX == X && targetY == Y));

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
