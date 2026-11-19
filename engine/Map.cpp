#include "Map.h"

void Map::displayBattlefield()
{
    cout << "   ";
    for (int i = 0; i < N; i++)
    {
        cout << setw(2) << setfill('0');
        cout << i << ' ';
    }
    cout << endl;

    for (int i = 0; i < M; ++i)
    {
        cout << setw(2) << setfill('0');
        cout << i << " ";
        for (int j = 0; j < N; ++j)
        {
            cout << ' ' << battlefield[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

Map::Map(int m, int n)
{
    //dynamically allocate memory and initialize to 0
    M = m;
    N = n;
    battlefield = new char*[M];
    for (int i = 0; i < M; i++)
        battlefield[i] = new char[N];

    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            battlefield[i][j] = '.';
        }
    }
}

bool Map::withinBattlefield(int X, int Y) //bounds checking 
{
    if (X < 0 || X >= M || Y < 0 || Y >= N)
        return false;
    else
        return true;
}

bool Map::robotPresent(int X, int Y)
{
    if (withinBattlefield(X, Y) == true && battlefield[X][Y] !='.') 
        return true;
    else
        return false;
}

Map::~Map()
{
    //delete dynamically allocated memory for battlefield
    for (int i = 0; i < M; ++i)
    {
        delete[] battlefield[i];
    }      
    delete[] battlefield;
}

ostream& operator<<(ostream& COUT, Map*& map) //to output to console and output file
{
    COUT << "   ";
    for (int i = 0; i < map->N; i++)
    {
        COUT << setw(2) << setfill('0');
        COUT << i << ' ';
    }
    COUT << endl;

    for (int i = 0; i < map->M; ++i)
    {
        COUT << setw(2) << setfill('0');
        COUT << i << " ";
        for (int j = 0; j < map->N; ++j)
        {
            COUT << ' ' << map->battlefield[i][j] << ' ';
        }
        COUT << endl;
    }
    COUT << endl;
    return COUT;
}
