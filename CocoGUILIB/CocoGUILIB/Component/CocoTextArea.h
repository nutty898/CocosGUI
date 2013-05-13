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

#ifndef __CocoGUI__CocoTextArea__
#define __CocoGUI__CocoTextArea__

#include "CocoWidget.h"
#include "UITextArea.h"

namespace cs{
    class CocoTextArea : public CocoWidget
    {
    public:
        CocoTextArea();
        virtual ~CocoTextArea();
        static CocoTextArea* create();
//        static CocoTextArea* create(cocos2d::CCDictionary* options);
//        static CocoTextArea* createWithJson(sp::SPJsonDictionary* options);
        virtual bool init();
//        virtual bool initWithOptions(cocos2d::CCDictionary* options);
//        virtual bool initWithOptions_json(sp::SPJsonDictionary* options);
        void setText(const char* text);
        void setTextAreaSize(float width,float height);
        void setTextHorizontalAlignment(int alignment);
        void setTextVerticalAlignment(int alignment);
        int getStringLength();
        const char* getStringValue();
        void setTextColor(int r,int g,int b);
        void setFontSize(int size);
        void setFontName(const char* fontName);
        virtual CRenderNode* getValidNode();
        virtual void setAnchorPoint(const cocos2d::CCPoint &pt);
        virtual void setColor(int r,int g,int b);
        virtual void setOpacity(int opcity);
        virtual void setFlipX(bool flipX);
        virtual void setFlipY(bool flipY);
    protected:
        UITextArea* m_pArea;
    };
}

#endif /* defined(__CocoGUI__CocoTextArea__) */
