#pragma once
#include "vector"

//base class for all tiles
class Tile
{
public:
	Tile();
	~Tile();
	int x, y;
	char symbol;
};

//tile with an update func, basically one that does something every tick
class ActiveTile : public Tile
{
public:
	ActiveTile();
	~ActiveTile();
	void Update();
protected:
	static std::vector<ActiveTile> allActives;
};

class Tile_Rock : Tile
{

};