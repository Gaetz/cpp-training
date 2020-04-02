#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <unordered_map>
#include <vector>
#include <bitset>
#include <functional>
#include "../ecs/c_position.h"
#include "../ecs/c_spritesheet.h"
#include "../ecs/c_state.h"
#include "../ecs/c_movable.h"
#include "../ecs/c_controller.h"
#include "../ecs/c_collidable.h"
#include "../io/asset_texture.h"
#include "../utils/more_hash.h"
#include "../utils/bitmask.h"


using EntityId = unsigned int;

using ComponentContainer = std::vector<C_Base*>;
using EntityData = std::pair<Bitmask, ComponentContainer>;
using EntityContainer = std::unordered_map<EntityId, EntityData>;
using ComponentFactory = std::unordered_map<Component, std::function<C_Base*(void)>, EnumClassHash>;

class SystemManager;

class EntityManager
{
public:
    EntityManager(SystemManager* sysMgr, Asset_Texture* textureMgr);
    ~EntityManager();

    int addEntity(const Bitmask& mask);
    int addEntity(const std::string& entityFile);
    bool removeEntity(const EntityId& id);

    template<class T>
    T* getComponent(const EntityId& id, const Component& component) {
        auto itr = mEntities.find(id);
        // Check entity
        if(itr == mEntities.end())
            return nullptr;
        // Check component
        if(!itr->second.first.getBit((unsigned int)component)) {
            return nullptr;
        }
        // Component exists
        auto& container = itr->second.second;
        auto resComponent = std::find_if(container.begin(), container.end(), [&component](C_Base* c) {
                return c->getType() == component;
        });
        return (resComponent != container.end() ? dynamic_cast<T*>(*resComponent) : nullptr);
    }

    bool addComponent(const EntityId& id, const Component& component);
    bool removeComponent(const EntityId& id, const Component& component);
    bool hasComponent(const EntityId& id, const Component& component);

    void purge();

private:
    unsigned int mIdCounter;
    EntityContainer mEntities;
    ComponentFactory mComponentFactory;

    SystemManager* mSystems;
    Asset_Texture* mTextureManager;

    template<class T>
    void addComponentType(const Component& id) {
        mComponentFactory[id] = []() -> C_Base* {
            return new T();
        };
    }
};

#endif // ENTITY_MANAGER_H
