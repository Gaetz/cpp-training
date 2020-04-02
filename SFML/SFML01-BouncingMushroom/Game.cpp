#include "Game.h"

const Window& Game::getWindow() const {
    return this->mWindow;
}

sf::Time Game::getElapsed() const {
    return mElapsed;
}

Game::Game(): mWindow("Bouncing Mushroom", sf::Vector2u(800, 600)) {
    // Mushroom setup
    mMushroomTexture.loadFromFile("img/mushroom.png");
    mMushroom = sf::Sprite(mMushroomTexture);
    sf::Vector2u mushroomSize = mMushroomTexture.getSize();
    mMushroom.setOrigin(mushroomSize.x / 2, mushroomSize.y / 2);
    mMushroom.setPosition(mWindow.getWindowSize().x / 2, mWindow.getWindowSize().y / 2);
    // Mushroom movement
    mMoveIncrement = sf::Vector2f(400.0f, 400.0f);
}

Game::~Game() {

}

void Game::handleInput() {

}

void Game::update() {
    mWindow.update();
    moveMushroom();
}

void Game::moveMushroom() {
    sf::Vector2u mushroomSize = mMushroomTexture.getSize();
    // Handle border collisions
    if((mMushroom.getPosition().x + mushroomSize.x / 2 > mWindow.getWindowSize().x && mMoveIncrement.x > 0)
    || (mMushroom.getPosition().x - mushroomSize.x / 2 < 0 && mMoveIncrement.x < 0)) {
        mMoveIncrement.x *= -1;
        mMushroom.setScale(mMushroom.getScale().x * -1, 1); // Horizontal flip
    }
    if((mMushroom.getPosition().y + mushroomSize.y / 2 > mWindow.getWindowSize().y && mMoveIncrement.y > 0)
    || (mMushroom.getPosition().y - mushroomSize.y / 2 < 0 && mMoveIncrement.y < 0)) {
        mMoveIncrement.y *= -1;            
    }
    // Handle time delta
    float delta = mElapsed.asSeconds();
    sf::Vector2f moveDelta = sf::Vector2f(mMoveIncrement.x * delta, mMoveIncrement.y * delta);
    // Move the mushroom
    mMushroom.setPosition(mMushroom.getPosition() + moveDelta);
}

void Game::render() {
    mWindow.beginDraw();
    mWindow.draw(mMushroom);
    mWindow.endDraw();
}

void Game::restartClock() {
    mElapsed = mClock.restart();
}