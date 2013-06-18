#ifndef __GUI_CCBI__GUICCLayerLoader__
#define __GUI_CCBI__GUICCLayerLoader__

#include "GUICCNodeLoader.h"

namespace cs
{
    /* Forward declaration. */
    class GUICCBReader;
    
    class GUICCLayerLoader : public GUICCNodeLoader {
    public:
        virtual ~GUICCLayerLoader() {};
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GUICCLayerLoader, loader);
        
    protected:
        GUI_CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCLayer);
        
        virtual void onHandlePropTypeCheck(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, bool pCheck, GUICCBReader * pCCBReader);
        virtual void onHandlePropTypeSize(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char* pPropertyName, CCSize pSize, GUICCBReader * pCCBReader);
    };
}

#endif /* defined(__GUI_CCBI__GUICCLayerLoader__) */
