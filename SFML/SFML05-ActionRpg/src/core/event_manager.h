#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <fstream>
#include <sstream>
#include <iostream>
#include "../utils/more_hash.h"

using std::string;

/*
As a reference

enum EventType
{
    Closed,                 0
    Resized,                1
    LostFocus,              2
    GainedFocus,            3
    TextEntered,            4
    KeyPressed,             5
    KeyReleased,            6
    MouseWheelMoved,        7
    MouseWheelScrolled,     8
    MouseButtonPressed,     9
    MouseButtonReleased,    10
    MouseMoved,             11
    MouseEntered,           12
    MouseLeft,              13
    JoystickButtonPressed,  14
    JoystickButtonReleased, 15
    JoystickMoved,          16
    JoystickConnected,      17
    JoystickDisconnected,   18
    TouchBegan,             19
    TouchMoved,             20
    TouchEnded,             21
    SensorChanged,          22
    Count
};                   
*/

enum class EventType
{
    KeyDown = sf::Event::KeyPressed,
    KeyUp = sf::Event::KeyReleased,
    MButtonDown = sf::Event::MouseButtonPressed,
    MButtonUp = sf::Event::MouseButtonReleased,
    MouseWheel = sf::Event::MouseWheelMoved,
    WindowResized = sf::Event::Resized,
    GainedFocus = sf::Event::GainedFocus,
    LostFocus = sf::Event::LostFocus,
    MouseEntered = sf::Event::MouseEntered,
    MouseLeft = sf::Event::MouseLeft,
    Closed = sf::Event::Closed,
    TextEntered = sf::Event::TextEntered,
    Keyboard = sf::Event::Count + 1,
    Mouse,
    Joystick
};

struct EventInfo
{
    EventInfo() { mCode = 0; }
    EventInfo(int event) { mCode = event; }
    union {
        int mCode;
    };
};

using Events = std::vector<std::pair<EventType, EventInfo> >;

struct EventDetails
{
    string mName;

    sf::Vector2i mSize;
    sf::Uint32 mTextEntered;
    sf::Vector2i mMouse;
    int mMouseWheelDelta;
    int mKeyCode; // Single key code

    EventDetails(const string &bindName) : mName(bindName)
    {
        clear();
    }

    void clear()
    {
        mSize = sf::Vector2i(0, 0);
        mTextEntered = 0;
        mMouse = sf::Vector2i(0, 0);
        mMouseWheelDelta = 0;
        mKeyCode = -1;
    }
};

struct Binding
{
    Events mEvents;
    string mName;
    int c; // Count of events that are happening
    EventDetails mDetails;

    Binding(const string &name) : mName(name), mDetails(name), c(0) {}

    void bindEvent(EventType type, EventInfo info = EventInfo())
    {
        mEvents.emplace_back(type, info);
    }
};

using Bindings = std::unordered_map<string, Binding *>;

// Contains callbacks for a given state
using CallbacksContainer = std::unordered_map<string, std::function<void(EventDetails*)>>;
// By state callback container
enum class StateType;
using Callbacks = std::unordered_map<StateType, CallbacksContainer, EnumClassHash>;

class EventManager
{
  public:
    EventManager();
    ~EventManager();

    bool addBinding(Binding *binding);
    bool removeBinding(string name);
    void setFocus(const bool &focus);
    void setCurrentState(const StateType type);

    // Defined in the header because it is templated
    template <class T>
    bool addCallback(StateType state, const string &name, void (T::*func)(EventDetails *), T *instance)
    {
        auto itr = mCallbacks.emplace(state, CallbacksContainer()).first;
        auto temp = std::bind(func, instance, std::placeholders::_1);
        return itr->second.emplace(name, temp).second;
    }

    bool removeCallback(StateType state, const string &name)
    {
        auto itr = mCallbacks.find(state);
        if(itr == mCallbacks.end()) return false;
        auto itr2 = itr->second.find(name);
        if(itr2 == itr->second.end()) return false;
        itr->second.erase(name);
        return true;
    }

    void handleEvent(sf::Event &event);

    /// Update
    void update();

    /// Get mouse position
    sf::Vector2i getMousePosition(sf::RenderWindow *window = nullptr)
    {
        return (window ? sf::Mouse::getPosition(*window) : sf::Mouse::getPosition());
    }

  private:
    void loadBindings();

    Bindings mBindings;
    StateType mCurrentState;
    Callbacks mCallbacks;
    bool mHasFocus;
};

#endif // EVENT_MANAGER_H
