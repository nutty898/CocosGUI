//
//  GUISprite.cpp
//  Test
//
//  Created by pipu on 13-6-5.
//
//


#include "GUISprite.h"

namespace cs
{
    GUISprite::GUISprite()
    : cocos2d::CCSprite()
    {        
    }
    
    GUISprite::~GUISprite()
    {
    }
    
    GUISprite* GUISprite::createWithSpriteFrameName(const char *pszSpriteFrameName)
    {
        cocos2d::CCSpriteFrame *pFrame = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);
        
#if COCOS2D_DEBUG > 0
        char msg[256] = {0};
        sprintf(msg, "Invalid spriteFrameName: %s", pszSpriteFrameName);
        if (pFrame == NULL)
        {
            return NULL;
        }
        CCAssert(pFrame != NULL, msg);
#endif
        
        return  dynamic_cast<GUISprite*>(cocos2d::CCSprite::createWithSpriteFrame(pFrame));
    }
}

