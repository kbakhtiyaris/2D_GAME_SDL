#pragma once
#include "components.h"
#include "Vector2D.h"


class TransformComponent : public Component
{

public:

	Vector2D position;


	TransformComponent()
	{
		position.x = 0.0f;
		position.y = 0.0f;
	}

	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}
	// expose and our x and y position
	void update() override
	{

	}

	
};



