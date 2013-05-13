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

#include "UIScale9Sprite.h"

namespace cs {
    
    UIScale9Sprite::UIScale9Sprite()
    {
        
    }
    
    UIScale9Sprite::~UIScale9Sprite()
    {
        
    }
    
    void UIScale9Sprite::init()
    {
        this->m_pCRenderNode = new CRenderNode();
        this->m_pCRenderNode->initNode(10);
    }
    
    void UIScale9Sprite::loadTexture(const char* fileName,float x,float y,float w,float h,bool useSpriteFrame)
    {
        if (x < 0 || y < 0 || w < 0 || h < 0){
            x = 0;
            y = 0;
            w = 0;
            h = 0;
        }
        this->m_pCRenderNode->setScale9FileAndCapInsets(fileName,x,y,w,h,useSpriteFrame);
    }
    
    void UIScale9Sprite::setScaleSize(float width,float height)
    {
        this->m_pCRenderNode->setScale9Size(width,height);
    }
}