#include "ironlotus.h"
#include <algorithm>

Scene::Scene() {}

/**
 * @brief Destroy the Scene:: Scene object
 * NB: remove() objects from scene you don't want freed before calling this.
 */
Scene::~Scene() {
    std::cout << "Scene destructor" << std::endl;
    for(GameObject *gameObj : gameObjects) {
        delete gameObj;
    }
}

void Scene::attach(GameObject* gameObj) {
    std::cout << gameObj << std::endl;
    gameObjects.push_back(gameObj);
    std::cout << gameObjects[0] << std::endl;
}

// todo: unit test - not currently working
// due to address of Town.player changing after Town constructor
void Scene::remove(GameObject* gameObj) {
    std::cout << "Removing gameobject from Scene... " << gameObj << std::endl;

    // debug
    std::cout << (gameObj == gameObjects[0] ? "true" : "false") << std::endl;
    std::cout << gameObjects[0] << std::endl;
    
    int index = 0;
    for(GameObject *g : gameObjects) {
        if(gameObj == g) {
            std::cout << "... erasing" << std::endl;
            gameObjects.erase(gameObjects.begin() + index);
        }
        index++;
    }
    //std::remove(gameObjects.begin(), gameObjects.end(), gameObj);
    
    //std::vector<GameObject*>::iterator it = std::find(gameObjects.begin(), gameObjects.end(), gameObj);
    /*if(it != gameObjects.end()) {
        std::cout << "Removing gameobject from Scene" << std::endl;
        gameObjects.erase(it);
    }*/
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