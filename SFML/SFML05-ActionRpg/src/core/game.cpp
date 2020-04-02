#include "game.h"

Game::Game():
    mWindow("2D Rpg", sf::Vector2u(800, 600)),
    mStateManager(&mContext),
    mEntityManager(&mSystemManager, &mTextureManager)
{
    mClock.restart();
    srand(time(nullptr));

    mContext.mWindow = &mWindow;
    mContext.mEventManager = mWindow.getEventManager();
    mContext.mTextureManager = &mTextureManager;
    mSystemManager.setEntityManager(&mEntityManager);
    mContext.mSystemManager = &mSystemManager;
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
