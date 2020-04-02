#ifndef S_SHEET_ANIMATION_H
#define S_SHEET_ANIMATION_H

#include "s_base.h"

class S_SheetAnimation : public S_Base{
public:
    S_SheetAnimation(SystemManager* systemManager);
    ~S_SheetAnimation();

    void update(float dt);
    void handleEvent(const EntityId& entity, const EntityEvent& event);
    void notify(const Message& message);
private:
    void changeAnimation(const EntityId& entity, const std::string& anim, bool play, bool loop);
};
#endif // S_SHEET_ANIMATION_H
