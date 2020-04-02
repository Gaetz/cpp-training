#ifndef S_RENDERER_H
#define S_RENDERER_H

#include "s_base.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include "../core/window.h"

class S_Renderer : public S_Base
{
public:
    S_Renderer(SystemManager* systemManager);
    ~S_Renderer();

    void update(float dt);
    void handleEvent(const EntityId &entity, const EntityEvent &event);
    void notify(const Message& message);
    void render(Window* window, unsigned int layer);

private:
    void setSheetDirection(const EntityId& entity, const Direction& direction);
    void sortDrawables();
};

#endif // S_RENDERER_H
