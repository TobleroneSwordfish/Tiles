#pragma once
#include "vector"
//--BASE CLASSES--

//base class for all tiles
class Tile
{
public:
	const static enum tileIDs;
	
	int ID;
	Tile();
	~Tile();
	int x, y;
	char symbol;
	std::vector<TileEffect> effects;
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

//tile effects are applied to tiles and have their own independant update functions
class TileEffect
{
	const static enum effectIDs;
	int ID;
	void Update();
};

//--TILE CLASSES--
class Tile_Rock : public Tile
{
public:
	Tile_Rock();
	~Tile_Rock();
};