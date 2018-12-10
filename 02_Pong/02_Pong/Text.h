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
	Text(const Vector2& position, std::string& text, std::string& font, int w, int h, const Color& color, SDL_Renderer& renderer);
	virtual ~Text();

	void draw(SDL_Renderer& renderer);
	void setText(std::string& text, SDL_Renderer & renderer);

private:
	Rect rect_;
	Color color_;
	std::string text_;
	std::unique_ptr<TTF_Font> font_;
	std::unique_ptr<SDL_Texture> texture_;
};
