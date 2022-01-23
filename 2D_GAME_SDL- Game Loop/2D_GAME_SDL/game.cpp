#include "Game.h"
#include <iostream>

using namespace std;
Game::Game()
{



}
Game::~Game()
{


}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) // declare init
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN; // to get full screen just pass true or false in the argument in declare init
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		cout << "Subsystem initialised!...." << endl;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			cout << "Window created" << endl;
		}
		//                          sdl window, int index, Uint32 flags
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // this is white color
			cout << "Renderer is created" << endl;
		}
		isRunning = true;
	}
	else
	{
		isRunning = false;// if sdl is not initialized correctly isrunning will return false and loop will should it carry on running the game
	}
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event); // this way it will know where it is .
	switch (event.type)// to find out what type of event it is
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	}
}

void Game::update() //initialize SDL
{
	cnt++;
	cout << cnt << endl;
}

void Game::render()// render our obj to the screen
{ //first it clears what is in the renders buffer as buffer so we can go SDL
	SDL_RenderClear(renderer);
	// this is where we would add stuff to render
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	cout << "Game cleaned" << endl;
}
