#ifndef __GUI_CCBI__CCLabelTTFLoader__
#define __GUI_CCBI__CCLabelTTFLoader__

#include "GUICCNodeLoader.h"

namespace cs
{
    /* Forward declaration. */
    class GUICCBReader;
    
    class GUICCLabelTTFLoader : public GUICCNodeLoader {
    public:
        virtual ~GUICCLabelTTFLoader() {};
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GUICCLabelTTFLoader, loader);
        
    protected:
        GUI_CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCLabelTTF);
        
        virtual void onHandlePropTypeColor3(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccColor3B pCCColor3B, GUICCBReader * pCCBReader);
        virtual void onHandlePropTypeByte(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, unsigned char pByte, GUICCBReader * pCCBReader);
        virtual void onHandlePropTypeBlendFunc(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccBlendFunc pCCBlendFunc, GUICCBReader * pCCBReader);
        virtual void onHandlePropTypeFontTTF(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char * pFontTTF, GUICCBReader * pCCBReader);
        virtual void onHandlePropTypeText(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char * pText, GUICCBReader * pCCBReader);
        virtual void onHandlePropTypeFloatScale(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, float pFloatScale, GUICCBReader * pCCBReader);
        virtual void onHandlePropTypeIntegerLabeled(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, int pIntegerLabeled, GUICCBReader * pCCBReader);
        virtual void onHandlePropTypeSize(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCSize pSize, GUICCBReader * pCCBReader);
    };
}

#endif /* defined(__GUI_CCBI__CCLabelTTFLoader__) */
