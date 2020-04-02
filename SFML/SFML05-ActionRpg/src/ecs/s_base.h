#ifndef S_BASE_H
#define S_BASE_H

#include <vector>
#include "../core/entity_manager.h"
#include "../core/event_queue.h"
#include "entity_events.h"
#include "ecs_types.h"
#include "../core/messaging/observer.h"

using EntityList = std::vector<EntityId>;
using Requirements = std::vector<Bitmask>;

class SystemManager;

class S_Base : public Observer
{
public:
    S_Base(const System& id, SystemManager* systemManager);
    virtual ~S_Base();

    bool addEntity(const EntityId& entity);
    bool hasEntity(const EntityId& entity);
    bool removeEntity(const EntityId& entity);

    System getId();

    bool fitsRequirements(const Bitmask& bits);
    void purge();

    virtual void update(float dt) = 0;
    virtual void handleEvent(const EntityId& entity, const EntityEvent& event) = 0;

protected:
    System mId;
    Requirements mRequiredComponents;
    EntityList mEntities;
    SystemManager* mSystemManager;
};

#endif // S_BASE_H
