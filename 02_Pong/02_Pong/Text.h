#pragma once
#include "Drawable.h"
#include "Rect.h"
#include "Color.h"

#include <memory>
#include <string>
#include <SDL_ttf.h> 

class Text :
	public Drawable
{
public:
	Text();
	Text(const Vector2& position_, const std::string& text_, TTF_Font* font_, int w, int h, const Color& color_, SDL_Renderer& renderer_);
	virtual ~Text();

	void draw(SDL_Renderer& renderer);
	void s_text(const std::string& text_, TTF_Font* font);

private:
	Rect rect;
	Color color;
	std::string text;
	SDL_Texture* texture = nullptr;
	SDL_Renderer* renderer = nullptr;
};
