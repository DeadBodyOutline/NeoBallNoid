#include "Background.h"

BackgroundSprite::BackgroundSprite()
    : Sprite(NULL)
{
}

bool BackgroundSprite::init()
{
    // sprites/animations
    setImage("backgrounds/background.png");
    addChild(m_sprite);
    //

    return true;
}
