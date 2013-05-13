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

#include "CocoSlider.h"
#include "DictionaryHelper.h"

namespace cs {
    CocoSlider::CocoSlider():
    m_fBarLength(0.0),
    m_nDirection(0),
    m_nBarPercent(0),
    m_pSlidBall(NULL),
    m_fBarNodeScaleValue(1.0),
    m_fTouchMoveStartLocation(0.0),
    m_fMinLength(0.0),
    m_pBarNode(NULL),
    m_pPercentListener(NULL),
    m_pfnPercentSelector(NULL),
    m_bBarScale9Enable(false)
    {
        
    }
    
    CocoSlider::~CocoSlider()
    {
        
    }
    
    CocoSlider* CocoSlider::create()
    {
//        return CocoSlider::create(NULL);
        CocoSlider* widget = new CocoSlider();
        if (widget && widget->init()) {
            return widget;
        }
        CC_SAFE_DELETE(widget);
        return NULL;
    }
    
    bool CocoSlider::init()
    {
        if (CocoWidget::init()) {
            this->m_pBarNode = new UISprite();
            this->m_pBarNode->init();
            this->addUIElement(this->m_pBarNode);
            this->m_pSlidBall = CocoButton::create();
            this->addChild(this->m_pSlidBall);
            return true;
        }
        return false;
    }
    
    void CocoSlider::setBarTexture(const char* fileName,bool useSpriteFrame)
    {
        if (this->m_bBarScale9Enable) {
            return;
        }
        ((UISprite*)(this->m_pBarNode))->loadTexture(fileName,useSpriteFrame);
        this->m_fBarLength = this->m_pBarNode->getContentSize().width;
        this->setSlidBallPercent(this->m_nBarPercent);
    }
    
    
    void CocoSlider::setBarTextureScale9(const char *fileName, float x, float y, float width, float height,bool useSpriteFrame)
    {
        if (!this->m_bBarScale9Enable) {
            return;
        }
        ((UIScale9Sprite*)(this->m_pBarNode))->loadTexture(fileName,x,y,width,height,useSpriteFrame);
        ((UIScale9Sprite*)(this->m_pBarNode))->setScaleSize(this->m_fBarLength, this->m_pBarNode->getContentSize().height);
        this->setSlidBallPercent(this->m_nBarPercent);
    }
    
    void CocoSlider::setBarTextureScale9Enable(bool able)
    {
        if (this->m_bBarScale9Enable == able) {
            return;
        }
        this->removeAllUIElementsAndCleanUp(true);
        this->m_pBarNode = NULL;
        this->m_bBarScale9Enable = able;
        if (this->m_bBarScale9Enable) {
            this->m_pBarNode = new UIScale9Sprite();
            this->m_pBarNode->init();
        }else{
            this->m_pBarNode = new UISprite();
            this->m_pBarNode->init();
        }
        this->addUIElement(this->m_pBarNode);
    }
    
    void CocoSlider::setSlidBallTextures(const char* normal,const char* pressed,const char* disabled,bool useSpriteFrame)
    {
        this->m_pSlidBall->setTextures(normal, pressed, disabled,useSpriteFrame);
    }
    
    void CocoSlider::setSlidBallNormalTexture(const char* normal,bool useSpriteFrame)
    {
        this->m_pSlidBall->setNormalTexture(normal,useSpriteFrame);
    }
    
    void CocoSlider::setSlidBallPressedTexture(const char* pressed,bool useSpriteFrame)
    {
        this->m_pSlidBall->setPressedTexture(pressed,useSpriteFrame);
    }
    
    void CocoSlider::setSlidBallDisabledTexture(const char* disabled,bool useSpriteFrame)
    {
        this->m_pSlidBall->setDisabledTexture(disabled,useSpriteFrame);
    }
    
    void CocoSlider::setBarLength(float length)
    {
        if (!this->m_bBarScale9Enable) {
            return;
        }
        this->m_fBarLength = length;
        ((UIScale9Sprite*)(this->m_pBarNode))->setScaleSize(length, this->m_pBarNode->getContentSize().height);
        this->setSlidBallPercent(this->m_nBarPercent);
    }
    
