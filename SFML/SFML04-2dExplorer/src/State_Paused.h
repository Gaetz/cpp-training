#ifndef STATE_PAUSED_H
#define STATE_PAUSED_H

#include "BaseState.h"
#include "EventManager.h"

class State_Paused : public BaseState
{
  public:
    State_Paused(StateManager *stateManager);
    ~State_Paused();

    void onCreate();
    void onDestroy();
    void activate();
    void deactivate();
    void update(const sf::Time &time);
    void draw();

    void unpause(EventDetails *details);

  private:
    sf::Font mFont;    
    sf::Text mText;
    sf::RectangleShape mRect;
};

#endif // STATE_PAUSED_H
