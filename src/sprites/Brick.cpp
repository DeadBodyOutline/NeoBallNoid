#include "Ball.h"
#include "Brick.h"

BrickSprite::BrickSprite(b2World *world, Type type)
    : Sprite(world)
    , m_type(type)
    , m_canBeDeleted(false)
    , m_restitution(0.0f)
    , m_density(25.0f)
    , m_friction(0.0f)
{
    // XXX rest., dens. and fric. will vary according Type
    // (sprite/animations as well)
}

bool BrickSprite::init()
{
    // sprites/animations
    setImage("sprites/bricks/brick.png");
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

BrickSprite::Type BrickSprite::getType() const
{
    return m_type;
}

bool BrickSprite::canBeDeleted() const
{
    return m_canBeDeleted;
}

void BrickSprite::beginContact(Sprite *sprite)
{
    BallSprite *ball = dynamic_cast<BallSprite *>(sprite);
    if (!ball)
        return;

    // XXX each ball can have different modificators that can affect the way it
    // interacts with the bricks. Also need to define how the brick contacts
    // will sum points to the player (each player will have its ball? or it'll
    // add points to the latest player's pad it had contact?)

    CCLog("Some player made points!");

    // XXX check if it can be destructed and call animation
    destroy();

    // XXX aaaaaand, give a reaction to the action ;)
}

void BrickSprite::destroy()
{
    m_canBeDeleted = true;
}
