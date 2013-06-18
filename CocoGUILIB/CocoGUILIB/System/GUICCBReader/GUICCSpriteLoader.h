#ifndef __GUI_CCBI__GUICCSpriteLoader__
#define __GUI_CCBI__GUICCSpriteLoader__

#include "GUICCNodeLoader.h"

namespace cs
{
    /* Forward declaration. */
    class GUICCBReader;
    
    class GUICCSpriteLoader : public GUICCNodeLoader {
    public:
        virtual ~GUICCSpriteLoader() {};
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GUICCSpriteLoader, loader);
        
    protected:
        GUI_CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCSprite);
        
        virtual void onHandlePropTypeColor3(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccColor3B pCCColor3B, GUICCBReader * pCCBReader);
        virtual void onHandlePropTypeByte(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, unsigned char pByte, GUICCBReader * pCCBReader);
        virtual void onHandlePropTypeBlendFunc(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccBlendFunc pCCBBlendFunc, GUICCBReader * pCCBReader);
        virtual void onHandlePropTypeSpriteFrame(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCSpriteFrame * pCCSpriteFrame, GUICCBReader * pCCBReader);
        virtual void onHandlePropTypeFlip(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, bool * pFlip, GUICCBReader * pCCBReader);
    };
}

#endif /* defined(__GUI_CCBI__GUICCSpriteLoader__) */
