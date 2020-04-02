#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Textbox.h"

struct SnakeSegment
{
    SnakeSegment(int x, int y) : position(x, y) {}
    sf::Vector2i position;
};

using SnakeContainer = std::vector<SnakeSegment>;

enum class Direction
{
    None,
    Up,
    Down,
    Left,
    Right
};

class Snake
{
  public:
    Snake(int blockSize, Textbox* log);
    ~Snake();

    Direction getDirection();
    void setDirection(Direction dir);
    int getSpeed();
    sf::Vector2i getPosition();
    int getLives();
    int getScore();
    void increaseScore();
    bool hasLost();

    /// Returns the direciton the snake is facing
    Direction getPhysicalDirection();

    /// Handle losing
    void lose();

    /// Invert loss status
    void toggleLose();

    /// Make the snake grow
    void extend();

    /// Reset snake to starting position
    void reset();

    /// Movement method
    void move();

    /// Update method
    void tick();

    /// Cut a number of the snake's segments
    void cut(int segments);

    /// Draw snake in window
    void render(sf::RenderWindow &window);

  private:
    /// Segment vector
    SnakeContainer mSnakeBody;

    /// Size of the graphics
    int mSize;

    /// Current direction
    Direction mDir;

    /// Snake speed
    int mSpeed;

    /// Lives
    int mLives;

    /// Score
    int mScore;

    /// Losing state
    bool mLost;

    /// Log system
    Textbox* mLog;

    /// Shape used in rendering
    sf::RectangleShape mBodyRect;

    /// Checking for collisions
    void checkCollision();
};