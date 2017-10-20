#include "World.h"
int main()
{
	World bob;
	bob.SetTile(2, 2, new Tile_Rock);
	bob.Render();
}