#include "ironlotus.h"

Scene::Scene(SDL_Renderer* rend) {
    renderer = rend;
}

void Scene::attach(GameObject* gameObj) {
    gameObjects.push_back(gameObj);
}

// todo: look at how this is used in KTH
void Scene::remove(GameObject* gameObj) {

}

void Scene::updateCycle() {
    for(GameObject *gameObj : gameObjects) {
        gameObj->update();
    }
}

void Scene::renderCycle() {
    SDL_RenderClear(renderer);
    for(GameObject *gameObj : gameObjects) {
        gameObj->render(renderer);
    }
    SDL_RenderPresent(renderer);
}