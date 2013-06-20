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

#include "CocoLoadingBar.h"
#include "DictionaryHelper.h"

NS_CC_EXT_BEGIN

CocoLoadingBar::CocoLoadingBar():
m_nBarType(LoadingBarTypeLeft),
m_nPercent(100),
m_fTotalLength(0),
m_fBarHeight(0),
m_pRenderBar(NULL),
m_bUseSpriteFrame(false)
{
}

CocoLoadingBar::~CocoLoadingBar()
{
    
}

CocoLoadingBar* CocoLoadingBar::create()
{
    CocoLoadingBar* widget = new CocoLoadingBar();
    if (widget && widget->init())
    {
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

void CocoLoadingBar::initNodes()
{
    CocoWidget::initNodes();
    this->m_pRenderBar = cocos2d::CCSprite::create();
    this->m_pCCRenderNode->addChild(m_pRenderBar);
    this->m_pRenderBar->setAnchorPoint(ccp(0.0,0.5));
}

void CocoLoadingBar::setDirection(LoadingBarType dir)
{
    if (this->m_nBarType == dir)
    {
        return;
    }
    this->m_nBarType = dir;

    switch (this->m_nBarType)
    {
        case LoadingBarTypeLeft:
            this->m_pRenderBar->setAnchorPoint(ccp(0.0,0.5));
            this->m_pRenderBar->setPosition(ccp(-this->m_fTotalLength*0.5f,0.0f));
            this->m_pRenderBar->setFlipX(false);
            break;
        case LoadingBarTypeRight:
            
            this->m_pRenderBar->setAnchorPoint(ccp(1.0,0.5));
            this->m_pRenderBar->setPosition(ccp(this->m_fTotalLength*0.5f,0.0f));
            this->m_pRenderBar->setFlipX(true);

            break;
    }
}

int CocoLoadingBar::getDirection()
{
    return this->m_nBarType;
}

void CocoLoadingBar::setTexture(const char* texture,bool useSpriteFrame)
{
    this->m_bUseSpriteFrame = useSpriteFrame;
    if (useSpriteFrame)
    {
        this->m_pRenderBar->initWithSpriteFrameName(texture);
    }
    else
    {
        this->m_pRenderBar->initWithFile(texture);
    }
    this->m_fTotalLength = this->m_pRenderBar->getContentSize().width;
    this->m_fBarHeight = this->m_pRenderBar->getContentSize().height;

    switch (this->m_nBarType)
    {
    case LoadingBarTypeLeft:
        this->m_pRenderBar->setAnchorPoint(ccp(0.0,0.5));
        this->m_pRenderBar->setPosition(ccp(-this->m_fTotalLength*0.5f,0.0f));
        this->m_pRenderBar->setFlipX(false);
        break;
    case LoadingBarTypeRight:
        this->m_pRenderBar->setAnchorPoint(ccp(1.0,0.5));
        this->m_pRenderBar->setPosition(ccp(this->m_fTotalLength*0.5f,0.0f));
        this->m_pRenderBar->setFlipX(true);
        break;
    }
}

void CocoLoadingBar::setPercent(int percent)
{
    if ( percent < 0 || percent > 100)
    {
        return;
    }
    if (this->m_fTotalLength <= 0)
    {
        return;
    }
    this->m_nPercent = percent;
    float res = this->m_nPercent/100.0;
    
    int x = 0, y = 0;                        
    if (this->m_bUseSpriteFrame)
    {
        cocos2d::CCSprite* barNode = DYNAMIC_CAST_CCSPRITE;
        if (barNode)
        {
            cocos2d::CCPoint to = barNode->getTextureRect().origin;
            x = to.x;
            y = to.y;
        }
    }
    
    this->m_pRenderBar->setTextureRect(cocos2d::CCRect(x, y, this->m_fTotalLength * res, this->m_fBarHeight));
}

int CocoLoadingBar::getPercent()
{
    return this->m_nPercent;
}

cocos2d::CCNode* CocoLoadingBar::getValidNode()
{
    return this->m_pRenderBar;
}

float CocoLoadingBar::getTotalWidth()
{
    return this->m_fTotalLength;
}

float CocoLoadingBar::getTotalHeight()
{
    return this->m_fBarHeight;
}

NS_CC_EXT_END