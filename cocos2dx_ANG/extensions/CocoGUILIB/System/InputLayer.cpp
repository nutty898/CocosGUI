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

#include "InputLayer.h"

NS_CC_EXT_BEGIN
    
InputLayer::InputLayer():m_pUISystem(NULL)
{
    
}

InputLayer::~InputLayer()
{
}

InputLayer* InputLayer::createWithUISystem(UISystem *system)
{
    InputLayer *pRet = new InputLayer();
    pRet->scheduleUpdate();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        pRet->m_pUISystem = system;
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool InputLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return this->m_pUISystem->onTouchPressed(pTouch);   
}

void InputLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    this->m_pUISystem->onTouchMoved(pTouch);
}

void InputLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    this->m_pUISystem->onTouchReleased(pTouch);
}

void InputLayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    this->m_pUISystem->onTouchCanceled(pTouch);
}

void InputLayer::update(float dt)
{
    if (m_pUISystem)
    {
        m_pUISystem->update(dt);
    }
}

NS_CC_EXT_END