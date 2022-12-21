#include "ironlotus.h"

Player::Player(std::queue<SDL_Keycode> *input) {
    spr = new Sprite("../assets/reaper.png");
    inputQueue = input;
}

Player::~Player() {
    delete spr;
}

void Player::update() {
    while (inputQueue->size() > 0) {
        switch (inputQueue->front()) {
            case SDLK_RIGHT:
                spr->move(Direction::Right);
                break;
            case SDLK_DOWN:
                spr->move(Direction::Down);
                break;
            case SDLK_UP:
                spr->move(Direction::Up);
                break;
            case SDLK_LEFT:
                spr->move(Direction::Left);
                break;
        }
        inputQueue->pop();
    }
}

void Player::render() {
    GraphicsContext::renderCopy(spr->getCurrentFrame(), spr->getPosition());
}