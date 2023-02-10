#include "ironlotus.h"

GameStrategy::GameStrategy(Scene* scn) {
    scene = scn;
}

GameStrategy::~GameStrategy() {
    std::cout << "GameStrategy destructor" << std::endl;
    delete scene;
}

LevelState GameStrategy::runFrame() {
    scene->updateCycle();
	scene->renderCycle();
    return LevelState::Proceed;
}