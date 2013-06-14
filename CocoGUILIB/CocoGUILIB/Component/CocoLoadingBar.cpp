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

#include "CocoLoadingBar.h"
#include "DictionaryHelper.h"

namespace cs {
    
    CocoLoadingBar::CocoLoadingBar():
    m_nBarType(0),
    m_nPercent(100),
    m_fTotalLength(0),
    m_fBarHeight(0),
    m_pRenderBar(NULL)
    {
    }
    
    CocoLoadingBar::~CocoLoadingBar()
    {
        
    }
    
    CocoLoadingBar* CocoLoadingBar::create()
    {
        CocoLoadingBar* widget = new CocoLoadingBar();
        if (widget && widget->init()) {
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
    
    void CocoLoadingBar::setDirection(int dir)
    {
        if (this->m_nBarType == dir) {
            return;
        }
        this->m_nBarType = dir;

        switch (this->m_nBarType){
            case 0:
                this->m_pRenderBar->setAnchorPoint(ccp(0.0,0.5));
				this->m_pRenderBar->setPosition(ccp(-this->m_fTotalLength*0.5f,0.0f));
				this->m_pRenderBar->setFlipX(false);
                break;
            case 1:
				
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
        if (useSpriteFrame) {
            this->m_pRenderBar->initWithSpriteFrameName(texture);
        }else{
            this->m_pRenderBar->initWithFile(texture);
        }
        this->m_fTotalLength = this->m_pRenderBar->getContentSize().width;
        this->m_fBarHeight = this->m_pRenderBar->getContentSize().height;

		switch (this->m_nBarType){
		case 0:
			this->m_pRenderBar->setAnchorPoint(ccp(0.0,0.5));
			this->m_pRenderBar->setPosition(ccp(-this->m_fTotalLength*0.5f,0.0f));
			this->m_pRenderBar->setFlipX(false);
			break;
		case 1:
			this->m_pRenderBar->setAnchorPoint(ccp(1.0,0.5));
			this->m_pRenderBar->setPosition(ccp(this->m_fTotalLength*0.5f,0.0f));
			this->m_pRenderBar->setFlipX(true);
			break;
		}
    }
    
    void CocoLoadingBar::setPercent(int percent)
    {
        if ( percent < 0 || percent > 100){
            return;
        }
        if (this->m_fTotalLength <= 0){
            return;
        }
        this->m_nPercent = percent;
        float res = this->m_nPercent/100.0;
        
        int x = 0, y = 0;                        
//        if (this->m_pRenderBar->getCRenderNode()->getUseSpriteFrame())
//        {
//            using namespace cocos2d;
//            CCSprite* barNode = dynamic_cast<CCSprite*>(m_pRenderBar->getCRenderNode()->getRenderNode());
//            if (barNode)
//            {
//                CCPoint to = barNode->getTextureRect().origin;
//                x = to.x;
//                y = to.y;
//            }
//        }
        
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
}