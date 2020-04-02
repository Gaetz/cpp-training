#ifndef STATE_MAIN_MENU_H
#define STATE_MAIN_MENU_H

#include "BaseState.h"
#include "EventManager.h"

class State_MainMenu : public BaseState
{
  public:
    State_MainMenu(StateManager *stateManager);
    ~State_MainMenu();

    void onCreate();
    void onDestroy();
    void activate();
    void deactivate();
    void update(const sf::Time &time);
    void draw();

    /// Click on menu
    void mouseClick(EventDetails *details);

    /// Validate to quickly start
    void quickStart(EventDetails *details);

    /// Escape to get back to game when it has begun
    void quickResume(EventDetails *details);    

  private:
    // Menu font
    sf::Font mFont;
    
    /// Menu title
    sf::Text mText;

    sf::Vector2f mButtonSize;
    sf::Vector2f mButtonPosition;
    unsigned int mButtonPadding;

    sf::RectangleShape mRects[3];
    sf::Text mLabels[3];
};

#endif // STATE_MAIN_MENU_H
