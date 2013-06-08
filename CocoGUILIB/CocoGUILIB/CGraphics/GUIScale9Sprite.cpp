//
//  GUIScale9Sprite.cpp
//  Test
//
//  Created by pipu on 13-5-29.
//
//

#include "GUIScale9Sprite.h"

namespace cs
{
    GUIScale9Sprite::GUIScale9Sprite()
    : cocos2d::extension::CCScale9Sprite()
    {
        
    }
    
    GUIScale9Sprite::~GUIScale9Sprite()
    {
        
    }
    
    GUIScale9Sprite* GUIScale9Sprite::create()
    {
        GUIScale9Sprite* pRet = new GUIScale9Sprite();
        if (pRet && pRet->init())
        {
            pRet->autorelease();
            return pRet;
        }
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
    
    bool GUIScale9Sprite::init()
    {
        if (CCScale9Sprite::init())
        {
            setCascadeOpacityEnabled(true);
            setCascadeColorEnabled(true);
            return true;
        }
        return false;
    }
    
    void GUIScale9Sprite::setOpacityModifyRGB(bool bValue)
    {
        if (!_scale9Image)
        {
            return;
        }
        CCScale9Sprite::setOpacityModifyRGB(bValue);
    }
    
    void GUIScale9Sprite::setOpacity(GLubyte opacity)
    {
        if (!_scale9Image)
        {
            return;
        }
        CCScale9Sprite::setOpacity(opacity);
    }
    
    void GUIScale9Sprite::setColor(const cocos2d::ccColor3B &color)
    {
        if (!_scale9Image)
        {
            return;
        }
        CCScale9Sprite::setColor(color);
    }
    
    void GUIScale9Sprite::updateDisplayedOpacity(GLubyte parentOpacity)
    {
        CCNodeRGBA::updateDisplayedOpacity(parentOpacity);
        setOpacity(parentOpacity);
    }
    
    void GUIScale9Sprite::updateDisplayedColor(const cocos2d::ccColor3B &color)
    {
        CCNodeRGBA::updateDisplayedColor(color);
        setColor(color);
    }
}
/**/