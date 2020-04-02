#include "s_renderer.h"
#include "../core/system_manager.h"

S_Renderer::S_Renderer(SystemManager* systemManager): S_Base(System::Renderer, systemManager)
{
    Bitmask req;
    req.turnOnBit((unsigned int) Component::Position);
    req.turnOnBit((unsigned int) Component::SpriteSheet);
    mRequiredComponents.push_back(req);
    req.clear();

    mSystemManager->getMessageHandler()->subscribe(EntityMessage::Direction_Changed, this);
}

S_Renderer::~S_Renderer() {}

void S_Renderer::update(float dt)
{
    EntityManager* entities = mSystemManager->getEntityManager();
    for(auto &entity: mEntities) {
        C_Position* position = entities->getComponent<C_Position>(entity, Component::Position);
        C_Drawable* drawable = nullptr;
        if(entities->hasComponent(entity, Component::SpriteSheet)) {
            drawable = entities->getComponent<C_Drawable>(entity, Component::SpriteSheet);
        } else {
            continue;
        }
        drawable->updatePosition(position->getPosition());
    }
}

void S_Renderer::handleEvent(const EntityId &entity, const EntityEvent &event)
{
    if(event == EntityEvent::Moving_Left
            || event == EntityEvent::Moving_Right
            || event == EntityEvent::Moving_Down
            || event == EntityEvent::Moving_Up
            || event == EntityEvent::Elevation_Change
            || event == EntityEvent::Spawned) {
        sortDrawables();
    }
}

void S_Renderer::notify(const Message &message)
{
    if(hasEntity(message.mReceiver)) {
        EntityMessage m = (EntityMessage)message.mType;
        switch(m) {
        case EntityMessage::Direction_Changed: {
            setSheetDirection(message.mReceiver, (Direction)message.mInt);
        }
            break;
        default:
            break;
        }
    }
}

void S_Renderer::render(Window *window, unsigned int layer)
{
    EntityManager* entities = mSystemManager->getEntityManager();
    for(auto &entity: mEntities) {
        C_Position* position = entities->getComponent<C_Position>(entity, Component::Position);
        // Only render layer
        if(position->getElevation() < layer)
            continue;
        if(position->getElevation() > layer)
            break;
        // Culling
        C_Drawable* drawable = nullptr;
        if(!entities->hasComponent(entity, Component::SpriteSheet))
            continue;
        drawable = entities->getComponent<C_Drawable>(entity, Component::SpriteSheet);
        sf::FloatRect drawableBounds;
        drawableBounds.left = position->getPosition().x - (drawable->getSize().x / 2);
        drawableBounds.top = position->getPosition().y - drawable->getSize().y;
        drawableBounds.width = drawable->getSize().x;
        drawableBounds.height = drawable->getSize().y;
        if(!window->getViewSpace().intersects(drawableBounds)) {
            continue;
        }
        drawable->draw(window->getRenderWindow());
    }
}

void S_Renderer::setSheetDirection(const EntityId &entity, const Direction &direction)
{
    EntityManager* entities = mSystemManager->getEntityManager();
    if(!entities->hasComponent(entity, Component::SpriteSheet)) {
        return;
    }
    C_SpriteSheet* sheet = entities->getComponent<C_SpriteSheet>(entity, Component::SpriteSheet);
    sheet->getSpriteSheet()->setDirection(direction);
}

void S_Renderer::sortDrawables()
{
    EntityManager* entities = mSystemManager->getEntityManager();
    std::sort(mEntities.begin(), mEntities.end(), [entities](unsigned int l_1, unsigned int l_2) {
        auto pos1 = entities->getComponent<C_Position>(l_1, Component::Position);
        auto pos2 = entities->getComponent<C_Position>(l_2, Component::Position);
        if(pos1->getElevation() == pos2->getElevation()) {
            return pos1->getPosition().y < pos2->getPosition().y;
        }
        return pos1->getElevation() < pos2->getElevation();
    });
}
