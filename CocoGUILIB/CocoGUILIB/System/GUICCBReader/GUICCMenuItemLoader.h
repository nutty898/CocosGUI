#ifndef __GUI_CCBI__GUICCMenuItemLoader__
#define __GUI_CCBI__GUICCMenuItemLoader__

#include "GUICCLayerLoader.h"

namespace cs
{
    /* Forward declaration. */
    class GUICCBReader;
    
    class GUICCMenuItemLoader : public GUICCNodeLoader {
    public:
        virtual ~GUICCMenuItemLoader() {};
        
    protected:
        GUI_CCB_PURE_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCMenuItem);
        
        virtual void onHandlePropTypeBlock(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, BlockData * pBlockData, GUICCBReader * pCCBReader);
        virtual void onHandlePropTypeCheck(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, bool pCheck, GUICCBReader * pCCBReader);
    };
}

#endif /* defined(__GUI_CCBI__GUICCMenuItemLoader__) */
