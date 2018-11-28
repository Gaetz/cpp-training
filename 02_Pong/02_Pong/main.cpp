#include <SDL.h> 
#include <SDL_image.h> 
#include <string>

// Screen dimension constants 
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Window and renderer
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

// Texture and rect
SDL_Texture* texture = nullptr;
SDL_Rect * rect = nullptr;

// Quit flag<
bool quit = false;

// Event handler
SDL_Event event;


int main(int argc, char* args[])
{
	// Init sdl
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	IMG_Init(IMG_INIT_PNG);

	// Load image
	std::string path = "assets/tile.png";
	SDL_Surface* loaded = IMG_Load(path.c_str());
	texture = SDL_CreateTextureFromSurface(renderer, loaded);
	SDL_FreeSurface(loaded);

	// Rect
	rect = new SDL_Rect();
	rect->x = 100;
	rect->y = 100;
	rect->w = 20;
	rect->h = 20;

	// Loop
	while (!quit) {
		// Update events
		while (SDL_PollEvent(&event) != 0) {
			// Program close
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}

		// Draw
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, nullptr, rect);
		SDL_RenderPresent(renderer);
	}

	// Close
	delete(rect);
	SDL_DestroyTexture(texture);
	texture = nullptr;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = nullptr;
	window = nullptr;

	SDL_Quit();
	return 0;
}