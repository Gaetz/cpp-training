#include "Game.h"
#include <string>
#include <SDL_image.h>
#include "Color.h"
#include "Constants.h"

Game::Game()
{
}


Game::~Game()
{
	TTF_CloseFont(font);
	TTF_Quit();
}

void Game::load(SDL_Renderer& renderer)
{
	left_paddle = std::make_shared<Paddle>(Vector2(0, 200), Vector2(20, 100), renderer, true);
	right_paddle = std::make_shared<Paddle>(OPPONENT_START, Vector2(20, 100), renderer, false);
	font = TTF_OpenFont("assets/arial.ttf", 24);

	ball = Ball(BALL_START, BALL_SPEED, renderer, left_paddle, right_paddle);

	left_score = 0;
	right_score = 0;
	std::string left_score_string = std::to_string(left_score);
	std::string right_score_string = std::to_string(right_score);
	Color text_color = Color(255, 255, 255, 255);
	left_score_text = Text(Vector2(50, 50), left_score_string, font, 60, 60, text_color, renderer);
	right_score_text = Text(Vector2(SCREEN_WIDTH - 100, 50), right_score_string, font, 60, 60, text_color, renderer);
	left_score_text.s_text(left_score_string, font);
	right_score_text.s_text(right_score_string, font);
}

void Game::update(float dt)
{
	left_paddle->update(dt);
	right_paddle->update(dt);

	ball.update(dt);
	if (ball._position()._x() < 0) 
	{
		right_score_text.s_text(std::to_string(++right_score), font);
		reset();
	}
	else if (ball._position()._x() > SCREEN_WIDTH) 
	{
		left_score_text.s_text(std::to_string(++left_score), font);
		reset();
	}
}

void Game::draw(SDL_Renderer& renderer)
{
	SDL_RenderClear(&renderer);

	left_paddle->draw(renderer);
	right_paddle->draw(renderer);
	ball.draw(renderer);
	left_score_text.draw(renderer);
	right_score_text.draw(renderer);

	SDL_RenderPresent(&renderer);
}

void Game::reset() 
{
	ball.s_position(BALL_START);
	ball.s_speed(BALL_SPEED);
}