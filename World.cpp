#include "World.h"
#include <iostream>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

World::World()
{
	//initalize the world full of null tiles, basically so that GetTile is null-safe
	for (int x = 0; x <= xLimit; x++)
	{
		for (int y = 0; y <= yLimit; y++)
		{
			Tile *newTile = new TileNull();
			grid[x][y] = newTile;
			newTile->world = this;
		}
	}
}
//I think this is the correct way to clear up a heap array?
World::~World()
{
	for (int x = 0; x <= xLimit; x++)
	{
		for (int y = 0; y <= yLimit; y++)
		{
			delete grid[x][y];
		}
	}
}
Tile *World::GetTile(int x, int y)
{
	return grid[x][y];
}
void World::SetTile(int x, int y, Tile *newTile)
{
	newTile->world = this;
	newTile->x = x;
	newTile->y = y;
	grid[x][y] = newTile;
}
void World::SetTile(int x, int y, ActiveTile *newActive)
{
	SetTile(x,y, (Tile*)newActive);
	ActiveTile::allActives.push_back(newActive);
}
//draw the world to the console, would love to get actual graphics going later (OpenGL?)
//am aware this is a bit of a mess, but don't have time to fix it rn
void World::Render()
{
	for (int y = yLimit; y >= 0; y--)
	{
		//render initial bar across the top
		std::cout << "  ";
		for (int x = 0; x <= xLimit; x++)
		{
			std::cout << "+---";
		}
		std::cout << "+" << std::endl
				  << "  ";
		//render the top row of the box
		for (int x = 0; x <= xLimit; x++)
		{
			Tile *currentTile = GetTile(x, y);
			std::cout << "|";
			for (int i = 0; i < 3; i++) //<3
			{
				std::cout << (currentTile->effects.size() > i ? currentTile->effects[i]->symbol : ' ');
			}
		}
		std::cout << "|" << std::endl;
		//display y coordinate of row
		std::cout << y << (y < 10 ? " " : "");
		//render middle row, including main tile symbol
		for (int x = 0; x <= xLimit; x++)
		{
			std::cout << "| " << GetTile(x, y)->symbol << " ";
		}
		std::cout << "|" << std::endl
				  << "  ";
		//render bottom row
		for (int x = 0; x <= xLimit; x++)
		{
			std::cout << "|   ";
		}
		std::cout << "|" << std::endl;
	}
	//stick another bar on the bottom
	std::cout << "  ";
	for (int x = 0; x <= xLimit; x++)
	{
		std::cout << "+---";
	}
	std::cout << "+" << std::endl;
	//display x coordinate of column
	std::cout << "    ";
	for (int x = 0; x <= xLimit; x++)
	{
		std::cout << x << (x < 10 ? "   " : "  ");
	}
	std::cout << std::endl;
}
void World::Advance()
{
	for (int i = 0; i < ActiveTile::allActives.size(); i++)
	{
		ActiveTile::allActives[i]->Update();
	}
	for (int x = 0; x < xLimit; x++)
	{
		for (int y = 0; y < yLimit; y++)
		{
			std::vector<TileEffect *> *tileEffects = &(grid[x][y]->effects);
			for (auto i = tileEffects->begin(); i != tileEffects->end(); i++)
			{
				(*i)->Update();
			}
		}
	}
	//this turn is complete, increment turn number
	turn++;
}
std::string World::InspectTile(int x, int y)
{
	return GetTile(x, y)->Inspect();
}
void World::Save(const char *path)
{
	json output;
	for (int x = 0; x < xLimit; x++)
	{
		for (int y = 0; y < yLimit; y++)
		{
			Tile *tile = GetTile(x,y);
			if (tile->ID != TILE_NULL)
			{
				json jTile = tile->ToJson();
				output.push_back(jTile);
			}
		}
	}
	std::ofstream stream(path);
	stream << std::setw(4) << output << std::endl;
}

void World::Load(const char *path)
{
	for (int x = 0; x <= xLimit; x++)
	{
		for (int y = 0; y <= yLimit; y++)
		{
			Tile *newTile = new TileNull();
			grid[x][y] = newTile;
			newTile->world = this;
		}
	}
	ActiveTile::allActives.clear();
	std::ifstream stream(path);
	json j;
	stream >> j;
	//restofthefuckingcode
	for (json::iterator iter = j.begin(); iter != j.end(); iter++)
	{
		json jTile = *iter;
		Tile *t = new Tile(jTile);
		TileID id = static_cast<TileID>(t->ID);
		int x = t->x;
		int y = t->y;
		//use the ID to select the class to instance. Not happy with this along with the fromID method - needs a refactor
		switch (id)
		{
			case TILE_NULL: SetTile(x,y, new TileNull()); break;
			case TILE_ROCK: SetTile(x,y, new TileRock()); break;
			case TILE_WOOD: SetTile(x,y, new TileWood()); break;
			case TILE_ASH: SetTile(x,y, new TileAsh()); break;
			case TILE_CONVEYOR: SetTile(x,y, new TileConveyor(jTile)); break;
			case TILE_LASER: SetTile(x,y, new TileLaser()); break;
			case TILE_EARTH: SetTile(x,y, new TileEarth()); break;
			case TILE_WATER: SetTile(x,y, new TileWater()); break;
			default: SetTile(x,y, new TileNull()); break;
		}
		for (auto i = t->effects.begin(); i != t->effects.end(); i++)
		{
			GetTile(x,y)->AddEffect(*i);
		}
	}
}