#ifndef __GUI_CCBI__GUICCLayerGradientLoader__
#define __GUI_CCBI__GUICCLayerGradientLoader__

#include "GUICCLayerLoader.h"

namespace cs
{
    /* Forward declaration. */
    class GUICCBReader;
    
    class GUICCLayerGradientLoader : public GUICCLayerLoader {
    public:
        virtual ~GUICCLayerGradientLoader() {};
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GUICCLayerGradientLoader, loader);
        
    protected:
        GUI_CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCLayerGradient);
        
        virtual void onHandlePropTypeColor3(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccColor3B pCCColor3B, GUICCBReader * pCCBReader);
        virtual void onHandlePropTypeByte(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, unsigned char pByte, GUICCBReader * pCCBReader);
        virtual void onHandlePropTypePoint(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCPoint pPoint, GUICCBReader * pCCBReader);
        virtual void onHandlePropTypeBlendFunc(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccBlendFunc pCCBlendFunc, GUICCBReader * pCCBReader);
    };
}

#endif /* defined(__GUI_CCBI__GUICCLayerGradientLoader__) */
