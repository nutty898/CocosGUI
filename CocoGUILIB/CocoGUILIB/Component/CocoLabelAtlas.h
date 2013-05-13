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

#ifndef __CocoGUI__CocoLabelAtlas__
#define __CocoGUI__CocoLabelAtlas__

#include "CocoWidget.h"
#include "UILabelAtlas.h"

namespace cs {
    class CocoLabelAtlas : public CocoWidget
    {
    public:
        CocoLabelAtlas();
        virtual ~CocoLabelAtlas();
        static CocoLabelAtlas* create();
//        static CocoLabelAtlas* create(cocos2d::CCDictionary* options);
//        static CocoLabelAtlas* createWithJson(sp::SPJsonDictionary* options);
        virtual bool init();
//        virtual bool initWithOptions(cocos2d::CCDictionary* options);
//        virtual bool initWithOptions_json(sp::SPJsonDictionary* options);
        void setProperty(const char* stringValue,const char* charMapFile, int itemWidth, int itemHeight, const char* startCharMap,bool useSpriteFrame = false);
        void setStringValue(const char* value);
        const char* getStringValue();
        virtual CRenderNode* getValidNode();
        virtual void setAnchorPoint(const cocos2d::CCPoint &pt);
        virtual void setColor(int r,int g,int b);
        virtual void setOpacity(int opcity);
    protected:
        UILabelAtlas* uiLabelAtlas;
    };
}

#endif /* defined(__CocoGUI__CocoLabelAtlas__) */
