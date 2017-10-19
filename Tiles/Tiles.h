#pragma once
#include "vector"

class Tile
{
public:
	Tile();
	~Tile();
	int x, y;
	char symbol;
};

//tile with an update func
class ActiveTile : public Tile
{
public:
	ActiveTile();
	~ActiveTile();
	void Update();
protected:
	static std::vector<ActiveTile> allActives;
};

