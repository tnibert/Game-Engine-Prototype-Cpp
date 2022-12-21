#include "ironlotus.h"
#include <iostream>
#include <stdlib.h>

const int SS_DOWN = 4;
const int SS_ACROSS = 3;

Sprite::Sprite(char *spritesheet_fname) {
    std::cout << "constructing sprite" << std::endl;

    SDL_Surface *temp_surface = GraphicsContext::loadSurface(spritesheet_fname);
    if (temp_surface == NULL) {
        printf("Could not load spritesheet");
    }
    spritesheet = GraphicsContext::loadSpritesheet(temp_surface, SS_DOWN, SS_ACROSS);
    SDL_FreeSurface(temp_surface);

    position.x = 20;
    position.y = 20;
    position.w = SPRITE_FRAME_W;
    position.h = SPRITE_FRAME_H;

    speed = 5;

    facing = Direction::Down;

    cur_frame = 0;

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
    return spritesheet[facing].at(cur_frame%SS_ACROSS);
}

SDL_Rect* Sprite::getPosition() {
    return &position;
}

// todo: boundary checking
void Sprite::move(Direction d) {
    facing = d;
    switch (d) {
        case Direction::Left: 
            position.x -= speed;
            break;
        case Direction::Right:
            position.x += speed;
            break;
        case Direction::Up:
            position.y -= speed;
            break;
        case Direction::Down:
            position.y += speed;
            break;
    }
    cur_frame++;
}