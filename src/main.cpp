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

	// todo: create window within initialize()
	GraphicsContext::initialize(sdl_window);

	std::queue<SDL_Keycode> *inputQueue = new std::queue<SDL_Keycode>();

	Player *player = new Player(inputQueue);
	std::cout << player << std::endl;

	Town *gameTown = new Town(player);

	bool isRunning = true;
	SDL_Event sdl_event;
	std::cout << player << std::endl;
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
		
		gameTown->runFrame();

		SDL_Delay(1000 / FPS);
	}
	std::cout << player << std::endl;

	// clean up
	std::cout << "1" << std::endl;
	delete gameTown;
	std::cout << "2" << std::endl;
    delete player;
	std::cout << "3" << std::endl;
	delete inputQueue;
	std::cout << "4" << std::endl;
    GraphicsContext::destroy();
	SDL_Quit();

	return 0;
}