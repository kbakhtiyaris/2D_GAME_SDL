#include "Game.h"
#include "TextureManager.h"
//#include "GameObject.h"
#include "Map.h"
#include <iostream>
#include "components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
#include "ProjectileComponent.h"

using namespace std;

/*
SDL_Texture* playerTex;
SDL_Rect srcR, destR ;

GameObject* player;
GameObject* enemy;*/

Map* myMap;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = { 0, 0 , 800, 640 };

AssetManager* Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;

auto& player(manager.addEntity());



//auto& tile0(manager.addEntity());
//auto& tile1(manager.addEntity());
//auto& tile2(manager.addEntity());

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title,int width, int height, bool fullscreen) // declare init
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN; // to get full screen just pass true or false in the argument in declare init
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		//cout << "Subsystem initialised!...." << endl;
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
	
	assets->AddTexture("terrain", "assets/terrain_ss.png");
	assets->AddTexture("player", "assets/player_anims.png");

	assets->AddTexture("projectile", "assets/proj.png");

	myMap = new Map("terrain", 3, 32);

	myMap->LoadMap("assets/map.map",25 , 20);

	//esc omplementations
	//tile0.addComponent<TileComponent>(200, 200, 32, 32, 0);
	//tile1.addComponent<TileComponent>(250, 250, 32, 32, 1);
	//tile1.addComponent<ColliderComponent>("dirt");
	//tile2.addComponent<TileComponent>(150, 150, 32, 32, 2);
	//tile2.addComponent<ColliderComponent>("grass");

	player.addComponent<TransformComponent>(800.0f, 640.0f, 32, 32, 4);
	player.addComponent<SpriteComponent>("player", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);
	
	
	assets->CreateProjectile(Vector2D(600, 600), Vector2D(2, 0), 200, 2, "projectile");
	assets->CreateProjectile(Vector2D(600, 620), Vector2D(2, 0), 200, 2, "projectile");
	assets->CreateProjectile(Vector2D(400, 600), Vector2D(2, 1), 200, 2, "projectile");
	assets->CreateProjectile(Vector2D(600, 600), Vector2D(2, -1), 200, 2, "projectile");
	
	/*wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
	wall.addComponent<SpriteComponent>("assets/dirt.png");
	wall.addComponent<ColliderComponent>("wall");
	wall.addGroup(groupMap);*/
}

auto& tiles(manager.getGroup(Game::groupMap));// this will pass into here all the tiles into the group
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));

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
	SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
	Vector2D playerPos = player.getComponent<TransformComponent>().position;


	manager.refresh();
	manager.update();

	for (auto& c : colliders)
	{
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCol, playerCol))
		{
			player.getComponent<TransformComponent>().position = playerPos;
		}
	}

	for (auto& p : projectiles)
	{
		if (Collision::AABB(player.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider))
		{
			std::cout << "hit player" << std::endl;
			p->destroy();
		}
	}

	camera.x = player.getComponent<TransformComponent>().position.x - 400;
	camera.y = player.getComponent<TransformComponent>().position.y - 320;

	if (camera.x < 0)
		camera.x = 0;
	if (camera.y < 0)
		camera.y = 0;
	if (camera.x > camera.w)
		camera.x = camera.w;
	if (camera.y > camera.h)
		camera.y = camera.h;


	/*Vector2D pVel = player.getComponent<TransformComponent>().velocity;
	int pSpeed = player.getComponent<TransformComponent>().speed;

	for (auto t : tiles)
	{
		t->getComponent<TileComponent>().destRect.x += -(pVel.x * pSpeed);
		t->getComponent<TileComponent>().destRect.y += -(pVel.y * pSpeed);
	}*/





	//if (Collision::AABB(player.getComponent<ColliderComponent>().collider,
		//wall.getComponent<ColliderComponent>().collider))
	/*for (auto cc : colliders)
	{
		if Collision::AABB(player.getComponent<ColliderComponent>(), *cc);
			//{
				//player.getComponent<TransformComponent>().scale = 1;
				//player.getComponent<TransformComponent>().velocity * -1;
				//cout << "wall hit!" << endl;
			//}
	}*/
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
	//map->DrawMap();
	//manager.draw();

	for (auto& t : tiles)
	{
		t->draw();
	 }

	/*for (auto& c : colliders)
	{
		c->draw();
	}*/


	for (auto& p : players)
	{
		p->draw();
	}

	for (auto& p : projectiles)
	{
		p->draw();
	}

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
/*void Game::AddTile(int srcX, int srcY, int xpos, int ypos)
{
	  taken to map.cpp
}*/
