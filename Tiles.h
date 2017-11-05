#pragma once
#include "vector"
#include "World.h"
enum TileID {TILE_NULL, TILE_ROCK, TILE_WOOD, TILE_ASH, TILE_CONVEYOR};
enum EffectID {EFFECT_FIRE, EFFECT_PLANT};
enum Direction {NORTH, SOUTH, EAST, WEST};
//--BASE CLASSES--
class Tile;
class World;

//tile effects are applied to tiles and have their own independant update functions
class TileEffect
{
public:
	EffectID ID;
	virtual void Update();
	TileEffect();
	~TileEffect();
	Tile *parent;
	char symbol;
protected:
	int lifeTime = 0;
};

//base class for all tiles
class Tile
{
public:
	TileID ID;
	Tile();
	~Tile();
	int x, y;
	World *world;
	char symbol;
	bool flammable = false; //can catch fire
	//int catchTime; //how many turns it has to be next to a fire in order to catch
	int burnTime; //how many turns it will burn for
	int lastMoved = -1; //the last turn that this tile was moved by a conveyor
	std::vector<TileEffect*> effects;
	void AddEffect(TileEffect *effect);
	bool HasEffect(EffectID effect);
};

//tile with an update func, basically one that does something every tick
class ActiveTile : public Tile
{
public:
	ActiveTile();
	~ActiveTile();
	virtual void Update();
	static std::vector<ActiveTile*> allActives;
};

//--TILE CLASSES--
class TileNull : public Tile
{
public:
	TileNull();
	~TileNull();
};

class TileRock : public Tile
{
public:
	TileRock();
	~TileRock();
};

class TileWood : public Tile
{
public:
	TileWood();
	~TileWood();
};

class TileAsh : public Tile
{
public:
	TileAsh();
	~TileAsh();
};

class TileConveyor : public ActiveTile
{
public:
	Direction facing;
	TileConveyor(Direction dir);
	~TileConveyor();
	void Update();
};

//--EFFECT CLASSES--
class EffectFire : public TileEffect
{
public:
	EffectFire();
	~EffectFire();
	void Update();
};