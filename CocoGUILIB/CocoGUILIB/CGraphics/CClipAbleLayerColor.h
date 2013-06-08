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

#ifndef SPII_CClipAbleLayerColor_h
#define SPII_CClipAbleLayerColor_h

#include "cocos2d.h"


namespace cs {
    
    class CClipAbleLayerColor : public cocos2d::CCLayerColor {
    public:
        CClipAbleLayerColor():m_bClipAble(false),m_fScissorX(0.0),m_fScissorY(0.0),m_fScissorWidth(0.0),m_fScissorHeight(0.0),m_bEnableCustomArea(false),m_bColorEnable(false){};
        virtual ~CClipAbleLayerColor(){};
        static CClipAbleLayerColor* create(cocos2d::ccColor4B color,float width ,float height);
        static CClipAbleLayerColor* create();
        bool init();
        virtual void visit();
        void setClipAble(bool able);
        void setColorEnable(bool enable);
        bool getColorEnable();
        void setClipRect(float x,float y,float width,float height);
        void setClipSize(float width,float height);
        virtual void draw();
    protected:
        bool m_bClipAble;
        float m_fScissorX;
        float m_fScissorY;
        float m_fScissorWidth;
        float m_fScissorHeight;
        bool m_bEnableCustomArea;
        bool m_bColorEnable;
    };
}


#endif
