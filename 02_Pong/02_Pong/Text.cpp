#include "Text.h"

Text::Text()
{
}

Text::Text(const Vector2& position_, const std::string& text_, TTF_Font* font_, int w, int h, const Color & color_, SDL_Renderer & renderer_):
	Drawable(position_), text(text_), color(color_), renderer(&renderer_)
{
	rect = Rect(0, 0, w, h);
}

Text::~Text()
{
	renderer = nullptr;
	SDL_DestroyTexture(texture);
}

void Text::draw(SDL_Renderer & renderer)
{
	SDL_RenderCopy(&renderer, texture, nullptr, rect.to_sdl_rect(position).get());
}

void Text::set_text(const std::string & text_, TTF_Font* font_)
{
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
	}
	text = text_;
	SDL_Surface* surface = TTF_RenderText_Solid(font_, text.c_str(), color.to_sdl_color());
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}
