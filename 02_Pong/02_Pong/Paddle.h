#pragma once
#include "GameObject.h"
#include "DrawableRect.h"

class Paddle :
	public GameObject
{
public:
	Paddle();
	Paddle(Vector2 position, Vector2 size, SDL_Renderer& renderer);
	virtual ~Paddle();

	void update(float dt);
	void draw(SDL_Renderer & renderer);


private:
	Vector2 _position;
	DrawableRect _graphics;
	int _width;
	int _height;
};

