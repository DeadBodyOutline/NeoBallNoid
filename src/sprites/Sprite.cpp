#include "Sprite.h"

Sprite::Sprite(b2World *world)
    : CCNode()
    , m_sprite(NULL)
    , m_body(NULL)
    , m_world(world)
{
}

Sprite::~Sprite()
{
    if (m_body)
        m_world->DestroyBody(m_body);
}

float Sprite::width() const
{
    if (!m_sprite)
        return 0;

    return m_sprite->getTextureRect().size.width;
}

float Sprite::height() const
{
    if (!m_sprite)
        return 0;

    return m_sprite->getTextureRect().size.height;
}

void Sprite::setImage(const char *imageFile)
{
    if (m_sprite) {
        CCImage *image = new CCImage();
        image->initWithImageFile(imageFile);

        CCTexture2D *texture = new CCTexture2D();
        texture->initWithImage(image);

        m_sprite->setTexture(texture);
    } else
        m_sprite = CCSprite::create(imageFile);
}

void Sprite::draw()
{
#ifdef DEBUGDRAW
    ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position);
    kmGLPushMatrix();

    ccDrawColor4F(0.0, 0.8, 1.0, 1.0);
    glLineWidth(1);

    float w = width() / 2;
    float h = height() / 2;

    CCPoint vertices[] = {
        CCPointMake(-w, -h),
        CCPointMake(-w, h),
        CCPointMake(w, h),
        CCPointMake(w, -h)
    };
    ccDrawPoly(vertices, 4, true);

    // return default values
    glLineWidth(1);
    ccDrawColor4F(1.0, 1.0, 1.0, 1.0);
    ccPointSize(1);

    kmGLPopMatrix();
    CHECK_GL_ERROR_DEBUG();
#endif
}
