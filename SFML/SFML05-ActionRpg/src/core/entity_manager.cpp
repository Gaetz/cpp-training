#include "entity_manager.h"
#include "system_manager.h"


EntityManager::EntityManager(SystemManager* sysMgr, Asset_Texture* textureMgr):
    mIdCounter(0),
    mSystems(sysMgr),
    mTextureManager(textureMgr)
{
    addComponentType<C_Position>(Component::Position);
    addComponentType<C_SpriteSheet>(Component::SpriteSheet);
    addComponentType<C_State>(Component::State);
    addComponentType<C_Movable>(Component::Movable);
    addComponentType<C_Controller>(Component::Controller);
    //addComponentType<C_Collidable>(Component::Collidable);
}

EntityManager::~EntityManager()
{
    purge();
}

int EntityManager::addEntity(const Bitmask &mask)
{
    unsigned int id = mIdCounter;
    if(!mEntities.emplace(id, EntityData(0, ComponentContainer())).second) {
        return -1;
    }
    ++mIdCounter;
    for(unsigned int i = 0; i < N_COMPONENT_TYPES; ++i) {
        if(mask.getBit(i)) {
            addComponent(id, (Component)i);
        }
    }
    // Notify system manager of a modified entity
    mSystems->entityModified(id, mask);
    mSystems->addEvent(id, (EventId)EntityEvent::Spawned);
    return id;
}

int EntityManager::addEntity(const std::string &entityFile)
{
    int entityId = -1;

    std::ifstream file;
    file.open(Utils::getWorkingDirectory() + "assets/data/entities/" + entityFile + ".entity");
    if(!file.is_open()) {
        std::cout << "Failed to load entity: " << entityFile << std::endl;
        return -1;
    }
    std::string line;
    while(std::getline(file, line)) {
        if(line[0] == '|')
            continue;
        std::stringstream keystream(line);
        std::string type;
        keystream >> type;
        if(type == "Name") {

        } else if(type == "Attributes") {
            if(entityId != -1)
                continue;
            Bitset set = 0;
            Bitmask mask;
            keystream >> set;
            mask.setMask(set);
            entityId = addEntity(mask);
            if(entityId == -1)
                return -1;
        } else if(type == "Component") {
            if(entityId == -1)
                continue;
            unsigned int cId = 0;
            keystream >> cId;
            C_Base* component = getComponent<C_Base>(entityId, (Component)cId);
            if(!component)
                continue;
            keystream >> *component;
            if(component->getType() == Component::SpriteSheet) {
                C_SpriteSheet* sheet = (C_SpriteSheet*)component;
                sheet->create(mTextureManager);
            }
        }
    }
    file.close();
    return entityId;
}


bool EntityManager::removeEntity(const EntityId &id) {
    auto itr = mEntities.find(id);
    if(itr == mEntities.end())
        return false;
    // Remove all components
    while(itr->second.second.begin() != itr->second.second.end()) {
        delete itr->second.second.back();
        itr->second.second.pop_back();
    }
    // Remove entity
    mEntities.erase(itr);
    mSystems->removeEntity(id);
    return true;
}

bool EntityManager::addComponent(const EntityId &id, const Component &component)
{
    // Checks
    auto itr = mEntities.find(id);
    if(itr == mEntities.end())
        return false;
    if(itr->second.first.getBit((unsigned int)component))
        return false;
    auto itr2 = mComponentFactory.find(component);
    if(itr2 == mComponentFactory.end())
        return false;
    // Component type exists
    C_Base* newComponent = itr2->second();
    itr->second.second.emplace_back(newComponent);
    itr->second.first.turnOnBit((unsigned int)component);
    // Notify systems
    mSystems->entityModified(id, itr->second.first);
    return true;
}

bool EntityManager::removeComponent(const EntityId &id, const Component &component)
{
    // Checks
    auto itr = mEntities.find(id);
    if(itr == mEntities.end())
        return false;
    if(!itr->second.first.getBit((unsigned int)component))
        return false;
    // Component exists
    auto& container = itr->second.second;
    auto foundComponent = std::find_if(container.begin(), container.end(), [&component](C_Base* c) {
        return c->getType() == component;
    });
    if(foundComponent == container.end())
        return false;
    delete(*foundComponent);
    container.erase(foundComponent);
    itr->second.first.clearBit((unsigned int)component);
    // Notify systems
    mSystems->entityModified(id, itr->second.first);
    return true;
}

bool EntityManager::hasComponent(const EntityId &id, const Component &component)
{
    auto itr = mEntities.find(id);
    if(itr == mEntities.end())
        return false;
    return itr->second.first.getBit((unsigned int)component);
}

void EntityManager::purge()
{
    mSystems->purgeEntities();
    for(auto& entity : mEntities) {
        for(auto &component : entity.second.second) {
            delete component;
        }
        entity.second.second.clear();
        entity.second.first.clear();
    }
    mEntities.clear();
    mIdCounter = 0;
}
