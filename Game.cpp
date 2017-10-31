#include "World.h"
int main()
{
	World bob;
	Tile_Rock *rock;
	bob.SetTile(2, 2, rock);
	bob.Render();
}
