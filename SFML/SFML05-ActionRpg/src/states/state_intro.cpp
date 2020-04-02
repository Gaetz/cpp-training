#include "state_intro.h"
#include "../core/state_manager.h"

State_Intro::State_Intro(StateManager *stateManager) : BaseState(stateManager) {}

State_Intro::~State_Intro() {}

void State_Intro::onCreate()
{
    mTimePassed = 0.0f;
    sf::Vector2u windowSize = mStateManager->getContext()->mWindow->getRenderWindow()->getSize();
    // Sprite
    mIntroTexture.loadFromFile("assets/img/intro.png");
    mIntroSprite.setTexture(mIntroTexture);
    mIntroSprite.setOrigin(mIntroTexture.getSize().x / 2.0f, mIntroTexture.getSize().y / 2.0f);
    mIntroSprite.setPosition(windowSize.x / 2.0f, 0);
    // Text
    mFont.loadFromFile("assets/arial.ttf");
    mText.setFont(mFont);
    mText.setString({"Appuyez sur ESPACE pour continuer"});
    mText.setCharacterSize(18);
    sf::FloatRect textRect = mText.getLocalBounds();
    mText.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
    mText.setPosition(windowSize.x / 2.0f, windowSize.y * 0.75f);

    EventManager *evMgr = mStateManager->getContext()->mEventManager;
    evMgr->addCallback(StateType::Intro, "KeySpace", &State_Intro::carryOn, this);
}

void State_Intro::onDestroy()
{
    EventManager *evMgr = mStateManager->getContext()->mEventManager;
    evMgr->removeCallback(StateType::Intro, "KeySpace");
}

void State_Intro::update(const sf::Time &time)
{
    if (mTimePassed < 5.0f)
    {
        mTimePassed += time.asSeconds();
        mIntroSprite.setPosition(mIntroSprite.getPosition().x, mIntroSprite.getPosition().y + (48 * time.asSeconds()));
    }
}

void State_Intro::draw()
{
    sf::RenderWindow *window = mStateManager->getContext()->mWindow->getRenderWindow();
    window->draw(mIntroSprite);
    if (mTimePassed >= 5.0f)
    {
        window->draw(mText);
    }
}

void State_Intro::carryOn(EventDetails *details)
{
    if(mTimePassed < 5.0f)
    {
        // Skip intro
        mIntroSprite.setPosition(mIntroSprite.getPosition().x, 48 * 5.0f);        
        mTimePassed = 5.0f;
    }
    else
    {
        mStateManager->switchTo(StateType::MainMenu);
        mStateManager->remove(StateType::Intro);
    }
}

void State_Intro::activate() {}

void State_Intro::deactivate() {}
