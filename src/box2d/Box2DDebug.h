#ifndef __BOX2DDEBUG_H__
#define __BOX2DDEBUG_H__

#include "Box2D/Box2D.h"
#include "cocos2d.h"

USING_NS_CC;

// Debug Render
struct b2AABB;

class GLRender : public b2Draw
{
public:
    GLRender();
    GLRender(float32 ratio);

    virtual void DrawPolygon(const b2Vec2 *vertices, int vertexCount,
            const b2Color &color);
    virtual void DrawSolidPolygon(const b2Vec2 *vertices, int vertexCount,
            const b2Color &color);
    virtual void DrawCircle(const b2Vec2 &center, float32 radius,
            const b2Color &color);
    virtual void DrawSolidCircle(const b2Vec2 &center, float32 radius,
            const b2Vec2 &axis, const b2Color &color);
    virtual void DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2,
            const b2Color &color);
    virtual void DrawTransform(const b2Transform &xf);
    virtual void DrawPoint(const b2Vec2 &p, float32 size, const b2Color &color);
    virtual void DrawString(int x, int y, const char* string, ...);
    virtual void DrawAABB(b2AABB *aabb, const b2Color &color);

private:
    void initShader();

    CCGLProgram *m_shaderProgram;
    GLint m_colorLocation;
    float32 m_ratio;
};
// Debug Render

// Debug Layer
class Box2DDebugLayer : public CCLayer
{
public:
    Box2DDebugLayer(b2World *world, float ratio);
    static Box2DDebugLayer *create(b2World *world, float ratio);

    virtual bool init();
    virtual void draw();

private:
    b2World *m_world;
    GLRender *m_render;
    const float m_ratio;
};
// Debug Layer

#endif // __BOX2DDEBUG_H__
