#include "ironlotus.h"

Town::Town(Player* p) : GameStrategy(new Scene()) {
    std::cout << "Constructing town" << std::endl;
    Player *player = p;
	scene->attach(player);
    std::cout << player << std::endl;
}

// todo: remove this method after issue fix and use GameStrategy implementation
LevelState Town::runFrame() {
    // the following player pointer value is different than in constructor...
    std::cout << "frame - " << player << std::endl;
    scene->updateCycle();
	scene->renderCycle();
    return LevelState::Proceed;
}

Town::~Town() {
    std::cout << "Town destructor" << std::endl;
    std::cout << player << std::endl;
    scene->remove(player);
}