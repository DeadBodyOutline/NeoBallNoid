#include "GameScene.h"
#include "MainScene.h"
#include "AppMacros.h"

CCScene *MainScene::scene()
{
    CCScene *scene = CCScene::create();

    MainScene *layer = MainScene::create();
    scene->addChild(layer);

    return scene;
}

bool MainScene::init()
{
    if (!CCLayer::init())
        return false;

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();


    // XXX remove when not necessary
    CCLabelTTF *labelStart = CCLabelTTF::create("START!", "arial.ttf", 48);
    CCMenuItemLabel *start = CCMenuItemLabel::create(labelStart, this,
                                        menu_selector(MainScene::menuStartCallback));

    start->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));

    CCMenu *pMenu = CCMenu::create(start, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    return true;
}

void MainScene::menuCloseCallback(CCObject *pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void MainScene::menuStartCallback(CCObject* pSender)
{
    CCScene *gameScene = GameScene::scene();

    CCDirector::sharedDirector()->pushScene(
            CCTransitionSlideInR::create(0.5, gameScene));
}
