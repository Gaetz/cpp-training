#include <SDL.h> 
#include <SDL_image.h> 
#include <string>

#include "Game.h"

// Screen dimension constants 
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Window and renderer
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

// Quit flag<
bool quit = false;

// Delta time
const int FPS = 60;
const int frameDelay = 1000 / FPS;
int frameStart;
int lastFrame = 0;
int dt;
int frameTime;

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

	// Load game
	Game game;
	game.load(*renderer);

	float dt = 0;
	// Loop
	while (!quit) {
		// Delta time
		frameStart = SDL_GetTicks();
		dt = (frameStart - lastFrame) * 0.001;
		lastFrame = frameStart;

		// Update events
		while (SDL_PollEvent(&event) != 0) {
			// Program close
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}
		game.update(dt);
		game.draw(*renderer);

		// Delay frame if game runs too fast
		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < frameDelay) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	// Close
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = nullptr;
	window = nullptr;

	SDL_Quit();
	return 0;
}