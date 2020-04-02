#include "StateManager.h"


StateManager::StateManager(SharedContext *context) : mContext(context)
{
    registerState<State_Intro>(StateType::Intro);
    registerState<State_MainMenu>(StateType::MainMenu);
    registerState<State_Game>(StateType::Game);
    registerState<State_Paused>(StateType::Paused);
}

StateManager::~StateManager()
{
    for (auto &itr : mStates)
    {
        itr.second->onDestroy();
        delete itr.second;
    }
}

SharedContext *StateManager::getContext()
{
    return mContext;
}

void StateManager::update(const sf::Time &time)
{
    if (mStates.empty())
        return;

    // Check if last added state is transcendent
    // and if transcendency is relevant.
    if (mStates.back().second->isTranscendent() && mStates.size() > 1)
    {
        auto itr = mStates.end();
        // Iterate backward until a state is not transcendent (or until the first state)
        while (itr != mStates.begin())
        {
            if (itr != mStates.end())
            {
                if (!itr->second->isTranscendent())
                {
                    break;
                }
            }
            --itr;
        }
        // From this first non-transcendent state, draw all states in correct order
        for (; itr != mStates.end(); ++itr)
        {
            itr->second->update(time);
        }
    }
    // Only one state
    else
    {
        mStates.back().second->update(time);
    }
}

void StateManager::draw()
{
    if (mStates.empty())
        return;

    // Check if last added state is transparent
    // and if tranparency is relevant.
    if (mStates.back().second->isTransparent() && mStates.size() > 1)
    {
        auto itr = mStates.end();
        // Iterate backward until a state is not transparent (or until the first state)
        while (itr != mStates.begin())
        {
            if (itr != mStates.end())
            {
                if (!itr->second->isTransparent())
                {
                    break;
                }
            }
            --itr;
        }
        // From this first non-transparent state, draw all states in correct order
        for (; itr != mStates.end(); ++itr)
        {
            itr->second->draw();
        }
    }
    // Only one state
    else
    {
        mStates.back().second->draw();
    }
}

void StateManager::processRequests()
{
    while (mToRemove.begin() != mToRemove.end())
    {
        // Deallocate ressource
        removeState(*mToRemove.begin());
        // Erase element
        mToRemove.erase(mToRemove.begin());
    }
}

bool StateManager::hasState(const StateType &type)
{
    for (auto itr = mStates.begin(); itr != mStates.end(); ++itr)
    {
        if (itr->first == type)
        {
            // Check if state is not about to be removed
            auto removed = std::find(mToRemove.begin(), mToRemove.end(), type);
            // If it is not, state has been found
            if (removed == mToRemove.end())
                return true;
            // Else, consider state is not found
            return false;
        }
    }
    // State not found
    return false;
}

void StateManager::remove(const StateType &type)
{
    mToRemove.push_back(type);
}

void StateManager::switchTo(const StateType &type)
{
    mContext->mEventManager->setCurrentState(type);
    // Search if state already exists
    for (auto itr = mStates.begin(); itr != mStates.end(); ++itr)
    {
        // If state already exists, deactivate former active state,
        // move found state to the top of the stack (last position) and activate
        if (itr->first == type)
        {
            mStates.back().second->deactivate();
            StateType tmpType = itr->first;
            BaseState *tmpState = itr->second;
            mStates.erase(itr);
            mStates.emplace_back(tmpType, tmpState);
            tmpState->activate();
            return;
        }
    }
    // If state not found, create a new state
    if (!mStates.empty())
        mStates.back().second->deactivate();
    createState(type);
    mStates.back().second->activate();
}

void StateManager::createState(const StateType &type)
{
    auto newState = mStateFactory.find(type);
    if (newState == mStateFactory.end())
        return;
    BaseState *state = newState->second();
    mStates.emplace_back(type, state);
    state->onCreate();
}

void StateManager::removeState(const StateType& type)
{
    for(auto itr = mStates.begin(); itr != mStates.end(); ++itr)
    {
        if(itr->first == type)
        {
            itr->second->onDestroy();
            delete itr->second;
            mStates.erase(itr);
            return;
        }
    }
}
