#ifndef __PAD_H__
#define __PAD_H__

#include "Sprite.h"

class PadSprite : public Sprite
{
public:
    PadSprite(b2World *world);

    virtual bool init();

    void beginContact(Sprite *sprite);

private:
    float m_restitution;
    float m_density;
    float m_friction;
};

#endif // __PAD_H__
