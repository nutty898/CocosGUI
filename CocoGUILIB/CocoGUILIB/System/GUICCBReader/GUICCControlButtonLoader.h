#ifndef __GUI_CCBI__GUICCControlButtonLoader__
#define __GUI_CCBI__GUICCControlButtonLoader__

#include "GUICCControlLoader.h"
#include "../extensions/GUI/CCControlExtension/CCControlButton.h"

namespace cs
{
    /* Forward declaration. */
    class GUICCBReader;
    
    class GUICCControlButtonLoader : public GUICCControlLoader
    {
    public:
        virtual ~GUICCControlButtonLoader() {};
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GUICCControlButtonLoader, loader);
        
    protected:
        GUI_CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCControlButton);
        
        virtual void onHandlePropTypeCheck(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, bool pCheck, GUICCBReader * pCCBReader);
        virtual void onHandlePropTypeString(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char * pString, GUICCBReader * pCCBReader);
        virtual void onHandlePropTypeFontTTF(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char * pFontTTF, GUICCBReader * pCCBReader);
        virtual void onHandlePropTypeFloatScale(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, float pFloatScale, GUICCBReader * pCCBReader);
        virtual void onHandlePropTypePoint(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCPoint pPoint, GUICCBReader * pCCBReader);
        virtual void onHandlePropTypeSize(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCSize pSize, GUICCBReader * pCCBReader);
        virtual void onHandlePropTypeSpriteFrame(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCSpriteFrame * pCCSpriteFrame, GUICCBReader * pCCBReader);
        virtual void onHandlePropTypeColor3(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccColor3B pCCColor3B, GUICCBReader * pCCBReader);
    };
}

#endif /* defined(__GUI_CCBI__GUICCControlButtonLoader__) */
