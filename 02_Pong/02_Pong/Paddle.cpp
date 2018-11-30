#include "Paddle.h"



Paddle::Paddle()
{
}

Paddle::Paddle(Vector2 position, Vector2 size, SDL_Renderer& renderer): _position(position), _width(static_cast<int>(size.x())), _height(static_cast<int>(size.y()))
{
	_graphics = DrawableRect(position, static_cast<int>(size.x()), static_cast<int>(size.y()), Color(), renderer);
}


Paddle::~Paddle()
{
}

void Paddle::update(float dt)
{
	_graphics.setPosition(_position);
}

void Paddle::draw(SDL_Renderer & renderer)
{
	_graphics.draw(renderer);
}
