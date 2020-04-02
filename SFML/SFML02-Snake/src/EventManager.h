#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <fstream>
#include <sstream>
#include <iostream>

using std::string;

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

using Events = std::vector<std::pair<EventType, EventInfo>>;

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

using Callbacks = std::unordered_map<string, std::function<void(EventDetails *)>>;

class EventManager
{
  public:
    EventManager();
    ~EventManager();

    bool addBinding(Binding *binding);
    bool removeBinding(string name);
    void setFocus(const bool &focus);

    // Defined in the header because it is templated
    template <class T>
    bool addCallback(const string &name, void (T::*func)(EventDetails *), T *instance)
    {
        auto temp = std::bind(func, instance, std::placeholders::_1);
        return mCallbacks.emplace(name, temp).second;
    }

    void removeCallback(const string &name)
    {
        mCallbacks.erase(name);
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
    Callbacks mCallbacks;
    bool mHasFocus;
};
