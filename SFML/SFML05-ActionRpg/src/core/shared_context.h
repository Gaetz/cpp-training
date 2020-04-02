#ifndef SHARED_CONTEXT_H
#define SHARED_CONTEXT_H

#include "window.h"
#include "event_manager.h"
#include "entity_manager.h"
#include "system_manager.h"
#include "../io/asset_texture.h"
#include "../utils/debug_overlay.h"

class Map;
struct SharedContext
{
    SharedContext():
        mWindow(nullptr),
        mEventManager(nullptr),
        mTextureManager(nullptr),
        mEntityManager(nullptr),
        mSystemManager(nullptr),
        mGameMap(nullptr){}

    Window *mWindow;
    EventManager *mEventManager;
    Asset_Texture *mTextureManager;
    EntityManager* mEntityManager;
    SystemManager* mSystemManager;
    Map* mGameMap;
    DebugOverlay mDebugOverlay;
};

#endif // SHARED_CONTEXT_H
