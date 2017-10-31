#pragma once
#include "vector"
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
	enum TileID {Null, Rock, Wood};
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
protected:
	static std::vector<ActiveTile> allActives;
};

//--TILE CLASSES--
class Tile_Null : public Tile
{
public:
	const static TileID ID = Null;
	const static char symbol = ' ';

};

class Tile_Rock : public Tile
{
public:
	const static TileID ID = Rock;
	const static char symbol = 'R';
	Tile_Rock();
	~Tile_Rock();
};