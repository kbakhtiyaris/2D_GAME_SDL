#pragma once
//#include "Game.h"
#include <string>
class Map
{
public:
	Map(); // constructor
	~Map(); //destructor

	static void LoadMap(std::string path, int sizeX, int sizeY);
	//void DrawMap();
private:

	//SDL_Rect src, dest;

//	SDL_Texture* dirt;
//	SDL_Texture* grass;
//	SDL_Texture* water;

	//int map[20][25];
};