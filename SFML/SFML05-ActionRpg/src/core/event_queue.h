#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include <queue>

using EventId = unsigned int;

class EventQueue
{
public:
    void addEvent(const EventId& event)
    {
        mQueue.push(event);
    }

    bool processEvents(EventId& id)
    {
        if(mQueue.empty()) {
            return false;
        }
        id = mQueue.front();
        mQueue.pop();
        return true;
    }

    void clear()
    {
        while(!mQueue.empty())
        {
            mQueue.pop();
        }
    }

private:
    std::queue<EventId> mQueue;

};

#endif // EVENTQUEUE_H
