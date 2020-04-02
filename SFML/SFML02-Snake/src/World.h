#pragma once
#include <SFML/Graphics.hpp>
#include "Snake.h"

class World
{
public:
  World(sf::Vector2u windowSize);
  ~World();

  int getBlockSize();

  /// Update
  void update(Snake &player);

  /// Make an apple appear
  void respawnApple();

  /// Draw world in window
  void render(sf::RenderWindow &window);

private:
  sf::Vector2u mWindowSize;
  sf::Vector2i mItem; // Apple coordinates
  int mBlockSize;
  sf::CircleShape mAppleShape;
  sf::RectangleShape mBounds[4];
};