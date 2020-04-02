#ifndef MESSAGE_H
#define MESSAGE_H

using MessageType = unsigned int;
struct TwoFloats { float mX; float mY; };

struct Message
{
    Message(const MessageType& type) : mType(type) {}

    MessageType mType;
    int mSender;
    int mReceiver;

    union {
        TwoFloats m2f;
        bool mBool;
        int mInt;
    };
};

#endif // MESSAGE_H
