#include "Tiles-Base.h"
#include <sstream>
#include <algorithm>
#include <iostream>

Tile::Tile()
{
	effects = std::vector<TileEffect*>(0);
}

Tile::Tile(json j)
{
	TileID id = static_cast<TileID>(j.at("ID").get<int>());
	Tile t = *Tile::FromID(id);
	t.x = j.at("x").get<int>();
	t.y = j.at("y").get<int>();
	t.facing = static_cast<Direction>(j.at("direction").get<int>());
	std::memcpy(this, &t, sizeof(Tile));
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
	if (effectsCount > 0)
	{
		for (auto pointer = effects.begin(); pointer != effects.end(); pointer++)
		{
			output << (*pointer)->Inspect();
		}
	}
	return output.str();
}

json Tile::ToJson()
{
    json j;
	//setup initial JSON object with simple members
	j = json{{"ID", ID}, {"x", x}, {"y", y}, {"symbol", symbol}, {"direction", facing}};
	//array to store the effects in
	json array = json::array();
	for (std::vector<TileEffect*>::const_iterator pointer = effects.begin(); pointer != effects.end(); pointer ++)
	{
		//dereference the iterator to get the pointer then dereference that to get the value. Phew, see this IS a pointer project!
		TileEffect t = *(*pointer);
		json effect = t.ToJson();
		array.push_back(effect);
	}
	//no point sticking a potentially problematic array in the json
	if (!array.empty())
	{
		j.push_back(json::object_t::value_type("effects", array));
	}
	return j;
}

std::vector<ActiveTile*> ActiveTile::allActives;
ActiveTile::ActiveTile()
{
	
}

ActiveTile::ActiveTile(json j) : Tile(j)
{

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

json TileEffect::ToJson()
{
	return json{{"ID", ID}, {"symbol", symbol}, {"lifetime", lifeTime}};
}