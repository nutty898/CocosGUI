#ifndef __GUI_CCBI__GUICCScrollViewLoader__
#define __GUI_CCBI__GUICCScrollViewLoader__

#include "GUICCNodeLoader.h"
#include "../extensions/GUI/CCScrollView/CCScrollView.h"

namespace cs
{
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
}

#endif /* defined(__GUI_CCBI__GUICCScrollViewLoader__) */
