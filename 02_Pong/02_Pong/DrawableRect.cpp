#include "DrawableRect.h"

DrawableRect::DrawableRect(): Drawable(Vector2(0, 0)), _color(Color(255, 255, 255, 255))
{
	_rect = Rect(0, 0, 1, 1);
}

DrawableRect::DrawableRect(const Vector2& position, int w, int h, const Color& color, SDL_Renderer& renderer): Drawable(position), _color(color)
{
	_rect = Rect(0, 0, w, h);
	loadSurface();
	loadTexture(renderer);
}


DrawableRect::~DrawableRect()
{
	SDL_DestroyTexture(_texture);
	_texture = nullptr;
}

void DrawableRect::draw(SDL_Renderer& renderer) 
{
	SDL_RenderCopy(&renderer, _texture, nullptr, _rect.toSDLRect(_position).get());
}

void DrawableRect::loadSurface() {/*
	Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif

	_surface = SDL_CreateRGBSurface(0, _rect.w(), _rect.h(), 32, rmask, gmask, bmask, amask);
	SDL_FillRect(_surface, NULL, SDL_MapRGB(_surface->format, _color.r, _color.g, _color.b));*/
	_surface = SDL_CreateRGBSurface(0, _rect.w(), _rect.h(), 32, 0, 0, 0, 0);

	/* Filling the surface with red color. */
	SDL_FillRect(_surface, NULL, SDL_MapRGB(_surface->format, 255, 0, 0));
}

void DrawableRect::loadTexture(SDL_Renderer & renderer) {
	_texture = SDL_CreateTextureFromSurface(&renderer, _surface);
	SDL_FreeSurface(_surface);
	_surface = nullptr;
}