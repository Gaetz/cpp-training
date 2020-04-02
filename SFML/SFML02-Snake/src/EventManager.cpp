#include "EventManager.h"

EventManager::EventManager() : mHasFocus(true) { loadBindings(); }

EventManager::~EventManager()
{
    for (auto &itr : mBindings)
    {
        delete itr.second;
        itr.second = nullptr;
    }
}

void EventManager::setFocus(const bool &focus) { mHasFocus = focus; }

bool EventManager::addBinding(Binding *binding)
{
    if (mBindings.find(binding->mName) != mBindings.end())
        return false;

    return mBindings.emplace(binding->mName, binding).second;
}

bool EventManager::removeBinding(string name)
{
    auto itr = mBindings.find(name);
    if (itr == mBindings.end())
        return false;
    delete itr->second;
    mBindings.erase(itr);
    return true;
}

void EventManager::handleEvent(sf::Event &event)
{
    for (auto &bItr : mBindings)
    {
        Binding *bind = bItr.second;
        for (auto &eItr : bind->mEvents)
        {
            EventType sfmlEvent = (EventType)event.type;
            if (eItr.first != sfmlEvent)
                continue;
            if (sfmlEvent == EventType::KeyDown || sfmlEvent == EventType::KeyUp)
            {
                if (eItr.second.mCode == event.key.code)
                {
                    // Matching event/keystroke
                    if (bind->mDetails.mKeyCode != -1)
                    {
                        bind->mDetails.mKeyCode = eItr.second.mCode;
                    }
                    // Increase count
                    ++(bind->c);
                    break;
                }
            }
            else if (sfmlEvent == EventType::MButtonDown || sfmlEvent == EventType::MButtonUp)
            {
                if (eItr.second.mCode == event.mouseButton.button)
                {
                    // Matching event/keystroke
                    bind->mDetails.mMouse.x = event.mouseButton.x;
                    bind->mDetails.mMouse.y = event.mouseButton.y;
                    if (bind->mDetails.mKeyCode != -1)
                    {
                        bind->mDetails.mKeyCode = eItr.second.mCode;
                    }
                    // Increase count
                    ++(bind->c);
                    break;
                }
                // No additional checking
                else
                {
                    if (sfmlEvent == EventType::MouseWheel)
                    {
                        bind->mDetails.mMouseWheelDelta = event.mouseWheel.delta;
                    }
                    else if (sfmlEvent == EventType::WindowResized)
                    {
                        bind->mDetails.mSize.x = event.size.width;
                        bind->mDetails.mSize.y = event.size.height;
                    }
                    else if (sfmlEvent == EventType::TextEntered)
                    {
                        bind->mDetails.mTextEntered = event.text.unicode;
                    }
                    ++(bind->c);
                }
            }
        }
    }
}

void EventManager::update()
{
    if (!mHasFocus)
        return;

    for (auto &bItr : mBindings)
    {
        Binding *bind = bItr.second;
        for (auto &eItr : bind->mEvents)
        {
            switch (eItr.first)
            {
            case (EventType::Keyboard):
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(eItr.second.mCode)))
                {
                    if (bind->mDetails.mKeyCode != -1)
                    {
                        bind->mDetails.mKeyCode = eItr.second.mCode;
                    }
                    ++(bind->c);
                }
                break;
            case (EventType::Mouse):
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button(eItr.second.mCode)))
                {
                    if (bind->mDetails.mKeyCode != -1)
                    {
                        bind->mDetails.mKeyCode = eItr.second.mCode;
                    }
                    ++(bind->c);
                }
                break;
            case (EventType::Joystick):
                // Up for expansion.
                break;
            }
        }

        if (bind->mEvents.size() == bind->c)
        {
            auto callItr = mCallbacks.find(bind->mName);
            if (callItr != mCallbacks.end())
            {
                // Invoke callback function with details as arguments
                callItr->second(&bind->mDetails);
            }
            bind->c = 0;
            bind->mDetails.clear();
        }
    }
}

void EventManager::loadBindings()
{
    string delimiter = ":";

    std::ifstream bindings;
    bindings.open("keys.cfg");
    if (!bindings.is_open())
    {
        std::cout << "Failed loading keys.cfg" << std::endl;
        return;
    }

    string line;
    while (std::getline(bindings, line))
    {
        std::stringstream keystream(line);
        string callbackName;
        keystream >> callbackName;
        Binding *bind = new Binding(callbackName);
        while (!keystream.eof())
        {
            string keyval;
            keystream >> keyval;
            int start = 0;
            int end = keyval.find(delimiter);
            if (end == string::npos)
            {
                delete bind;
                bind = nullptr;
                break;
            }
            EventType type = EventType(stoi(keyval.substr(start, end - start)));
            int code = stoi(keyval.substr(end + delimiter.length(), keyval.find(delimiter, end + delimiter.length())));
            EventInfo eventInfo;
            eventInfo.mCode = code;

            bind->bindEvent(type, eventInfo);
        }

        if (!addBinding(bind))
        {
            delete bind;
        }
        bind = nullptr;
    }
    bindings.close();
}