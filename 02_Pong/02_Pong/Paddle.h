#pragma once
#include "GameObject.h"
#include "DrawableRect.h"

class Paddle :
	public GameObject
{
public:
	Paddle();
	Paddle(Vector2 position, Vector2 size, SDL_Renderer& renderer, bool isPlayer);
	virtual ~Paddle();

	void update(float dt);
	void draw(SDL_Renderer & renderer);

	int width();
	int height();


private:
	DrawableRect graphics_;
	int width_;
	int height_;
	bool isPlayer_;
};

