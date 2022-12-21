#include "ironlotus.h"

Scene::Scene() {}

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
    GraphicsContext::renderClear();
    for(GameObject *gameObj : gameObjects) {
        gameObj->render();
    }
    GraphicsContext::renderPresent();
}