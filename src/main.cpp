#include "ironlotus.h"
#include <stdio.h>

const int FPS = 30;

int main(int argc, char *argv[]) {
	SDL_Window *sdl_window = nullptr;

	unsigned int window_flags = SDL_WINDOW_OPENGL /*| SDL_WINDOW_FULLSCREEN_DESKTOP*/;

	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		printf("Failed to init SDL, error: %s", SDL_GetError());
		return -1;
	}

	int win_width = 640;
	int win_height = 480;

	// Create an application window with the following settings:
	sdl_window = SDL_CreateWindow(
		"Iron Lotus Demo (ESC: quit)",
		SDL_WINDOWPOS_UNDEFINED,					  // initial x position
		SDL_WINDOWPOS_UNDEFINED,					  // initial y position
		win_width,									  // width, in pixels
		win_height,									  // height, in pixels
		window_flags								  // flags - see below
	);

	// Check that the window was successfully created
	if (sdl_window == nullptr) {
		printf("Could not create SDL window: %s", SDL_GetError());
		return -1;
	}

	// triggers the program that controls
    // your graphics hardware and sets flags
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
 
    // creates a renderer to render our images
    SDL_Renderer *rend = SDL_CreateRenderer(sdl_window, -1, render_flags);

	std::queue<SDL_Keycode> *inputQueue = new std::queue<SDL_Keycode>();

	// todo: move setup to Town
	Player *player = new Player(rend, SDL_GetWindowPixelFormat(sdl_window), inputQueue);
	Scene *scene = new Scene(rend);
	scene->attach(player);
	GameStrategy *test = new Town(scene);

	bool isRunning = true;
	SDL_Event sdl_event;
	while (isRunning) {
		// check events
		while (SDL_PollEvent(&sdl_event) != 0) {
			if (sdl_event.type == SDL_QUIT) {
				isRunning = false;
			}
			else if (sdl_event.type == SDL_KEYDOWN) {
				switch (sdl_event.key.keysym.sym) {
					case SDLK_ESCAPE:
						isRunning = false;
						break;
					case SDLK_RIGHT:
						inputQueue->push(SDLK_RIGHT);
						break;
					case SDLK_DOWN:
						inputQueue->push(SDLK_DOWN);
						break;
					case SDLK_UP:
						inputQueue->push(SDLK_UP);
						break;
					case SDLK_LEFT:
						inputQueue->push(SDLK_LEFT);
						break;
				}
			}
		}
		
		test->runFrame();

		SDL_Delay(1000 / FPS);
	}

	// clean up
    delete player;
	delete test;
	delete inputQueue;
    SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(sdl_window);
	SDL_Quit();

	return 0;
}