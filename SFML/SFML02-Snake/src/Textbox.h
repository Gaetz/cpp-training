#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

using MessageContainer = std::vector<std::string>;

class Textbox
{
  public:
    Textbox();
    Textbox(int visible, int charSize, int width, sf::Vector2f screenPosition);
    ~Textbox();

    /// Setup text box
    void setup(int visible, int charSize, int width, sf::Vector2f screenPosition);

    /// Add text in textbox
    void add(std::string message);

    /// Clear textbox
    void clear();

    /// Draw textbox in window
    void render(sf::RenderWindow &window);

  private:
    MessageContainer mMessages;
    int mNumVisible;

    sf::RectangleShape mBackdrop;
    sf::Font mFont;
    sf::Text mContent;
};