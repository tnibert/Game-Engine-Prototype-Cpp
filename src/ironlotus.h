#ifndef IRONLOTUS_H
#define IRONLOTUS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unordered_map>
#include <vector>
#include <queue>
#include <iostream>

typedef int Layer;

enum class Direction {Left, Right, Up, Down};
enum class LevelState {EndLevel, Proceed};

class Sprite {
    private:
        std::unordered_map<Direction, std::vector<SDL_Texture*>> spritesheet;
        SDL_Rect position;          // position on screen
        int speed;
        Direction facing;
        int cur_frame;
    public:
        Sprite(char*, SDL_Renderer*, Uint32);
        ~Sprite();
        SDL_Texture* getCurrentFrame();
        SDL_Rect* getPosition();
        void move(Direction);
};

/*
 * A renderable object in the scene.
 */
class GameObject {
    public:
        virtual void update() = 0;
        virtual void render(SDL_Renderer*) = 0;
};

class Scene {
    private:
        std::vector<GameObject*> gameObjects;
        SDL_Renderer* renderer;
    public:
        Scene(SDL_Renderer*);
        void attach(GameObject*);
        void remove(GameObject*);
        void updateCycle();
        void renderCycle();
};

/*
 * Implementations define how GameObjects enter and exit the scene
*/
class GameStrategy {
    private:
        Scene *scene;
    public:
        GameStrategy(Scene*);        // GameStrategy takes ownership of Scene
        ~GameStrategy();
        LevelState runFrame();
};

class Player : public GameObject {
    private:
        Sprite *spr;
        std::queue<SDL_Keycode> *inputQueue;
    public:
        Player(SDL_Renderer*, Uint32, std::queue<SDL_Keycode>*);
        ~Player();
        void update();
        void render(SDL_Renderer*);
};

/*class Town : public GameStrategy {

}*/

#endif