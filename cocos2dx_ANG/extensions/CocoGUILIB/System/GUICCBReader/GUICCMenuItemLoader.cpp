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

#include "GUICCMenuItemLoader.h"
#include "CocoButton.h"



#define PROPERTY_BLOCK "block"
#define PROPERTY_ISENABLED "isEnabled"

NS_CC_EXT_BEGIN

void GUICCMenuItemLoader::onHandlePropTypeBlock(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, BlockData * pBlockData, GUICCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_BLOCK) == 0) {
        if (NULL != pBlockData) // Add this condition to allow CCMenuItemImage without target/selector predefined
        {
            ((CCMenuItem *)pNode)->setTarget(pBlockData->mTarget, pBlockData->mSELMenuHandler);
        }
    } else {
        GUICCNodeLoader::onHandlePropTypeBlock(pWidget, pNode, pParent, pPropertyName, pBlockData, pCCBReader);
    }
}

void GUICCMenuItemLoader::onHandlePropTypeCheck(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, bool pCheck, GUICCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_ISENABLED) == 0) {
        /**/
//            ((CCMenuItem *)pNode)->setEnabled(pCheck);
        dynamic_cast<CocoButton*>(pWidget)->setBeTouchAble(pCheck);
        /**/
    } else {
        GUICCNodeLoader::onHandlePropTypeCheck(pWidget, pNode, pParent, pPropertyName, pCheck, pCCBReader);
    }
}

NS_CC_EXT_END
