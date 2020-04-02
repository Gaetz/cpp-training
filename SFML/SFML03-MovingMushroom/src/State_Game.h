#pragma once
#include "BaseState.h"
#include "EventManager.h"

class State_Game : public BaseState
{
  public:
    State_Game(StateManager *stateManager);
    ~State_Game();

    void onCreate();
    void onDestroy();
    void activate();
    void deactivate();
    void update(const sf::Time &time);
    void draw();

    /// Go to main menu callback
    void stateMainMenu(EventDetails *details);
    
    /// Go to pause callback
    void statePaused(EventDetails *details);

  private:
    /// Tutorial font
    sf::Font mFont;

    /// Tutorial text
    sf::Text mText;

    /// Mushroom texture
    sf::Texture mMushroomTexture;

    /// Mushroom sprite
    sf::Sprite mMushroom;

    /// Mushroom movement
    sf::Vector2f mMoveIncrement;

    /// True when player move the mushroom by mouse
    bool mIsPlayerControlled;

    /// Move mMushroom
    void moveMushroom(const sf::Time &time);

    /// Player move mushroom
    void playerMoveMushroom(EventDetails* details);

    /// Player move mushroom
    void playerReleaseMushroom(EventDetails* details);
  };