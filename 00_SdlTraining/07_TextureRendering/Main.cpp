#include <SDL.h> 
#include <SDL_image.h> 
#include <stdio.h> 
#include <string>

// Screen dimension constants 
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// The window we'll be rendering to 
SDL_Window* window = nullptr;

SDL_Renderer* renderer = nullptr;
SDL_Texture* texture = nullptr;

// Quit flag
bool quit = false;

// Event handler
SDL_Event event;

// Starts up SDL and creates window 
bool Init();

// Loads media
bool Load();

// Frees media and shuts down SDL
void Close();

// Load Image
SDL_Surface* LoadSurface(std::string path);



int main(int argc, char* args[])
{
	if (!Init()) {
		printf("Failed to initialize!\n");
		SDL_Delay(1000);
	}
	else {
		if (!Load()) {
			printf("Failed to load media!\n");
			SDL_Delay(1000);
		}
		else {
			while (!quit) {

				// Update events
				while (SDL_PollEvent(&event) != 0) {
					// Program close
					if (event.type == SDL_QUIT) {
						quit = true;
					}
				}

				SDL_RenderClear(renderer);
				SDL_RenderCopy(renderer, texture, nullptr, nullptr);
				SDL_RenderPresent(renderer);

			}
		}
	}

	Close();
	return 0;
}

bool Init()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else {
		//Create window 
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == nullptr) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == nullptr) {
				printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
				success = false;
			}
			else {
				SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					printf("SDL_Image could not be initialised! SDL_Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}
	return success;
}

SDL_Texture* LoadTexture(std::string path)
{
	SDL_Texture* loadedTexture = nullptr;
	SDL_Surface* loaded = IMG_Load(path.c_str());
	if (loaded == nullptr) {
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), IMG_GetError());
	}
	else {
		loadedTexture = SDL_CreateTextureFromSurface(renderer, loaded);
		if (loadedTexture == nullptr) {
			printf("Unable to create texture from surface %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		SDL_FreeSurface(loaded);
	}

	return loadedTexture;
}

bool Load()
{
	bool success = true;
	texture = LoadTexture("png.png");
	if (texture == nullptr) {
		printf("Failed to texture!\n");
		success = false;
	}

	return success;
}

void Close()
{
	SDL_DestroyTexture(texture);
	texture = nullptr;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = nullptr;
	window = nullptr;

	SDL_Quit();
}