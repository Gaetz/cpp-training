#include <SDL.h> 
#include <stdio.h> 

//Screen dimension constants 
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// The window we'll be rendering to 
SDL_Window* window = nullptr;
// The surface contained by the window 
SDL_Surface* screenSurface = nullptr;
// The image we will load and show on the screen
SDL_Surface* helloWorld = nullptr;

// Starts up SDL and creates window 
bool Init();

// Loads media
bool LoadMedia();

// Frees media and shuts down SDL
void Close();

int main(int argc, char* args[])
{
	if (!Init()) {
		printf("Failed to initialize!\n");
	}
	else {
		if (!LoadMedia()) {
			printf("Failed to load media!\n");
		}
		else {
			SDL_BlitSurface(helloWorld, nullptr, screenSurface, nullptr);
			SDL_UpdateWindowSurface(window);
			//Wait two seconds
			SDL_Delay( 2000 );
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

bool LoadMedia()
{
	bool success = true;
	helloWorld = SDL_LoadBMP("helloworld.bmp");
	if (helloWorld == nullptr) {
		printf("Unable to load image %s! SDL Error: %s\n", "helloworld.bmp", SDL_GetError());
		success = false;
	}
	return success;
}

void Close()
{
	SDL_FreeSurface(helloWorld);
	helloWorld = nullptr;

	SDL_DestroyWindow(window);
	window = nullptr;

	SDL_Quit();
}