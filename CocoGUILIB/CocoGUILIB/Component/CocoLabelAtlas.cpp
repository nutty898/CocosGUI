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
#include "CocoLabelAtlas.h"
#include "DictionaryHelper.h"

namespace cs {
    CocoLabelAtlas::CocoLabelAtlas()
    {

    }
    
    CocoLabelAtlas::~CocoLabelAtlas()
    {
        
    }
    
    CocoLabelAtlas* CocoLabelAtlas::create()
    {
        CocoLabelAtlas* widget = new CocoLabelAtlas();
        if (widget && widget->init()) {
            return widget;
        }
        CC_SAFE_DELETE(widget);
        return NULL;
    }
    
    void CocoLabelAtlas::initNodes()
    {
        this->m_pCCRenderNode = CLabelAtlas::create();
    }
    
    void CocoLabelAtlas::setProperty(const char *stringValue, const char *charMapFile, int itemWidth, int itemHeight, const char *startCharMap,bool useSpriteFrame)
    {
        DYNAMIC_CAST_CLABELATLAS->setProperty(stringValue, charMapFile, itemWidth, itemHeight, (int)(startCharMap[0]));
    }
    
    void CocoLabelAtlas::setStringValue(const char *value)
    {
        DYNAMIC_CAST_CLABELATLAS->setString(value);
    }
    
    const char* CocoLabelAtlas::getStringValue()
    {
        return DYNAMIC_CAST_CLABELATLAS->getString();
    }
    
    void CocoLabelAtlas::setAnchorPoint(const cocos2d::CCPoint &pt)
    {
        this->m_pCCRenderNode->setAnchorPoint(ccp(pt.x, pt.y-0.25f));
    }
}