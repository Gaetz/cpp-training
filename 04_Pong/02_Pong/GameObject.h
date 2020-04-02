#pragma once
#include <SDL.h>
#include "Vector2.h"
#include "Input.h"

class GameObject
{
public:
	GameObject();
	GameObject(const Vector2& position_);
	virtual ~GameObject();

	Vector2 get_position() const;
	void set_position(const Vector2& v);

	virtual void update(float dt) = 0;
	virtual void draw(SDL_Renderer& renderer_) = 0;

protected:
	Vector2 position;
};

