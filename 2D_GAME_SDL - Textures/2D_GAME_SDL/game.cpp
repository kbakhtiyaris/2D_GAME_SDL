#include "Game.h"
#include "TextureManager.h"
//#include "GameObject.h"
#include "Map.h"
#include <iostream>
#include "components.h"
#include "Vector2D.h"


using namespace std;

/*
SDL_Texture* playerTex;
SDL_Rect srcR, destR ;

GameObject* player;
GameObject* enemy;*/

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;


auto& player(manager.addEntity());


Game::Game()
{
}

Game::~Game()
{
}

void Game::init(const char* title,int width, int height, bool fullscreen) // declare init
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN; // to get full screen just pass true or false in the argument in declare init
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		cout << "Subsystem initialised!...." << endl;
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		
		//                          sdl window, int index, Uint32 flags
		
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // this is white color
			cout << "Renderer is created" << endl;
		}
		isRunning = true;
	}
	//else not needed anymore
	//{
	// isRunning = false;// if sdl is not initialized correctly isrunning will return false and loop will should it carry on running the game
	//}
	// not nneded any more
		//SDL_Surface* tmpSurface = IMG_Load("assets/player.png");
		//playerTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
		//SDL_FreeSurface(tmpSurface);
	
	map = new Map();

	player.addComponent<TransformComponent>();
	player.addComponent<SpriteComponent>("assets/player.png");
	player.addComponent<KeyboardController>();
}

void Game::handleEvents()
{
	

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
	/*cnt++;
	destR.h = 64;
	destR.w = 64;
	destR.x = cnt;
	cout << cnt << endl;*/
	manager.refresh();
	manager.update();

	/*updated > modified because it was moving player down the screen
	and now we have introduces KeyboardController*/
	//player.getComponent<TransformComponent>().position.Add(Vector2D(3, 1));

	//if (player.getComponent<TransformComponent>().position.x > 100)
	//{
	//	player.getComponent<SpriteComponent>().setTex("assets/enemy.png");
	//}

}

void Game::render()// render our obj to the screen
{ //first it clears what is in the renders buffer as buffer so we can go SDL
	SDL_RenderClear(renderer);
	//SDL_RenderCopy(renderer, playerTex, NULL, &destR);
	map->DrawMap();
	manager.draw();
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
