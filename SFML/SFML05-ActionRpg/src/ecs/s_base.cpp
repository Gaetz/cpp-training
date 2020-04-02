#include "s_base.h"
#include "../core/system_manager.h"

S_Base::S_Base(const System &id, SystemManager *systemManager): mId(id), mSystemManager(systemManager) {}

S_Base::~S_Base()
{
    purge();
}

bool S_Base::addEntity(const EntityId &entity)
{
    if(hasEntity(entity))
        return false;
    mEntities.emplace_back(entity);
    return true;
}

bool S_Base::hasEntity(const EntityId &entity)
{
    return std::find(mEntities.begin(), mEntities.end(), entity) != mEntities.end();
}

bool S_Base::removeEntity(const EntityId &entity)
{
    auto foundEntity = std::find_if(mEntities.begin(), mEntities.end(), [&entity](EntityId& id) { return id == entity; });
    if(foundEntity == mEntities.end())
        return false;
    mEntities.erase(foundEntity);
    return true;
}

bool S_Base::fitsRequirements(const Bitmask& bits)
{
    return std::find_if(mRequiredComponents.begin(), mRequiredComponents.end(), [&bits](Bitmask& b) {
        return b.matches(bits, b.getMask());
    }) != mRequiredComponents.end();
}

void S_Base::purge()
{
    mEntities.clear();
}
