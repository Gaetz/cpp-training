#ifndef STATE_GAME_H
#define STATE_GAME_H

#include "BaseState.h"
#include "EventManager.h"
#include "Map.h"

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

    /// Toggle debug overlay
    void toggleOverlay(EventDetails* details);

private:
    /// Tutorial font
    sf::Font mFont;

    /// Tutorial text
    sf::Text mText;

    /// Game map
    Map* mGameMap;
};

#endif // STATE_GAME_H
