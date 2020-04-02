#ifndef C_BASE_H
#define C_BASE_H

#include <iostream>
#include <sstream>
#include "ecs_types.h"

class C_Base
{
public:
    C_Base(const Component& type): mType(type) {}
    virtual ~C_Base() {}

    Component getType() { return mType; }

    friend std::stringstream& operator >> (std::stringstream& stream, C_Base& b) {
        b.readIn(stream);
        return stream;
    }

    virtual void readIn(std::stringstream& stream) = 0;

protected:
    Component mType;
};

#endif // C_BASE_H
