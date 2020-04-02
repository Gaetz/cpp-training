#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include <SFML/Graphics.hpp>
#include "window.h"
#include "../ecs/s_renderer.h"
#include "../ecs/s_movement.h"
#include "../ecs/s_control.h"
#include "../ecs/s_state.h"
#include "../ecs/s_sheet_animation.h"
//#include "../ecs/s_collision.h"
#include "event_queue.h"
#include "messaging/message_handler.h"
#include <unordered_map>
#include "../utils/debug_overlay.h"
#include "../utils/more_hash.h"

using SystemContainer = std::unordered_map<System, S_Base*, EnumClassHash>;
using EntityEventContainer = std::unordered_map<EntityId, EventQueue>;

class EntityManager;

class SystemManager
{
public:
    SystemManager();
    ~SystemManager();

    EntityManager* getEntityManager();
    void setEntityManager(EntityManager* entityManager);
    MessageHandler* getMessageHandler();

    template<class T>
    T* getSystem(const System& system)
    {
        auto itr = mSystems.find(system);
        return (itr != mSystems.end() ? dynamic_cast<T*>(itr->second) : nullptr);
    }

    void addEvent(const EntityId& entityId, const EventId& event);

    void update(float dt);
    void handleEvents();
    void draw(Window* window, unsigned int elevation);

    void entityModified(const EntityId& entityId, const Bitmask& bits);
    void removeEntity(const EntityId& entity);

    void purgeEntities();
    void purgeSystems();

private:
    SystemContainer mSystems;
    EntityManager* mEntityManager;
    EntityEventContainer mEvents;
    MessageHandler mMessages;
};


#endif // SYSTEM_MANAGER_H
