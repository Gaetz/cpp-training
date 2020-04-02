
#pragma once
#include <SFML/Graphics.hpp>

class StateManager;

class BaseState
{
    friend class StateManager;

  public:
    BaseState(StateManager *stateManager) : mStateManager(stateManager), mTransparent(false), mTranscendent(false) {}
    virtual ~BaseState() {}

    StateManager *getStateManager()
    {
        return mStateManager;
    }

    bool isTransparent() const { return mTransparent; }
    void setTransparent(const bool &transparent)
    {
        mTransparent = transparent;
    }

    bool isTranscendent() const { return mTranscendent; }
    void setTranscendent(const bool &transcendent)
    {
        mTranscendent = transcendent;
    }

    virtual void onCreate() = 0;
    virtual void onDestroy() = 0;

    virtual void activate() = 0;
    virtual void deactivate() = 0;

    virtual void update(const sf::Time &time) = 0;
    virtual void draw() = 0;

  protected:
    StateManager *mStateManager;

    /// Tell if the state need to render the state that came before it
    bool mTransparent;

    /// Tell if the state need to update the state that came before it
    bool mTranscendent;
};
