#include "anim_base.h"
#include "sprite_sheet.h"

Anim_Base::Anim_Base():
    mCurrentFrame(0),
    mFrameStart(0),
    mFrameEnd(0),
    mFrameRow(0),
    mFrameTime(0.f),
    mElapsedTime(0.f),
    mFrameActionStart(-1),
    mFrameActionEnd(-1),
    mLoop(false),
    mPlaying(false) {}

Anim_Base::~Anim_Base() {}

void Anim_Base::setSpriteSheet(SpriteSheet* sheet){ mSpriteSheet = sheet; }
void Anim_Base::setStartFrame(Frame frame){ mFrameStart = frame; }
void Anim_Base::setEndFrame(Frame frame){ mFrameEnd = frame; }
void Anim_Base::setFrameRow(Frame row){ mFrameRow = row; }
void Anim_Base::setActionStart(Frame frame){ mFrameActionStart = frame; }
void Anim_Base::setActionEnd(Frame frame){ mFrameActionEnd = frame; }
void Anim_Base::setFrameTime(float time){ mFrameTime = time; }
void Anim_Base::setLooping(bool loop){ mLoop = loop; }
void Anim_Base::setName(const std::string& name){ mName = name; }

void Anim_Base::setFrame(Frame frame)
{
    if((frame >= mFrameStart && frame <= mFrameEnd)
            || (frame >= mFrameEnd && frame <= mFrameActionStart)) // For backward play
    {
        mCurrentFrame = frame;
    }
}

SpriteSheet* Anim_Base::getSpriteSheet(){ return mSpriteSheet; }
Frame Anim_Base::getFrame(){ return mCurrentFrame; }
Frame Anim_Base::getStartFrame(){ return mFrameStart; }
Frame Anim_Base::getEndFrame(){ return mFrameEnd; }
Frame Anim_Base::getFrameRow(){ return mFrameRow; }
int Anim_Base::getActionStart(){ return mFrameActionStart; }
int Anim_Base::getActionEnd(){ return mFrameActionEnd; }
float Anim_Base::getFrameTime(){ return mFrameTime; }
float Anim_Base::getElapsedTime(){ return mElapsedTime; }
std::string Anim_Base::getName(){ return mName; }
bool Anim_Base::isLooping(){ return mLoop; }
bool Anim_Base::isPlaying(){ return mPlaying; }

bool Anim_Base::isInAction()
{
    if(mFrameActionStart == -1 || mFrameActionEnd == -1)
    {
        return true;
    }
    return (mCurrentFrame >= mFrameActionStart && mCurrentFrame <= mFrameActionEnd);
}


void Anim_Base::play(){ mPlaying = true; }
void Anim_Base::pause(){ mPlaying = false; }

void Anim_Base::stop()
{
    mPlaying = false;
    reset();
}

void Anim_Base::reset()
{
    mCurrentFrame = mFrameStart;
    mElapsedTime = 0.0f;
    cropSprite();
}

void Anim_Base::update(const float &dt)
{
    if(!mPlaying)
        return;
    mElapsedTime += dt;
    if(mElapsedTime < mFrameTime)
        return;
    frameStep();
    cropSprite();
    mElapsedTime = 0;
}
