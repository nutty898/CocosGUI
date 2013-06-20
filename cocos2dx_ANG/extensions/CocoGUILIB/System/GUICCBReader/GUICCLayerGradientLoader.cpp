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

#include "GUICCLayerGradientLoader.h"
#include "CocoGradientPanel.h"


#define PROPERTY_STARTCOLOR "startColor"
#define PROPERTY_ENDCOLOR "endColor"
#define PROPERTY_STARTOPACITY "startOpacity"
#define PROPERTY_ENDOPACITY "endOpacity"
#define PROPERTY_VECTOR "vector"
#define PROPERTY_BLENDFUNC "blendFunc"

NS_CC_EXT_BEGIN

void GUICCLayerGradientLoader::onHandlePropTypeColor3(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccColor3B pCCColor3B, GUICCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_STARTCOLOR) == 0) {
        /**/
//            ((CCLayerGradient *)pNode)->setStartColor(pCCColor3B);
        dynamic_cast<CocoGradientPanel*>(pWidget)->setStartColor(pCCColor3B);
        dynamic_cast<CocoGradientPanel*>(pWidget)->setStartOpacity(255);
//            dynamic_cast<CocoContainerWidget*>(pWidget)->setOpacity(255);
        /**/
    } else if(strcmp(pPropertyName, PROPERTY_ENDCOLOR) == 0) {
        /**/
//            ((CCLayerGradient *)pNode)->setEndColor(pCCColor3B);
        dynamic_cast<CocoGradientPanel*>(pWidget)->setEndColor(pCCColor3B);
        dynamic_cast<CocoGradientPanel*>(pWidget)->setEndOpacity(255);
//            dynamic_cast<CocoContainerWidget*>(pWidget)->setOpacity(255);
        /**/
    } else {
        GUICCLayerLoader::onHandlePropTypeColor3(pWidget, pNode, pParent, pPropertyName, pCCColor3B, pCCBReader);
    }
}

void GUICCLayerGradientLoader::onHandlePropTypeByte(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, unsigned char pByte, GUICCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_STARTOPACITY) == 0) {
        /**/
//            ((CCLayerGradient *)pNode)->setStartOpacity(pByte);
//            dynamic_cast<CocoContainerWidget*>(pWidget)->setStartOpacity(pByte);
        dynamic_cast<CocoContainerWidget*>(pWidget)->setOpacity(pByte);
        /**/
    } else if(strcmp(pPropertyName, PROPERTY_ENDOPACITY) == 0) {
        /**/
//            ((CCLayerGradient *)pNode)->setEndOpacity(pByte);
//            dynamic_cast<CocoContainerWidget*>(pWidget)->setEndOpacity(pByte);
        dynamic_cast<CocoContainerWidget*>(pWidget)->setOpacity(pByte);
        /**/
    } else {
        GUICCLayerLoader::onHandlePropTypeByte(pWidget, pNode, pParent, pPropertyName, pByte, pCCBReader);
    }
}

void GUICCLayerGradientLoader::onHandlePropTypeBlendFunc(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccBlendFunc pCCBlendFunc, GUICCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_BLENDFUNC) == 0) {
        /**/
//            ((CCLayerGradient *)pNode)->setBlendFunc(pCCBlendFunc);
        pWidget->setBlendFunc(pCCBlendFunc);
        /**/
    } else {
        GUICCLayerLoader::onHandlePropTypeBlendFunc(pWidget, pNode, pParent, pPropertyName, pCCBlendFunc, pCCBReader);
    }
}


void GUICCLayerGradientLoader::onHandlePropTypePoint(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCPoint pPoint, GUICCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_VECTOR) == 0) {
        ((CCLayerGradient *)pNode)->setVector(pPoint);
        
        // TODO Not passed along the ccbi file.
        // ((CCLayerGradient *)pNode)->setCompressedInterpolation(true);
    } else {
        GUICCLayerLoader::onHandlePropTypePoint(pWidget, pNode, pParent, pPropertyName, pPoint, pCCBReader);
    }
}

NS_CC_EXT_END
