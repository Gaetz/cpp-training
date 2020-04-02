#include <string>
#include <SFML/Graphics.hpp>
#include "EventManager.h"

class Window
{
public:
  bool isDone() const;
  bool isFullscreen() const;
  bool isFocused() const;
  sf::Vector2u getWindowSize() const;
  sf::RenderWindow *getRenderWindow();
  EventManager *getEventManager();

  /// Create a 640 * 480 window named "Window"
  Window();

  /// Create a window with custom title and size
  Window(const std::string &title, const sf::Vector2u &size);

  /// Destroy window
  ~Window();

  /// Clear window
  void beginDraw();

  /// Display changes
  void endDraw();

  /// Event and input update
  void update();

  /// Make window fullscreen
  void toggleFullscreen(EventDetails *details);

  /// Close window
  void close(EventDetails *details = nullptr);

  /// Draw content in window
  void draw(sf::Drawable &drawable);

private:
  sf::RenderWindow mWindow;
  EventManager mEventManager;
  sf::Vector2u mWindowSize;
  std::string mWindowTitle;
  bool mIsDone;
  bool mIsFullscreen;
  bool mIsFocused;

  /// Common setup method
  void setup(const std::string &title, const sf::Vector2u &size);

  /// Destroy process
  void destroy();

  /// Window creation process
  void create();
};