#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <vector>
#include "observer.h"

using ObserverContainer = std::vector<Observer*>;

class Communicator
{
public:
    ~Communicator() { mObservers.clear(); }

    bool addObserver(Observer* observer) {
        if(hasObserver(observer))
            return false;
        mObservers.emplace_back(observer);
        return true;
    }

    bool removeObserver(Observer* observer) {
        auto foundObserver = std::find_if(mObservers.begin(), mObservers.end(), [&observer](Observer* o) { return o == observer; });
        if(foundObserver == mObservers.end())
            return false;
        mObservers.erase(foundObserver);
        return true;
    }

    bool hasObserver(const Observer* observer) {
        return (std::find_if(mObservers.begin(), mObservers.end(), [&observer](Observer* o) { return o == observer; }) != mObservers.end());
    }

    void broadcast(const Message& message) {
        for(auto& itr : mObservers) { itr->notify(message); }
    }

private:
    ObserverContainer mObservers;
};

#endif // COMMUNICATOR_H
