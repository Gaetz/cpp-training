#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <unordered_map>
#include <functional>
#include "Player.h"
#include "Enemy.h"

using std::string;

using EntityContainer = std::unordered_map<unsigned int, EntityBase*>;
using EntityFactory = std::unordered_map<EntityType, std::function<EntityBase*(void)>, EnumClassHash>;
using EnemyTypes = std::unordered_map<string, string>;

struct SharedContext;

class EntityManager
{
public:
    EntityManager(SharedContext* context, unsigned int maxEntities);
    ~EntityManager();

    SharedContext* getContext();

    int add(const EntityType& type, const string& name = "");

    EntityBase* find(unsigned int id);

    EntityBase* find(const string& name);

    void remove(unsigned int id);

    void update(float dt);

    void draw();

    void purge();

private:
    SharedContext* mContext;
    EntityContainer mEntities;
    EnemyTypes mEnemyTypes;
    EntityFactory mEntityFactory;

    /// Highest id given to entity manager
    unsigned int mIdCounter;
    unsigned int mMaxEntities;
    std::vector<unsigned int> mEntitiesToRemove;

    void processRemoval();
    void loadEnemyTypes(const string& name);
    void entityCollisionCheck();

    template<class T>
    void registerEntity(const EntityType& type)
    {
        mEntityFactory[type] = [this]() -> EntityBase*
        {
            return new T(this);
        };
    }
};

#endif // ENTITY_MANAGER_H
