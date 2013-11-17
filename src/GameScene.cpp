#include "GameScene.h"
#include "AppMacros.h"

#include "box2d/Utils.h"
#include "box2d/Box2DDebug.h"
#include "box2d/ContactListener.h"

USING_NS_CC;

GameScene::GameScene()
    : m_world(NULL)
{
}

GameScene::~GameScene()
{
    CC_SAFE_DELETE(m_world);
}

CCScene *GameScene::scene()
{
    CCScene *scene = CCScene::create();

    GameScene *layer = GameScene::create();
    scene->addChild(layer);

    return scene;
}

bool GameScene::init()
{
    if (!CCLayer::init())
        return false;

    initPhysics();
    scheduleUpdate();

    // TODO sprites
    //CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    return true;
}

void GameScene::initPhysics()
{
    b2Vec2 gravity;
    gravity.Set(0.0f, -10.0f);
    m_world = new b2World(gravity);

    m_world->SetAllowSleeping(true);
    m_world->SetContinuousPhysics(true);
    m_world->SetContactListener(new ContactListener());

    // debug
#ifdef DEBUGDRAW
    Box2DDebugLayer *debugLayer = Box2DDebugLayer::create(m_world, PTM_RATIO);
    addChild(debugLayer, 9999999);
#endif
    //
}

void GameScene::update(float dt)
{
    int velocityIterations = 8;
    int positionIterations = 1;

    m_world->Step(dt, velocityIterations, positionIterations);

    for (b2Body* b = m_world->GetBodyList(); b; b = b->GetNext()) {
        if (b->GetUserData() != NULL) {
            CCNode *node = (CCNode *)b->GetUserData();

            node->setPosition(CCPointMake(b->GetPosition().x * PTM_RATIO,
                        b->GetPosition().y * PTM_RATIO));

            node->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
        }
    }
}