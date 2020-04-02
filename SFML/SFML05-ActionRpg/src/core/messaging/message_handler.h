#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include "communicator.h"
#include "../../ecs/entity_messages.h"
#include "../../utils/more_hash.h"

#include <unordered_map>

using Subscriptions = std::unordered_map<EntityMessage, Communicator, EnumClassHash>;

class MessageHandler
{
public:
    bool subscribe(const EntityMessage& type, Observer* observer)
    {
        return mCommunicators[type].addObserver(observer);
    }

    bool unsubscribe(const EntityMessage& type, Observer* observer)
    {
        return mCommunicators[type].removeObserver(observer);
    }

    void dispatch(const Message& message)
    {
        auto itr = mCommunicators.find((EntityMessage)message.mType);
        if(itr == mCommunicators.end()) { return; }
        itr->second.broadcast(message);
    }

private:
    Subscriptions mCommunicators;
};

#endif // MESSAGE_HANDLER_H
