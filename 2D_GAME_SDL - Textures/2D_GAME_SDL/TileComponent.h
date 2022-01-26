#pragma once
#include "ESC.h"
#include "SDL.h"
#include "Vector2D.h"
#include "Game.h"
#include "TextureManager.h"

class TileComponent : public Component
{
public:
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	Vector2D position;
	
	//const char* path;

	TileComponent() = default;

	~TileComponent()
	{
		SDL_DestroyTexture(texture);
	}


	TileComponent(int srcX, int srcY, int xpos, int ypos, int tsize, int tscale, std::string id)
	{
		texture = Game::assets->GetTexture(id);
	
		position.x = xpos;
		position.y = ypos;

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = tsize;

		destRect.x = xpos;
		destRect.y = ypos;
		destRect.w = destRect.h = tsize * tscale;
	}

	void update() override
	{
		destRect.x = position.x - Game::camera.x;
		destRect.y = position.y - Game::camera.y;
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);

	}



	/*this is was all inside tilecomponent*/

		/*tileRect.x = x;
		tileRect.y = y;
		tileRect.w = w;
		tileRect.h = h;
		tileID = id; */// it will help us to automaticly sign the texture for us when we create tile

		/*switch (tileID)
		{
		case 0:
			path = "assets/dirt.png";
			break;
		case 1:
			path = "assets/grass.png";
			break;
		case 2:
			path = "assets/water.png";
				break;
		default:
			break;
		}*/
	

	/*void init() override
	{
		entity->addComponent<TransformComponent>((float)tileRect.x, (float)tileRect.y, tileRect.w, tileRect.h, 1);
		transform = &entity->getComponent<TransformComponent>();

		entity->addComponent<SpriteComponent>(path);
		sprite = &entity->getComponent<SpriteComponent>();
	
	}*/
};