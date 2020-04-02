#ifndef BITMASK_H
#define BITMASK_H

#include <stdint.h>

using Bitset = uint32_t;

class Bitmask
{
public:
    Bitmask() : mBits(0){}
    Bitmask(const Bitset& bits) : mBits(bits) {}

    Bitset getMask() const { return mBits; }
    void setMask(const Bitset& value) { mBits = value; }

    bool matches(const Bitmask& bits, const Bitset& relevant = 0) const
    {
        return (relevant ? ((bits.getMask() & relevant) == (mBits & relevant)) : (bits.getMask() == mBits));
    }

    bool getBit(const unsigned int& pos) const
    {
        return ((mBits & (1 << pos)) != 0);
    }

    void turnOnBit(const unsigned int& pos)
    {
        mBits |= 1 << pos;
    }

    void turnOnBits(const Bitset& bits)
    {
        mBits |= bits;
    }

    void clearBit(const unsigned int& pos)
    {
        mBits &= ~(1 << pos);
    }

    void toggleBit(const unsigned int& pos)
    {
        mBits ^= 1 << pos;
    }

    void clear()
    {
        mBits = 0;
    }

private:
    Bitset mBits;
};

#endif // BITMASK_H
