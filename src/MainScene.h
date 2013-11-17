#ifndef __MAINSCREEN_H__
#define __MAINSCREEN_H__

#include "cocos2d.h"

USING_NS_CC;

class MainScene : public CCLayer
{
public:
    virtual bool init();

    static CCScene *scene();

    void menuCloseCallback(CCObject *pSender);
    void menuStartCallback(CCObject *pSender);

    CREATE_FUNC(MainScene);
};

#endif // __MAINSCREEN_H__
