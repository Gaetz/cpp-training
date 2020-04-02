#include <SDL.h> 
#include <stdio.h> 
#include <string>

enum KeyPressSurfaces
{
	SURFACE_DEFAULT,
	SURFACE_UP,
	SURFACE_DOWN,
	SURFACE_LEFT,
	SURFACE_RIGHT,
	SURFACE_TOTAL
};

// Screen dimension constants 
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// The window we'll be rendering to 
SDL_Window* window = nullptr;

// The surface contained by the window 
SDL_Surface* screenSurface = nullptr;

// Array of images that correspond to a keypress
SDL_Surface* keyPressSurfaces[SURFACE_TOTAL];

// Current displayed image
SDL_Surface* currentSurface = nullptr;

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
	}
	else {
		if (!Load()) {
			printf("Failed to load media!\n");
		}
		else {
			while (!quit) {

				// Update events
				while (SDL_PollEvent(&event) != 0) {
					// Program close
					if (event.type == SDL_QUIT) {
						quit = true;
					}
					// Key press
					else if (event.type == SDL_KEYDOWN) {
						switch (event.key.keysym.sym) {
						case SDLK_UP:
							currentSurface = keyPressSurfaces[SURFACE_UP];
							break;
						case SDLK_DOWN:
							currentSurface = keyPressSurfaces[SURFACE_DOWN];
							break;
						case SDLK_RIGHT:
							currentSurface = keyPressSurfaces[SURFACE_RIGHT];
							break;
						case SDLK_LEFT:
							currentSurface = keyPressSurfaces[SURFACE_LEFT];
							break;
						default:
							currentSurface = keyPressSurfaces[SURFACE_DEFAULT];
							break;
						}
					}
				}

				// Draw
				SDL_BlitSurface(currentSurface, nullptr, screenSurface, nullptr);
				SDL_UpdateWindowSurface(window);
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
	}
	else {
		//Create window 
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == nullptr) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			//Get window surface 
			screenSurface = SDL_GetWindowSurface(window);
		}
	}
	return success;
}

bool Load()
{
	bool success = true;
	// Standard
	keyPressSurfaces[SURFACE_DEFAULT] = LoadSurface("press.bmp");
	if (keyPressSurfaces[SURFACE_DEFAULT] == nullptr) {
		printf("Failed to load default image!\n");
		success = false;
	}
	// Up
	keyPressSurfaces[SURFACE_UP] = LoadSurface("up.bmp");
	if (keyPressSurfaces[SURFACE_UP] == nullptr) {
		printf("Failed to load up image!\n");
		success = false;
	}
	// Down
	keyPressSurfaces[SURFACE_DOWN] = LoadSurface("down.bmp");
	if (keyPressSurfaces[SURFACE_DOWN] == nullptr) {
		printf("Failed to load down image!\n");
		success = false;
	}
	// Left
	keyPressSurfaces[SURFACE_LEFT] = LoadSurface("left.bmp");
	if (keyPressSurfaces[SURFACE_LEFT] == nullptr) {
		printf("Failed to load left image!\n");
		success = false;
	}
	// Right
	keyPressSurfaces[SURFACE_RIGHT] = LoadSurface("right.bmp");
	if (keyPressSurfaces[SURFACE_RIGHT] == nullptr) {
		printf("Failed to load right image!\n");
		success = false;
	}

	currentSurface = keyPressSurfaces[SURFACE_DEFAULT];
	return success;
}

SDL_Surface* LoadSurface(std::string path)
{
	SDL_Surface* loaded = SDL_LoadBMP(path.c_str());
	if (loaded == nullptr) {
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}
	return loaded;
}

void Close()
{
	SDL_FreeSurface(currentSurface);
	currentSurface = nullptr;

	SDL_DestroyWindow(window);
	window = nullptr;

	SDL_Quit();
}