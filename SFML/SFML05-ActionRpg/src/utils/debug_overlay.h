#ifndef DEBUG_OVERLAY_H
#define DEBUG_OVERLAY_H

#include <vector>
#include <SFML/Graphics.hpp>

class DebugOverlay{
public:
    DebugOverlay(){
        mDebug = false;
    }

    void add(sf::Drawable* drawable){
        mDrawables.push_back(drawable);
    }

    void draw(sf::RenderWindow* window){
        while(mDrawables.begin() != mDrawables.end()){
            window->draw(*mDrawables.back());
            delete mDrawables.back();
            mDrawables.pop_back();
        }
    }

    bool debug(){ return mDebug; }
    void setDebug(const bool& val){ mDebug = val; }
private:
    std::vector<sf::Drawable*> mDrawables;
    bool mDebug;
};
#endif // DEBUG_OVERLAY_H
