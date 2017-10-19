#pragma once
#include "Tiles.h"
class World
{
public:
	World();
	~World();
	Tile *GetTile(int x, int y);
	const static int xLimit = 50, yLimit = 50;
private:
	char grid[xLimit][yLimit];
};