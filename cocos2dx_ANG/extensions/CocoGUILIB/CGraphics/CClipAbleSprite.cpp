/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "CClipAbleSprite.h"

NS_CC_EXT_BEGIN
    
CClipAbleSprite::CClipAbleSprite():
m_bClipAble(false),
m_fScissorX(0.0f),
m_fScissorY(0.0f),
m_fScissorWidth(0.0f),
m_fScissorHeight(0.0f)
{
    
}

CClipAbleSprite::~CClipAbleSprite()
{
    
}

CClipAbleSprite* CClipAbleSprite::create()
{
    CClipAbleSprite *pobSprite = new CClipAbleSprite();
    if (pobSprite && pobSprite->init())
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

CClipAbleSprite* CClipAbleSprite::create(const char *file)
{
    CClipAbleSprite *pobSprite = new CClipAbleSprite();
    if (pobSprite && pobSprite->initWithFile(file))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

void CClipAbleSprite::setClipAble(bool able)
{
    this->m_bClipAble = able;
}

void CClipAbleSprite::setClipRect(float x, float y, float width, float height)
{
    this->m_fScissorX = x;
    this->m_fScissorY = y;
    this->m_fScissorWidth = width;
    this->m_fScissorHeight = height;
}

void CClipAbleSprite::visit()
{
    if (this->m_bClipAble)
    {
        glEnable(GL_SCISSOR_TEST);
        glScissor(m_fScissorX, m_fScissorY, m_fScissorWidth, m_fScissorHeight);
        CCSprite::visit();
        glDisable(GL_SCISSOR_TEST);
    }
    else
    {
        CCSprite::visit();
    }
}
    
NS_CC_EXT_END