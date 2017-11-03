#include "World.h"
class World
{
	const static int xLimit = 50, yLimit = 50;
	char grid[xLimit][yLimit];
	Tile *GetTile(int x, int y)
	{
		return grid[x][y];
	}
};