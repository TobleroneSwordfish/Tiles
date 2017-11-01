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

TileNull::TileNull()
{
	symbol = ' ';
}

TileRock::TileRock()
{
	symbol = 'R';
}
