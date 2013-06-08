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

#ifndef CursorInputDemo_CursorTextField_h
#define CursorInputDemo_CursorTextField_h

#include "cocos2d.h"

/* gui mark */
namespace cs
{
    class CTextField: public cocos2d::CCTextFieldTTF, public cocos2d::CCTextFieldDelegate, public cocos2d::CCTouchDelegate
    {
    public:
        CTextField();
        ~CTextField();
        
        void onEnter();
        
        // static
        static CTextField* create(const char *placeholder, const char *fontName, float fontSize);
        
        // CCTextFieldDelegate
        virtual bool onTextFieldAttachWithIME(CCTextFieldTTF *pSender);
        virtual bool onTextFieldDetachWithIME(CCTextFieldTTF * pSender);
        virtual bool onTextFieldInsertText(CCTextFieldTTF * pSender, const char * text, int nLen);
        virtual bool onTextFieldDeleteBackward(CCTextFieldTTF * pSender, const char * delText, int nLen);
        
        void insertText(const char* text, int len);
        void deleteBackward();
        
        void openIME();
        void closeIME();
        
        void setPswText(const char* text);
        
    protected:
        // intput limit character amount
        CC_SYNTHESIZE(int, m_nCharacterLength, CharacterLength);
        
        // whether show with password
        CC_SYNTHESIZE(bool, m_bIsPassword, IsPassword);
        
        CC_SYNTHESIZE(bool, m_bAttachWithIME, AttachWithIME);
        CC_SYNTHESIZE(bool, m_bDetachWithIME, DetachWithIME);
        CC_SYNTHESIZE(bool, m_bInsertText, InsertText);
        CC_SYNTHESIZE(bool, m_bDeleteBackward, DeleteBackward);
        
        int m_nTextTotalLength;
    };
}
/**/

#endif
