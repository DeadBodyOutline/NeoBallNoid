#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "../box2d/Utils.h"
#include "../box2d/Contact.h"

USING_NS_CC;

using namespace std;

class Sprite : public CCNode
{
public:
    Sprite(b2World *world);
    virtual ~Sprite();

    virtual bool init() = 0;

    // contact stuff
    virtual void beginContact(Sprite *sprite) { CC_UNUSED_PARAM(sprite); };
    virtual void endContact(Sprite *sprite) { CC_UNUSED_PARAM(sprite); };
    virtual void preContact(Sprite *sprite, Contact *contact) {
        CC_UNUSED_PARAM(sprite);
        CC_UNUSED_PARAM(contact);
    };
    virtual void posContact(Sprite *sprite, Contact *contact) {
        CC_UNUSED_PARAM(sprite);
        CC_UNUSED_PARAM(contact);
    };

    // physics stuff
    virtual void applyLinearImpulse(float x, float y) {
        CC_UNUSED_PARAM(x);
        CC_UNUSED_PARAM(y);
    };
    b2Body *getBody() { return m_body; }

    // sprite related stuff
    virtual void setImage(const char *imageFile);

    float width() const;
    float height() const;

protected:
    virtual void updateSprite() {};

    CCSprite *m_sprite;

    b2Body *m_body;
    b2World *m_world;

private:
    void draw();
};

#endif // __SPRITE_H__
