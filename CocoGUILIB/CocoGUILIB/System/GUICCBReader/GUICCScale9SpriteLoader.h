#ifndef __GUI_CCBI__GUICCScale9SpriteLoader__
#define __GUI_CCBI__GUICCScale9SpriteLoader__

#include "GUICCNodeLoader.h"
#include "GUICCScale9SpriteLoader.h"
#include "../extensions/GUI/CCControlExtension/CCScale9Sprite.h"

namespace cs
{
    /* Forward declaration. */
    class GUICCBReader;
    
    class GUICCScale9SpriteLoader : public GUICCNodeLoader {
    public:
        virtual ~GUICCScale9SpriteLoader() {};
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GUICCScale9SpriteLoader, loader);
        
    protected:
        GUI_CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCScale9Sprite);
        
        virtual void onHandlePropTypeColor3(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccColor3B pCCColor3B, GUICCBReader * pCCBReader);
        virtual void onHandlePropTypeByte(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, unsigned char pByte, GUICCBReader * pCCBReader);
        virtual void onHandlePropTypeBlendFunc(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccBlendFunc pCCBlendFunc, GUICCBReader * pCCBReader);
        virtual void onHandlePropTypeSpriteFrame(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCSpriteFrame * pCCSpriteFrame, GUICCBReader * pCCBReader);
        virtual void onHandlePropTypeSize(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCSize pSize, GUICCBReader * pCCBReader);
        virtual void onHandlePropTypeFloat(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, float pFloat, GUICCBReader * pCCBReader);
    };
}

#endif /* defined(__GUI_CCBI__GUICCScale9SpriteLoader__) */
