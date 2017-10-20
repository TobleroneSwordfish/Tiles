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

ActiveTile::~ActiveTile()
{
	
}

Tile_Rock::Tile_Rock()
{

}
