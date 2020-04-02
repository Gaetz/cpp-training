#ifndef C_COLLIDABLE_H
#define C_COLLIDABLE_H

#include "c_base.h"

class C_Collidable: public C_Base {
public:
    C_Collidable(): C_Base(Component::Collidable) {}
    ~C_Collidable() {}

};
#endif // C_COLLIDABLE_H
