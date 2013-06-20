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

#include "GUICCSpriteLoader.h"
#include "CocoImageView.h"

#define PROPERTY_FLIP "flip"
#define PROPERTY_DISPLAYFRAME "displayFrame"
#define PROPERTY_COLOR "color"
#define PROPERTY_OPACITY "opacity"
#define PROPERTY_BLENDFUNC "blendFunc"

NS_CC_EXT_BEGIN

void GUICCSpriteLoader::onHandlePropTypeSpriteFrame(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCSpriteFrame * pCCSpriteFrame, GUICCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_DISPLAYFRAME) == 0) {
        /**/
//            ((CCSprite *)pNode)->setDisplayFrame(pCCSpriteFrame);
        dynamic_cast<CocoImageView*>(pWidget)->setDisplayFrame(pCCSpriteFrame);
        /**/
    } else {
        GUICCNodeLoader::onHandlePropTypeSpriteFrame(pWidget, pNode, pParent, pPropertyName, pCCSpriteFrame, pCCBReader);
    }
}

void GUICCSpriteLoader::onHandlePropTypeFlip(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, bool * pFlip, GUICCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_FLIP) == 0) {
        /**/
        /*
        ((CCSprite *)pNode)->setFlipX(pFlip[0]);
        ((CCSprite *)pNode)->setFlipY(pFlip[1]);
         */
        pWidget->setFlipX(pFlip[0]);
        pWidget->setFlipY(pFlip[1]);
        /*
        dynamic_cast<CocoImageView*>(pWidget)->setFlipX(pFlip[0]);
        dynamic_cast<CocoImageView*>(pWidget)->setFlipY(pFlip[1]);
         */
        /**/
    } else {
        GUICCNodeLoader::onHandlePropTypeFlip(pWidget, pNode, pParent, pPropertyName, pFlip, pCCBReader);
    }
}

void GUICCSpriteLoader::onHandlePropTypeColor3(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccColor3B pCCColor3B, GUICCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_COLOR) == 0) {
        /**/
//            ((CCSprite *)pNode)->setColor(pCCColor3B);
        pWidget->setColor(pCCColor3B);
        /**/
    } else {
        GUICCNodeLoader::onHandlePropTypeColor3(pWidget, pNode, pParent, pPropertyName, pCCColor3B, pCCBReader);
    }
}

void GUICCSpriteLoader::onHandlePropTypeByte(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, unsigned char pByte, GUICCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_OPACITY) == 0) {
        /**/
//            ((CCSprite *)pNode)->setOpacity(pByte);
        pWidget->setOpacity(pByte);
        /**/
    } else {
        GUICCNodeLoader::onHandlePropTypeByte(pWidget, pNode, pParent, pPropertyName, pByte, pCCBReader);
    }
}

void GUICCSpriteLoader::onHandlePropTypeBlendFunc(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccBlendFunc pCCBlendFunc, GUICCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_BLENDFUNC) == 0) {
        /**/
//            ((CCSprite *)pNode)->setBlendFunc(pCCBlendFunc);
        pWidget->setBlendFunc(pCCBlendFunc);
        /**/
    } else {
        GUICCNodeLoader::onHandlePropTypeBlendFunc(pWidget, pNode, pParent, pPropertyName, pCCBlendFunc, pCCBReader);
    }
}

NS_CC_EXT_END
