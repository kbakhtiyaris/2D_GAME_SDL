#include "Game.h"
#include "SDL.h"

Game *game = nullptr; // instance of game //  null pointer for now
int main(int argc, char* argv[])
{
	game = new Game();
	game->init("bakhtiyars engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
	while (game->running()) // it will run until is running is truw
	{
		game->handleEvents(); // runs handleevent
		game->update();// runs update
		game->render();// runs render
	}
	// is running becomes false
	game->clean();
	return 0;
}