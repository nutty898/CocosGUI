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
    CTextField::CTextField() :
    m_nCharacterLength(3),
    m_pCursorSprite(NULL),
    m_bIsPassword(false)
    {
    }
    
    CTextField::~CTextField()
    {
//        delete m_pCursorSprite;
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
            
            pRet->initCursorSprite(fontSize);
            
            return pRet;
        }
        
        CC_SAFE_DELETE(pRet);
        
        return NULL;
    }
    
    void CTextField::initCursorSprite(int nHeight)
    {
        using namespace cocos2d;
        
        int column = 4;
        //  int pixels[nHeight][column];
		int (*pixels)[4] = new int[nHeight][4];
        
        for (int i = 0; i < nHeight; ++i)
        {
            for (int j = 0; j < column; ++j)
            {
                pixels[i][j] = 0xff696969;
            }
        }
        
        CCTexture2D * texture = new CCTexture2D();
        texture->initWithData(pixels, kCCTexture2DPixelFormat_RGB888, 1, 1, CCSizeMake(column, nHeight));
        
        m_pCursorSprite = CCSprite::createWithTexture(texture);
        CCSize parentSize = getContentSize();
        m_pCursorSprite->setPosition(ccp(0, parentSize.height / 2));
        addChild(m_pCursorSprite);
        
        /*
         CCFadeOut * fadeOut = CCFadeOut::create(0.25f);
         CCFadeIn * fadeIn = CCFadeIn::create(0.25f);
         CCSequence * seq = CCSequence::create(fadeOut, fadeIn, NULL);
         CCRepeatForever * forever = CCRepeatForever::create(seq);
         m_pCursorSprite->runAction(forever);
         */
        
        m_pCursorSprite->setVisible(false);
        
		delete []pixels;
		pixels = NULL;
    }
    
    void CTextField::onEnter()
    {
        CCTextFieldTTF::setDelegate(this);
    }
    
    
    bool CTextField::onTextFieldAttachWithIME(cocos2d::CCTextFieldTTF *pSender)
    {
        return false;
    }
    
    bool CTextField::onTextFieldInsertText(cocos2d::CCTextFieldTTF *pSender, const char *text, int nLen)
    {
        if (CCTextFieldTTF::getCharCount() >= m_nCharacterLength)
        {
            return true;
        }
        
        return false;
    }
    
    bool CTextField::onTextFieldDeleteBackward(cocos2d::CCTextFieldTTF *pSender, const char *delText, int nLen)
    {
        return false;
    }
    
    bool CTextField::onTextFieldDetachWithIME(cocos2d::CCTextFieldTTF *pSender)
    {
        return false;
    }
    
    void CTextField::insertText(const char * text, int len)
    {
        CCTextFieldTTF::insertText(text, len);
        
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
        
        // cursor
        m_pCursorSprite->setPositionX(getContentSize().width);
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
        
        // cursor
        m_pCursorSprite->setPositionX(getContentSize().width);
        
        if (CCTextFieldTTF::getCharCount() == 0)
        {
            m_pCursorSprite->setPositionX(0);
        }
    }
    
    void CTextField::openIME()
    {
        //        m_pCursorSprite->setVisible(true);
        CCTextFieldTTF::attachWithIME();
    }
    
    void CTextField::closeIME()
    {
        m_pCursorSprite->setVisible(false);
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