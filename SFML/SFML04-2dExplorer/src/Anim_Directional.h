#ifndef ANIM_DIRECTIONAL_H
#define ANIM_DIRECTIONAL_H

#include "Anim_Base.h"
#include "Directions.h"

class Anim_Directional : public Anim_Base
{
protected:
    void frameStep();
    void cropSprite();
    void readIn(std::stringstream& stream);
};

#endif // ANIM_DIRECTIONAL_H
