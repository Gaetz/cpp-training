#include "Window.h"

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

    /// Draw game
    void render();

    /// Restart time clock
    void restartClock();


private:
    Window mWindow;
    sf::Texture mMushroomTexture;
    sf::Sprite mMushroom;
    sf::Vector2f mMoveIncrement;
    sf::Clock mClock;
    sf::Time mElapsed;

    /// Move mMushroom
    void moveMushroom();
};