
#ifndef Game_h
#define Game_h
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

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
	bool running()// lets the main function know that the game should still be running
	{
		return isRunning;
	}

	static SDL_Renderer* renderer;
	static SDL_Event event;
private:
	int cnt = 0;
	bool isRunning;
	SDL_Window *window;
	// updated SDL_Renderer *renderer;


};
#endif /* game_h*/
