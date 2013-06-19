/*
 * Copyright (c) 2012 Chukong Technologies, Inc.
 *
 * http://www.sweetpome.com
 * http://tools.cocoachina.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to permit
 * persons to whom the Software is furnished to do so, subject to the
 * following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

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