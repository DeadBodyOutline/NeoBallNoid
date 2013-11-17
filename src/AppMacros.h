#ifndef __APPMACROS_H__
#define __APPMACROS_H__

#include "cocos2d.h"

#define DESIGN_RESOLUTION_320X480    0
#define DESIGN_RESOLUTION_480X800    1
#define DESIGN_RESOLUTION_1536X2048  2

#define TARGET_DESIGN_RESOLUTION_SIZE  DESIGN_RESOLUTION_480X800

typedef struct tagResource
{
    cocos2d::CCSize size;
    char directory[100];
}Resource;

static Resource smallResource  =  { cocos2d::CCSizeMake(320, 480),   "." };
static Resource mediumResource =  { cocos2d::CCSizeMake(480, 800),  "." };
static Resource largeResource  =  { cocos2d::CCSizeMake(1536, 2048), "." };

#if (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_320X480)
static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(320, 480);
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_480X800)
static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(480, 800);
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_1536X2048)
static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(1536, 2048);
#else
#error unknown target design resolution!
#endif

// The font size 24 is designed for small resolution, so we should change it to fit for current design resolution
#define TITLE_FONT_SIZE  (cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width / smallResource.size.width * 24)

#endif // __APPMACROS_H__
