#include "World.h"
#include <iostream>
int main()
{
	World bob;
	TileRock *rock;
	rock = new TileRock();
	//std::cout << "Rock ID: " << rock->ID << " symbol: " << rock->symbol << std::endl;
	bob.SetTile(2, 2, rock);
	//Tile *shouldBeRock = bob.GetTile(2,2);
	//std::cout << "GetTile ID: " << shouldBeRock->ID << " symbol: " << shouldBeRock->symbol << std::endl;
	//std::cout << "In theory null ID: " << bob.GetTile(10,10)->ID << std::endl;
	bob.Render();
}
