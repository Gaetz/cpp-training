#include "anim_directional.h"
#include "sprite_sheet.h"

void Anim_Directional::frameStep()
{
    if(mFrameStart < mFrameEnd) {
        ++mCurrentFrame;
    } else {
        --mCurrentFrame;
    }

    if((mFrameStart < mFrameEnd && mCurrentFrame > mFrameEnd)
            || (mFrameStart > mFrameEnd && mCurrentFrame < mFrameEnd)) {
        if(mLoop) {
            mCurrentFrame = mFrameStart;
            return;
        }
        mCurrentFrame = mFrameEnd;
        pause();
    }
}

void Anim_Directional::cropSprite()
{
    sf::IntRect rect(
                mSpriteSheet->getSpriteSize().x * mCurrentFrame,
                mSpriteSheet->getSpriteSize().y * (mFrameRow + (short)mSpriteSheet->getDirection()),
                mSpriteSheet->getSpriteSize().x,
                mSpriteSheet->getSpriteSize().y);
    mSpriteSheet->cropSprite(rect);
}

void Anim_Directional::readIn(std::stringstream &stream)
{
    stream >> mFrameStart >> mFrameEnd >> mFrameRow >> mFrameTime >> mFrameActionStart >> mFrameActionEnd;
}
