#include "StateManager.h"

class Game {

public:
    const Window& getWindow() const;
    sf::Time getElapsed() const;    

    /// Start game
    Game();

    /// End game
    ~Game();
    
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
    sf::Clock mClock;
    sf::Time mElapsed;    
};