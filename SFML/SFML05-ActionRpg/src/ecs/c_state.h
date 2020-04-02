#ifndef C_STATE_H
#define C_STATE_H

#include "c_base.h"

enum class EntityState { Idle, Walking, Attacking, Hurt, Dying };

class C_State: public C_Base {
public:
    C_State(): C_Base(Component::State) {}
    ~C_State() {}

    void readIn(std::stringstream &stream) {
        unsigned int state = 0;
        stream >> state;
        mState = (EntityState)state;
    }

    EntityState getState() { return mState; }
    void setState(const EntityState state) {
        mState = state;
    }

    private:
        EntityState mState;
};

#endif // C_STATE_H
