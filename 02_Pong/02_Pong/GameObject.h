#pragma once
#include <SDL.h>
#include "Vector2.h"

class GameObject
{
public:
	GameObject();
	GameObject(Vector2& position);
	virtual ~GameObject();

	Vector2 position() const;
	Vector2& rPosition();
	void setPosition(const Vector2& v);

	virtual void update(float dt) = 0;
	virtual void draw(SDL_Renderer& renderer) = 0;

protected:
	Vector2 position_;
};

