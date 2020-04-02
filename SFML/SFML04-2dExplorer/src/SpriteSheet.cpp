#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(Asset_Texture *textureManager) :
    mTextureManager(textureManager),
    mCurrentAnimation(nullptr),
    mSpriteScale(1.0f, 1.0f),
    mDirection(Direction::Right) {}

SpriteSheet::~SpriteSheet()
{
    releaseSheet();
}

void SpriteSheet::setSpriteSize(const sf::Vector2i &size)
{
    mSpriteSize = size;
    mSprite.setOrigin(mSpriteSize.x / 2, mSpriteSize.y);
}

void SpriteSheet::setSpritePosition(const sf::Vector2f &position)
{
    mSprite.setPosition(position);
}

void SpriteSheet::setDirection(const Direction &direction)
{
    if(direction == mDirection)
        return;
    mDirection = direction;
    mCurrentAnimation->cropSprite();
}

bool SpriteSheet::setAnimation(const std::string &name, const bool &play, const bool &loop)
{
    auto itr = mAnimations.find(name);
    if(itr == mAnimations.end())
        return false;
    if(itr->second == mCurrentAnimation)
        return false;
    // Stop current animation and replace it by a new one. Setup it.
    if(mCurrentAnimation) {
        mCurrentAnimation->stop();
    }
    mCurrentAnimation = itr->second;
    mCurrentAnimation->setLooping(loop);
    if(play) {
        mCurrentAnimation->play();
    }
    mCurrentAnimation->cropSprite();
    return true;
}

void SpriteSheet::cropSprite(const sf::IntRect &rect)
{
    mSprite.setTextureRect(rect);
}

void SpriteSheet::releaseSheet()
{
    mTextureManager->releaseAsset(mTexture);
    mCurrentAnimation = nullptr;
    while(mAnimations.begin() != mAnimations.end()) {
        delete mAnimations.begin()->second;
        mAnimations.erase(mAnimations.begin());
    }
}

bool SpriteSheet::loadSheet(const string &file)
{
    std::ifstream sheet;
    sheet.open(Utils::getWorkingDirectory() + file);
    if(sheet.is_open()) {
        releaseSheet(); // Release former sheet
        string line;
        while(std::getline(sheet, line)) {
            if(line[0] == '|') // Descriptive line
                continue;
            std::stringstream keystream(line);
            string type;
            keystream >> type;
            // Texture
            if(type == "Texture"){
                if (mTexture != ""){
                    std::cerr << "Duplicate texture entries in: " << file << std::endl;
                    continue;
                }
                std::string texture;
                keystream >> texture;
                if (!mTextureManager->requireAsset(texture)){
                    std::cerr << "Could not set up the texture: " << texture << std::endl;
                    continue;
                }
                mTexture = texture;
                mSprite.setTexture(*mTextureManager->getAsset(mTexture));
            } else if(type == "Size"){
                keystream >> mSpriteSize.x >> mSpriteSize.y;
                setSpriteSize(mSpriteSize);
            } else if(type == "Scale"){
                keystream >> mSpriteScale.x >> mSpriteScale.y;
                mSprite.setScale(mSpriteScale);
            } else if(type == "AnimationType"){
                keystream >> mAnimType;
            } else if(type == "Animation"){
                std::string name;
                keystream >> name;
                if (mAnimations.find(name) != mAnimations.end()){
                    std::cerr << "Duplicate animation(" << name << ") in: " << file << std::endl;
                    continue;
                }
                Anim_Base* anim	= nullptr;
                if(mAnimType == "Directional"){
                    anim = new Anim_Directional();
                } else {
                    std::cerr << "Unknown animation type: " << mAnimType << std::endl;
                    continue;
                }

                keystream >> *anim;
                anim->setSpriteSheet(this);
                anim->setName(name);
                anim->reset();
                mAnimations.emplace(name, anim);

                if (mCurrentAnimation){ continue; }
                mCurrentAnimation = anim;
                mCurrentAnimation->play();
            }
        }
        sheet.close();
        return true;
    }
    std::cerr << "Failed loading spritesheet: " << file << std::endl;
    return false;
}

void SpriteSheet::update(const float &dt)
{
    mCurrentAnimation->update(dt);
}

void SpriteSheet::draw(sf::RenderWindow *window)
{
    window->draw(mSprite);
}
