#pragma once
#include <SDL.h> 
#include <SDL_ttf.h> 

#include "Paddle.h"
#include "Ball.h"
#include "Text.h"
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
	int leftScore_;
	int rightScore_;
	Text leftScoreText_;
	Text rightScoreText_;
	TTF_Font* font_;

};

