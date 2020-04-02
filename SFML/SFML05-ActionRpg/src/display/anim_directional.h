#ifndef ANIM_DIRECTIONAL_H
#define ANIM_DIRECTIONAL_H

#include "anim_base.h"
#include "directions.h"

class Anim_Directional : public Anim_Base
{
protected:
    void frameStep();
    void cropSprite();
    void readIn(std::stringstream& stream);
};

#endif // ANIM_DIRECTIONAL_H
