#include "World.h"
#include <iostream>
#include <cassert>
#include <cstring>

void Play(World *world)
{
	world->Render();
	while (true)
	{
		std::cin.ignore();
		world->Advance();
		world->Render();
	}
}

//testing

void TestWorldInitalize()
{
	World world;
	assert(world.GetTile(1,1)->ID == TILE_NULL);
	assert(world.GetTile(1,7)->ID == TILE_NULL);
	assert(world.GetTile(5,9)->ID == TILE_NULL);
}

void TestSetGet()
{
	World world;
	world.SetTile(5,5, new TileWood());
	assert(world.GetTile(5,5)->ID == TILE_WOOD);
	world.SetTile(5,5, new TileRock());
	assert(world.GetTile(5,5)->ID == TILE_ROCK);
}

void TestConveyor()
{
	World world;
	world.SetTile(4,5, new TileWood());
	world.SetTile(5,5, new TileConveyor(EAST));
	world.Advance();
	assert(world.GetTile(6,5)->ID == TILE_WOOD);
}

void TestLaser()
{
	World world;
	world.SetTile(5,5, new TileWood());
	world.SetTile(1,5, new TileLaser());
	world.Advance();
	assert(world.GetTile(5,5)->HasEffect(EFFECT_FIRE));
}

//no easy way to reliably test spread, as it is RNG based
void TestFire()
{
	World world;
	world.SetTile(5,5, new TileWood());
	EffectFire *fire = new EffectFire();
	world.GetTile(5,5)->AddEffect(fire);
	for (int i = 0; i < 8; i++)
	{
		world.Advance();
	}
	assert(world.GetTile(5,5)->ID == TILE_ASH);
	delete fire;
}

void RunTests()
{
	TestWorldInitalize();
	TestSetGet();
	TestConveyor();
	TestLaser();
	TestFire();
	std::cout << "All tests pass" << std::endl;
}

int main(int n, char *args[])
{
	//run automatic testing
	if (n == 1)
	{
		RunTests();
		return 0;
	}
	else if (strcmp(args[1], "play") == 0)
	{
		//run the default scenario
		World test;
		TileRock *rock;
		rock = new TileRock();
		test.SetTile(4, 3, rock);
		test.SetTile(2,2, new TileConveyor(NORTH));
		test.SetTile(3,3, new TileConveyor(EAST));
		test.SetTile(4,2, new TileConveyor(SOUTH));
		test.SetTile(3,1, new TileConveyor(WEST));
		
		test.SetTile(5,6, new TileWood());
		test.SetTile(6,6, new TileWood());
		//test.SetTile(7,6, new TileWood());
		test.SetTile(5,7, new TileWood());
		test.SetTile(5,8, new TileWood());
		test.SetTile(4,8, new TileWood());
		test.SetTile(4,6, new TileWood());
		test.SetTile(4,7, new TileWood());
		test.SetTile(6,7, new TileWood());
		//test.SetTile(7,7, new TileWood());
		test.SetTile(6,8, new TileWood());
		//test.SetTile(7,8, new TileWood());
	
		test.SetTile(1,9, new TileConveyor(SOUTH));
		test.SetTile(1,7, new TileConveyor(SOUTH));
		test.SetTile(2,6, new TileConveyor(EAST));
		test.SetTile(1,10, new TileWood());
		test.GetTile(1,10)->AddEffect(new EffectFire());
	
		test.SetTile(8,8, new TileLaser());
		test.SetTile(9,8, new TileWood());
		Play(&test);
	}
	else
	{
		std::cout << "Invalid input" << std::endl;
	}

}
