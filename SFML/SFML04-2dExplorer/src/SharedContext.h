#ifndef SHARED_CONTEXT_H
#define SHARED_CONTEXT_H

#include "Window.h"
#include "EventManager.h"
#include "EntityManager.h"
#include "Asset_Texture.h"
#include "DebugOverlay.h"

class Map;
struct SharedContext
{
    SharedContext():
        mWindow(nullptr),
        mEventManager(nullptr),
        mTextureManager(nullptr),
        mEntityManager(nullptr),
        mGameMap(nullptr){}

    Window *mWindow;
    EventManager *mEventManager;
    Asset_Texture *mTextureManager;
    EntityManager* mEntityManager;
    Map* mGameMap;
    DebugOverlay mDebugOverlay;
};

#endif // SHARED_CONTEXT_H
