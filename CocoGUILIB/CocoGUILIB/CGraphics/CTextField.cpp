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

namespace cs
{
    CTextField::CTextField()
    : m_nTextTotalLength(0)
    , m_nCharacterLength(3)
    , m_bIsPassword(false)
    {
    }
    
    CTextField::~CTextField()
    {
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
        CCTextFieldTTF::setDelegate(this);
    }
    
    
    bool CTextField::onTextFieldAttachWithIME(cocos2d::CCTextFieldTTF *pSender)
    {
        setAttachWithIME(true);
        return false;
    }
    
    bool CTextField::onTextFieldInsertText(cocos2d::CCTextFieldTTF *pSender, const char *text, int nLen)
    {
        setInsertText(true);
        if (CCTextFieldTTF::getCharCount() >= m_nCharacterLength)
        {
            return true;
        }
        
        return false;
    }
    
    bool CTextField::onTextFieldDeleteBackward(cocos2d::CCTextFieldTTF *pSender, const char *delText, int nLen)
    {
        setDeleteBackward(true);
        return false;
    }
    
    bool CTextField::onTextFieldDetachWithIME(cocos2d::CCTextFieldTTF *pSender)
    {
        setDetachWithIME(true);
        return false;
    }
    
    void CTextField::insertText(const char * text, int len)
    {
        std::string str_text = text;
        int str_len = strlen(CCTextFieldTTF::getString());
        
        if (strcmp(text, "\n") != 0)
        {
            if (str_len + len > m_nCharacterLength)
            {
                int mod = str_len % 3;
                int offset = (mod == 0) ? 0 : (3 - mod);
                int amount = str_len + offset;
                str_text = str_text.substr(0, m_nCharacterLength - amount);
                CCLOG("str_test = %s", str_text.c_str());
            }
        }
        CCTextFieldTTF::insertText(str_text.c_str(), len);
        
        // password
        if (m_bIsPassword)
        {
            setPswText(m_pInputText->c_str());
        }
        
        // return
        if (strcmp(text, "\n") == 0)
        {
            if (CCTextFieldTTF::getCharCount() == 0)
            {
                CCTextFieldTTF::setPlaceHolder(m_pPlaceHolder->c_str());
            }
            closeIME();
        }
    }        
    
    void CTextField::deleteBackward()
    {
        CCTextFieldTTF::deleteBackward();
        
        if (CCTextFieldTTF::getCharCount() > 0)
        {
            // password
            if (m_bIsPassword)
            {
                setPswText(m_pInputText->c_str());
            }
        }
        
        int str_len = strlen(CCTextFieldTTF::getString());
        m_nTextTotalLength = str_len;
    }
    
    void CTextField::openIME()
    {
        CCTextFieldTTF::attachWithIME();
    }
    
    void CTextField::closeIME()
    {
        CCTextFieldTTF::detachWithIME();
    }
    
    void CTextField::setPswText(const char *text)
    {
        std::string tempStr;
        for (int i = 0; i < strlen(text); ++i)
        {
            tempStr.append("*");
        }
        CCLabelTTF::setString(tempStr.c_str());
    }
}