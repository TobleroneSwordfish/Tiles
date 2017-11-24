#pragma once
#include "vector"
#include "Tiles-Base.h"
#include "World.h"

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

class TileLaser : public ActiveTile
{
public:
	TileLaser();
	~TileLaser();
	void Update();
};

class TileEarth : public Tile
{
	TileEarth();
	~TileEarth();
};

class TileWater : public ActiveTile
{
	TileWater();
	~TileWater();
	void Update();
};

//--EFFECT CLASSES--
class EffectFire : public TileEffect
{
public:
	EffectFire();
	~EffectFire();
	void Update();
private:
	void Spread(); //watch the world burn
	int lastSpread = -1; //last time this fire spread or was spread
};