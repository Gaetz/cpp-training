#include "Game.h"
#include <string>
#include <SDL_image.h>
#include "Color.h"

Game::Game()
{
}


Game::~Game()
{
	delete(rect);
	SDL_DestroyTexture(texture);
	texture = nullptr;
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

	Vector2 shapePosition = Vector2(200, 200);
	Color shapeColor = Color(20, 150, 200, 255);
	shape = DrawableRect(shapePosition, 50, 50, shapeColor);

	Vector2 circlePosition = Vector2(400, 100);
	Color circleColor = Color(200, 150, 50, 255);
	circle = DrawableCircle(circlePosition, 20, 5, circleColor, true);
}

void Game::update(float dt)
{
}

void Game::draw(SDL_Renderer& renderer)
{
	SDL_RenderClear(&renderer);
	SDL_RenderCopy(&renderer, texture, nullptr, rect);
	shape.draw(renderer);
	circle.draw(renderer);
	SDL_RenderPresent(&renderer);
}
