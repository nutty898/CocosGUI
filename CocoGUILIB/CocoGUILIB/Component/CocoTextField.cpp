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

#include "CocoTextField.h"
#include "DictionaryHelper.h"
namespace cs {
    
    CocoTextField::CocoTextField():
    m_fTouchWidth(0.0),
    m_fTouchHeight(0.0),
    m_bUseTouchArea(false)
    {
        
    }
    
    CocoTextField::~CocoTextField()
    {
        
    }
    
    CocoTextField* CocoTextField::create()
    {
        CocoTextField* widget = new CocoTextField();
        if (widget && widget->init()) {
            return widget;
        }
        CC_SAFE_DELETE(widget);
        return NULL;
    }
    
    bool CocoTextField::init()
    {
        if (CocoWidget::init()) {
            setUpdateEnable(true);
            return true;
        }
        return false;
    }
    
    void CocoTextField::initNodes()
    {
        this->m_pCCRenderNode = CTextField::create("input words here", "Thonburi", 20);
    }
    
    void CocoTextField::setTouchSize(float width,float height)
    {
        this->m_bUseTouchArea = true;
        this->m_fTouchWidth = width;
        this->m_fTouchHeight = height;
    }
    
    void CocoTextField::setText(const char* text)
    {
        dynamic_cast<CTextField*>(this->m_pCCRenderNode)->setString(text);
    }
    
    void CocoTextField::setSize(cocos2d::CCSize &size)
    {
        dynamic_cast<CTextField*>(this->m_pCCRenderNode)->setDimensions(size);
    }
    
    void CocoTextField::setPlaceHolder(const char *value)
    {
        dynamic_cast<CTextField*>(this->m_pCCRenderNode)->setPlaceHolder(value);
    }
    
    void CocoTextField::setFontSize(int size)
    {
        dynamic_cast<CTextField*>(this->m_pCCRenderNode)->setFontSize(size);
    }

    void CocoTextField::didNotSelectSelf()
    {
        dynamic_cast<CTextField*>(this->m_pCCRenderNode)->closeIME();
    }
    
    const char* CocoTextField::getStringValue()
    {
        return dynamic_cast<CTextField*>(this->m_pCCRenderNode)->getString();
    }
    
    bool CocoTextField::onTouchPressed(cocos2d::CCPoint &touchPoint)
    {
        CocoWidget::onTouchPressed(touchPoint);
        dynamic_cast<CTextField*>(this->m_pCCRenderNode)->openIME();
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
        dynamic_cast<CTextField*>(this->m_pCCRenderNode)->setCharacterLength(length);
    }
    
    void CocoTextField::setIsPassWord(bool isPassword)
    {
        dynamic_cast<CTextField*>(this->m_pCCRenderNode)->setIsPassword(isPassword);
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
        return dynamic_cast<CTextField*>(this->m_pCCRenderNode)->getAttachWithIME();
    }
    
    void CocoTextField::setAttachWithIME(bool attach)
    {
        dynamic_cast<CTextField*>(this->m_pCCRenderNode)->setAttachWithIME(attach);
    }
    
    bool CocoTextField::getDetachWithIME()
    {
        return dynamic_cast<CTextField*>(this->m_pCCRenderNode)->getDetachWithIME();
    }
    
    void CocoTextField::setDetachWithIME(bool detach)
    {
        dynamic_cast<CTextField*>(this->m_pCCRenderNode)->setDetachWithIME(detach);
    }
    
    bool CocoTextField::getInsertText()
    {
        return dynamic_cast<CTextField*>(this->m_pCCRenderNode)->getInsertText();
    }
    
    void CocoTextField::setInsertText(bool insertText)
    {
        dynamic_cast<CTextField*>(this->m_pCCRenderNode)->setInsertText(insertText);
    }
    
    bool CocoTextField::getDeleteBackward()
    {
        return dynamic_cast<CTextField*>(this->m_pCCRenderNode)->getDeleteBackward();
    }
    
    void CocoTextField::setDeleteBackward(bool deleteBackward)
    {
        dynamic_cast<CTextField*>(this->m_pCCRenderNode)->setDeleteBackward(deleteBackward);
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
}