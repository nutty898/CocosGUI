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

#ifndef __CocoGUI__CocoPanel__
#define __CocoGUI__CocoPanel__

#include "CocoContainerWidget.h"

namespace cs {
    class CocoPanel : public CocoContainerWidget
    {
    public:
        CocoPanel();
        virtual ~CocoPanel();
        static CocoPanel* create();
        virtual void initBackGround(bool scale9);
        void setBackGroundImage(const char* fileName,bool useSpriteFrame = false);
        void setBackGroundImageScale9(const char* fileName,const cocos2d::CCRect &capInsets,bool useSpriteFrame = false);
        virtual void setBackGroundColorEnable(bool able);
        virtual void setSize(const cocos2d::CCSize &size);
        void setBackGroundImageScale9Enable(bool able);
    protected:
        bool m_bBackGroundInited;
        bool m_bBackGroundScale9Enable;
        cocos2d::CCNode* m_pBackGroundImage;
    };
}

#endif /* defined(__CocoGUI__CocoPanel__) */
