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

#ifndef __Test__CocoImageButton__
#define __Test__CocoImageButton__

#include <iostream>
#include "CocoButton.h"

namespace cs
{
    class CocoImageButton : public CocoButton
    {
    public:
        CocoImageButton();
        virtual ~CocoImageButton();
        static CocoImageButton* create();
        //        static CocoImageButton* create(cocos2d::CCDictionary* options);
        //        static CocoImageButton* createWithJson(sp::SPJsonDictionary* options);
        bool init();
        //        virtual bool initWithOptions(cocos2d::CCDictionary* options);
        //        virtual bool initWithOptions_json(sp::SPJsonDictionary* options);
        void initPressState(int state);
        
        void setImageScale9Enable(bool able);
        void setImageScale9Size(float width, float height);
        void setImageTextures(const char* normal, const char* selected, const char* disabled, bool useSpriteFrame = false);
        void setImageTexturesScale9(const char* normal, const char* selected, const char* disabled,
                                    cocos2d::CCRect capInsets,
                                    bool useSpriteFrame = false);
        void setImageNormalTexture(const char* normal, bool useSpriteFrame = false);
        void setImagePressedTexture(const char* selected, bool useSpriteFrame = false);
        void setImageDisabledTexture(const char* disabled, bool useSpriteFrame = false);
        void setImageNormalTextureScale9(const char* normal, cocos2d::CCRect capInsets, bool useSpriteFrame = false);
        void setImagePressedTextureScale9(const char* selected, cocos2d::CCRect capInsets, bool useSpriteFrame = false);
        void setImageDisabledTextureScale9(const char* disabled, cocos2d::CCRect capInsets, bool useSpriteFrame = false);
        void setImageColor(GLubyte r, GLubyte g, GLubyte b);
        void setImageOpacity(GLubyte opacity);
        void setImageFlipX(bool flipX);
        void setImageFlipY(bool flipY);
        cocos2d::CCNode* getImageValidNode();
        
        // override
        void setScale9Enable(bool able);
        void setScale9Size(float buttonWidth, float buttonHeight, float imageWidth, float imageHeight);
        void setTextures(const char* buttonNormal, const char* buttonSelected, const char* buttonDisabled,
                         const char* imageNormal, const char* imageSelected, const char* imageDisabled,
                         bool useSpriteFrame = false);
        void setTexturesScale9(const char* buttonNormal, const char* buttonSelected, const char* buttonDisabled,
                               const char* imageNormal, const char* imageSelected, const char* imageDisabled,
                               cocos2d::CCRect buttonCapInsets, cocos2d::CCRect imageCapInsets,
                               bool useSpriteFrame = false);
        void setColor(GLubyte buttonR, GLubyte buttonG, GLubyte buttonB,
                      GLubyte imageR, GLubyte imageG, GLubyte imageB);
        void setOpacity(GLubyte buttonOpacity, GLubyte imageOpacity);
        void setFlipX(bool buttonFlipX, bool imageFlipX);
        void setFlipY(bool buttonFlipY, bool imageFlipY);
        
        void onPressStateChangedToNormal();
        void onPressStateChangedToPressed();
        void onPressStateChangedToDisabled();
        
    protected:
        cocos2d::CCNode* m_pImageNormal;
        cocos2d::CCNode* m_pImageClicked;
        cocos2d::CCNode* m_pImageDisable;
        
        bool m_bScale9Enable;
    };
}

#endif /* defined(__Test__CocoImageButton__) */
