#include "Paddle.h"



Paddle::Paddle()
{
}

Paddle::Paddle(Vector2 position, Vector2 size, SDL_Renderer& renderer): position_(position), width_(static_cast<int>(size.x())), height_(static_cast<int>(size.y()))
{
	graphics_ = DrawableRect(position, static_cast<int>(size.x()), static_cast<int>(size.y()), Color(), renderer);
}


Paddle::~Paddle()
{
}

void Paddle::update(float dt)
{
	graphics_.setPosition(position_);
}

void Paddle::draw(SDL_Renderer & renderer)
{
	graphics_.draw(renderer);
}
