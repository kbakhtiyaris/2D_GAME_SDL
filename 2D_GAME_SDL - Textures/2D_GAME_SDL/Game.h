#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>


class ColliderComponent;


class Game // responsible for updating and refreshing SDL
{
public:
	Game();   //game constructor
	~Game(); // deconstructor
																	//   this is for flag
	void init(const char *title, int width, int height, bool fullscreen); // method for initiallizing it
	
	void handleEvents(); //to handle events
	void update(); //this will list go through all  our game objects and update them all
	void render();
	void clean(); // do some memory management clears obj from memory once you're finished with them
	bool running() { return isRunning; }// lets the main function know that the game should still be running
	
	static void AddTile(int srcX, int srcY, int xpos, int ypos);;
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static std::vector<ColliderComponent*> colliders;
	 static bool isRunning;
	 static SDL_Rect camera;
private:

	int cnt = 0;
	
	SDL_Window *window;
	// updated SDL_Renderer *renderer;


	//bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);

	//bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);

};
 /* game_h*/
