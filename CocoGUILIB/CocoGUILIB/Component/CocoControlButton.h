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

#ifndef __Test__CocoControlButton__
#define __Test__CocoControlButton__

#include "CocoWidget.h"
#include "cocos2d.h"
#include "GUIScale9Sprite.h"

namespace cs {
    class CocoControlButton : public CocoWidget
    {
    public:
        CocoControlButton();
        virtual ~CocoControlButton();
        static CocoControlButton* create();
        virtual bool init();
        virtual void initNodes();
        void setTextures(const char* backgroundNormal,const char* backgroundPressed,const char* backgroundDisabled);
        void setTitle(const char* titleNormal,const char* titlePressed,const char* titleDisabled);
        virtual void onPressStateChangedToNormal();
        virtual void onPressStateChangedToPressed();
        virtual void onPressStateChangedToDisabled();
        virtual cocos2d::CCNode* getValidNode();
        virtual void setAnchorPoint(const cocos2d::CCPoint &pt);
        virtual void setColor(int r,int g,int b);
        virtual void setOpacity(int opcity);
        virtual void setFlipX(bool flipX);
        virtual void setFlipY(bool flipY);
        void setNormalTitle(const char* title);
        void setPressedTitle(const char* title);
        void setDisabledTitle(const char* title);
        void setNormalFontName(const char* name);
        void setPressedFontName(const char* name);
        void setDisabledFontName(const char* name);
        void setNormalFontSize(float size);
        void setPressedFontSize(float size);
        void setDisabledFontSize(float size);
        void setNormalFontColor(const cocos2d::ccColor3B& color);
        void setPressedFontColor(const cocos2d::ccColor3B& color);
        void setDisalbedFontColor(const cocos2d::ccColor3B& color);
        void setLabelAnchorPoint(const cocos2d::CCPoint& labelAnchorPoint);
        void setPreferredSize(const cocos2d::CCSize& size);
        void setNormalBackgroundSpriteFrame(cocos2d::CCSpriteFrame * spriteFrame);
        void setPressedBackgroundSpriteFrame(cocos2d::CCSpriteFrame * spriteFrame);
        void setDisabledBackgroundSpriteFrame(cocos2d::CCSpriteFrame * spriteFrame);
    protected:        
        GUIScale9Sprite* m_pNormalBackGround;
        GUIScale9Sprite* m_pPressedBackGround;
        GUIScale9Sprite* m_pDisabledBackGround;
        cocos2d::CCLabelTTF* m_pNormalTitle;
        cocos2d::CCLabelTTF* m_pPressedTitle;
        cocos2d::CCLabelTTF* m_pDisabledTitle;
        CC_SYNTHESIZE(bool, m_bZoomOnTouchDown, ZoomOnTouchDown);
    };
}


#endif /* defined(__Test__CocoControlButton__) */
