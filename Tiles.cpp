#include "Tiles.h"
#include <cstdlib>
#include <random>
//debugging, remove after
#include <iostream>
Tile::Tile()
{

}

//not exactly sure how to free all the tile effects, this code causes a segfault, hence it being commented out
Tile::~Tile()
{
	// for (auto i = effects.begin(); i != effects.end(); i++)
	// {
	// 	delete *i;
	// }
	// effects.clear();
}

void Tile::AddEffect(TileEffect *effect)
{
	effects.push_back(effect);
	effect->parent = this;
}

bool Tile::HasEffect(EffectID effect)
{
	for (auto i = effects.begin(); i != effects.end(); i++)
	{
		if ((*i)->ID == effect)
		{
			return true;
		}
	}
	return false;
}

std::vector<ActiveTile*> ActiveTile::allActives;
ActiveTile::ActiveTile()
{
	allActives.push_back(this);
}

void ActiveTile::Update()
{

}

ActiveTile::~ActiveTile()
{
	for (int i = 0; i < allActives.size(); i++)
	{
		if (allActives[i] == this)
		{
			allActives.erase(allActives.begin() + i);
			return;
		}
	}
}

TileEffect::TileEffect()
{

}
TileEffect::~TileEffect()
{

}
void TileEffect::Update()
{
	lifeTime++;
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
	burnTime = 3;
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
		std::cout << "Moving tile ID " << origin->ID << " from " << x + ox << "," << y + oy << " to " << x - ox << "," << y - oy << std::endl;
		world->SetTile(x - ox, y - oy, origin);
		world->SetTile(x + ox, y + oy, new TileNull());
		origin->lastMoved = world->turn;
	}
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
//fire will burn down to ash after a number of turns defined by the tile it is burning
void EffectFire::Update()
{
	//call the base
	TileEffect::Update();
	World *world = parent->world;
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
	Tile *target = world->GetTile(parent->x + xOffset, parent->y + yOffset);
	if (target->flammable && !target->HasEffect(this->ID)) //is the chosen tile flammable and not already on fire
	{
		target->AddEffect(new EffectFire());
	}
	//check if the fire has burned out
	if (lifeTime > parent->burnTime)
	{
		Tile *burning = parent;
		world->SetTile(parent->x, parent->y, new TileAsh());
		std::cout << "Tile at " << parent->x << "," << parent->y << " burned down to ash" << std::endl;
		delete parent;
	}
}