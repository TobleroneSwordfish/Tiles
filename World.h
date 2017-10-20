#pragma once
#include "Tiles.h"
class World
{
public:
	World();
	~World();
	Tile *GetTile(int x, int y);
	void SetTile(int x, int y, Tile *newTile);
	const static int xLimit = 50, yLimit = 50;
	void Render();
private:
	Tile *grid[xLimit + 1][yLimit + 1];
};
