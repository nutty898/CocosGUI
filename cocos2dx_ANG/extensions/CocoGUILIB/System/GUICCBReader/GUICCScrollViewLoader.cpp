/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "GUICCScrollViewLoader.h"
#include "CocoScrollView.h"



#define PROPERTY_CONTAINER "container"
#define PROPERTY_DIRECTION "direction"
#define PROPERTY_CLIPSTOBOUNDS "clipsToBounds"
#define PROPERTY_BOUNCES "bounces"
#define PROPERTY_SCALE "scale"

NS_CC_EXT_BEGIN

void GUICCScrollViewLoader::onHandlePropTypeSize(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCSize pSize, GUICCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_CONTENTSIZE) == 0) {
        ((CCScrollView *)pNode)->setViewSize(pSize);
        dynamic_cast<CocoScrollView*>(pWidget)->setSize(pSize);
    } else {
        GUICCNodeLoader::onHandlePropTypeSize(pWidget, pNode, pParent, pPropertyName, pSize, pCCBReader);
    }
}

void GUICCScrollViewLoader::onHandlePropTypeCheck(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, bool pCheck, GUICCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_CLIPSTOBOUNDS) == 0) {
        ((CCScrollView *)pNode)->setClippingToBounds(pCheck);
        dynamic_cast<CocoScrollView*>(pWidget)->setClipAble(pCheck);
    } else if(strcmp(pPropertyName, PROPERTY_BOUNCES) == 0) {
        ((CCScrollView *)pNode)->setBounceable(pCheck);
    } else {
        GUICCNodeLoader::onHandlePropTypeCheck(pWidget, pNode, pParent, pPropertyName, pCheck, pCCBReader);
    }
}

void GUICCScrollViewLoader::onHandlePropTypeCCBFile(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCNode * pCCBFileNode, GUICCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_CONTAINER) == 0) {
        ((CCScrollView *)pNode)->setContainer(pCCBFileNode);
        ((CCScrollView *)pNode)->updateInset();
    } else {
        GUICCNodeLoader::onHandlePropTypeCCBFile(pWidget, pNode, pParent, pPropertyName, pCCBFileNode, pCCBReader);
    }
}

void GUICCScrollViewLoader::onHandlePropTypeFloat(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, float pFloat, GUICCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_SCALE) == 0) {
        ((CCScrollView *)pNode)->setScale(pFloat);
        dynamic_cast<CocoScrollView*>(pWidget)->setScale(pFloat);            
    } else {
        GUICCNodeLoader::onHandlePropTypeFloat(pWidget, pNode, pParent, pPropertyName, pFloat, pCCBReader);
    }
}

void GUICCScrollViewLoader::onHandlePropTypeIntegerLabeled(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, int pIntegerLabeled, GUICCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_DIRECTION) == 0) {
        ((CCScrollView *)pNode)->setDirection(CCScrollViewDirection(pIntegerLabeled));
        
        SCROLLVIEW_DIR eDirection;
        switch (CCScrollViewDirection(pIntegerLabeled))
        {
            case cocos2d::extension::kCCScrollViewDirectionVertical:
                eDirection = SCROLLVIEW_DIR_VERTICAL;
                break;
                
            case cocos2d::extension::kCCScrollViewDirectionHorizontal:
                eDirection = SCROLLVIEW_DIR_HORIZONTAL;
                break;
                
            default:
                eDirection = SCROLLVIEW_DIR_VERTICAL;
                break;
        }
        dynamic_cast<CocoScrollView*>(pWidget)->setDirection(eDirection);
    } else {
        GUICCNodeLoader::onHandlePropTypeFloatScale(pWidget, pNode, pParent, pPropertyName, pIntegerLabeled, pCCBReader);
    }
}

NS_CC_EXT_END
