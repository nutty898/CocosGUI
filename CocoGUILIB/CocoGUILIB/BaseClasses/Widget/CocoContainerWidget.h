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

#ifndef __CocoGUI__CocoContainerWidget__
#define __CocoGUI__CocoContainerWidget__

#include "CocoWidget.h"

namespace cs {
    class CocoContainerWidget : public CocoWidget
    {
    public:
        CocoContainerWidget();
        virtual ~CocoContainerWidget();
        static CocoContainerWidget* create();
        //Only containerWidget can use the LayoutParameter for do layout to child widget
        virtual void setLayoutParameter(/*LayoutParameter * parmeter*/);
//        static CocoContainerWidget* create(cocos2d::CCDictionary* options);
//        static CocoContainerWidget* createWithJson(sp::SPJsonDictionary* options);
        virtual bool init();
//        virtual bool initWithOptions(cocos2d::CCDictionary* options);
//        virtual bool initWithOptions_json(sp::SPJsonDictionary* options);
        virtual void initNodes();
        virtual bool addChild(CocoWidget* child);
        virtual void setClipAble(bool able);
        virtual void setClipRect(cocos2d::CCRect rect);
        virtual void updateWidth();
        virtual void updateHeight();
        virtual void setColorAndSize(int r,int g,int b,int o,float width,float height);
        virtual void setSize(float width,float height);
        virtual void setWidth(float width);
        virtual float getWidth();
        virtual void setHeight(float height);
        virtual float getHeight();
        virtual void setColor(int r,int g,int b);
        virtual void setOpacity(int opacity);
//        virtual cocos2d::CCRect getRect();
//        virtual cocos2d::CCRect getRelativeRect();
        virtual bool getClipAble();
        virtual bool pointAtSelfBody(cocos2d::CCPoint &pt);
        virtual void updateChildrenScaleXDirty(bool dirty);
        virtual void updateChildrenScaleYDirty(bool dirty);
        virtual void setScale(float scale);
        virtual void setScaleX(float scaleX);
        virtual void setScaleY(float scaleY);
        virtual void updateClipSize();
    protected:
        float m_fWidth;
        float m_fHeight;
        bool m_bClipAble;
    };
}

#endif /* defined(__CocoGUI__CocoContainerWidget__) */
