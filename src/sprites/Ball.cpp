#include "Ball.h"

BallSprite::BallSprite(b2World *world)
    : Sprite(world)
    , m_restitution(0.0f)
    , m_density(40.0f)
    , m_friction(0.0f)
{
}

bool BallSprite::init()
{
    // sprites/animations
    setImage("sprites/ball.png");
    addChild(m_sprite);
    //

    // physics
    CCPoint p = getPosition();

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(p.x / PTM_RATIO, p.y / PTM_RATIO);
    bodyDef.userData = this;
    bodyDef.allowSleep = true;

    m_body = m_world->CreateBody(&bodyDef);

    // prepare the spinning shape
    b2CircleShape shape;
    shape.m_radius = width() / 2. / PTM_RATIO;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.restitution = m_restitution;
    fixtureDef.density = m_density;
    fixtureDef.friction = m_friction;

    m_body->CreateFixture(&fixtureDef);

    return true;
}
