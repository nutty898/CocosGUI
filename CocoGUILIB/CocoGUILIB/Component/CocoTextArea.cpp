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
#include "CocoTextArea.h"
#include "DictionaryHelper.h"

namespace cs {
    CocoTextArea::CocoTextArea():
    m_pArea(NULL)
    {
        
    }
    
    CocoTextArea::~CocoTextArea()
    {
        
    }

    CocoTextArea* CocoTextArea::create()
    {
//        return CocoTextArea::create(NULL);
        CocoTextArea* widget = new CocoTextArea();
        if (widget && widget->init()) {
            return widget;
        }
        CC_SAFE_DELETE(widget);
        return NULL;
    }
    
    bool CocoTextArea::init()
    {
        if (CocoWidget::init()) {
            this->m_pArea = new UITextArea();
            this->m_pArea->init();
            this->addUIElement(this->m_pArea);
            return true;
        }
        return false;
    }
    
    void CocoTextArea::setText(const char* text)
    {
        this->m_pArea->setStringValue(text);
    }
    
    void CocoTextArea::setTextAreaSize(float width,float height)
    {
        this->m_pArea->setTextAreaSize(width,height);
    }
    
    void CocoTextArea::setTextHorizontalAlignment(int alignment)
    {
        this->m_pArea->setTextHorizontalAlignment(alignment);
    }
    
    void CocoTextArea::setTextVerticalAlignment(int alignment)
    {
        this->m_pArea->setTextVerticalAlignment(alignment);
    }
    
    int CocoTextArea::getStringLength()
    {
        return this->m_pArea->getStringLength();
    }
    
    const char* CocoTextArea::getStringValue()
    {
        return this->m_pArea->getStringValue();
    }
    
    void CocoTextArea::setTextColor(int r,int g,int b)
    {
        this->m_pArea->setTextColor(r,g,b);
    }
    
    void CocoTextArea::setFontSize(int size)
    {
        this->m_pArea->setFontSize(size);
    }
    
    void CocoTextArea::setFontName(const char *fontName)
    {
        this->m_pArea->setFontName(fontName);
    }
    
    CRenderNode* CocoTextArea::getValidNode()
    {
        return this->m_pArea->getCRenderNode();
    }
    
    void CocoTextArea::setColor(int r, int g, int b)
    {
        this->m_pArea->setColor(r, g, b);
    }
    
    void CocoTextArea::setOpacity(int opcity)
    {
        this->m_pArea->setOpacity(opcity);
    }
    
    void CocoTextArea::setFlipX(bool flipX)
    {
        CocoWidget::setFlipX(flipX);
        this->m_pArea->getCRenderNode()->setFlipX(flipX);
    }
    
    void CocoTextArea::setFlipY(bool flipY)
    {
        CocoWidget::setFlipY(flipY);
        this->m_pArea->getCRenderNode()->setFlipY(flipY);
    }
    
    void CocoTextArea::setAnchorPoint(const cocos2d::CCPoint &pt)
    {
        CocoWidget::setAnchorPoint(pt);
        this->m_pArea->setAnchorPoint(pt);
    }
}