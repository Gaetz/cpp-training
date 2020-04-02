#ifndef S_CONTROL_H
#define S_CONTROL_H

#include "s_base.h"

class S_Control : public S_Base{
public:
    S_Control(SystemManager* systemManager);
    ~S_Control();

    void update(float dt);
    void handleEvent(const EntityId& entity, const EntityEvent& event);
    void notify(const Message& message);
private:
    void moveEntity(const EntityId& entity, const Direction& dir);
};

#endif // S_CONTROL_H
