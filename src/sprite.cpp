#include "ironlotus.h"
#include <iostream>
#include <stdlib.h>

const int SPRITE_FRAME_W = 96/3;
const int SPRITE_FRAME_H = 144/4;
const int SS_DOWN = 4;
const int SS_ACROSS = 3;

/*
Load a surface from a file
Return NULL if we can't load the surface
*/
SDL_Surface* loadSurface(SDL_Window *window, char *fname) {
    SDL_Surface *temp = NULL;
    SDL_Surface *opt = NULL;

    if ((temp = IMG_Load(fname)) == NULL) {
        return NULL;
    }

    if(window == NULL) return NULL;

    opt = SDL_ConvertSurfaceFormat(temp, SDL_GetWindowPixelFormat(window), 0);
    SDL_FreeSurface(temp);

    return opt;
}

// todo: error handling with teeth
std::unordered_map<Direction, std::vector<SDL_Texture*>> loadSpritesheet(SDL_Renderer *rend, SDL_Surface *spritesheet, int rows, int columns) {
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
                printf("error creating crop surface: %s\n", SDL_GetError());
            }
            if (SDL_BlitSurface(spritesheet, NULL, cropped, &clip)) {
                printf("Could not create spritesheet frame: %s\n", SDL_GetError());
            }
            sheet[order[index]].push_back(SDL_CreateTextureFromSurface(rend, cropped));
            SDL_FreeSurface(cropped);
        }
        index += 1;
    }
    return sheet; 
}


Sprite::Sprite(char *spritesheet_fname, SDL_Renderer *rend, SDL_Window *window) {
    std::cout << "constructing sprite" << std::endl;

    SDL_Surface *temp_surface = loadSurface(window, spritesheet_fname);
    if (temp_surface == NULL) {
        printf("Could not load spritesheet");
    }
    spritesheet = loadSpritesheet(rend, temp_surface, SS_DOWN, SS_ACROSS);
    SDL_FreeSurface(temp_surface);
    std::cout << "constructing sprite completed" << std::endl;
}

Sprite::~Sprite() {
    for (const auto &direction_vec : spritesheet) {
        for(SDL_Texture *tex : direction_vec.second) {
            std::cout << "Destroying sprite texture" << std::endl;
            SDL_DestroyTexture(tex);
        }
    }
}

SDL_Texture* Sprite::getCurrentFrame() {
    return spritesheet[Direction::Down].at(0);
}