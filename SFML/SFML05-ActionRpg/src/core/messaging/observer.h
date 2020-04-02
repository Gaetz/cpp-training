#ifndef OBSERVER_H
#define OBSERVER_H

#include "message.h"

class Observer
{
public:
    virtual ~Observer() {}
    virtual void notify(const Message& message) = 0;
};

#endif // OBSERVER_H
