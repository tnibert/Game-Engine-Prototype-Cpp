#include "ironlotus.h"

Player::Player(SDL_Renderer *rend, Uint32 pixelFmt) {
    spr = new Sprite("../assets/reaper.png", rend, pixelFmt);
}

Player::~Player() {
    delete spr;
}

void Player::update() {

}

void Player::render(SDL_Renderer *rend) {
    SDL_RenderCopy(rend, spr->getCurrentFrame(), NULL, spr->getPosition());
}