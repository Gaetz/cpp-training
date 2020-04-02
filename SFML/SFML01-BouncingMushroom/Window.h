#include <string>
#include <SFML/Graphics.hpp>

class Window {

public:

    bool isDone() const;
    bool isFullscreen() const;
    sf::Vector2u getWindowSize() const;

    /// Create a 640 * 480 window named "Window"
    Window();

    /// Create a window with custom title and size
    Window(const std::string& title, const sf::Vector2u& size);
    
    /// Destroy window
    ~Window();
     
    /// Clear window
    void beginDraw();

    /// Display changes
    void endDraw();

    /// Event and input update
    void update();

    /// Make window fullscreen
    void toggleFullscreen();

    /// Draw content in window
    void draw(sf::Drawable& drawable);

private:

    sf::RenderWindow mWindow;
    sf::Vector2u mWindowSize;
    std::string mWindowTitle;
    bool mIsDone;
    bool mIsFullscreen;

    /// Common setup method
    void setup(const std::string& title, const sf::Vector2u& size);
    
    /// Destroy process
    void destroy();

    /// Window creation process
    void create();
};