#include "World.h"
//#include <cstdio>
#include <iostream>
	World::World()
	{
		for (int x = 0; x <= xLimit; x++)
		{
			for (int y = 0; y <= yLimit; y++)
			{
				grid[x][y] = new Tile_Null;
			}
		}
	}
	World::~World()
	{

	}
	Tile *World::GetTile(int x, int y)
	{
		return grid[x][y];
	}
	void World::SetTile(int x, int y, Tile *newTile)
	{
		grid[x][y] = newTile;
	}
	void World::Render()
	{
		for (int y = yLimit; y >= 0; y--)
		{
			for (int x = 0; x <= xLimit; x++)
			{
				std::cout << GetTile(x, y)->symbol;
				//printf("%c[1;32m%c", 27, GetTile(x, y)->symbol); // green
			}
			//printf("\n");
			std::cout << "\n";
		}
	}
