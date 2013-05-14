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

#ifndef __CocoGUI__CocoButton__
#define __CocoGUI__CocoButton__

#include "CocoWidget.h"
#include "UISprite.h"
#include "UIScale9Sprite.h"

namespace cs {
    class CocoButton : public CocoWidget
    {
    public:
        CocoButton();
        virtual ~CocoButton();
        static CocoButton* create();
//        static CocoButton* create(cocos2d::CCDictionary* options);
//        static CocoButton* createWithJson(sp::SPJsonDictionary* options);
        virtual bool init();
//        virtual bool initWithOptions(cocos2d::CCDictionary* options);
//        virtual bool initWithOptions_json(sp::SPJsonDictionary* options);
        void initPressState(int state);
        
        virtual void setTextures(const char* normal,const char* selected,const char* disabled,bool useSpriteFrame = false);
        virtual void setTexturesScale9(const char* normal,const char* selected,const char* disabled,cocos2d::CCRect capInsets,bool useSpriteFrame = false);
        void setNormalTexture(const char* normal,bool useSpriteFrame = false);
        void setPressedTexture(const char* selected,bool useSpriteFrame = false);
        void setDisabledTexture(const char* disabled,bool useSpriteFrame = false);
        void setNormalTextureScale9(const char* normal,cocos2d::CCRect capInsets,bool useSpriteFrame = false);
        void setPressedTextureScale9(const char* selected,cocos2d::CCRect capInsets,bool useSpriteFrame = false);
        void setDisabledTextureScale9(const char* disabled,cocos2d::CCRect capInsets,bool useSpriteFrame = false);
        virtual void onPressStateChangedToNormal();
        virtual void onPressStateChangedToPressed();
        virtual void onPressStateChangedToDisabled();
        virtual CRenderNode* getValidNode();
        virtual void setAnchorPoint(const cocos2d::CCPoint &pt);
        virtual void setScale9Enable(bool able);
        virtual void setScale9Size(float width,float height);
        virtual void setColor(int r,int g,int b);
        virtual void setOpacity(int opcity);
        virtual void setFlipX(bool flipX);
        virtual void setFlipY(bool flipY);
    protected:
        UIElement* m_pButtonNormal;
        UIElement* m_pButtonClicked;
        UIElement* m_pButtonDisable;
        
        bool m_bScale9Enable;
    };
}

#endif /* defined(__CocoGUI__CocoButton__) */
