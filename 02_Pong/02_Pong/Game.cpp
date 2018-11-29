#include "Game.h"
#include <string>
#include <SDL_image.h>
#include "Color.h"

Game::Game()
{
}


Game::~Game()
{
	//delete(rect);
	//SDL_DestroyTexture(texture);
	//texture = nullptr;
}

void Game::load(SDL_Renderer& renderer)
{
	/*
	// Load image
	std::string path = "assets/tile.png";
	SDL_Surface* loaded = IMG_Load(path.c_str());
	texture = SDL_CreateTextureFromSurface(&renderer, loaded);
	SDL_FreeSurface(loaded);

	// Rect
	rect = new SDL_Rect();
	rect->x = 100;
	rect->y = 100;
	rect->w = 20;
	rect->h = 20;
	*/

	leftPaddle = DrawableRect(Vector2(0, 200), 50, 50, Color());

	Vector2 ballPosition = Vector2(400, 400);
	Vector2 ballSpeed = Vector2(1, 1);
	ball = Ball(ballPosition, ballSpeed);

}

void Game::update(float dt)
{
	ball.update(dt);
}

void Game::draw(SDL_Renderer& renderer)
{
	SDL_RenderClear(&renderer);

	//SDL_RenderCopy(&renderer, texture, nullptr, rect);
	leftPaddle.draw(renderer);
	ball.draw(renderer);

	SDL_RenderPresent(&renderer);
}
