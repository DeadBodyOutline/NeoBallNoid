#ifndef __BRICK_H__
#define __BRICK_H__

#include "Sprite.h"

class BrickSprite : public Sprite
{
public:
    // XXX the game will accept different types of
    // bricks, with different materials and so on
    enum Type {
        Normal
    };

    BrickSprite(b2World *world, Type type = Normal);

    virtual bool init();
    void beginContact(Sprite *sprite);

    Type getType() const;
    bool canBeDeleted() const;

private:
    void destroy();

    Type m_type;
    bool m_canBeDeleted;

    float m_restitution;
    float m_density;
    float m_friction;
};

#endif // __BRICK_H__
