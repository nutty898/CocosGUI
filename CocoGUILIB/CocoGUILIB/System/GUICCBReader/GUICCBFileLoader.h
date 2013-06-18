#ifndef __GUI_CCBI__GUICCBFileLoader__
#define __GUI_CCBI__GUICCBFileLoader__

#include "GUICCNodeLoader.h"
#include "CCBReader.h"

namespace cs
{
    /* Forward declaration. */
    class GUICCBReader;
    
    class GUICCBFileLoader : public GUICCNodeLoader
    {
    public:
        ~GUICCBFileLoader() {};
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GUICCBFileLoader, loader);
        
    protected:
        GUI_CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCBFile);
        
        virtual void onHandlePropTypeCCBFile(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCNode * pCCBFileNode, GUICCBReader * pCCBReader);
        virtual void onHandlePropTypeCCBFile(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char* pPropertyName, CCNode * pCCBFileNode, CocoWidget* pCCBFileWidget,  GUICCBReader * pCCBReader);
    };
}

#endif /* defined(__GUI_CCBI__GUICCBFileLoader__) */
