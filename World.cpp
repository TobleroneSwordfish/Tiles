#include "World.h"
#include <iostream>
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
	World::World(char *path)
	{
		
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
			std::cout << "+" << std::endl << "  ";
			//render the top row of the box
			for (int x = 0; x <= xLimit; x++)
			{
				Tile *currentTile = GetTile(x,y);
				std::cout << "|";
				for (int i = 0; i <3; i++) //<3
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
			std::cout << "|" << std::endl << "  ";
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
				std::vector<TileEffect*> *tileEffects = &(grid[x][y]->effects);
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
		return GetTile(x,y)->Inspect();
	}
