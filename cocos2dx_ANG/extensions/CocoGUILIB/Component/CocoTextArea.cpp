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

#include "CocoTextArea.h"
#include "DictionaryHelper.h"

NS_CC_EXT_BEGIN

CocoTextArea::CocoTextArea()
{
    
}

CocoTextArea::~CocoTextArea()
{
    
}

CocoTextArea* CocoTextArea::create()
{
    CocoTextArea* widget = new CocoTextArea();
    if (widget && widget->init())
    {
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

void CocoTextArea::initNodes()
{
    this->m_pCCRenderNode = cocos2d::CCLabelTTF::create();
}

void CocoTextArea::setText(const char* text)
{
    DYNAMIC_CAST_CCLABELTTF->setString(text);
}

void CocoTextArea::setTextAreaSize(const cocos2d::CCSize &size)
{
    DYNAMIC_CAST_CCLABELTTF->setDimensions(size);
}

void CocoTextArea::setTextHorizontalAlignment(cocos2d::CCTextAlignment alignment)
{
    DYNAMIC_CAST_CCLABELTTF->setHorizontalAlignment(alignment);
}

void CocoTextArea::setTextVerticalAlignment(cocos2d::CCVerticalTextAlignment alignment)
{
    DYNAMIC_CAST_CCLABELTTF->setVerticalAlignment(alignment);
}

int CocoTextArea::getStringLength()
{
    const char* str = DYNAMIC_CAST_CCLABELTTF->getString();
    return strlen(str);
}

const char* CocoTextArea::getStringValue()
{
    return DYNAMIC_CAST_CCLABELTTF->getString();
}

void CocoTextArea::setTextColor(int r,int g,int b)
{
    DYNAMIC_CAST_CCLABELTTF->setColor(cocos2d::ccc3(r, g, b));
}

void CocoTextArea::setFontSize(int size)
{
    DYNAMIC_CAST_CCLABELTTF->setFontSize(size);
}

void CocoTextArea::setFontName(const char *fontName)
{
    DYNAMIC_CAST_CCLABELTTF->setFontName(fontName);
}

void CocoTextArea::setFlipX(bool flipX)
{
    DYNAMIC_CAST_CCLABELTTF->setFlipX(flipX);
}

void CocoTextArea::setFlipY(bool flipY)
{
    DYNAMIC_CAST_CCLABELTTF->setFlipY(flipY);
}

NS_CC_EXT_END