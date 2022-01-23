#include "Game.h"
#include "SDL.h"

Game *game = nullptr; // instance of game //  null pointer for now
int main(int argc, char* argv[])
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();
	
	game->init("bakhtiyars engine", 800, 640, false);
	
	while (game->running()) // it will run until is running is truw
	{
		frameStart = SDL_GetTicks();

		game->handleEvents(); // runs handleevent
		game->update();// runs update
		game->render();// runs render
		
		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}
	// is running becomes false
	game->clean();
	return 0;
}