#ifndef __GUI_CCBI__GUICCLabelBMFontLoader__
#define __GUI_CCBI__GUICCLabelBMFontLoader__

#include "GUICCNodeLoader.h"
    
namespace cs
{
    /* Forward declaration. */
    class GUICCBReader;
    
    class GUICCLabelBMFontLoader : public GUICCNodeLoader {
    public:
        virtual ~GUICCLabelBMFontLoader() {};
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GUICCLabelBMFontLoader, loader);
        
    protected:
        GUI_CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCLabelBMFont);
        
        virtual void onHandlePropTypeColor3(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccColor3B pCCColor3B, GUICCBReader * pCCBReader);
        virtual void onHandlePropTypeByte(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, unsigned char pByte, GUICCBReader * pCCBReader);
        virtual void onHandlePropTypeBlendFunc(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccBlendFunc pCCBlendFunc, GUICCBReader * pCCBReader);
        virtual void onHandlePropTypeFntFile(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char* pFntFile, GUICCBReader * pCCBReader);
        virtual void onHandlePropTypeText(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char* pText, GUICCBReader * pCCBReader);
    };
}
    
#endif /* defined(__GUI_CCBI__GUICCLabelBMFontLoader__) */
