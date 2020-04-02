#pragma once
#include "BaseState.h"
#include "EventManager.h"

class State_Intro : public BaseState
{
  public:
    State_Intro(StateManager *stateManager);
    ~State_Intro();

    void onCreate();
    void onDestroy();
    void activate();
    void deactivate();
    void update(const sf::Time &time);
    void draw();

    /// Handle transition to other state
    void carryOn(EventDetails* details);

  private:
    /// Intro sprite's texture
    sf::Texture mIntroTexture;

    /// Intro sprite
    sf::Sprite mIntroSprite;

    /// Intro text's font
    sf::Font mFont;

    /// Intro text
    sf::Text mText;

    /// Time passed on intro state
    float mTimePassed;
};