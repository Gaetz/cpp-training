#ifndef ANIM_BASE_H
#define ANIM_BASE_H

#include <string>

class SpriteSheet;

using Frame = unsigned int;
using std::string;

class Anim_Base {
  friend class SpriteSheet;

public:
    Anim_Base();
    virtual ~Anim_Base();

    void setSpriteSheet(SpriteSheet* sheet);
    void setFrame(Frame frame);
    void setStartFrame(Frame frame);
    void setEndFrame(Frame frame);
    void setFrameRow(Frame row);
    void setActionStart(Frame frame);
    void setActionEnd(Frame frame);
    void setFrameTime(float time);
    void setLooping(bool loop);
    void setName(const std::string& name);

    SpriteSheet* getSpriteSheet();
    Frame getFrame();
    Frame getStartFrame();
    Frame getEndFrame();
    Frame getFrameRow();
    int getActionStart();
    int getActionEnd();
    float getFrameTime();
    float getElapsedTime();
    bool isLooping();
    bool isPlaying();
    bool isInAction();
    std::string getName();

    /// Play animation
    void play();

    /// Pause animation
    void pause();

    /// Stop animation
    void stop();

    /// Reset animation
    void reset();

    /// Update
    virtual void update(const float &dt);

    /// Easier reading operator
    friend std::stringstream& operator >> (std::stringstream& stream, Anim_Base& anim)
    {
        anim.readIn(stream);
        return stream;
    }

protected:
    Frame mCurrentFrame;
    Frame mFrameStart;
    Frame mFrameEnd;
    Frame mFrameRow;
    int mFrameActionStart; // Frame when a specific action starts
    int mFrameActionEnd; // Frame when a specific action endd
    float mFrameTime;
    float mElapsedTime;
    bool mLoop;
    bool mPlaying;
    string mName;
    SpriteSheet* mSpriteSheet;

    /// Animation type specific update portion
    virtual void frameStep() = 0;

    /// Animation type specific way to obtain sprites
    virtual void cropSprite() = 0;

    /// How stringstream is used when data is being load from file
    virtual void readIn(std::stringstream& stream) = 0;
};
#endif // ANIM_BASE_H
