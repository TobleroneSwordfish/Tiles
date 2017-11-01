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
}