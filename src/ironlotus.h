#ifndef IRONLOTUS_H
#define IRONLOTUS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unordered_map>
#include <vector>

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
        GameObject();
        ~GameObject();
        virtual void update() = 0;
        void render(SDL_Renderer*);
};

class Scene {
    private:
        std::vector<GameObject*> gameObjects;
        SDL_Renderer* renderer;
    public:
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
        Scene scene;
    public:
        GameStrategy(Scene);        // GameStrategy takes ownership of Scene
        ~GameStrategy();
        virtual void setup() = 0;
        LevelState runGame();
};

#endif