#pragma once
#include <SDL.h> 
#include "DrawableRect.h"
#include "Ball.h"

class Game
{
public:
	Game();
	~Game();

	void load(SDL_Renderer& renderer);
	void update(float dt);
	void draw(SDL_Renderer& renderer);

private:
	//SDL_Texture* texture;
	//SDL_Rect * rect;
	DrawableRect leftPaddle;
	//Ball ball;
};

