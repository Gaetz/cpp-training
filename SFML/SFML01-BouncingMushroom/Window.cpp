#include "Window.h"

bool Window::isDone() const {
    return mIsDone;
}

bool Window::isFullscreen() const {
    return mIsFullscreen;
}

sf::Vector2u Window::getWindowSize() const {
    return mWindowSize;
}

Window::Window() {
    setup("Window", sf::Vector2u(640, 480));
}

Window::Window(const std::string& title, const sf::Vector2u& size) {
    setup(title, size);
}

Window::~Window() {
    destroy();
}

void Window::setup(const std::string& title, const sf::Vector2u& size) {
    mWindowTitle = title;
    mWindowSize = size;
    mIsFullscreen = false;
    mIsDone = false;
    create();
}

void Window::create() {
    auto style = (mIsFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
    mWindow.create({ mWindowSize.x, mWindowSize.y, 32 }, mWindowTitle, style );
    mWindow.setFramerateLimit(60);    
}

void Window::destroy() {
    mWindow.close();
}

void Window::update() {
    sf::Event event;
    while(mWindow.pollEvent(event)) {
        // Close
        if(event.type == sf::Event::Closed) {
            mIsDone = true;
        }
        // Fullscreen toggle
        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F11) {
            toggleFullscreen();
        }
    }
}

void Window::toggleFullscreen() {
    mIsFullscreen = !mIsFullscreen;
    destroy();
    create();
}

void Window::beginDraw() {
    mWindow.clear(sf::Color::Black);    
}

void Window::endDraw() {
    mWindow.display();    
}

void Window::draw(sf::Drawable& drawable) {
    mWindow.draw(drawable);
}