#ifndef __BALL_H__
#define __BALL_H__

#include "Sprite.h"

class BallSprite : public Sprite
{
public:
    BallSprite(b2World *world);

    virtual bool init();

private:
    float m_restitution;
    float m_density;
    float m_friction;
};

#endif // __BALL_H__
