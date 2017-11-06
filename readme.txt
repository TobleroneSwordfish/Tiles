--IMPORTANT--
The project requires the c++11 standard for more reasons than I can count, this unfortunately means that it will not compile on snowy,
so I am not able to verify that it will work on that environment.
It should be compiled like so: "g++ Game.cpp World.cpp Tiles.cpp -fno-exceptions -std=c++11 -o Binary"
If you have issues compiling it please email me, I didn't realise that c++11 wasn't installed on snowy :(

The project is a tile based simulation. Think of it as kinda like dwarf fortress.
It is written in c++, because OOP.
It is based on a 10x10 (by default, because console windows are tiny) grid.
All tiles on the grid can be affected by other tiles.
Tiles can have effects on them, currently the only one is fire.
All effects and active tiles are updated every turn.
To run automatic testing run with no args, to play the default scenario run like "./Binary play"
To go to the next turn hit enter.

Currently implemented tiles are:
Wood - flammable, burns for 7 turns before collapsing into ash. Symbol 'W'
Rock - not flammable, basic inert tile. Symbol 'R'
Conveyor - moves the tile behind it to in front of it, direction indicated by the arrow. Symbols: '>' '<' '^' 'V'
Laser - sets the first flammable tile in its path on fire. Only fires horizontally. Symbol '-'

Effects:
Fire - tries to spread randomly every turn to adjacent flammable tiles. Eventually burns its host tile down to ash after a number of turns dependant on the tile. Symbol 'f'
Effects are displayed in the box above the tile symbol

The scenario set up in this version is designed to show each of the mechanics in action.

There is an infinite loop of conveyors in the lower half, rotating a rock around in a circle.
In the top half there is a large block of wood that is set on fire both from a laser to the right and a burning wood tile moved in on conveyors from the left.
All the wood eventually burns down to ash.

This project is provided very much unfinished, so here's a list of features I'd like to add in the future:
A proper way of exiting the game, right now I just CTRL C it
Reading in game states from text files.
Plants that spread, mature, die, and crossbreed.
Water that erodes rock, turns earth into mud etc. Plants would grow better on mud.
Tiles that create other tiles, for example a volcano that spews out rocks.
Proper rendering with sprites for each tile and effect, rather than the kinda restrictive console format.

I'd like feedback on a couple of things specifically:
The randomizer I'm using for fire seems to always produce the same series of "random" numbers each time I run the program, how can I improve this?
Memory management, pretty sure this thing has a few memory leaks.


If you've got down this far then thank you! I'm sorry it's so long...

TL;DR - compile with "g++ Game.cpp World.cpp Tiles.cpp -fno-exceptions -std=c++11 -o Binary", run with either "./Binary" or "./Binary play".