#include "State_Game.h"
#include "StateManager.h"

State_Game::State_Game(StateManager *stateManager) : BaseState(stateManager) {}

State_Game::~State_Game() {}

void State_Game::onCreate()
{
    Window *window = mStateManager->getContext()->mWindow;
    EventManager *evMgr = window->getEventManager();
    // Mushroom setup
    mMushroomTexture.loadFromFile("img/mushroom.png");
    mMushroom = sf::Sprite(mMushroomTexture);
    sf::Vector2u mushroomSize = mMushroomTexture.getSize();
    mMushroom.setOrigin(mushroomSize.x / 2, mushroomSize.y / 2);
    mMushroom.setPosition(window->getWindowSize().x / 2, window->getWindowSize().y / 2);
    // Mushroom movement
    mMoveIncrement = sf::Vector2f(400.0f, 400.0f);
    mIsPlayerControlled = false;
    // Text
    mFont.loadFromFile("arial.ttf");
    mText.setFont(mFont);
    mText.setFillColor(sf::Color(100, 100, 100));
    mText.setString({L"Shift gauche: contrôle souris | Echap: menu"});
    mText.setCharacterSize(18);
    sf::FloatRect textRect = mText.getLocalBounds();
    mText.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
    mText.setPosition(window->getWindowSize().x * 0.75f, window->getWindowSize().y - 20);
    // Callback for mouse move
    evMgr->addCallback(StateType::Game, "game_move", &State_Game::playerMoveMushroom, this);
    evMgr->addCallback(StateType::Game, "game_releaseMove", &State_Game::playerReleaseMushroom, this);
    // Callback for state transition
    evMgr->addCallback(StateType::Game, "game_keyEscape", &State_Game::stateMainMenu, this);
    evMgr->addCallback(StateType::Game, "game_keyP", &State_Game::statePaused, this);
}

void State_Game::onDestroy()
{
    EventManager *evMgr = mStateManager->getContext()->mEventManager;
    evMgr->removeCallback(StateType::Game, "game_move");
    evMgr->removeCallback(StateType::Game, "game_releaseMove");
    evMgr->removeCallback(StateType::Game, "game_keyEscape");
    evMgr->removeCallback(StateType::Game, "game_keyP");
}

void State_Game::activate()
{
    mIsPlayerControlled = false;
}

void State_Game::deactivate()
{

}

void State_Game::update(const sf::Time &time)
{
    moveMushroom(time);
}

void State_Game::moveMushroom(const sf::Time &time)
{
    float deltaTime = time.asSeconds();
    sf::Vector2u mushroomSize = mMushroomTexture.getSize();
    Window *window = mStateManager->getContext()->mWindow;
    // Handle border collisions
    if ((mMushroom.getPosition().x + mushroomSize.x / 2 > window->getWindowSize().x && mMoveIncrement.x > 0) || (mMushroom.getPosition().x - mushroomSize.x / 2 < 0 && mMoveIncrement.x < 0))
    {
        mMoveIncrement.x *= -1;
        mMushroom.setScale(mMushroom.getScale().x * -1, 1); // Horizontal flip
    }
    if ((mMushroom.getPosition().y + mushroomSize.y / 2 > window->getWindowSize().y && mMoveIncrement.y > 0) || (mMushroom.getPosition().y - mushroomSize.y / 2 < 0 && mMoveIncrement.y < 0))
    {
        mMoveIncrement.y *= -1;
    }
    // Handle time delta
    sf::Vector2f moveDelta = sf::Vector2f(mMoveIncrement.x * deltaTime, mMoveIncrement.y * deltaTime);
    // Move the mushroom
    if (!mIsPlayerControlled)
    {
        mMushroom.setPosition(mMushroom.getPosition() + moveDelta);
    }
}

void State_Game::playerMoveMushroom(EventDetails *details)
{
    if (!mIsPlayerControlled)
    {
        mIsPlayerControlled = true;
    }
    sf::RenderWindow *renderWindow = mStateManager->getContext()->mWindow->getRenderWindow();
    sf::Vector2i mousePosition = mStateManager->getContext()->mEventManager->getMousePosition(renderWindow);
    mMushroom.setPosition(mousePosition.x, mousePosition.y);
}

void State_Game::playerReleaseMushroom(EventDetails *details)
{
    mIsPlayerControlled = false;
}

void State_Game::draw()
{
    mStateManager->getContext()->mWindow->getRenderWindow()->draw(mMushroom);
    mStateManager->getContext()->mWindow->getRenderWindow()->draw(mText);
}

void State_Game::stateMainMenu(EventDetails *details)
{
    mStateManager->switchTo(StateType::MainMenu);
}

void State_Game::statePaused(EventDetails *details)
{
    mStateManager->switchTo(StateType::Paused);
}