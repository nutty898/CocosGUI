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

#include "UITextArea.h"

namespace cs {
    UITextArea::UITextArea()
    {
        
    }
    
    UITextArea::~UITextArea()
    {
        
    }
    
    void UITextArea::init()
    {
        this->m_pCRenderNode = new CRenderNode();
        this->m_pCRenderNode->initNode(11);
    }
    
    void UITextArea::setStringValue(const char* value)
    {
        this->m_pCRenderNode->setStringValue(value);
    }
    
    const char* UITextArea::getStringValue()
    {
        return this->m_pCRenderNode->getStringValue();
    }
    
    int UITextArea::getStringLength()
    {
        const char* str = this->getStringValue();
        return strlen(str);
    }
    
    void UITextArea::setTextColor(int r,int g,int b)
    {
        this->m_pCRenderNode->setTextColor(r,g,b);
    }
    
    void UITextArea::setFontSize(int size)
    {
        this->m_pCRenderNode->setFontSize(size);
    }
    
    void UITextArea::setFontName(const char *fontName)
    {
        this->m_pCRenderNode->setFontName(fontName);
    }
    
    void UITextArea::setTextAreaSize(float width,float height)
    {
        this->m_pCRenderNode->setTextAreaSize(width,height);
    }
    
    void UITextArea::setTextHorizontalAlignment(int alignment)
    {
        this->m_pCRenderNode->setTextHorizontalAlignment(alignment);
    }
    
    void UITextArea::setTextVerticalAlignment(int alignment)
    {
        this->m_pCRenderNode->setTextVerticalAlignment(alignment);
    }
}