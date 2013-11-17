#include "AppDelegate.h"

#include <vector>
#include <string>

#include "MainScene.h"
#include "AppMacros.h"

using namespace std;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    CCDirector *pDirector = CCDirector::sharedDirector();
    CCEGLView *pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);

    pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionNoBorder);

    CCSize frameSize = pEGLView->getFrameSize();

    vector<string> searchPath;

    if (frameSize.height > mediumResource.size.height) {
        searchPath.push_back(largeResource.directory);
        pDirector->setContentScaleFactor(MIN(largeResource.size.height/designResolutionSize.height, largeResource.size.width/designResolutionSize.width));
    } else if (frameSize.height > smallResource.size.height) {
        searchPath.push_back(mediumResource.directory);
        pDirector->setContentScaleFactor(MIN(mediumResource.size.height/designResolutionSize.height, mediumResource.size.width/designResolutionSize.width));
    } else {
        searchPath.push_back(smallResource.directory);
        pDirector->setContentScaleFactor(MIN(smallResource.size.height/designResolutionSize.height, smallResource.size.width/designResolutionSize.width));
    }

    CCFileUtils::sharedFileUtils()->setSearchPaths(searchPath);

#ifdef DEBUGDRAW
    pDirector->setDisplayStats(true);
#endif

    pDirector->setAnimationInterval(1.0 / 60);

    CCScene *pScene = MainScene::scene();
    pDirector->runWithScene(pScene);

    return true;
}

void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
}
