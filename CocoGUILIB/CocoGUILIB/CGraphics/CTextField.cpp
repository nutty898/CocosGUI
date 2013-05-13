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
#include "CTextField.h"

using namespace cocos2d;

namespace cs {
    
    CTextField::CTextField()
    {
        m_pInputText = "";
    }
    
    CTextField::~CTextField()
    {
        //    delete m_pInputText;
    }
    
    
    CTextField * CTextField::create(const char *placeholder, const char *fontName, float fontSize)
    {
        CTextField *pRet = new CTextField();
        
        if(pRet && pRet->initWithString("", fontName, fontSize))
        {
            pRet->autorelease();
            if (placeholder)
            {
                pRet->setPlaceHolder(placeholder);
            }
            
            return pRet;
        }
        
        CC_SAFE_DELETE(pRet);
        
        return NULL;
    }
    
    void CTextField::onEnter()
    {
        this->setDelegate(this);
    }
    
    
    bool CTextField::onTextFieldAttachWithIME(cocos2d::CCTextFieldTTF *pSender)
    {
        if (m_pInputText.empty()) {
            return false;
        }
        return false;
    }
    
    bool CTextField::onTextFieldInsertText(cocos2d::CCTextFieldTTF *pSender, const char *text, int nLen)
    {
        m_pInputText.append(text);
        setString(m_pInputText.c_str());
        return true;
    }
    
    bool CTextField::onTextFieldDeleteBackward(cocos2d::CCTextFieldTTF *pSender, const char *delText, int nLen)
    {
        m_pInputText.resize(m_pInputText.size() - nLen);
        setString(m_pInputText.c_str());
        return false;
    }
    
    bool CTextField::onTextFieldDetachWithIME(cocos2d::CCTextFieldTTF *pSender)
    {
        return false;
    }
    
    void CTextField::openIME()
    {
        this->attachWithIME();
    }
    
    void CTextField::closeIME()
    {
        this->detachWithIME();
    }
}