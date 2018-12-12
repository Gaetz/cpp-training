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

	std::shared_ptr<Paddle> left_paddle;
	std::shared_ptr<Paddle> right_paddle;
	Ball ball;
	int left_score;
	int right_score;
	Text left_score_text;
	Text right_score_text;
	TTF_Font* font;

};

