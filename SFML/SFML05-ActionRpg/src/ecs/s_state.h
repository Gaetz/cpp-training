#ifndef S_STATE_H
#define S_STATE_H

#include "s_base.h"
#include "c_state.h"

class S_State : public S_Base{
public:
    S_State(SystemManager* systemManager);
    ~S_State();

    void update(float dt);
    void handleEvent(const EntityId& entity,const EntityEvent& event);
    void notify(const Message& message);
private:
    void changeState(const EntityId& entity, const EntityState& state,
        const bool& force);
};

#endif // S_STATE_H
