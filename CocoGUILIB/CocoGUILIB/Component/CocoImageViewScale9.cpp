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

#include "CocoImageViewScale9.h"
#include "GUIScale9Sprite.h"

namespace cs
{
    CocoImageViewScale9::CocoImageViewScale9()    
    {
        
    }
    
    CocoImageViewScale9::~CocoImageViewScale9()
    {
        
    }
    
    CocoImageViewScale9* CocoImageViewScale9::create()
    {
        CocoImageViewScale9* widget = new CocoImageViewScale9();
        if (widget && widget->init())
        {
            return widget;
        }
        CC_SAFE_DELETE(widget);
        return NULL;
    }
    
    void CocoImageViewScale9::initNodes()
    {
        this->m_pCCRenderNode = GUIScale9Sprite::create();
    }
    
    void CocoImageViewScale9::setTexture(const char *fileName, bool useSpriteFrame)
    {
        if (useSpriteFrame) {
            DYNAMIC_CAST_SCALE9SPRITE->initWithSpriteFrameName(fileName);
        }else{
            DYNAMIC_CAST_SCALE9SPRITE->initWithFile(fileName);
        }
        
    }
    
    void CocoImageViewScale9::setTextureRect(float x, float y, float width, float height)
    {
        
    }
    
    void CocoImageViewScale9::setScale9Enable(bool able)
    {
        
    }
    
    void CocoImageViewScale9::setScale9Size(const cocos2d::CCSize& size)
    {
        DYNAMIC_CAST_SCALE9SPRITE->setContentSize(size);
    }
    
    void CocoImageViewScale9::setTexturesScale9(const char *fileName, cocos2d::CCRect capInsets, bool useSpriteFrame)
    {
        if (useSpriteFrame) {
            DYNAMIC_CAST_SCALE9SPRITE->initWithSpriteFrameName(fileName, capInsets);
        }else{
            DYNAMIC_CAST_SCALE9SPRITE->initWithFile(fileName, capInsets);
        }
    }
    
    void CocoImageViewScale9::setDisplayFrame(cocos2d::CCSpriteFrame *pNewFrame)
    {
        
    }
    
    void CocoImageViewScale9::setSpriteFrame(cocos2d::CCSpriteFrame *pNewFrame)
    {
        DYNAMIC_CAST_SCALE9SPRITE->setSpriteFrame(pNewFrame);
    }
    
    void CocoImageViewScale9::setPreferredSize(const cocos2d::CCSize &pSize)
    {
        DYNAMIC_CAST_SCALE9SPRITE->setPreferredSize(pSize);
    }
    
    void CocoImageViewScale9::setInsetLeft(float insetLeft)
    {
        DYNAMIC_CAST_SCALE9SPRITE->setInsetLeft(insetLeft);
    }
    
    void CocoImageViewScale9::setInsetTop(float insetTop)
    {
        DYNAMIC_CAST_SCALE9SPRITE->setInsetTop(insetTop);
    }
    
    void CocoImageViewScale9::setInsetRight(float insetRight)
    {
        DYNAMIC_CAST_SCALE9SPRITE->setInsetRight(insetRight);
    }
    
    void CocoImageViewScale9::setInsetBottom(float insetBottom)
    {
        DYNAMIC_CAST_SCALE9SPRITE->setInsetBottom(insetBottom);
    }
}