    void CocoSlider::setSlidBallPercent(int percent)
    {
        this->m_nBarPercent = percent;
        float dis = this->m_fBarLength*(percent/100.0);
        this->m_pSlidBall->setPosition(ccp(-this->m_fBarLength/2.0+dis,0));
    }
    
    int CocoSlider::getClickPercent(float location)
    {
        this->getLocationInWindow();
        float leftEndPos = this->m_locationInWindow.x - this->m_fBarLength/2.0;
        float per = (location - leftEndPos)/this->m_fBarLength;
        per *= 100;
        return per;
    }
    
    void CocoSlider::checkSlidBoundary()
    {
        if (this->m_pSlidBall->getPosition().x > this->m_fBarLength/2.0){
            this->m_pSlidBall->setPosition(ccp(this->m_fBarLength/2.0,0));
        }else if(this->m_pSlidBall->getPosition().x < -this->m_fBarLength/2.0){
            this->m_pSlidBall->setPosition(ccp(-this->m_fBarLength/2.0,0));
        }
    }
    
    bool CocoSlider::onTouchPressed(cocos2d::CCPoint &touchPoint)
    {
        CocoWidget::onTouchPressed(touchPoint);
        cocos2d::CCPoint nsp = this->m_pCContainerNode->convertToNodeSpace(touchPoint);
        this->m_pSlidBall->setPosition(ccp(nsp.x,0));
        this->m_pSlidBall->setPressState(1);
        this->m_nBarPercent = this->getPercentWithBallPos(this->m_pSlidBall->getPosition().x,0);
        percentChangedEvent();
        return true;
    }
    
    bool CocoSlider::onTouchMoved(cocos2d::CCPoint &touchPoint)
    {
        cocos2d::CCPoint nsp = this->m_pCContainerNode->convertToNodeSpace(touchPoint);
        this->m_pSlidBall->setPosition(ccp(nsp.x,0));
        this->checkSlidBoundary();
        this->m_nBarPercent = this->getPercentWithBallPos(this->m_pSlidBall->getPosition().x,0);
        percentChangedEvent();
        return true;
    }
    
    bool CocoSlider::onTouchReleased(cocos2d::CCPoint &touchPoint)
    {
        CocoWidget::onTouchReleased(touchPoint);
        this->m_pSlidBall->setPressState(0);
        return true;
    }
    
    bool CocoSlider::onTouchCanceled(cocos2d::CCPoint &touchPoint)
    {
        CocoWidget::onTouchReleased(touchPoint);
        this->m_pSlidBall->setPressState(0);
        return true;
    }
    
    float CocoSlider::getPercentWithBallPos(float px,float py)
    {
        return (((px-(-this->m_fBarLength/2.0))/this->m_fBarLength)*100);
    }
    
    bool CocoSlider::pointAtSelfBody(cocos2d::CCPoint &pt)
    {
        if (!this->getAbsoluteVisible()) {
            return false;
        }
        bool hitBar = this->getValidNode()->hitTest(pt);
        if (hitBar) {
            return true;
        }
        bool hitBall = this->m_pSlidBall->getValidNode()->hitTest(pt);
        if (hitBall) {
            return true;
        }
        return false;
    }
    
    CRenderNode* CocoSlider::getValidNode()
    {
        return this->m_pBarNode->getCRenderNode();
    }
    
    void CocoSlider::addPercentChangedEvent(cocos2d::CCObject *target, SEL_PushEvent selector)
    {
        this->m_pPercentListener = target;
        this->m_pfnPercentSelector = selector;
    }
    
    void CocoSlider::percentChangedEvent()
    {
        if (m_pPercentListener && m_pfnPercentSelector) {
            (m_pPercentListener->*m_pfnPercentSelector)(this);
        }
    }
    
    int CocoSlider::getPercent()
    {
        return this->m_nBarPercent;
    }
    
    void CocoSlider::setColor(int r, int g, int b)
    {
        this->m_pBarNode->setColor(r, g, b);
        this->m_pSlidBall->setColor(r, g, b);
    }
    
    void CocoSlider::setOpacity(int opcity)
    {
        this->m_pBarNode->setOpacity(opcity);
        this->m_pSlidBall->setOpacity(opcity);
    }
}