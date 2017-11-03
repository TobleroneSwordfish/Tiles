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
	while (true)
	{
		world->Render();
		world->Advance();
		mySleep(FRAME_TIME);
	}
}

int main()
{
	World bob;
	TileRock *rock;
	rock = new TileRock();
	//std::cout << "Rock ID: " << rock->ID << " symbol: " << rock->symbol << std::endl;
	bob.SetTile(2, 2, rock);
	Tile *shouldBeRock = bob.GetTile(2,2);
	std::cout << "GetTile ID: " << shouldBeRock->ID << " symbol: " << shouldBeRock->symbol << std::endl;
	
	bob.SetTile(5,5, new TileWood());
	bob.SetTile(6,5, new TileWood());
	bob.SetTile(7,5, new TileWood());
	bob.GetTile(5,5)->effects.push_back(EffectFire());
	Play(&bob);
}