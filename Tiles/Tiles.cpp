#include "Tiles.h"
class Tile
{
public:
	int x, y;
	char symbol;
};

class ActiveTile
{
public:
	ActiveTile()
	{
		allActives.push_back(*this);
	}
protected:
	static std::vector<ActiveTile> allActives;
};

class Rock : Tile
{
public:
	Rock()
	{
		symbol = '#';
	}
};