#include "Game.h"

Game::Game():
    mWindow("2D Explorer", sf::Vector2u(800, 600)),
    mStateManager(&mContext),
    mEntityManager(&mContext, 100)
{
    mClock.restart();
    srand(time(nullptr));

    mContext.mWindow = &mWindow;
    mContext.mEventManager = mWindow.getEventManager();
    mContext.mTextureManager = &mTextureManager;
    mContext.mEntityManager = &mEntityManager;

    mStateManager.switchTo(StateType::Intro);
}

Game::~Game() {}

const Window &Game::getWindow() const
{
    return this->mWindow;
}

sf::Time Game::getElapsed() const
{
    return mElapsed;
}

void Game::handleInput()
{
}

void Game::update()
{
    mWindow.update();
    mStateManager.update(mElapsed);
}

void Game::render()
{
    mWindow.beginDraw();
    mStateManager.draw();
    mWindow.endDraw();
}

void Game::lateUpdate()
{
    mStateManager.processRequests();
    restartClock();
}

void Game::restartClock()
{
    mElapsed = mClock.restart();
}
