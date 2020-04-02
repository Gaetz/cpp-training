#include "state_paused.h"
#include "../core/state_manager.h"

State_Paused::State_Paused(StateManager *stateManager) : BaseState(stateManager) {}

State_Paused::~State_Paused() {}

void State_Paused::onCreate()
{
    setTransparent(true);

    mFont.loadFromFile("assets/arial.ttf");
    mText.setFont(mFont);
    mText.setFillColor(sf::Color::White);
    mText.setString(sf::String("PAUSE"));
    mText.setCharacterSize(18);
    mText.setStyle(sf::Text::Bold);
    sf::Vector2u windowSize = mStateManager->getContext()->mWindow->getRenderWindow()->getSize();
    sf::FloatRect textRect = mText.getLocalBounds();
    mText.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
    mText.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

    mRect.setSize(sf::Vector2f(windowSize));
    mRect.setPosition(0, 0);
    mRect.setFillColor(sf::Color(0, 0, 0, 150));

    EventManager *evMgr = mStateManager->getContext()->mEventManager;
    evMgr->addCallback(StateType::Paused, "KeyP", &State_Paused::unpause, this);
}

void State_Paused::onDestroy()
{
    EventManager *evMgr = mStateManager->getContext()->mEventManager;
    evMgr->removeCallback(StateType::Paused, "KeyP");
}

void State_Paused::activate()
{
}

void State_Paused::deactivate()
{
}

void State_Paused::update(const sf::Time &time)
{
}

void State_Paused::unpause(EventDetails *details)
{
    mStateManager->switchTo(StateType::Game);
}

void State_Paused::draw()
{
    sf::RenderWindow *window = mStateManager->getContext()->mWindow->getRenderWindow();
    window->draw(mRect);
    window->draw(mText);    
}
