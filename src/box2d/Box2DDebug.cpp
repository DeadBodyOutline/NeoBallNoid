#include "Box2DDebug.h"
#include "cocos2d.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

// Debug Render
GLRender::GLRender()
    : m_ratio(1.0f)
{
    this->initShader();
}

GLRender::GLRender(float32 ratio)
    : m_ratio(ratio)
{
    this->initShader();
}

void GLRender::initShader()
{
    m_shaderProgram = CCShaderCache::sharedShaderCache()->programForKey(
            kCCShader_Position_uColor);

    m_colorLocation = glGetUniformLocation(m_shaderProgram->getProgram(), "u_color");
}

void GLRender::DrawPolygon(const b2Vec2 *old_vertices, int vertexCount,
        const b2Color &color)
{
    m_shaderProgram->use();
    m_shaderProgram->setUniformsForBuiltins();

    b2Vec2 *vertices = new b2Vec2[vertexCount];
    for (int i = 0; i < vertexCount; i++) {
        vertices[i] = old_vertices[i];
        vertices[i] *= m_ratio;
    }

    m_shaderProgram->setUniformLocationWith4f(m_colorLocation, color.r, color.g,
            color.b, 1);

    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0,
            vertices);
    glDrawArrays(GL_LINE_LOOP, 0, vertexCount);

    CC_INCREMENT_GL_DRAWS(1);
    CHECK_GL_ERROR_DEBUG();

    delete[] vertices;
}

void GLRender::DrawSolidPolygon(const b2Vec2 *old_vertices, int vertexCount,
        const b2Color &color)
{
    m_shaderProgram->use();
    m_shaderProgram->setUniformsForBuiltins();

    b2Vec2 *vertices = new b2Vec2[vertexCount];
    for (int i = 0; i < vertexCount; i++) {
        vertices[i] = old_vertices[i];
        vertices[i] *= m_ratio;
    }

    m_shaderProgram->setUniformLocationWith4f(m_colorLocation, color.r * 0.5f,
            color.g * 0.5f, color.b * 0.5f, 0.5f);

    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0,
            vertices);

    glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);

    m_shaderProgram->setUniformLocationWith4f(m_colorLocation, color.r, color.g,
            color.b, 1);
    glDrawArrays(GL_LINE_LOOP, 0, vertexCount);

    CC_INCREMENT_GL_DRAWS(2);
    CHECK_GL_ERROR_DEBUG();

    delete[] vertices;
}

void GLRender::DrawCircle(const b2Vec2 &center, float32 radius,
        const b2Color &color)
{
    m_shaderProgram->use();
    m_shaderProgram->setUniformsForBuiltins();

    const float32 k_segments = 16.0f;
    int vertexCount = 16;
    const float32 k_increment = 2.0f * b2_pi / k_segments;
    float32 theta = 0.0f;

    GLfloat *glVertices = new GLfloat[vertexCount * 2];
    for (int i = 0; i < k_segments; ++i) {
        b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
        glVertices[i * 2] = v.x * m_ratio;
        glVertices[i * 2 + 1] = v.y * m_ratio;
        theta += k_increment;
    }

    m_shaderProgram->setUniformLocationWith4f(m_colorLocation, color.r, color.g,
            color.b, 1);
    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0,
            glVertices);

    glDrawArrays(GL_LINE_LOOP, 0, vertexCount);

    CC_INCREMENT_GL_DRAWS(1);

    CHECK_GL_ERROR_DEBUG();

    delete[] glVertices;
}

void GLRender::DrawSolidCircle(const b2Vec2 &center, float32 radius,
        const b2Vec2 &axis, const b2Color &color)
{
    m_shaderProgram->use();
    m_shaderProgram->setUniformsForBuiltins();

    const float32 k_segments = 16.0f;
    int vertexCount = 16;
    const float32 k_increment = 2.0f * b2_pi / k_segments;
    float32 theta = 0.0f;

    GLfloat *glVertices = new GLfloat[vertexCount * 2];
    for (int i = 0; i < k_segments; ++i) {
        b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
        glVertices[i * 2] = v.x * m_ratio;
        glVertices[i * 2 + 1] = v.y * m_ratio;
        theta += k_increment;
    }

    m_shaderProgram->setUniformLocationWith4f(m_colorLocation, color.r * 0.5f,
            color.g * 0.5f, color.b * 0.5f, 0.5f);
    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0,
            glVertices);
    glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);

    m_shaderProgram->setUniformLocationWith4f(m_colorLocation, color.r, color.g,
            color.b, 1);
    glDrawArrays(GL_LINE_LOOP, 0, vertexCount);

    DrawSegment(center, center + radius * axis, color);

    CC_INCREMENT_GL_DRAWS(2);
    CHECK_GL_ERROR_DEBUG();

    delete[] glVertices;
}

