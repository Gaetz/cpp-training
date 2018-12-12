#pragma once
#include <SDL.h>
#include "Vector2.h"

class GameObject
{
public:
	GameObject();
	GameObject(const Vector2& position_);
	virtual ~GameObject();

	Vector2 _position() const;
	Vector2& r_position();
	void s_position(const Vector2& v);

	virtual void update(float dt) = 0;
	virtual void draw(SDL_Renderer& renderer_) = 0;

protected:
	Vector2 position;
};

