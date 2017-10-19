#pragma once
class Grid
{
public:
	Grid();
	~Grid();
	const static int xLimit = 50, yLimit = 50;
private:
	char array[xLimit][yLimit];
};