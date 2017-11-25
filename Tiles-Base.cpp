#include "Tiles-Base.h"
#include <sstream>
#include <algorithm>
#include <iostream>

void to_json(json &j, const Tile &t)
{
    j = json{{"ID", t.ID}, {"x", t.x}, {"y", t.y}, {"symbol", t.symbol}};
    //j.push_back({"effects", t.effects});
}

void to_json(json &j, const TileEffect &e)
{
    j = json{{"ID", e.ID}, {"symbol", e.symbol}, {"lifetime", e.lifeTime}};
}

Tile::Tile()
{
	effects = std::vector<TileEffect*>(0);
}

//not exactly sure how to free all the tile effects, this code causes a segfault, hence it being commented out
Tile::~Tile()
{
	// if (effectsCount > 0)
	// {
	// 	for (auto i = effects.begin(); i != effects.end(); i++)
	// 	{
	// 		 delete *i;
	// 	}
	// 	effects.clear();
	// }
}

void Tile::AddEffect(TileEffect *effect)
{
	effects.push_back(effect);
	effect->parent = this;
	effectsCount++;
}

void Tile::RemoveEffect(TileEffect *effect)
{
	effects.erase(std::remove(effects.begin(), effects.end(), effect), effects.end());
	effectsCount--;
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

std::string Tile::Inspect()
{
	//gotta love C++ for this at least
	std::ostringstream output;
	output << "ID: " << ID << "\n";
	output << "Symbol: " << symbol << "\n";
	output << "Position: " << x << ", " << y << "\n";
	output << "Effects: \n";
	//std::cout << "Effects size: " << effects.size();
	if (effectsCount > 0)
	{
		for (auto pointer = effects.begin(); pointer != effects.end(); pointer++)
		{
			output << "   " << (*pointer)->Inspect();
		}
	}
	return output.str();
}

json Tile::ToJson()
{
    json j = *this;
    return j;
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
	//remove the pointer to this tile from the list of all active tiles
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

std::string TileEffect::Inspect()
{
	std::ostringstream output;
	output << "ID: " << ID << "\n";
	output << "Symbol: " << symbol << "\n";
	return output.str();
}