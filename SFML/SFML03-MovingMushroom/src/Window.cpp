#include "Window.h"

bool Window::isDone() const { return mIsDone; }

bool Window::isFullscreen() const { return mIsFullscreen; }

sf::Vector2u Window::getWindowSize() const { return mWindowSize; }

sf::RenderWindow *Window::getRenderWindow() { return &mWindow; }

EventManager *Window::getEventManager() { return &mEventManager; }

Window::Window()
{
    setup("Window", sf::Vector2u(640, 480));
}

Window::Window(const std::string &title, const sf::Vector2u &size)
{
    setup(title, size);
}

Window::~Window()
{
    destroy();
}

void Window::setup(const std::string &title, const sf::Vector2u &size)
{
    mWindowTitle = title;
    mWindowSize = size;
    mIsFullscreen = false;
    mIsDone = false;
    mIsFocused = true;
    mEventManager.addCallback(StateType(0), "window_close", &Window::close, this);        
    mEventManager.addCallback(StateType(0), "fullscreen_toggle", &Window::toggleFullscreen, this);
    create();
}

void Window::create()
{
    auto style = (mIsFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
    mWindow.create({mWindowSize.x, mWindowSize.y, 32}, mWindowTitle, style);
    mWindow.setFramerateLimit(60);
}

void Window::destroy()
{
    mWindow.close();
}

void Window::update()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        // Closse
        if (event.type == sf::Event::Closed)
        {
            mIsDone = true;
        }
        // Focus
        if (event.type == sf::Event::LostFocus)
        {
            mIsFocused = false;
            mEventManager.setFocus(false);
        }
        if (event.type == sf::Event::GainedFocus)
        {
            mIsFocused = true;
            mEventManager.setFocus(true);       
        }
        mEventManager.handleEvent(event);
    }
    mEventManager.update();
}

void Window::toggleFullscreen(EventDetails *details)
{
    mIsFullscreen = !mIsFullscreen;
    destroy();
    create();
}

void Window::close(EventDetails *details)
{
    mIsDone = true;
}

void Window::beginDraw()
{
    mWindow.clear(sf::Color::Black);
}

void Window::endDraw()
{
    mWindow.display();
}

void Window::draw(sf::Drawable &drawable)
{
    mWindow.draw(drawable);
}