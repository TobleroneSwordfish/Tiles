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
	void Render(); //print to screen
	void Advance(); //run all the updates
	void Save(const char *path); //save to file with name path (yeah I know, I was tired), does not include file extension
	void Load(const char *path); //load in same way
private:
	Tile *grid[xLimit + 1][yLimit + 1];
};
