#ifndef MORE_HASH_H
#define MORE_HASH_H

struct EnumClassHash
{
    template <typename T>
    std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};

#endif // MORE_HASH_H
