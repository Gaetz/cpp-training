#pragma once
#include <SDL.h> 
#include <SDL_image.h> 
#include <string>

#include "Constants.h"
#include "Game.h"
#include "Input.h"



// Window and renderer
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

// Quit flag<
bool quit = false;

// Delta time
const int FPS = 60;
const float frame_delay = 1000 / FPS;
int frame_start;
int last_frame = 0;
int dt;
int frame_time;


int main(int argc, char* args[])
{
	// Init sdl
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();
	
	// Load game
	Game game;
	game.load(*renderer);

	float dt = 0;
	// Loop
	while (!quit) {
		// Delta time
		frame_start = SDL_GetTicks();
		dt = (frame_start - last_frame) * 0.001f;
		last_frame = frame_start;

		quit = Input::update();
		game.update(dt);
		game.draw(*renderer);

		// Delay frame if game runs too fast
		frame_time = SDL_GetTicks() - frame_start;
		//if (frame_time < frame_delay) {
		//	SDL_Delay(frame_delay - frame_time);
		//}
	}

	// Close
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = nullptr;
	window = nullptr;

	SDL_Quit();
	return 0;
}