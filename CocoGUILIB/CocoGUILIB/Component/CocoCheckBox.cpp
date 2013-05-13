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

#include "CocoCheckBox.h"
#include "DictionaryHelper.h"

namespace cs {
    CocoCheckBox::CocoCheckBox():
    m_pBackGroundBox(NULL),
    m_pBackGroundSelectedBox(NULL),
    m_pFrontCross(NULL),
    m_bIsSelected(true),
    m_pSelectListener(NULL),
    m_pfnSelectSelector(NULL),
    m_pUnSelectListener(NULL),
    m_pfnUnSelectSelector(NULL),
    m_pBackGroundBoxDisabled(NULL),
    m_pFrontCrossDisabled(NULL)
    {

    }
    
    CocoCheckBox::~CocoCheckBox()
    {
        
    }

    CocoCheckBox* CocoCheckBox::create()
    {
//        return CocoCheckBox::create(NULL);
        CocoCheckBox* widget = new CocoCheckBox();
        if (widget && widget->init()) {
            return widget;
        }
        CC_SAFE_DELETE(widget);
        return NULL;
    }
    
    bool CocoCheckBox::init()
    {
        if (CocoWidget::init()) {
            this->m_pBackGroundBox = new UISprite();
            this->m_pBackGroundBox->init();
            this->m_pBackGroundSelectedBox = new UISprite();
            this->m_pBackGroundSelectedBox->init();
            this->m_pFrontCross = new UISprite();
            this->m_pFrontCross->init();
            this->m_pBackGroundBoxDisabled = new UISprite();
            this->m_pBackGroundBoxDisabled->init();
            this->m_pFrontCrossDisabled = new UISprite();
            this->m_pFrontCrossDisabled->init();
            this->addUIElement(m_pBackGroundBox);
            this->addUIElement(m_pBackGroundSelectedBox);
            this->addUIElement(m_pFrontCross);
            this->addUIElement(m_pBackGroundBoxDisabled);
            this->addUIElement(m_pFrontCrossDisabled);
            this->setPressState(0);
            this->setSelectedState(false);
            return true;
        }
        return false;
    }
    
    void CocoCheckBox::setTextures(const char *backGround, const char *backGroundSelected, const char *cross,const char* backGroundDisabled,const char* frontCrossDisabled,bool useSpriteFrame)
    {
        this->setBackGroundTexture(backGround,useSpriteFrame);
        this->setBackGroundSelectedTexture(backGroundSelected,useSpriteFrame);
        this->setFrontCrossTexture(cross,useSpriteFrame);
        this->setBackGroundDisabledTexture(backGroundDisabled,useSpriteFrame);
        this->setFrontCrossDisabledTexture(frontCrossDisabled,useSpriteFrame);
    }
    
    void CocoCheckBox::setBackGroundTexture(const char *backGround,bool useSpriteFrame)
    {
        this->m_pBackGroundBox->loadTexture(backGround,useSpriteFrame);
    }
    
    void CocoCheckBox::setBackGroundSelectedTexture(const char *backGroundSelected,bool useSpriteFrame)
    {
        this->m_pBackGroundSelectedBox->loadTexture(backGroundSelected,useSpriteFrame);
    }
    
    void CocoCheckBox::setFrontCrossTexture(const char *cross,bool useSpriteFrame)
    {
        this->m_pFrontCross->loadTexture(cross,useSpriteFrame);
    }
    
    void CocoCheckBox::setBackGroundDisabledTexture(const char *backGroundDisabled,bool useSpriteFrame)
    {
        this->m_pBackGroundBoxDisabled->loadTexture(backGroundDisabled,useSpriteFrame);
    }
    
    void CocoCheckBox::setFrontCrossDisabledTexture(const char *frontCrossDisabled,bool useSpriteFrame)
    {
        this->m_pFrontCrossDisabled->loadTexture(frontCrossDisabled,useSpriteFrame);
    }
    
    bool CocoCheckBox::onTouchReleased(cocos2d::CCPoint &touchPoint)
    {
        if (this->m_bFocus){
            this->releaseUpEvent();
            if (this->m_bIsSelected){
                this->setSelectedState(false);
                this->unSelectedEvent();
            }else{
                this->setSelectedState(true);
                this->selectedEvent();
            }
        }
        this->setBeFocus(false);
        this->m_pWidgetParent->checkChildInfo(2,this,touchPoint);
        return true;
    }
    
