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

#include "CocoTextButton.h"
#include "DictionaryHelper.h"

namespace cs {
    CocoTextButton::CocoTextButton():
    m_pTextLable(NULL)
    {
        
    }
    
    CocoTextButton::~CocoTextButton()
    {
        
    }
    
    CocoTextButton* CocoTextButton::create()
    {
//        return CocoTextButton::create(NULL);
        CocoTextButton* widget = new CocoTextButton();
        if (widget && widget->init()) {
            return widget;
        }
        CC_SAFE_DELETE(widget);
        return NULL;
    }
    
    bool CocoTextButton::init()
    {
        if (CocoButton::init()) {
            this->m_pTextLable = new UIText();
            this->m_pTextLable->init();
            this->addUIElement(this->m_pTextLable);
            return true;
        }
        return false;
    }
    
    void CocoTextButton::setText(const char* text)
    {
        this->m_pTextLable->setStringValue(text);
    }
    
    void CocoTextButton::setTextColor(int r,int g,int b)
    {
        this->m_pTextLable->setTextColor(r,g,b);
    }
    
    void CocoTextButton::setFontSize(int size)
    {
        this->m_pTextLable->setFontSize(size);
    }
    
    void CocoTextButton::setFontName(const char *fontName)
    {
        this->m_pTextLable->setFontName(fontName);
    }
    
    void CocoTextButton::setFlipX(bool flipX)
    {
        CocoButton::setFlipX(flipX);
        this->m_pTextLable->setFlipX(flipX);
    }
    
    void CocoTextButton::setFlipY(bool flipY)
    {
        CocoButton::setFlipY(flipY);
        this->m_pTextLable->setFlipY(flipY);
    }
    
    void CocoTextButton::setColor(int r, int g, int b)
    {
        CocoButton::setColor(r, g, b);
        this->m_pTextLable->setColor(r, g, b);
    }
    
    void CocoTextButton::setOpacity(int opcity)
    {
        CocoButton::setOpacity(opcity);
        this->m_pTextLable->setOpacity(opcity);
    }
    
    void CocoTextButton::setAnchorPoint(const cocos2d::CCPoint &pt)
    {
        CocoButton::setAnchorPoint(pt);
        this->m_pTextLable->setPosition(ccp(this->m_pButtonNormal->getContentSizeWidth()*(0.5f-this->m_pButtonNormal->getAnchorPoint().x), this->m_pButtonNormal->getContentSizeHeight()*(0.5f-this->m_pButtonNormal->getAnchorPoint().y)));
//        this->m_pTextLable->setAnchorPoint(pt);
    }
}