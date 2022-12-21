#include "ironlotus.h"

GraphicsContext* GraphicsContext::instance = NULL;

GraphicsContext::GraphicsContext(SDL_Window* w) {
    window = w;
    pixelFmt = SDL_GetWindowPixelFormat(window);

    // triggers the program that controls
    // your graphics hardware and sets flags
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    // creates a renderer to render our images
    renderer = SDL_CreateRenderer(window, -1, render_flags);
}

// todo: guarantee or error with this if not initialized
void GraphicsContext::initialize(SDL_Window* w) {
    instance = new GraphicsContext(w);
}

GraphicsContext::~GraphicsContext() {
    SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void GraphicsContext::destroy() {
    delete instance;
}

/*
Load a surface from a file
Return NULL if we can't load the surface
*/
SDL_Surface* GraphicsContext::loadSurface(char *fname) {
    SDL_Surface *temp = NULL;
    SDL_Surface *opt = NULL;

    if ((temp = IMG_Load(fname)) == NULL) {
        return NULL;
    }

    opt = SDL_ConvertSurfaceFormat(temp, instance->pixelFmt, 0);
    SDL_FreeSurface(temp);

    return opt;
}

// todo: error handling with teeth
std::unordered_map<Direction, std::vector<SDL_Texture*>> GraphicsContext::loadSpritesheet(
    SDL_Surface *spritesheet, int rows, int columns) {
    std::unordered_map<Direction, std::vector<SDL_Texture*>> sheet;
    Direction order[4] = {Direction::Down, Direction::Left, Direction::Right, Direction::Up};
    int index = 0;
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < columns; x++) {
            int frame_x_start = x * SPRITE_FRAME_W;
            int frame_y_start = y * SPRITE_FRAME_H;
            
            SDL_Rect clip = {.x = frame_x_start, .y = frame_y_start, .w = SPRITE_FRAME_W, .h = SPRITE_FRAME_H};
            SDL_Surface *cropped = SDL_CreateRGBSurface(0, SPRITE_FRAME_W, SPRITE_FRAME_H, 32, 0, 0, 0, 0);
            if (cropped == NULL) {
                printf("Error creating crop surface: %s\n", SDL_GetError());
            }
            if (SDL_BlitSurface(spritesheet, &clip, cropped, NULL)) {
                printf("Could not create spritesheet frame: %s\n", SDL_GetError());
            }
            SDL_Texture *texture_frame = SDL_CreateTextureFromSurface(instance->renderer, cropped);
            if (texture_frame == NULL) {
                printf("Error converting surface to texture: %s\n", SDL_GetError());
            }
            sheet[order[index]].push_back(texture_frame);
            SDL_FreeSurface(cropped);
        }
        index += 1;
    }
    return sheet; 
}

// todo: add error handling

void GraphicsContext::renderCopy(SDL_Texture* image, SDL_Rect* position) {
    SDL_RenderCopy(instance->renderer, image, NULL, position);
}

void GraphicsContext::renderClear() {
    SDL_RenderClear(instance->renderer);
}
void GraphicsContext::renderPresent() {
    SDL_RenderPresent(instance->renderer);
}