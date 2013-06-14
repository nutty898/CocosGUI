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

#ifndef __CocoGUI__CocoLoadingBar__
#define __CocoGUI__CocoLoadingBar__

#include "CocoWidget.h"
namespace cs {
    class CocoLoadingBar : public CocoWidget
    {
    public:
        CocoLoadingBar();
        virtual ~CocoLoadingBar();
        static CocoLoadingBar* create();
        virtual void initNodes();
        void setDirection(int dir);
        int getDirection();
        void setTexture(const char* texture,bool useSpriteFrame = false);
        void setPercent(int percent);
        int getPercent();
		float getTotalWidth();
		float getTotalHeight();
        virtual cocos2d::CCNode* getValidNode();
    protected:
        int m_nBarType;
        int m_nPercent;
        float m_fTotalLength;
        float m_fBarHeight;
        cocos2d::CCSprite* m_pRenderBar;

    };
}

#endif /* defined(__CocoGUI__CocoLoadingBar__) */
