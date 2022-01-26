#pragma once
//#include "Game.h"
#include <string>
class Map
{
public:
	Map(std::string tID, int ms, int ts); // constructor
	~Map(); //destructor

	 void LoadMap(std::string path, int sizeX, int sizeY);
	 void AddTile(int srcX, int srcY, int xpos, int ypos);
	//void DrawMap();
private:
	std::string texID;
	int mapScale;
	int tileSize;
	int scaledSize;
	//SDL_Rect src, dest;

//	SDL_Texture* dirt;
//	SDL_Texture* grass;
//	SDL_Texture* water;

	//int map[20][25];
};