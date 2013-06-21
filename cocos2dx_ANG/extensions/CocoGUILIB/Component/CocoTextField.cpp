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

#include "CocoTextField.h"
#include "DictionaryHelper.h"

NS_CC_EXT_BEGIN
    
CocoTextField::CocoTextField():
m_fTouchWidth(0.0),
m_fTouchHeight(0.0),
m_bUseTouchArea(false),
m_pRenderTextField(NULL),
m_pAttachWithIMEListener(NULL),
m_pDetachWithIMEListener(NULL),
m_pInsertTextListener(NULL),
m_pDeleteBackwardListener(NULL),
m_pfnAttachWithIMESelector(NULL),
m_pfnDetachWithIMESelector(NULL),
m_pfnInsertTextSelector(NULL),
m_pfnDeleteBackwardSelector(NULL)
{
    
}

CocoTextField::~CocoTextField()
{
    
}

CocoTextField* CocoTextField::create()
{
    CocoTextField* widget = new CocoTextField();
    if (widget && widget->init())
    {
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

bool CocoTextField::init()
{
    if (CocoWidget::init())
    {
        setUpdateEnable(true);
        return true;
    }
    return false;
}

void CocoTextField::initNodes()
{
    CocoWidget::initNodes();
    m_pRenderTextField = CTextField::create("input words here", "Thonburi", 20);
    this->m_pCCRenderNode->addChild(m_pRenderTextField);
}

void CocoTextField::setTouchSize(float width,float height)
{
    this->m_bUseTouchArea = true;
    this->m_fTouchWidth = width;
    this->m_fTouchHeight = height;
}

void CocoTextField::setText(const char* text)
{
    m_pRenderTextField->setString(text);
}

void CocoTextField::setSize(cocos2d::CCSize &size)
{
    m_pRenderTextField->setDimensions(size);
}

void CocoTextField::setPlaceHolder(const char *value)
{
    m_pRenderTextField->setPlaceHolder(value);
}

void CocoTextField::setFontSize(int size)
{
    m_pRenderTextField->setFontSize(size);
}

void CocoTextField::didNotSelectSelf()
{
    m_pRenderTextField->closeIME();
}

const char* CocoTextField::getStringValue()
{
    return m_pRenderTextField->getString();
}

bool CocoTextField::onTouchPressed(cocos2d::CCPoint &touchPoint)
{
    CocoWidget::onTouchPressed(touchPoint);
    m_pRenderTextField->openIME();
    return true;
}

bool CocoTextField::pointAtSelfBody(cocos2d::CCPoint &pt)
{
    if (!this->m_bUseTouchArea){
        return CocoWidget::pointAtSelfBody(pt);
    }
    if (!this->getAbsoluteVisible()) {
        return false;
    }
    return false;
}

void CocoTextField::setCharacterLength(int length)
{
    m_pRenderTextField->setCharacterLength(length);
}

void CocoTextField::setIsPassWord(bool isPassword)
{
    m_pRenderTextField->setIsPassword(isPassword);
}

void CocoTextField::update(float dt)
{
    if (getAttachWithIME())
    {
        attachWithIMEEvent();
        setAttachWithIME(false);
    }
    if (getDetachWithIME())
    {
        detachWithIMEEvent();
        setDetachWithIME(false);
    }
    if (getInsertText())
    {
        insertTextEvent();
        setInsertText(false);
    }
    if (getDeleteBackward())
    {
        deleteBackwardEvent();
        setDeleteBackward(false);
    }
}

bool CocoTextField::getAttachWithIME()
{
    return m_pRenderTextField->getAttachWithIME();
}

void CocoTextField::setAttachWithIME(bool attach)
{
    m_pRenderTextField->setAttachWithIME(attach);
}

bool CocoTextField::getDetachWithIME()
{
    return m_pRenderTextField->getDetachWithIME();
}

void CocoTextField::setDetachWithIME(bool detach)
{
    m_pRenderTextField->setDetachWithIME(detach);
}

bool CocoTextField::getInsertText()
{
    return m_pRenderTextField->getInsertText();
}

void CocoTextField::setInsertText(bool insertText)
{
    m_pRenderTextField->setInsertText(insertText);
}

bool CocoTextField::getDeleteBackward()
{
    return m_pRenderTextField->getDeleteBackward();
}

void CocoTextField::setDeleteBackward(bool deleteBackward)
{
    m_pRenderTextField->setDeleteBackward(deleteBackward);
}

void CocoTextField::attachWithIMEEvent()
{
    if (m_pAttachWithIMEListener && m_pfnAttachWithIMESelector)
    {
        (m_pAttachWithIMEListener->*m_pfnAttachWithIMESelector)(this);
    }
}

void CocoTextField::detachWithIMEEvent()
{
    if (m_pDetachWithIMEListener && m_pfnDetachWithIMESelector)
    {
        (m_pDetachWithIMEListener->*m_pfnDetachWithIMESelector)(this);
    }
}

void CocoTextField::insertTextEvent()
{
    if (m_pInsertTextListener && m_pfnInsertTextSelector)
    {
        (m_pInsertTextListener->*m_pfnInsertTextSelector)(this);
    }
}

void CocoTextField::deleteBackwardEvent()
{
    if (m_pDeleteBackwardListener && m_pfnDeleteBackwardSelector)
    {
        (m_pDeleteBackwardListener->*m_pfnDeleteBackwardSelector)(this);
    }
}

void CocoTextField::addAttachWithIMEEvent(cocos2d::CCObject *target, SEL_TextFieldAttachWithIMEEvent selecor)
{
    m_pAttachWithIMEListener = target;
    m_pfnAttachWithIMESelector = selecor;
}

void CocoTextField::addDetachWithIMEEvent(cocos2d::CCObject *target, SEL_TextFieldDetachWithIMEEvent selecor)
{
    m_pDetachWithIMEListener = target;
    m_pfnDetachWithIMESelector = selecor;
}

void CocoTextField::addInsertTextEvent(cocos2d::CCObject *target, SEL_TextFieldInsertTextEvent selecor)
{
    m_pInsertTextListener = target;
    m_pfnInsertTextSelector = selecor;
}

void CocoTextField::addDeleteBackwardEvent(cocos2d::CCObject *target, SEL_TextFieldDeleteBackwardEvent selecor)
{
    m_pDeleteBackwardListener = target;
    m_pfnDeleteBackwardSelector = selecor;
}

CCNode* CocoTextField::getValidNode()
{
    return this->m_pRenderTextField;
}

NS_CC_EXT_END