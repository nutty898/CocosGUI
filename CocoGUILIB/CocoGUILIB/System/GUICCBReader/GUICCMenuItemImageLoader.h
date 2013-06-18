#ifndef __GUI_CCBI__GUICCMenuItemImageLoader__
#define __GUI_CCBI__GUICCMenuItemImageLoader__

#include "GUICCMenuItemLoader.h"

namespace cs
{
    /* Forward declaration. */
    class GUICCBReader;
    
    class GUICCMenuItemImageLoader : public GUICCMenuItemLoader {
    public:
        virtual ~GUICCMenuItemImageLoader() {};
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GUICCMenuItemImageLoader, loader);
        
    protected:
        GUI_CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCMenuItemImage);
        
        virtual void onHandlePropTypeSpriteFrame(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCSpriteFrame * pCCSpriteFrame, GUICCBReader * pCCBReader);
    };
}

#endif /* defined(__GUI_CCBI__GUICCMenuItemImageLoader__) */
