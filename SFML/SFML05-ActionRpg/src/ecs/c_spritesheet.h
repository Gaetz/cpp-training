#ifndef C_SPRITESHEET_H
#define C_SPRITESHEET_H

#include "c_drawable.h"
#include "../display/sprite_sheet.h"

class C_SpriteSheet: public C_Drawable {
public:
    C_SpriteSheet(): C_Drawable(Component::SpriteSheet), mSpriteSheet(nullptr) {}

    ~C_SpriteSheet() { if(mSpriteSheet) delete mSpriteSheet; }

    SpriteSheet* getSpriteSheet() { return mSpriteSheet; }

    void readIn(std::stringstream& stream)
    {
        stream >> mSheetName;
    }

    void create(Asset_Texture* textureManager, const std::string& name = "")
    {
        if(mSpriteSheet)
            return;
        mSpriteSheet = new SpriteSheet(textureManager);
        mSpriteSheet->loadSheet("assets/data/animations/" + (name != "" ? name : mSheetName) + ".sheet");
    }

    void updatePosition(const sf::Vector2f& position)
    {
        mSpriteSheet->setSpritePosition(position);
    }

    const sf::Vector2u& getSize()
    {
        return mSpriteSheet->getSpriteSize();
    }

    void draw(sf::RenderWindow* window)
    {
        if(!mSpriteSheet)
            return;
        mSpriteSheet->draw(window);
    }

private:
    SpriteSheet* mSpriteSheet;
    std::string mSheetName;
};

#endif // C_SPRITESHEET_H