void GLRender::DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2,
        const b2Color &color)
{
    m_shaderProgram->use();
    m_shaderProgram->setUniformsForBuiltins();

    m_shaderProgram->setUniformLocationWith4f(m_colorLocation, color.r, color.g,
            color.b, 1);

    GLfloat glVertices[] = {
        p1.x * m_ratio, p1.y * m_ratio,
        p2.x * m_ratio, p2.y * m_ratio
    };
    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0,
            glVertices);

    glDrawArrays(GL_LINES, 0, 2);

    CC_INCREMENT_GL_DRAWS(1);
    CHECK_GL_ERROR_DEBUG();
}

void GLRender::DrawTransform(const b2Transform &xf)
{
    b2Vec2 p1 = xf.p, p2;
    const float32 k_axisScale = 0.4f;

    p2 = p1 + k_axisScale * xf.q.GetXAxis();
    DrawSegment(p1, p2, b2Color(1, 0, 0));

    p2 = p1 + k_axisScale * xf.q.GetYAxis();
    DrawSegment(p1, p2, b2Color(0, 1, 0));
}

void GLRender::DrawPoint(const b2Vec2 &p, float32 size, const b2Color &color)
{
    m_shaderProgram->use();
    m_shaderProgram->setUniformsForBuiltins();

    m_shaderProgram->setUniformLocationWith4f(m_colorLocation, color.r, color.g,
            color.b, 1);

    GLfloat glVertices[] = {
        p.x * m_ratio, p.y * m_ratio
    };

    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0,
            glVertices);

    glDrawArrays(GL_POINTS, 0, 1);

    CC_INCREMENT_GL_DRAWS(1);
    CHECK_GL_ERROR_DEBUG();
}

void GLRender::DrawString(int x, int y, const char *string, ...)
{
    // TODO
}

void GLRender::DrawAABB(b2AABB *aabb, const b2Color &color)
{
    m_shaderProgram->use();
    m_shaderProgram->setUniformsForBuiltins();

    m_shaderProgram->setUniformLocationWith4f(m_colorLocation, color.r, color.g,
            color.b, 1);

    GLfloat glVertices[] = {
        aabb->lowerBound.x * m_ratio, aabb->lowerBound.y * m_ratio,
        aabb->upperBound.x * m_ratio, aabb->lowerBound.y * m_ratio,
        aabb->upperBound.x * m_ratio, aabb->upperBound.y * m_ratio,
        aabb->lowerBound.x * m_ratio, aabb->upperBound.y * m_ratio
    };

    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0,
            glVertices);
    glDrawArrays(GL_LINE_LOOP, 0, 8);

    CC_INCREMENT_GL_DRAWS(1);
    CHECK_GL_ERROR_DEBUG();
}
// Debug Render

// Debug Layer
Box2DDebugLayer *Box2DDebugLayer::create(b2World *world, float ratio)
{
    Box2DDebugLayer *layer = new Box2DDebugLayer(world, ratio);

    if (layer && layer->init()) {
        layer->autorelease();
    } else {
        delete layer;
        layer = NULL;
    }

    return layer;
}

Box2DDebugLayer::Box2DDebugLayer(b2World *world, float ratio)
    : m_world(world)
    , m_ratio(ratio)
{
}

bool Box2DDebugLayer::init()
{
    if (!CCLayer::init())
        return false;

    m_render = new GLRender(m_ratio);

    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    flags += b2Draw::e_jointBit;
    flags += b2Draw::e_aabbBit;
    flags += b2Draw::e_pairBit;
    flags += b2Draw::e_centerOfMassBit;
    m_render->SetFlags(flags);

    m_world->SetDebugDraw(m_render);

    return true;
}

void Box2DDebugLayer::draw()
{
    if (m_world && m_render) {
        ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position);
        kmGLPushMatrix();

        m_world->DrawDebugData();

        kmGLPopMatrix();
        CHECK_GL_ERROR_DEBUG();
    }
}
// Debug Layer
