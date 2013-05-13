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

#include "CocoLabel.h"
#include "DictionaryHelper.h"

namespace cs{
    CocoLabel::CocoLabel():
    m_bTouchScaleChangeAble(false),
    m_pTextLable(NULL),
    m_nGravity(0),
    m_sFontName("Thonburi"),
    m_nFontSize(10),
    m_fOnSelectedScaleOffset(0.5),
    m_fNormalScaleValue(1)
    {

    }
    
    CocoLabel::~CocoLabel()
    {
        
    }
    
    CocoLabel* CocoLabel::create()
    {
//        return CocoLabel::create(NULL);
        CocoLabel* widget = new CocoLabel();
        if (widget && widget->init()) {
            return widget;
        }
        CC_SAFE_DELETE(widget);
        return NULL;
    }
    
    bool CocoLabel::init()
    {
        if (CocoWidget::init()) {
            this->m_pTextLable = new UIText();
            this->m_pTextLable->init();
            this->m_pTextLable->setAnchorPoint(ccp(0.5, 0.5));
            this->addUIElement(this->m_pTextLable);
            this->setPressState(0);
            return true;
        }
        return false;
    }
    
    void CocoLabel::setText(const char* text)
    {
        this->m_pTextLable->setStringValue(text);
    }
    
    const char* CocoLabel::getStringValue()
    {
        return this->m_pTextLable->getStringValue();
    }
    
    int CocoLabel::getStringLength()
    {
        return this->m_pTextLable->getStringLength();
    }
    
    void CocoLabel::setTextColor(int r,int g,int b)
    {
        this->m_pTextLable->setTextColor(r,g,b);
    }
    
    void CocoLabel::setFontSize(int size)
    {
        this->m_pTextLable->setFontSize(size);
    }
    
    void CocoLabel::setFontName(const char* name)
    {
        this->m_pTextLable->setFontName(name);
    }
    
    void CocoLabel::setTouchScaleChangeAble(bool able)
    {
        this->m_bTouchScaleChangeAble = able;
        this->m_fNormalScaleValue = this->getScale();
    }
    
    bool CocoLabel::getTouchScaleChangeAble()
    {
        return this->m_bTouchScaleChangeAble;
    }
    
    void CocoLabel::onPressStateChangedToNormal()
    {
        if (!this->m_bTouchScaleChangeAble){
            return;
        }
        this->clickScale(this->m_fNormalScaleValue);
    }
    
    void CocoLabel::onPressStateChangedToPressed()
    {
        if (!this->m_bTouchScaleChangeAble){
            return;
        }
        this->clickScale(this->m_fNormalScaleValue + this->m_fOnSelectedScaleOffset);
    }
    
    void CocoLabel::onPressStateChangedToDisabled()
    {
        
    }
    
    void CocoLabel::clickScale(float scale)
    {
        this->m_pCContainerNode->setScale(scale);
    }
    
    CRenderNode* CocoLabel::getValidNode()
    {
        return this->m_pTextLable->getCRenderNode();
    }
    
    void CocoLabel::setFlipX(bool flipX)
    {
        CocoWidget::setFlipX(flipX);
        this->m_pTextLable->setFlipX(flipX);
    }
    
    void CocoLabel::setFlipY(bool flipY)
    {
        CocoWidget::setFlipY(flipY);
        this->m_pTextLable->setFlipY(flipY);
    }
    
    void CocoLabel::setGravity(int gravity)
    {
        this->m_nGravity = gravity;
        switch (this->m_nGravity) {
            case 0:
                this->m_pTextLable->setAnchorPoint(ccp(0.5, 0.5));
                break;
            case 1:
                this->m_pTextLable->setAnchorPoint(ccp(0.0, 0.5));
                break;
            case 2:
                this->m_pTextLable->setAnchorPoint(ccp(1.0, 0.5));
                break;
            default:
                break;
        }
    }
    
    void CocoLabel::setColor(int r, int g, int b)
    {
        this->m_pTextLable->setColor(r, g, b);
    }
    
    void CocoLabel::setOpacity(int opcity)
    {
        this->m_pTextLable->setOpacity(opcity);
    }
    
    void CocoLabel::adaptSize(float xProportion, float yProportion)
    {
        float res = xProportion > yProportion ? xProportion : yProportion;
        this->m_pTextLable->setFontSize(this->m_pTextLable->getFontSize()*res);
    }
    
    void CocoLabel::setAnchorPoint(const cocos2d::CCPoint &pt)
    {
        CocoWidget::setAnchorPoint(pt);
        this->m_pTextLable->setAnchorPoint(pt);
    }
}