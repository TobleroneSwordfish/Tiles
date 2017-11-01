#pragma once
#include "vector"
enum TileID {TILE_NULL, TILE_ROCK, TILE_WOOD};
//--BASE CLASSES--

//tile effects are applied to tiles and have their own independant update functions
class TileEffect
{
	enum EffectID {Burning, Plant};
	EffectID ID;
	void Update();
};

//base class for all tiles
class Tile
{
public:
	TileID ID;
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
	static std::vector<ActiveTile> allActives;
};

//--TILE CLASSES--
class TileNull : public Tile
{
public:
	const static TileID ID = TILE_NULL;
	TileNull();
	~TileNull();
};

class TileRock : public Tile
{
public:
	const static TileID ID = TILE_ROCK;
	TileRock();
	~TileRock();
};