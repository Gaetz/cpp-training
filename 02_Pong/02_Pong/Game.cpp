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

}

void Game::load(SDL_Renderer& renderer)
{
	leftPaddle_ = std::make_shared<Paddle>(Vector2(0, 200), Vector2(20, 100), renderer);

	Vector2 ballPosition = BALL_START;
	Vector2 ballSpeed = BALL_SPEED;
	ball = Ball(ballPosition, ballSpeed, renderer, leftPaddle_);
}

void Game::update(float dt)
{
	leftPaddle_->update(dt);
	ball.update(dt);
	if (ball.position().x() < 0) {
		ball.setPosition(BALL_START);
		ball.setSpeed(BALL_SPEED);
	}
}

void Game::draw(SDL_Renderer& renderer)
{
	SDL_RenderClear(&renderer);

	leftPaddle_->draw(renderer);
	ball.draw(renderer);

	SDL_RenderPresent(&renderer);
}
