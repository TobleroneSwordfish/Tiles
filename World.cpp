#include "World.h"
//#include <cstdio>
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
		delete grid[x][y];
		newTile->world = this;
		grid[x][y] = newTile;
	}
	//draw the world to the console, would love to get actual graphics going later (OpenGL?)
	void World::Render()
	{
		for (int y = yLimit; y >= 0; y--)
		{
			//render initial bar across the top
			for (int x = 0; x < xLimit; x++)
			{
				std::cout << "+---";
			}
			std::cout << "+" << std::endl;
			//render the top row of the box
			for (int x = 0; x < xLimit; x++)
			{
				Tile *currentTile = GetTile(x,y);
				std::cout << "|  " << (currentTile->effects.size() > 0 ? currentTile->effects[0].symbol : ' ');
			}
			std::cout << "|" << std::endl;
			//render middle row, including main tile symbol
			for (int x = 0; x < xLimit; x++)
			{
				std::cout << "| " << GetTile(x, y)->symbol << " ";
			}
			std::cout << "|" << std::endl;
			//render bottom row
			for (int x = 0; x < xLimit; x++)
			{
				std::cout << "|   ";
			}
			std::cout << "|" << std::endl;
		}
		//stick another bar on the bottom
		for (int x = 0; x < xLimit; x++)
		{
			std::cout << "+---";
		}
		std::cout << "+" << std::endl;
	}
	void World::Advance()
	{
		for (int i = 0; i < ActiveTile::allActives.size(); i++)
		{
			ActiveTile::allActives[i].Update();
		}
		for (int x = 0; x < xLimit; x++)
		{
			for (int y = 0; y < yLimit; y++)
			{
				if (grid[x][y]->effects.size() != 0)
				{
					for (int i = 0; i < grid[x][y]->effects.size(); i++)
					{
						std::cout << "Effect found at " << x << "," << y << " symbol: " << grid[x][y]->effects[i].symbol;
						grid[x][y]->effects[i].Update();
					}
				}
			}
		}
	}
