#ifndef  __APP_DELEGATE_H__
#define  __APP_DELEGATE_H__

#include "cocos2d.h"

USING_NS_CC;

class  AppDelegate : private CCApplication
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    virtual bool applicationDidFinishLaunching();
    virtual void applicationDidEnterBackground();
    virtual void applicationWillEnterForeground();
};

#endif // __APPDELEGATE_H__
