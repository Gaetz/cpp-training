#include "Game.h"
#include <string>
#include <SDL_image.h>
#include "Color.h"

Game::Game()
{
}


Game::~Game()
{

}

void Game::load(SDL_Renderer& renderer)
{
	leftPaddle = DrawableRect(Vector2(0, 200), 50, 50, Color(), renderer);

	Vector2 ballPosition = Vector2(100, 100);
	Vector2 ballSpeed = Vector2(250, 250);
	//ball = Ball(ballPosition, ballSpeed);
}

void Game::update(float dt)
{
	//ball.update(dt);
}

void Game::draw(SDL_Renderer& renderer)
{
	SDL_RenderClear(&renderer);

	leftPaddle.draw(renderer);
	//ball.draw(renderer);

	SDL_RenderPresent(&renderer);
}
