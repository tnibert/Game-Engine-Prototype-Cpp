#include "ironlotus.h"
#include <stdio.h>

const int FPS = 30;

//https://stackoverflow.com/questions/32294913/getting-contiunous-window-resize-event-in-sdl-2
static int resizeCallback(void *data, SDL_Event *event) {
	if (event->type == SDL_WINDOWEVENT && event->window.event == SDL_WINDOWEVENT_RESIZED) {
		SDL_Window *win = SDL_GetWindowFromID(event->window.windowID);
		if (win == (SDL_Window *)data) {
			printf("resizing.....\n");
		}
	}
	return 0;
}

int main(int argc, char *argv[]) {
	SDL_Window *sdl_window = nullptr;

	unsigned int window_flags = SDL_WINDOW_OPENGL;

	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		printf("Failed to init SDL, error: %s", SDL_GetError());
		return -1;
	}

	int win_width = 640;
	int win_height = 480;
	enum class SCREENSIZE {
		is640x480,
		is1366x768,
		fullscreen
	} curr_screen_size = SCREENSIZE::is640x480,
	  last_non_fullscreen_size = SCREENSIZE::is640x480;

	// Create an application window with the following settings:
	sdl_window = SDL_CreateWindow(
		"Iron Lotus Demo (F11: fullscreen ESC: quit)",
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
    SDL_Renderer* rend = SDL_CreateRenderer(sdl_window, -1, render_flags);

	Sprite *spr = new Sprite("../assets/reaper.png", rend, SDL_GetWindowPixelFormat(sdl_window));

	SDL_AddEventWatch(resizeCallback, sdl_window);

	bool isRunning = true;
	SDL_Event sdl_event;
	while (isRunning) {
		// 1. check events
		while (SDL_PollEvent(&sdl_event) != 0) {
			if (sdl_event.type == SDL_QUIT) {
				isRunning = false;
			}
			else if (sdl_event.type == SDL_KEYDOWN) {
				switch (sdl_event.key.keysym.sym) {
					case SDLK_ESCAPE:
						isRunning = false;
						break;
					// todo: this full screen doesn't currently scale anything, it changes the dimensions
					case SDLK_F11:
						if (curr_screen_size != SCREENSIZE::fullscreen) { // then set it to fullscreen and save prev state
							last_non_fullscreen_size = curr_screen_size;
							curr_screen_size = SCREENSIZE::fullscreen;
							SDL_SetWindowFullscreen(sdl_window, window_flags | SDL_WINDOW_FULLSCREEN_DESKTOP);
						} else { // is currently fullscreen, set it back to the prev state
							curr_screen_size = last_non_fullscreen_size;
							SDL_SetWindowFullscreen(sdl_window, window_flags);
						}
						SDL_GetWindowSize(sdl_window, &win_width, &win_height);
						break;
					case SDLK_RIGHT:
						spr->move(Direction::Right);
						break;
					case SDLK_DOWN:
						spr->move(Direction::Down);
						break;
					case SDLK_UP:
						spr->move(Direction::Up);
						break;
					case SDLK_LEFT:
						spr->move(Direction::Left);
						break;
				}
			}
		}

		// 2. update screen

		// clears the screen
		SDL_RenderClear(rend);
		SDL_RenderCopy(rend, spr->getCurrentFrame(), NULL, spr->getPosition());

		// triggers the double buffers
		// for multiple rendering
		SDL_RenderPresent(rend);

		SDL_Delay(1000 / FPS);
	}

	// clean up
    delete spr;
    SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(sdl_window);
	SDL_Quit();

	return 0;
}