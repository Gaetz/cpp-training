#ifndef SPRITE_SHEET_H
#define SPRITE_SHEET_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <unordered_map>
#include "Asset_Texture.h"
#include "Anim_Directional.h"
#include "Utilities.h"

using std::string;

using Animations = std::unordered_map<string, Anim_Base*>;

class SpriteSheet
{
public:
    SpriteSheet(Asset_Texture* textureManager);
    ~SpriteSheet();

    sf::Vector2i getSpriteSize() const { return mSpriteSize; }
    sf::Vector2f getSpriteScale() const { return mSpriteScale; }
    sf::Vector2f getSpritePosition() const { return mSprite.getPosition(); }
    Direction getDirection() const { return mDirection; }
    Anim_Base* getCurrentAnim() { return mCurrentAnimation; }

    void setSpriteSize(const sf::Vector2i& size);
    void setSpritePosition(const sf::Vector2f& position);
    void setDirection(const Direction& direction);

    bool setAnimation(const std::string& name,
        const bool& play = false,
        const bool& loop = false);

    void cropSprite(const sf::IntRect& rect);

    bool loadSheet(const string& file);

    void releaseSheet();

    void update(const float& dt);

    void draw(sf::RenderWindow* window);

private:
    string mTexture;
    sf::Sprite mSprite;
    sf::Vector2i mSpriteSize;
    sf::Vector2f mSpriteScale;
    Direction mDirection;

    string mAnimType;
    Animations mAnimations;
    Anim_Base* mCurrentAnimation;
    Asset_Texture* mTextureManager;
};

#endif // SPRITE_SHEET_H
