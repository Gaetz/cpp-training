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
	TTF_CloseFont(font_);
	TTF_Quit();
}

void Game::load(SDL_Renderer& renderer)
{
	leftPaddle_ = std::make_shared<Paddle>(Vector2(0, 200), Vector2(20, 100), renderer, true);
	rightPaddle_ = std::make_shared<Paddle>(Vector2(SCREEN_WIDTH - 20, 200), Vector2(20, 100), renderer, false);
	font_ = TTF_OpenFont("assets/arial.ttf", 24);

	Vector2 ballPosition = BALL_START;
	Vector2 ballSpeed = BALL_SPEED;
	ball = Ball(ballPosition, ballSpeed, renderer, leftPaddle_, rightPaddle_);

	leftScore_ = 0;
	rightScore_ = 0;
	Color textColor = Color(255, 255, 255, 255);
	leftScoreText_ = Text(Vector2(50, 50), std::to_string(leftScore_), font_, 50, 50, textColor, renderer);
	rightScoreText_ = Text(Vector2(SCREEN_WIDTH - 100, 50), std::to_string(rightScore_), font_, 50, 50, textColor, renderer);
	leftScoreText_.setText(std::to_string(leftScore_), font_);
	rightScoreText_.setText(std::to_string(rightScore_), font_);
}

void Game::update(float dt)
{
	leftPaddle_->update(dt);
	rightPaddle_->update(dt);

	ball.update(dt);
	if (ball.position().x() < 0) {
		rightScoreText_.setText(std::to_string(++rightScore_), font_);
		reset();
	}
	else if (ball.position().x() > SCREEN_WIDTH) {
		leftScoreText_.setText(std::to_string(++leftScore_), font_);
		reset();
	}
}

void Game::draw(SDL_Renderer& renderer)
{
	SDL_RenderClear(&renderer);

	leftPaddle_->draw(renderer);
	rightPaddle_->draw(renderer);
	ball.draw(renderer);
	leftScoreText_.draw(renderer);
	rightScoreText_.draw(renderer);

	SDL_RenderPresent(&renderer);
}

void Game::reset() 
{
	ball.setPosition(BALL_START);
	ball.setSpeed(BALL_SPEED);
}