#include "Tiles.h"
Tile::Tile()
{

}

Tile::~Tile()
{

}
std::vector<ActiveTile> ActiveTile::allActives;
ActiveTile::ActiveTile()
{
	allActives.push_back(*this);
}

void ActiveTile::Update()
{

}

ActiveTile::~ActiveTile()
{
	for (int i = 0; i < allActives.size; i++)
	{
		if (&allActives[i] == this)
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
}

//--EFFECT CLASSES
EffectFire::EffectFire()
{
	ID = EFFECT_FIRE;
}

void EffectFire::Update()
{
	TileEffect::Update();
	World *world = parent->world;
	int values[] = {1, -1};
	bool found = false;
	int xOffset = 0;
	int yOffset = 0;
	if (rand() % 2 == 0)
	{
		yOffset = values[rand() % 2];
	}
	else
	{
		xOffset = values[rand() % 2];
	}
	if (world->GetTile(parent->x + xOffset, parent->y + yOffset)->flammable) //is the chosen tile flammable?
	{
		EffectFire *newFire = new EffectFire();
		world->GetTile(parent->x + xOffset, parent->y + yOffset)->effects->push_back(newFire);

	}
}