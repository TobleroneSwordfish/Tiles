#include "World.h"
//#include <cstdio>
#include <iostream>
	World::World()
	{
		std::cout << "Intializing world" << std::endl;
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
	// void World::SetTile(int x, int y, TileID ID)
	// {
	// 	switch (ID)
	// 	{
	// 		case TILE_NULL:
	// 			grid[x][y] = new TileNull();
	// 			break;
	// 		case TILE_ROCK:
	// 			grid[x][y] = new TileRock();
	// 			break;
	// 	}
	// }
	void World::Render()
	{
		for (int y = yLimit; y >= 0; y--)
		{
			for (int x = 0; x < xLimit; x++)
			{
				std::cout << "+---";
			}
			std::cout << "+" << std::endl;
			for (int x = 0; x < xLimit; x++)
			{
				std::cout << "|   ";
			}
			std::cout << "|" << std::endl;
			for (int x = 0; x < xLimit; x++)
			{
				std::cout << "| " << GetTile(x, y)->symbol << " ";
				//printf("%c[1;32m%c", 27, GetTile(x, y)->symbol); // green
			}
			std::cout << "|" << std::endl;
			for (int x = 0; x < xLimit; x++)
			{
				std::cout << "|   ";
			}
			std::cout << "|" << std::endl;
		}
		for (int x = 0; x < xLimit; x++)
		{
			std::cout << "+---";
		}
		std::cout << "+" << std::endl;
	}
	void World::Advance(int turns)
	{
		for (int currentTurn = 0; currentTurn < turns - 1; currentTurn++)
		{
			for (int i = 0; i < ActiveTile::allActives.size(); i++)
			{
				ActiveTile::allActives[i].Update();
			}
		}
	}
