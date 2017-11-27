#include "Tiles.h"
#include <cstdlib>
#include <random>
#include <iostream>

Tile *Tile::FromID(TileID id)
{
	switch (id)
	{
		case TILE_NULL: return new TileNull();
		case TILE_ROCK: return new TileRock();
		case TILE_WOOD: return new TileWood();
		case TILE_ASH: return new TileAsh();
		case TILE_CONVEYOR: return new TileConveyor(NORTH);
		case TILE_LASER: return new TileLaser();
		case TILE_EARTH: return new TileEarth();
		case TILE_WATER: return new TileWater();
		default: return new TileNull();
	}
}

//--TILE CLASSES
TileNull::TileNull()
{
	ID = TILE_NULL;
	symbol = ' ';
}

TileRock::TileRock()
{
	ID = TILE_ROCK;
	symbol = 'R';
}

TileWood::TileWood()
{
	ID = TILE_WOOD;
	symbol = 'W';
	flammable = true;
	burnTime = 7;
}

TileAsh::TileAsh()
{
	ID = TILE_ASH;
	symbol = 'A';
}

TileConveyor::TileConveyor(Direction dir)
{
	ID = TILE_CONVEYOR;
	facing = dir;
	switch(dir)
	{
		case NORTH: symbol = '^'; break;
		case SOUTH: symbol = 'V'; break;
		case EAST: symbol = '>'; break;
		case WEST: symbol = '<'; break;
	}
}
TileConveyor::TileConveyor(json j) : ActiveTile(j)
{
	Direction dir = static_cast<Direction>(j.at("direction").get<int>());
	facing = dir;
	switch(dir)
	{
		case NORTH: symbol = '^'; break;
		case SOUTH: symbol = 'V'; break;
		case EAST: symbol = '>'; break;
		case WEST: symbol = '<'; break;
	}
}

TileConveyor::~TileConveyor()
{

}

void TileConveyor::Update()
{
	//offset of origin from conveyor
	int ox = 0;
	int oy = 0;
	switch (facing)
	{
		case NORTH: oy = -1; break;
		case SOUTH: oy = 1; break;
		case EAST: ox = -1; break;
		case WEST: ox = 1; break;
	}
	Tile *origin = world->GetTile(x + ox, y + oy);
	Tile *nextTile = world->GetTile(x - ox, y - oy);
	//check that we're moving a non-null tile to a null tile, and that the tile we're moving hasn't moved already this turn
	if (origin->ID != TILE_NULL && nextTile->ID == TILE_NULL && origin->lastMoved != world->turn)
	{
		std::cout << "Conveyor moving tile ID " << origin->ID << " from " << x + ox << "," << y + oy << " to " << x - ox << "," << y - oy << std::endl;
		world->SetTile(x - ox, y - oy, origin);
		world->SetTile(x + ox, y + oy, new TileNull());
		origin->lastMoved = world->turn;
	}
}

TileLaser::TileLaser()
{
	ID = TILE_LASER;
	symbol = '-';
}

void TileLaser::Update()
{
	//look for flammable tile to set on fire
	for (int i = x; i <= world->xLimit; i++)
	{
		Tile *currentTile = world->GetTile(i, y);
		if (currentTile->flammable)
		{
			if (!currentTile->HasEffect(EFFECT_FIRE))
			{
				currentTile->AddEffect(new EffectFire);	
				std::cout << "Laser at " << x << "," << y << " set fire to tile at " << currentTile->x << "," << currentTile->y << std::endl;
			}
			break;
		}
	}
	//copy pasted code here, ik but it's nearly midnight and I'll deal with it later
	for (int i = x; i >= 0; i--)
	{
		Tile *currentTile = world->GetTile(i, y);
		if (currentTile->flammable)
		{
			if (!currentTile->HasEffect(EFFECT_FIRE))
			{
				currentTile->AddEffect(new EffectFire);	
				std::cout << "Laser at " << x << "," << y << " set fire to tile at " << currentTile->x << "," << currentTile->y << std::endl;
			}
			break;
		}
	}
}

TileEarth::TileEarth()
{
	symbol = 'E';
	ID = TILE_EARTH;
}

TileWater::TileWater()
{
	symbol = '~';
	ID = TILE_WATER;
}

void TileWater::Update()
{
	//stuff stuff stuff
}



//--EFFECT CLASSES
EffectFire::EffectFire()
{
	ID = EFFECT_FIRE;
	symbol = 'f';
}
EffectFire::~EffectFire()
{

}

//fire can spread to any directly adjacent tile, it will pick one of the four randomly each tick and attempt to spread to it
void EffectFire::Spread()
{
	//set up the randomiser?
	srand(time(NULL));
	//list of offset values to select from
	int values[] = {1, -1};
	int xOffset = 0;
	int yOffset = 0;
	int rxy = rand() % 2;
	int rOff = values[rand() % 2];
	//std::cout << "offset = " << rOff << std::endl;
	//choose whether we're offsetting by x or y
	if (rxy == 0)
	{
		//std::cout << "checking y" << std::endl;
		yOffset = rOff;
	}
	else
	{
		//std::cout << "checking x" << std::endl;
		xOffset = rOff;
	}
	Tile *target = parent->world->GetTile(parent->x + xOffset, parent->y + yOffset);
	if (target->flammable && !target->HasEffect(this->ID)) //is the chosen tile flammable and not already on fire
	{
		EffectFire *nextFire = new EffectFire();
		nextFire->lastSpread = parent->world->turn;
		lastSpread = parent->world->turn;
		target->AddEffect(nextFire);
		std::cout << "Fire spreading from " << parent->x << "," << parent->y << " to " << target->x << "," << target->y << std::endl;
	}
}

//fire will burn down to ash after a number of turns defined by the tile it is burning
void EffectFire::Update()
{
	//call the base
	TileEffect::Update();
	World *world = parent->world;
	if (world->turn > lastSpread + 1)
	{
		Spread();
	}
	//Spread();
	//check if the fire has burned out
	if (lifeTime > parent->burnTime)
	{
		Tile *burning = parent;
		world->SetTile(parent->x, parent->y, new TileAsh());
		std::cout << "Tile at " << parent->x << "," << parent->y << " burned down to ash" << std::endl;
		delete parent;
	}
}