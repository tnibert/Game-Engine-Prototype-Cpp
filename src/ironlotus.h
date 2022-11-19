#ifndef IRONLOTUS_H
#define IRONLOTUS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unordered_map>
#include <vector>

enum class Direction {Left, Right, Up, Down};

class Sprite {
    private:
        std::unordered_map<Direction, std::vector<SDL_Texture*>> spritesheet;
        SDL_Rect position;
    public:
        Sprite(char*, SDL_Renderer*, SDL_Window*);
        ~Sprite();
        SDL_Texture* getCurrentFrame();
};

#endif