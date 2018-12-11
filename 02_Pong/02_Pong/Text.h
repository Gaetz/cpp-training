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
	Text(const Vector2& position, const std::string& text, TTF_Font* font, int w, int h, const Color& color, SDL_Renderer& renderer);
	virtual ~Text();

	void draw(SDL_Renderer& renderer);
	void setText(const std::string& text, TTF_Font* font);

private:
	Rect rect_;
	Color color_;
	std::string text_;
	SDL_Texture* texture_ = nullptr;
	SDL_Renderer* renderer_ = nullptr;
};
