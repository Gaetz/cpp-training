#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <vector>
#include <unordered_map>
#include "../states/state_base.h"
#include "../states/state_intro.h"
#include "../states/state_mainmenu.h"
#include "../states/state_game.h"
#include "../states/state_paused.h"
#include "shared_context.h"

enum class StateType{ Intro = 1, MainMenu, Game, Paused, GameOver, Credits };

using StateContainer = std::vector<std::pair<StateType, BaseState *>>;
using TypeContainer = std::vector<StateType>;
using StateFactory = std::unordered_map<StateType, std::function<BaseState*(void)>, EnumClassHash>;

class StateManager
{
  public:
    StateManager(SharedContext *context);
    ~StateManager();

    SharedContext *getContext();

    void update(const sf::Time &time);
    void draw();

    /// Ensure states are no longer used
    void processRequests();

    bool hasState(const StateType &type);
    void switchTo(const StateType &type);
    void remove(const StateType &type);

  private:
    SharedContext *mContext;
    StateContainer mStates;
    TypeContainer mToRemove;
    StateFactory mStateFactory;

    void createState(const StateType &type);
    void removeState(const StateType &type);

    template <class T>
    void registerState(const StateType &type)
    {
        mStateFactory[type] = [this]() -> BaseState* 
        {
            return new T(this);
        };
    }
};

#endif // STATE_MANAGER_H
