#include "Paddle.h"
#include "Input.h"
#include <algorithm>
#include "Constants.h"

Paddle::Paddle()
{
}

Paddle::Paddle(Vector2 position, Vector2 size, SDL_Renderer& renderer): GameObject(position), width_(static_cast<int>(size.x())), height_(static_cast<int>(size.y()))
{
	graphics_ = DrawableRect(position, static_cast<int>(size.x()), static_cast<int>(size.y()), Color(), renderer);
}


Paddle::~Paddle()
{
}

void Paddle::update(float dt)
{
	float y = Input::mousePos().y() - height_ / 2;
	y = std::clamp<float>(y, 0, static_cast<float>(SCREEN_HEIGHT - height_));
	position_.setY(y);
	graphics_.setPosition(position_);
}

void Paddle::draw(SDL_Renderer & renderer)
{
	graphics_.draw(renderer);
}

int Paddle::width()
{
	return width_;
}

int Paddle::height()
{
	return height_;
}
