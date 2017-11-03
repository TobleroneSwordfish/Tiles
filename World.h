#pragma once
#include "Tiles.h"
class Tile;
class World
{
public:
	World();
	~World();
	Tile *GetTile(int x, int y);
	void SetTile(int x, int y, Tile *newTile);
	const static int xLimit = 20, yLimit = 20;
	void Render();
	void Advance();
private:
	Tile *grid[xLimit + 1][yLimit + 1];
};
