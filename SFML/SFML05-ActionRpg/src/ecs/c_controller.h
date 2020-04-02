#ifndef C_CONTROLLER_H
#define C_CONTROLLER_H

#include "c_base.h"

class C_Controller: public C_Base {
public:
    C_Controller(): C_Base(Component::Controller) {}
    ~C_Controller() {}

    void readIn(std::stringstream &stream) {}
};

#endif // C_CONTROLLER_H
