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
    CocoLabelAtlas::CocoLabelAtlas():
    uiLabelAtlas(NULL)
    {

    }
    
    CocoLabelAtlas::~CocoLabelAtlas()
    {
        
    }
    
    CocoLabelAtlas* CocoLabelAtlas::create()
    {
//        return CocoLabelAtlas::create(NULL);
        CocoLabelAtlas* widget = new CocoLabelAtlas();
        if (widget && widget->init()) {
            return widget;
        }
        CC_SAFE_DELETE(widget);
        return NULL;
    }
    
    bool CocoLabelAtlas::init()
    {
        if (CocoWidget::init()) {
            uiLabelAtlas = new UILabelAtlas();
            uiLabelAtlas->init();
            this->addUIElement(this->uiLabelAtlas);
            return true;
        }
        return false;
    }
     
    void CocoLabelAtlas::setProperty(const char *stringValue, const char *charMapFile, int itemWidth, int itemHeight, const char *startCharMap,bool useSpriteFrame)
    {
        this->uiLabelAtlas->setProperty(stringValue, charMapFile, itemWidth, itemHeight, startCharMap,useSpriteFrame);
    }
    
    void CocoLabelAtlas::setStringValue(const char *value)
    {
        this->uiLabelAtlas->setStringValue(value);
    }
    
    const char* CocoLabelAtlas::getStringValue()
    {
        return this->uiLabelAtlas->getStringValue();
    }
    
    CRenderNode* CocoLabelAtlas::getValidNode()
    {
        return this->uiLabelAtlas->getCRenderNode();
    }
    
    void CocoLabelAtlas::setColor(int r, int g, int b)
    {
        this->uiLabelAtlas->setColor(r, g, b);
    }
    
    void CocoLabelAtlas::setOpacity(int opcity)
    {
        this->uiLabelAtlas->setOpacity(opcity);
    }
    
    void CocoLabelAtlas::setAnchorPoint(const cocos2d::CCPoint &pt)
    {
        CocoWidget::setAnchorPoint(pt);
        this->uiLabelAtlas->setAnchorPoint(ccp(pt.x, pt.y-0.25f));
    }
}