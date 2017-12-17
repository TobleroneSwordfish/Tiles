#include "World.h"
#include "Graphics.h"
#include "Input.h"
#include <iostream>
#include <string>
#include <cassert>
#include <cstring>

void Play(World *world)
{
	//world->Render();
	Display *disp = new Display((char*)"Tiles++", world->xLimit + 2, world->yLimit + 2, 32);
	disp->LoadTextures();
	world->Render();
	int centerX = 5; //world->xLimit/2;
	int centerY = 5; //world->yLimit/2;
	int radius = 5; //world->xLimit/2;
	disp->Render(world, centerX, centerY, radius);
	bool exit = false;
	while (!exit)
	{
		std::cout << "Fetching input" << std::endl;
		char input = Input::GetKey();
		//std::cout << "Key read in: " << input;
		switch (input)
		{
			case 'i':
			{
				int x = -1;
				while (x < 0 || x > (world->xLimit))
				{
					//std::cout << "x coord: ";
					x = Input::GetKey();
					x -= '0';
				}
				int y = -1;
				while (y < 0 || y > (world->yLimit))
				{
					//std::cout << "\ny coord: ";
					y = Input::GetKey();
					y -= '0';
				}
				disp->MsgBox((char *)"Inspect", world->InspectTile(x, y).c_str());
				break;
			}
			case 's':
			{
				//this filename input isn't safe at all, #willfixitlater
				std::string path = Input::GetString("Enter filename");
				path.append(".json");
				world->Save(path.c_str());
				break;
			}
			case 'l':
			{
				std::string path = Input::GetString("Enter filename");
				path.append(".json");			
				world->Load(path.c_str());
				//world->Render();
				disp->Render(world, centerX, centerY, radius);
				break;
			}
			case 'a':
			{
				world->Advance();
				//world->Render();
				disp->Render(world, centerX, centerY, radius);
				break;
			}
			case 'q':
			{
				exit = true;
				break;
			}
		}
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
		test.Load("scenario.json");
		Play(&test);
	}
	else
	{
		std::cout << "Invalid input" << std::endl;
	}

}
