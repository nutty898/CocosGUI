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

#include "UITextField.h"

namespace cs {
    UITextField::UITextField()
    {
        
    }
    
    UITextField::~UITextField()
    {
        
    }
    
    void UITextField::init()
    {
        this->m_pCRenderNode = new CRenderNode();
		this->m_pCRenderNode->initNode(6);
    }
    
    void UITextField::openIME()
    {
        this->m_pCRenderNode->openIME();
    }
    
    void UITextField::closeIME()
    {
        this->m_pCRenderNode->closeIME();
    }
    
    void UITextField::setPlaceHolder(const char* value)
    {
        this->m_pCRenderNode->setPlaceHolder(value);
    }
    
    void UITextField::setStringValue(const char* value)
    {
        this->m_pCRenderNode->setStringValue(value);
    }
    
    void UITextField::setSize(float width,float height)
    {
        this->m_pCRenderNode->setTextFieldSize(width,height);
    }
    
    void UITextField::setTextColor(int r,int g,int b)
    {
        this->m_pCRenderNode->setTextColor(r,g,b);
    }
    
    void UITextField::setFontSize(int size)
    {
        this->m_pCRenderNode->setFontSize(size);
    }
    
    const char* UITextField::getStringValue()
    {
        return this->m_pCRenderNode->getStringValue();
    }
    
    void UITextField::setCharacterLength(int length)
    {
        this->m_pCRenderNode->setCharacterLength(length);
    }
    
    void UITextField::setIsPassWord(bool isPassword)
    {
        this->m_pCRenderNode->setIsPassword(isPassword);
    }
    
    bool UITextField::getAttachWithIME()
    {
        return m_pCRenderNode->getTextFieldAttachWithIME();
    }
    
    void UITextField::setAttachWithIME(bool attach)
    {
        m_pCRenderNode->setTextFieldAttachWithIME(attach);
    }
    
    bool UITextField::getDetachWithIME()
    {
        return m_pCRenderNode->getTextFieldDetachWithIME();
    }
    
    void UITextField::setDetachWithIME(bool detach)
    {
        m_pCRenderNode->setTextFieldDetachWithIME(detach);
    }
    
    bool UITextField::getInsertText()
    {
        return m_pCRenderNode->getTextFieldInsertText();
    }
    
    void UITextField::setInsertText(bool insertText)
    {
        m_pCRenderNode->setTextFieldInsertText(insertText);
    }
    
    bool UITextField::getDeleteBackward()
    {
        return m_pCRenderNode->getTextFieldDeleteBackward();
    }
    
    void UITextField::setDeleteBackward(bool deleteBackward)
    {
        m_pCRenderNode->setTextFieldDeleteBackward(deleteBackward);
    }
}