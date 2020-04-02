#ifndef GAME_H
#define GAME_H

#include "window.h"
#include "event_manager.h"
#include "state_manager.h"
#include "entity_manager.h"
#include "../io/asset_texture.h"
#include <iostream>

class Game {

public:
    /// Start game
    Game();

    /// End game
    ~Game();

    const Window& getWindow() const;
    sf::Time getElapsed() const;
    
    /// Manage player's inputs
    void handleInput();

    /// Frame update
    void update();

    /// Update after update
    void lateUpdate();

    /// Draw game
    void render();

    /// Restart time clock
    void restartClock();


private:
    SharedContext mContext;
    Window mWindow;
    StateManager mStateManager;
    SystemManager mSystemManager;
    EntityManager mEntityManager;
    Asset_Texture mTextureManager;

    sf::Clock mClock;
    sf::Time mElapsed;
};

#endif // GAME_H
