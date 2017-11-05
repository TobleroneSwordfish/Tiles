#pragma once
#include "Tiles.h"
class Tile;
class World
{
public:
	World();
	~World();
	int turn = 0;
	Tile *GetTile(int x, int y);
	void SetTile(int x, int y, Tile *newTile);
	const static int xLimit = 10, yLimit = 10;
	void Render();
	void Advance();
private:
	Tile *grid[xLimit + 1][yLimit + 1];
};
