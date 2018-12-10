#pragma once
#include <SDL.h> 
#include "Paddle.h"
#include "Ball.h"
#include <memory>

class Game
{
public:
	Game();
	~Game();

	void load(SDL_Renderer& renderer);
	void update(float dt);
	void draw(SDL_Renderer& renderer);

private:
	void reset();

	std::shared_ptr<Paddle> leftPaddle_;
	std::shared_ptr<Paddle> rightPaddle_;
	Ball ball;
};

