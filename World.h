#pragma once
#include "Tiles.h"
#include <string>
class Tile;
class World
{
public:
	World();
	~World();
	int turn = 0;
	Tile *GetTile(int x, int y);
	void SetTile(int x, int y, Tile *newTile);
	void SetTile(int x, int y, ActiveTile *newActive);
	std::string InspectTile(int x, int y);
	const static int xLimit = 10, yLimit = 10;
	void Render();
	void Advance();
	void Save(char *path);
	void Load(char *path);
private:
	Tile *grid[xLimit + 1][yLimit + 1];
};
