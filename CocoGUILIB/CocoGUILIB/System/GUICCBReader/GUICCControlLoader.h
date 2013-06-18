#ifndef __GUI_CCBI__GUICCControlLoader__
#define __GUI_CCBI__GUICCControlLoader__

#include "GUICCNodeLoader.h"
#include "../extensions/GUI/CCControlExtension/CCControl.h"

namespace cs
{
    /* Forward declaration. */
    class GUICCBReader;
    
    class GUICCControlLoader : public GUICCNodeLoader {
    public:
        virtual ~GUICCControlLoader() {};
        
    protected:
        GUI_CCB_PURE_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCControl);
        
        virtual void onHandlePropTypeBlockCCControl(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, BlockCCControlData * pBlockCCControlData, GUICCBReader * pCCBReader);
        virtual void onHandlePropTypeCheck(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, bool pCheck, GUICCBReader * pCCBReader);
    };
}

#endif /* defined(__GUI_CCBI__GUICCControlLoader__) */
