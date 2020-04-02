#include <SDL.h> 
#include <SDL_image.h> 
#include <stdio.h> 
#include <string>

// Screen dimension constants 
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// The window we'll be rendering to 
SDL_Window* window = nullptr;

// The surface contained by the window 
SDL_Surface* screenSurface = nullptr;

// Current displayed image
SDL_Surface* optimisedSurface = nullptr;

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
				}

				// Draw the image stretched 
				SDL_Rect stretchRect;
				stretchRect.x = 0;
				stretchRect.y = 0;
				stretchRect.w = SCREEN_WIDTH;
				stretchRect.h = SCREEN_HEIGHT;
				SDL_BlitScaled(optimisedSurface, NULL, screenSurface, &stretchRect);
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
			int imgFlags = IMG_INIT_PNG;
			if(! (IMG_Init(imgFlags) & imgFlags) ) {
				printf("SDL_Image could not be initialised! SDL_Error: %s\n", IMG_GetError());
				success = false;
			}
			//Get window surface 
			screenSurface = SDL_GetWindowSurface(window);
		}
	}
	return success;
}

bool Load()
{
	bool success = true;
	optimisedSurface = LoadSurface("png.png");
	if (optimisedSurface == nullptr) {
		printf("Failed to load optimized surface!\n");
		success = false;
	}

	return success;
}

SDL_Surface* LoadSurface(std::string path)
{
	SDL_Surface* loaded = IMG_Load(path.c_str());
	if (loaded == nullptr) {
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), IMG_GetError());
	}
	SDL_Surface* optimised = SDL_ConvertSurface(loaded, screenSurface->format, NULL);
	if (optimised == nullptr) {
		printf("Unable to optimise image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}
	SDL_FreeSurface(loaded);
	return optimised;
}

void Close()
{
	SDL_FreeSurface(optimisedSurface);
	optimisedSurface = nullptr;

	SDL_DestroyWindow(window);
	window = nullptr;

	SDL_Quit();
}