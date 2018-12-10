#include "Text.h"

Text::Text()
{
}

Text::Text(const Vector2 & position, std::string& text, std::string& font, int w, int h, const Color & color, SDL_Renderer & renderer):
	Drawable(position), text_(text), color_(color)
{
	font_ = std::make_unique<TTF_Font>(TTF_OpenFont(font.c_str(), 24));
	color_ = color;
	SDL_Surface* surface = TTF_RenderText_Solid(font_.get(), text.c_str(), color_.toSDLColor());
	texture_ = std::make_unique<SDL_Texture>(SDL_CreateTextureFromSurface(&renderer, surface));
	rect_ = Rect(0, 0, w, h);
}

Text::~Text()
{
}

void Text::draw(SDL_Renderer & renderer)
{
	SDL_RenderCopy(&renderer, texture_.get(), nullptr, rect_.toSDLRect(position_).get());
}

void Text::setText(std::string & text, SDL_Renderer & renderer)
{
	SDL_Surface* surface = TTF_RenderText_Solid(font_.get(), text.c_str(), color_.toSDLColor());
	texture_ = std::make_unique<SDL_Texture>(SDL_CreateTextureFromSurface(&renderer, surface));
}
