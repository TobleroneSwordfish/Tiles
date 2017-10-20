#include "World.h"
#include <iostream>
#include <cstdio>
void Render(World world)
{
	for (int y = world.yLimit; y >= 0; y--)
	{
		for (int x = 0; y <= world.xLimit; y++)
		{
			printf("%c[1;32m%c\n", 27, world.GetTile(x, y)->symbol); // green
		}
	}
}