    void CocoCheckBox::onPressStateChangedToNormal()
    {
        this->m_pBackGroundBox->setVisible(true);
        this->m_pBackGroundSelectedBox->setVisible(false);
        this->m_pBackGroundBoxDisabled->setVisible(false);
        this->m_pFrontCrossDisabled->setVisible(false);
    }
    
    void CocoCheckBox::onPressStateChangedToPressed()
    {
        this->m_pBackGroundBox->setVisible(false);
        this->m_pBackGroundSelectedBox->setVisible(true);
        this->m_pBackGroundBoxDisabled->setVisible(false);
        this->m_pFrontCrossDisabled->setVisible(false);
    }
    
    void CocoCheckBox::onPressStateChangedToDisabled()
    {
        this->m_pBackGroundBox->setVisible(false);
        this->m_pBackGroundSelectedBox->setVisible(false);
        this->m_pBackGroundBoxDisabled->setVisible(true);
        this->m_pFrontCross->setVisible(false);
        if (this->m_bIsSelected){
            this->m_pFrontCrossDisabled->setVisible(true);
        }
    }
    
    void CocoCheckBox::setSelectedState(bool selected)
    {
        if (selected == this->m_bIsSelected){
            return;
        }
        this->m_bIsSelected = selected;
        this->m_pFrontCross->setVisible(this->m_bIsSelected);
    }
    
    bool CocoCheckBox::getSelectedState()
    {
        return this->m_bIsSelected;
    }
    
    void CocoCheckBox::selectedEvent()
    {
        if (m_pSelectListener && m_pfnSelectSelector) {
            (m_pSelectListener->*m_pfnSelectSelector)(this);
        }
    }
    
    void CocoCheckBox::unSelectedEvent()
    {
        if (m_pUnSelectListener && m_pfnUnSelectSelector) {
            (m_pUnSelectListener->*m_pfnUnSelectSelector)(this);
        }
    }
    
    CRenderNode* CocoCheckBox::getValidNode()
    {
        return this->m_pBackGroundBox->getCRenderNode();
    }
    
    void CocoCheckBox::addSelectEvent(cocos2d::CCObject *target, SEL_SelectEvent selector)
    {
        this->m_pSelectListener = target;
        this->m_pfnSelectSelector = selector;
    }
    
    void CocoCheckBox::addUnSelectEvent(cocos2d::CCObject *target, SEL_UnSelectEvent selector)
    {
        this->m_pUnSelectListener = target;
        this->m_pfnUnSelectSelector = selector;
    }
    
    void CocoCheckBox::setColor(int r, int g, int b)
    {
        this->m_pBackGroundBox->setColor(r, g, b);
        this->m_pBackGroundSelectedBox->setColor(r, g, b);
        this->m_pFrontCross->setColor(r, g, b);
        this->m_pBackGroundBoxDisabled->setColor(r, g, b);
        this->m_pFrontCrossDisabled->setColor(r, g, b);
    }
    
    void CocoCheckBox::setOpacity(int opcity)
    {
        this->m_pBackGroundBox->setOpacity(opcity);
        this->m_pBackGroundSelectedBox->setOpacity(opcity);
        this->m_pFrontCross->setOpacity(opcity);
        this->m_pBackGroundBoxDisabled->setOpacity(opcity);
        this->m_pFrontCrossDisabled->setOpacity(opcity);
    }
    
    void CocoCheckBox::setFlipX(bool flipX)
    {
        this->m_pBackGroundBox->setFlipX(flipX);
        this->m_pBackGroundSelectedBox->setFlipX(flipX);
        this->m_pFrontCross->setFlipX(flipX);
        this->m_pBackGroundBoxDisabled->setFlipX(flipX);
        this->m_pFrontCrossDisabled->setFlipX(flipX);
    }
    
    void CocoCheckBox::setFlipY(bool flipY)
    {
        this->m_pBackGroundBox->setFlipX(flipY);
        this->m_pBackGroundSelectedBox->setFlipY(flipY);
        this->m_pFrontCross->setFlipY(flipY);
        this->m_pBackGroundBoxDisabled->setFlipY(flipY);
        this->m_pFrontCrossDisabled->setFlipY(flipY);
    }
    
    void CocoCheckBox::setAnchorPoint(const cocos2d::CCPoint &pt)
    {
        CocoWidget::setAnchorPoint(pt);
        this->m_pBackGroundBox->setAnchorPoint(pt);
        this->m_pBackGroundSelectedBox->setAnchorPoint(pt);
        this->m_pBackGroundBoxDisabled->setAnchorPoint(pt);
        this->m_pFrontCross->setAnchorPoint(pt);
        this->m_pFrontCrossDisabled->setAnchorPoint(pt);
    }
}