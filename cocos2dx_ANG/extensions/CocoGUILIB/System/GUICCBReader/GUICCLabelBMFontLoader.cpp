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

#include "GUICCLabelBMFontLoader.h"
#include "CocoLabelBMFont.h"



NS_CC_EXT_BEGIN

#define PROPERTY_COLOR "color"
#define PROPERTY_OPACITY "opacity"
#define PROPERTY_BLENDFUNC "blendFunc"
#define PROPERTY_FNTFILE "fntFile"
#define PROPERTY_STRING "string"

void GUICCLabelBMFontLoader::onHandlePropTypeColor3(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccColor3B pCCColor3B, GUICCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_COLOR) == 0) {
        /**/
//            ((CCLabelBMFont *)pNode)->setColor(pCCColor3B);
        dynamic_cast<CocoLabelBMFont*>(pWidget)->setColor(pCCColor3B);
        /**/
    } else {
        GUICCNodeLoader::onHandlePropTypeColor3(pWidget, pNode, pParent, pPropertyName, pCCColor3B, pCCBReader);
    }
}

void GUICCLabelBMFontLoader::onHandlePropTypeByte(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, unsigned char pByte, GUICCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_OPACITY) == 0) {
        /**/
//            ((CCLabelBMFont *)pNode)->setOpacity(pByte);
        dynamic_cast<CocoLabelBMFont*>(pWidget)->setOpacity(pByte);
        /**/
    } else {
        GUICCNodeLoader::onHandlePropTypeByte(pWidget, pNode, pParent, pPropertyName, pByte, pCCBReader);
    }
}

void GUICCLabelBMFontLoader::onHandlePropTypeBlendFunc(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccBlendFunc pCCBlendFunc, GUICCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_BLENDFUNC) == 0) {
        /**/
//            ((CCLabelBMFont *)pNode)->setBlendFunc(pCCBlendFunc);
        dynamic_cast<CocoLabelBMFont*>(pWidget)->setBlendFunc(pCCBlendFunc);
        /**/
    } else {
        GUICCNodeLoader::onHandlePropTypeBlendFunc(pWidget, pNode, pParent, pPropertyName, pCCBlendFunc, pCCBReader);
    }
}

void GUICCLabelBMFontLoader::onHandlePropTypeFntFile(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char* pFntFile, GUICCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_FNTFILE) == 0) {
        /**/
//            ((CCLabelBMFont *)pNode)->setFntFile(pFntFile);
        dynamic_cast<CocoLabelBMFont*>(pWidget)->setFntFile(pFntFile);
        /**/
    } else {
        GUICCNodeLoader::onHandlePropTypeFntFile(pWidget, pNode, pParent, pPropertyName, pFntFile, pCCBReader);
    }
}

void GUICCLabelBMFontLoader::onHandlePropTypeText(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char* pText, GUICCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_STRING) == 0) {
        /**/
//            ((CCLabelBMFont *)pNode)->setString(pText);
        dynamic_cast<CocoLabelBMFont*>(pWidget)->setText(pText);
        /**/
    } else {
        GUICCNodeLoader::onHandlePropTypeText(pWidget, pNode, pParent, pPropertyName, pText, pCCBReader);
    }
}

NS_CC_EXT_END
