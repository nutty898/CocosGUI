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

#include "CocoLabelBMFont.h"

NS_CC_EXT_BEGIN
    
CocoLabelBMFont::CocoLabelBMFont():
m_pLabelBMFont(NULL)
{
    
}

CocoLabelBMFont::~CocoLabelBMFont()
{
    
}

CocoLabelBMFont* CocoLabelBMFont::create()
{
    CocoLabelBMFont* widget = new CocoLabelBMFont();
    if (widget && widget->init())
    {
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

bool CocoLabelBMFont::init()
{
    if (CocoWidget::init())
    {
        this->m_pLabelBMFont = cocos2d::CCLabelBMFont::create();
        this->m_pCCRenderNode->addChild(this->m_pLabelBMFont);
        return true;
    }
    return false;
}

void CocoLabelBMFont::setFntFile(const char *fileName)
{
    this->m_pLabelBMFont->initWithString("", fileName);
}

void CocoLabelBMFont::setText(const char* value)
{
    this->m_pLabelBMFont->setString(value);
}

const char* CocoLabelBMFont::getStringValue()
{
    return this->m_pLabelBMFont->getString();
}

CCNode* CocoLabelBMFont::getValidNode()
{
    return this->m_pLabelBMFont;
}

NS_CC_EXT_END