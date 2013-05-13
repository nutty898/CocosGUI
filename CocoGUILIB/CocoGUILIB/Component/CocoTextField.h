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

#ifndef __CocoGUI__CocoTextField__
#define __CocoGUI__CocoTextField__

#include "CocoWidget.h"
#include "UITextField.h"

namespace cs {
    class CocoTextField : public CocoWidget
    {
    public:
        CocoTextField();
        virtual ~CocoTextField();
        static CocoTextField* create();
//        static CocoTextField* create(cocos2d::CCDictionary* options);
//        static CocoTextField* createWithJson(sp::SPJsonDictionary* options);
        virtual bool init();
//        virtual bool initWithOptions(cocos2d::CCDictionary* options);
//        virtual bool initWithOptions_json(sp::SPJsonDictionary* options);
        void setTouchSize(float width,float height);
        void setText(const char* text);
        void setSize(float width,float height);
        void setPlaceHolder(const char* value);
        void setFontSize(int size);
        void setTextColor(int r,int g,int b);
        virtual void didNotSelectSelf();
        const char* getStringValue();
        virtual bool onTouchPressed(cocos2d::CCPoint &touchPoint);
        virtual bool pointAtSelfBody(cocos2d::CCPoint &pt);
        virtual CRenderNode* getValidNode();
        virtual void setAnchorPoint(const cocos2d::CCPoint &pt);
        virtual void setColor(int r,int g,int b);
        virtual void setOpacity(int opcity);
    protected:
        UITextField* uiTextField;
        float m_fTouchWidth;
        float m_fTouchHeight;
        bool m_bUseTouchArea;
    };
}

#endif /* defined(__CocoGUI__CocoTextField__) */
