#include "Tiles.h"

class Tile
{
public:
	const static enum tileIDs { Rock, Wood };
	~Tile()
	{

	}
protected:
	std::vector<TileEffect> effects;
};

class ActiveTile : public Tile
{
public:
	ActiveTile()
	{
		allActives.push_back(*this);
	}
protected:
	static std::vector<ActiveTile> allActives;
};

class TileEffect
{
	const static enum effectIDs { Burning, Plant };
	int ID;
	void Update();
};


class Tile_Rock : public Tile
{
public:
	const static int ID = tileIDs::Rock;
	const static char symbol = '#';
	Tile_Rock()
	{

	}
};

//tile effect classes