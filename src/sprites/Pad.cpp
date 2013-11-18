#include "Pad.h"

PadSprite::PadSprite(b2World *world)
    : Sprite(world)
    , m_restitution(0.0f)
    , m_density(25.0f)
    , m_friction(0.0f)
{
}

bool PadSprite::init()
{
    // sprites/animations
    setImage("sprites/padblue.png");
    addChild(m_sprite);
    //

    // physics
    CCPoint p = getPosition();

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(p.x / PTM_RATIO, p.y / PTM_RATIO);
    bodyDef.userData = this;
    bodyDef.allowSleep = true;

    m_body = m_world->CreateBody(&bodyDef);

    b2Vec2 box[4];
    float xOffset = (width() / 2.f) / PTM_RATIO;
    float yOffset = (height() / 2.f) / PTM_RATIO;

    // counter clockwise
    box[0].Set(-xOffset, -yOffset);
    box[1].Set(xOffset, -yOffset);
    box[2].Set(xOffset, yOffset);
    box[3].Set(-xOffset, yOffset);

    b2PolygonShape shape;
    shape.Set(box, 4);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.restitution = m_restitution;
    fixtureDef.density = m_density;
    fixtureDef.friction = m_friction;

    m_body->CreateFixture(&fixtureDef);

    return true;
}

void PadSprite::beginContact(Sprite *sprite)
{
}
