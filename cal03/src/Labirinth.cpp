/*
 * labirinth.cpp
 */

#include "Labirinth.h"

#include <iostream>
using namespace std;



Labirinth::Labirinth(int values[10][10])
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			labirinth[i][j]=values[i][j];
}


void Labirinth::initializeVisited(int x, int y)
{
	for (int i = 0; i < 10; i++)
		for (int a = 0; a < 10; a++)
			visited[i][a] = false;
	visited[y][x] = true;
}




void  Labirinth::printLabirinth()
{
	for (int i = 0; i < 10; i++)
	{
		for (int a = 0; a < 10; a++)
			cout << labirinth[i][a] << " ";

		cout << endl;
	}
}


bool Labirinth::findGoal(int x, int y)
{

    initializeVisited(x, y);

    if (carve(x,y)) {

        cout << "Encontrou a solucao!\n";
        return true;
    }
    else {

        cout << "Nao tem solucao!\n";
        return false;
    }
}


bool Labirinth::carve (int x, int y) {

    if (foundTheSolution)
        return false;

    visited[y][x] = true;

    if (labirinth[y][x] == 2) {
        return true;
        foundTheSolution = true;
    }
    else if (labirinth[y][x] == 0)
        return false;

    labirinth[y][x] = 5;


    if (x > 0 && !visited[y][x-1] && carve(x-1, y))                     // go left
        return true;
    else if (x < 9 && !visited[y][x+1] && carve(x+1, y))                // go right
        return true;
    else if (y > 0 && !visited[y-1][x] && carve(x, y-1))                // go up
        return true;
    else if (y < 9 && !visited[y+1][x] && carve(x, y+1))                // go down
        return true;

    return false;
}
