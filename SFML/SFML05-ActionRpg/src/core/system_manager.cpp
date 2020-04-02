#include "system_manager.h"
#include "entity_manager.h"

SystemManager::SystemManager() : mEntityManager(nullptr)
{
    mSystems[System::Movement] = new S_Movement(this);
    mSystems[System::Renderer] = new S_Renderer(this);
    mSystems[System::State] = new S_State(this);
    mSystems[System::Control] = new S_Control(this);
    mSystems[System::SheetAnimation] = new S_SheetAnimation(this);
    //mSystems[System::Collision] = new S_Collision(this);
}

SystemManager::~SystemManager()
{
    purgeSystems();
}

void SystemManager::setEntityManager(EntityManager *entityManager)
{
    if(!mEntityManager) {
        mEntityManager = entityManager;
    }
}

EntityManager* SystemManager::getEntityManager() { return mEntityManager; }

MessageHandler* SystemManager::getMessageHandler() { return &mMessages; }

void SystemManager::addEvent(const EntityId &entityId, const EventId &event)
{
    mEvents[entityId].addEvent(event);
}

void SystemManager::update(float dt)
{
    for(auto &itr : mSystems) {
        itr.second->update(dt);
    }
    handleEvents();
}

void SystemManager::handleEvents()
{
    for(auto &event : mEvents) {
        EventId id = 0;
        // While we are processing event queue
        while(event.second.processEvents(id)) {
            // For each system
            for(auto &system : mSystems) {
                // Check if system has the entity of the event queue
                if(system.second->hasEntity(event.first)) {
                    // If so execute event
                    system.second->handleEvent(event.first, (EntityEvent)id);
                }
            }
        }
    }
}

void SystemManager::draw(Window *window, unsigned int elevation)
{
    auto itr = mSystems.find(System::Renderer);
    if(itr == mSystems.end())
        return;
    S_Renderer* system = (S_Renderer*)itr->second;
    system->render(window, elevation);
}

void SystemManager::entityModified(const EntityId &entityId, const Bitmask &bits)
{
    // Add or remove entities if it fits requirements for a system
    for(auto &sItr : mSystems) {
        S_Base* system = sItr.second;
        if(system->fitsRequirements(bits)) {
            if(!system->hasEntity(entityId)) {
                system->addEntity(entityId);
            }
        } else {
            if(system->hasEntity(entityId)) {
                system->removeEntity(entityId);
            }
        }
    }
}

void SystemManager::removeEntity(const EntityId &entity)
{
    for(auto &system : mSystems) {
        system.second->removeEntity(entity);
    }
}

void SystemManager::purgeEntities()
{
    for(auto &system : mSystems) {
        system.second->purge();
    }
}

void SystemManager::purgeSystems()
{
    for(auto &system : mSystems) {
        delete system.second;
    }
    mSystems.clear();
}
