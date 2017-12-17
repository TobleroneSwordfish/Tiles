#pragma once
#include <string>
#include "vector"
#include "json.hpp"

using json = nlohmann::json;
enum TileID {TILE_NULL, TILE_ROCK, TILE_WOOD, TILE_ASH, TILE_CONVEYOR, TILE_LASER, TILE_EARTH, TILE_WATER};
enum EffectID {EFFECT_FIRE, EFFECT_PLANT, EFFECT_BEAM};
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
	std::string Inspect();
	TileEffect();
	~TileEffect();
	Tile *parent;
	char symbol;
	virtual json ToJson();
	//add to a queue to be deleted at the end of the turn, solves a few issues with reallocation
	void Trash();
	//delete all items scheduled for destruction
	static void Collect();
	int lifeTime = 0;
protected:
	//the list of effects to be deleted at the end of the turn
	static std::vector<TileEffect*> garbage;
};

//base class for all tiles
class Tile
{
public:
	TileID ID;
	Tile();
	Tile(json j);
	~Tile();
	int x, y;
	World *world;
	char symbol; //what it's rendered as
	bool flammable = false; //can catch fire
	int burnTime; //how many turns it will burn for
	int lastMoved = -1; //the last turn that this tile was moved by a conveyor
	int humidity = 0; //how damp something is, being next to water increased this every turn
	Direction facing = NORTH;
	std::vector<TileEffect*> effects;
	void AddEffect(TileEffect *effect);
	void RemoveEffect(TileEffect *effect);
	bool HasEffect(EffectID effect);
	std::string Inspect();
	virtual json ToJson();
    static Tile *FromID(TileID id);
//protected:
	int effectsCount = 0;
};

//tile with an update func, basically one that does something every turn
class ActiveTile : public Tile
{
public:
	ActiveTile();
	ActiveTile(json j);
	~ActiveTile();
	virtual void Update();
	//a list of all the active tile, to save having to check each tile on the grid every turn
	static std::vector<ActiveTile*> allActives;
};

void to_json(json &j, const Tile &t);
void to_json(json &j, const TileEffect &e);
void from_json(const json &j, Tile &t);