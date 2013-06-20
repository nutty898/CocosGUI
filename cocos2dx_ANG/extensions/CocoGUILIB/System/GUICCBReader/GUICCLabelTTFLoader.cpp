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

#include "GUICCLabelTTFLoader.h"
#include "CocoTextArea.h"



NS_CC_EXT_BEGIN

#define PROPERTY_COLOR "color"
#define PROPERTY_OPACITY "opacity"
#define PROPERTY_BLENDFUNC "blendFunc"
#define PROPERTY_FONTNAME "fontName"
#define PROPERTY_FONTSIZE "fontSize"
#define PROPERTY_HORIZONTALALIGNMENT "horizontalAlignment"
#define PROPERTY_VERTICALALIGNMENT "verticalAlignment"
#define PROPERTY_STRING "string"
#define PROPERTY_DIMENSIONS "dimensions"

void GUICCLabelTTFLoader::onHandlePropTypeColor3(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccColor3B pCCColor3B, GUICCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_COLOR) == 0) {
        /**/
//            ((CCLabelTTF *)pNode)->setColor(pCCColor3B);
        dynamic_cast<CocoTextArea*>(pWidget)->setTextColor(pCCColor3B.r, pCCColor3B.g, pCCColor3B.b);
        /**/
    } else {
        GUICCNodeLoader::onHandlePropTypeColor3(pWidget, pNode, pParent, pPropertyName, pCCColor3B, pCCBReader);
    }
}

void GUICCLabelTTFLoader::onHandlePropTypeByte(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, unsigned char pByte, GUICCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_OPACITY) == 0) {
        /**/
//            ((CCLabelTTF *)pNode)->setOpacity(pByte);
        pWidget->setOpacity(pByte);
        /**/
    } else {
        GUICCNodeLoader::onHandlePropTypeByte(pWidget, pNode, pParent, pPropertyName, pByte, pCCBReader);
    }
}

void GUICCLabelTTFLoader::onHandlePropTypeBlendFunc(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccBlendFunc pCCBlendFunc, GUICCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_BLENDFUNC) == 0) {
        /**/
//            ((CCLabelTTF *)pNode)->setBlendFunc(pCCBlendFunc);
        pWidget->setBlendFunc(pCCBlendFunc);
        /**/
    } else {
        GUICCNodeLoader::onHandlePropTypeBlendFunc(pWidget, pNode, pParent, pPropertyName, pCCBlendFunc, pCCBReader);
    }
}

void GUICCLabelTTFLoader::onHandlePropTypeFontTTF(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char * pFontTTF, GUICCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_FONTNAME) == 0) {
        /**/
//            ((CCLabelTTF *)pNode)->setFontName(pFontTTF);
        dynamic_cast<CocoTextArea*>(pWidget)->setFontName(pFontTTF);
        /**/
    } else {
        GUICCNodeLoader::onHandlePropTypeFontTTF(pWidget, pNode, pParent, pPropertyName, pFontTTF, pCCBReader);
    }
}

void GUICCLabelTTFLoader::onHandlePropTypeText(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char * pText, GUICCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_STRING) == 0) {
        /**/
//            ((CCLabelTTF *)pNode)->setString(pText);
        dynamic_cast<CocoTextArea*>(pWidget)->setText(pText);
        /**/
    } else {
        GUICCNodeLoader::onHandlePropTypeText(pWidget, pNode, pParent, pPropertyName, pText, pCCBReader);
    }
}

void GUICCLabelTTFLoader::onHandlePropTypeFloatScale(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, float pFloatScale, GUICCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_FONTSIZE) == 0) {
        /**/
//            ((CCLabelTTF *)pNode)->setFontSize(pFloatScale);
        dynamic_cast<CocoTextArea*>(pWidget)->setFontSize(pFloatScale);
        /**/
    } else {
        GUICCNodeLoader::onHandlePropTypeFloatScale(pWidget, pNode, pParent, pPropertyName, pFloatScale, pCCBReader);
    }
}

void GUICCLabelTTFLoader::onHandlePropTypeIntegerLabeled(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, int pIntegerLabeled, GUICCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_HORIZONTALALIGNMENT) == 0) {
        /**/
//            ((CCLabelTTF *)pNode)->setHorizontalAlignment(CCTextAlignment(pIntegerLabeled));
        dynamic_cast<CocoTextArea*>(pWidget)->setTextHorizontalAlignment(CCTextAlignment(pIntegerLabeled));
        /**/
    } else if(strcmp(pPropertyName, PROPERTY_VERTICALALIGNMENT) == 0) {
        /**/
//            ((CCLabelTTF *)pNode)->setVerticalAlignment(CCVerticalTextAlignment(pIntegerLabeled));
        dynamic_cast<CocoTextArea*>(pWidget)->setTextVerticalAlignment(CCVerticalTextAlignment(pIntegerLabeled));
        /**/
    } else {
        GUICCNodeLoader::onHandlePropTypeFloatScale(pWidget, pNode, pParent, pPropertyName, pIntegerLabeled, pCCBReader);
    }
}

void GUICCLabelTTFLoader::onHandlePropTypeSize(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCSize pSize, GUICCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_DIMENSIONS) == 0) {
        /**/
//            ((CCLabelTTF *)pNode)->setDimensions(pSize);
        dynamic_cast<CocoTextArea*>(pWidget)->setTextAreaSize(pSize);
        /**/
    } else {
        GUICCNodeLoader::onHandlePropTypeSize(pWidget, pNode, pParent, pPropertyName, pSize, pCCBReader);
    }
}

NS_CC_EXT_END
