#include "ironlotus.h"

GameStrategy::GameStrategy(Scene* scn) {
    scene = scn;
}

GameStrategy::~GameStrategy() {
    delete scene;
}

LevelState GameStrategy::runFrame() {
    scene->updateCycle();
	scene->renderCycle();
    return LevelState::Proceed;
}