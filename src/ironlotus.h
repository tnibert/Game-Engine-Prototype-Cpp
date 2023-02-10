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

// todo: temporary defines, replace with something better
#define SPRITE_FRAME_W 96/3
#define SPRITE_FRAME_H 144/4

class Sprite {
    private:
        std::unordered_map<Direction, std::vector<SDL_Texture*>> spritesheet;
        SDL_Rect position;          // position on screen
        int speed;
        Direction facing;
        int cur_frame;
    public:
        Sprite(char*);
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
        virtual void render() = 0;
        virtual ~GameObject() = 0;
};

class Player : public GameObject {
    private:
        Sprite* spr;
        std::queue<SDL_Keycode>* inputQueue;
    public:
        Player(std::queue<SDL_Keycode>*);
        ~Player();
        void update();
        void render();
};

class TownMap : public GameObject {
    public:
        TownMap();
        ~TownMap();
        void update();
        void render();
};

class Scene {
    private:
        std::vector<GameObject*> gameObjects;           // consider using a set
    public:
        Scene();
        ~Scene();
        void attach(GameObject*);
        void remove(GameObject*);
        void updateCycle();
        void renderCycle();
};

/*
 * Implementations define how GameObjects enter and exit the scene
*/
class GameStrategy {
    protected:
        Scene* scene;
    public:
        GameStrategy(Scene*);        // GameStrategy takes ownership of Scene
        virtual ~GameStrategy() = 0;
        LevelState runFrame();
};

class Town : public GameStrategy {
    private:
        Player* player;
    public:
        Town(Player*);
        ~Town();
        LevelState runFrame();
};

/*
 * Encapsulates graphics context and prevents passing around of library specific graphics objects.
 * Private singleton used to provide static service methods to rest of engine.
 */
class GraphicsContext {
    private:
        Uint32 pixelFmt;
        SDL_Renderer* renderer;
        SDL_Window* window;
        static GraphicsContext* instance;
        static GraphicsContext* getInstance();
        GraphicsContext(SDL_Window*);
        ~GraphicsContext();

    public:
        GraphicsContext(const GraphicsContext& obj) = delete;
        static void initialize(SDL_Window*);
        static void destroy();
        static SDL_Surface* loadSurface(char *fname);
        static std::unordered_map<Direction, std::vector<SDL_Texture*>> loadSpritesheet(SDL_Surface *spritesheet, int rows, int columns);
        static void renderCopy(SDL_Texture*, SDL_Rect*);
        static void renderClear();
        static void renderPresent();
};

#endif