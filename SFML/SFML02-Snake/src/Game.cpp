#include "Game.h"

Game::Game() : mWindow("Snake", sf::Vector2u(800, 600)),
               mSnake(mWorld.getBlockSize(), &mTextbox),
               mWorld(sf::Vector2u(800, 600))
{
    mClock.restart();
    srand(time(NULL));

    mTextbox.setup(5, 14, 350, sf::Vector2f(225, 50));
    mTextbox.add("Seeded random number generator with: " + std::to_string(time(NULL)));
    mElapsed = 0.0f;
}

Game::~Game()
{
}

const Window &Game::getWindow() const
{
    return this->mWindow;
}

sf::Time Game::getElapsed() const
{
    return mClock.getElapsedTime();
}

void Game::handleInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && mSnake.getPhysicalDirection() != Direction::Down)
    {
        mSnake.setDirection(Direction::Up);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && mSnake.getPhysicalDirection() != Direction::Up)
    {
        mSnake.setDirection(Direction::Down);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && mSnake.getPhysicalDirection() != Direction::Right)
    {
        mSnake.setDirection(Direction::Left);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && mSnake.getPhysicalDirection() != Direction::Left)
    {
        mSnake.setDirection(Direction::Right);
    }
}

void Game::update()
{
    mWindow.update();

    float timestep = 1.0f / mSnake.getSpeed();
    if (mElapsed >= timestep)
    {
        mSnake.tick();
        mWorld.update(mSnake);
        mElapsed -= timestep;

        if (mSnake.hasLost())
        {
            mTextbox.add("GAME OVER. Your score: " + std::to_string(mSnake.getScore()));
            mSnake.reset();
        }
    }
}

void Game::render()
{
    mWindow.beginDraw();

    mWorld.render(*mWindow.getRenderWindow());
    mSnake.render(*mWindow.getRenderWindow());
    mTextbox.render(*mWindow.getRenderWindow());

    mWindow.endDraw();
}

void Game::restartClock()
{
    mElapsed += mClock.restart().asSeconds();
}