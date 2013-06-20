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

#ifndef __GUI_CCBI__GUICCScrollViewLoader__
#define __GUI_CCBI__GUICCScrollViewLoader__

#include "GUICCNodeLoader.h"
#include "../extensions/GUI/CCScrollView/CCScrollView.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class GUICCBReader;

class GUICCScrollViewLoader : public GUICCNodeLoader {
public:
    virtual ~GUICCScrollViewLoader() {};
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GUICCScrollViewLoader, loader);
    
protected:
    GUI_CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCScrollView);
    virtual void onHandlePropTypeSize(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCSize pSize, GUICCBReader * pCCBReader);
    virtual void onHandlePropTypeCCBFile(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCNode * pCCBFileNode, GUICCBReader * pCCBReader);
    virtual void onHandlePropTypeCheck(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, bool pCheck, GUICCBReader * pCCBReader);
    virtual void onHandlePropTypeFloat(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, float pFloat, GUICCBReader * pCCBReader);
    virtual void onHandlePropTypeIntegerLabeled(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, int pIntegerLabeled, GUICCBReader * pCCBReader);
};

NS_CC_EXT_END

#endif /* defined(__GUI_CCBI__GUICCScrollViewLoader__) */
