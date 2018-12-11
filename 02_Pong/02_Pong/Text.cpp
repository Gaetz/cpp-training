#include "Text.h"

Text::Text()
{
}

Text::Text(const Vector2& position, const std::string& text, TTF_Font* font, int w, int h, const Color & color, SDL_Renderer & renderer):
	Drawable(position), text_(text), color_(color), renderer_(&renderer)
{
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color_.toSDLColor());
	texture_ = SDL_CreateTextureFromSurface(&renderer, surface);
	rect_ = Rect(0, 0, w, h);
	SDL_FreeSurface(surface);
}

Text::~Text()
{
	renderer_ = nullptr;
	SDL_DestroyTexture(texture_);
}

void Text::draw(SDL_Renderer & renderer)
{
	SDL_RenderCopy(&renderer, texture_, nullptr, rect_.toSDLRect(position_).get());
}

void Text::setText(const std::string & text, TTF_Font* font)
{
	SDL_DestroyTexture(texture_);
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color_.toSDLColor());
	texture_ = SDL_CreateTextureFromSurface(renderer_, surface);
	SDL_FreeSurface(surface);
}
