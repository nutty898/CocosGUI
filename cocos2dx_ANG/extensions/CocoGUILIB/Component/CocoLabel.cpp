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

#include "CocoLabel.h"
#include "DictionaryHelper.h"

NS_CC_EXT_BEGIN

CocoLabel::CocoLabel():
m_bTouchScaleChangeAble(false),
m_nGravity(LabelGravityCenter),
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
    CocoLabel* widget = new CocoLabel();
    if (widget && widget->init())
    {
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

bool CocoLabel::init()
{
    if (CocoWidget::init())
    {
        this->setPressState(WidgetStateNormal);
        return true;
    }
    return false;
}

void CocoLabel::initNodes()
{
    this->m_pCCRenderNode = cocos2d::CCLabelTTF::create();
}

void CocoLabel::setText(const char* text)
{
    DYNAMIC_CAST_CCLABELTTF->setString(text);
}

const char* CocoLabel::getStringValue()
{
    return DYNAMIC_CAST_CCLABELTTF->getString();
}

int CocoLabel::getStringLength()
{
    const char* str = DYNAMIC_CAST_CCLABELTTF->getString();
    return strlen(str);
}

void CocoLabel::setFontSize(int size)
{
    DYNAMIC_CAST_CCLABELTTF->setFontSize(size);
}

void CocoLabel::setFontName(const char* name)
{
    DYNAMIC_CAST_CCLABELTTF->setFontName(name);
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
    this->m_pCCRenderNode->setScale(scale);
}

void CocoLabel::setFlipX(bool flipX)
{
    DYNAMIC_CAST_CCLABELTTF->setFlipX(flipX);
}

void CocoLabel::setFlipY(bool flipY)
{
    DYNAMIC_CAST_CCLABELTTF->setFlipY(flipY);
}

void CocoLabel::setGravity(LabelGravity gravity)
{
    this->m_nGravity = gravity;
    switch (this->m_nGravity)
    {
        case LabelGravityCenter:
            DYNAMIC_CAST_CCLABELTTF->setAnchorPoint(ccp(0.5, 0.5));
            break;
        case LabelGravityLelf:
            DYNAMIC_CAST_CCLABELTTF->setAnchorPoint(ccp(0.0, 0.5));
            break;
        case LabelGravityRight:
            DYNAMIC_CAST_CCLABELTTF->setAnchorPoint(ccp(1.0, 0.5));
            break;
        default:
            break;
    }
}

void CocoLabel::adaptSize(float xProportion, float yProportion)
{
    float res = xProportion > yProportion ? xProportion : yProportion;
    DYNAMIC_CAST_CCLABELTTF->setFontSize(DYNAMIC_CAST_CCLABELTTF->getFontSize()*res);
}

NS_CC_EXT_END