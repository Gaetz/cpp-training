#pragma once
#include "GameObject.h"
#include "DrawableRect.h"

class Paddle :
	public GameObject
{
public:
	Paddle();
	Paddle(const Vector2& position_, const Vector2& size_, SDL_Renderer& renderer_, bool is_player_);
	virtual ~Paddle();

	void update(float dt);
	void draw(SDL_Renderer & renderer_);

	int _width() const;
	int _height() const;


private:
	DrawableRect graphics;
	int width;
	int height;
	bool is_player;
};

