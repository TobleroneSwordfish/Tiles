#include "World.h"
#include <iostream>
#include <chrono>
#include <thread>
//milliseconds between frames
#define FRAME_TIME 2000

#ifdef __linux__
#include <unistd.h>
#endif
#ifdef _WIN32
#include <windows.h>
#endif

//cross platform sleep function from https://stackoverflow.com/questions/10918206/cross-platform-sleep-function-for-c
//if you know a better way, please tell me
void mySleep(int sleepMs)
{
#ifdef __linux__
    usleep(sleepMs * 1000);   // usleep takes sleep time in us (1 millionth of a second)
#endif
#ifdef _WIN32
    Sleep(sleepMs);
#endif
}

void Play(World *world)
{
	world->Render();
	while (true)
	{
		std::cin.ignore();
		world->Advance();
		world->Render();
		//mySleep(FRAME_TIME);
	}
}

int main()
{
	World bob;
	TileRock *rock;
	rock = new TileRock();
	//std::cout << "Rock ID: " << rock->ID << " symbol: " << rock->symbol << std::endl;
	//bob.SetTile(2, 3, rock);
	bob.SetTile(4, 3, rock);
	bob.SetTile(2,2, new TileConveyor(NORTH));
	bob.SetTile(3,3, new TileConveyor(EAST));
	bob.SetTile(4,2, new TileConveyor(SOUTH));
	bob.SetTile(3,1, new TileConveyor(WEST));
	//Tile *shouldBeRock = bob.GetTile(2,2);
	//std::cout << "GetTile ID: " << shouldBeRock->ID << " symbol: " << shouldBeRock->symbol << std::endl;
	
	bob.SetTile(5,6, new TileWood());
	bob.SetTile(6,6, new TileWood());
	bob.SetTile(7,6, new TileWood());
	bob.SetTile(5,7, new TileWood());
	bob.SetTile(5,8, new TileWood());
	bob.SetTile(4,8, new TileWood());
	bob.SetTile(4,6, new TileWood());
	bob.SetTile(4,7, new TileWood());
	bob.SetTile(6,7, new TileWood());
	bob.SetTile(7,7, new TileWood());
	bob.SetTile(6,8, new TileWood());
	bob.SetTile(7,8, new TileWood());
	bob.GetTile(5,6)->AddEffect(new EffectFire());
	Play(&bob);
}