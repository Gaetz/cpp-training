#pragma once
#include <SDL.h> 
#include "Paddle.h"
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
	Paddle leftPaddle;
	Ball ball;
};

