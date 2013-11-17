#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"

USING_NS_CC;

class GameScene : public CCLayer
{
public:
    GameScene();
    ~GameScene();

    virtual bool init();
    static CCScene *scene();

    void update(float dt);

    CREATE_FUNC(GameScene);

private:
    void initPhysics();

    b2World *m_world;
};

#endif // __GAMESCENE_H__
