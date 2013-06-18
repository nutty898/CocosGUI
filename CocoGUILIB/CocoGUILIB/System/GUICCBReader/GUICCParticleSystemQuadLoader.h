#ifndef __GUI_CCBI__GUICCParticleSystemQuadLoader__
#define __GUI_CCBI__GUICCParticleSystemQuadLoader__

#include "GUICCNodeLoader.h"

namespace cs
{
    /* Forward declaration. */
    class GUICCBReader;
    
    class GUICCParticleSystemQuadLoader : public GUICCNodeLoader {
    public:
        virtual ~GUICCParticleSystemQuadLoader() {};
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GUICCParticleSystemQuadLoader, loader);
        
    protected:
        GUI_CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCParticleSystemQuad);
        
        virtual void onHandlePropTypeIntegerLabeled(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, int pIntegerLabeled, GUICCBReader * pCCBReader);
        virtual void onHandlePropTypePoint(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCPoint pPoint, GUICCBReader * pCCBReader);
        virtual void onHandlePropTypeFloat(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, float pFloat, GUICCBReader * pCCBReader);
        virtual void onHandlePropTypeInteger(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, int pInteger, GUICCBReader * pCCBReader);
        virtual void onHandlePropTypeFloatVar(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, float * pFloatVar, GUICCBReader * pCCBReader);
        virtual void onHandlePropTypeColor4FVar(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccColor4F * pCCColor4FVar, GUICCBReader * pCCBReader);
        virtual void onHandlePropTypeBlendFunc(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccBlendFunc pCCBlendFunc, GUICCBReader * pCCBReader);
        virtual void onHandlePropTypeTexture(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCTexture2D * pCCTexture2D, GUICCBReader * pCCBReader);
    };
}

#endif /* defined(__GUI_CCBI__GUICCParticleSystemQuadLoader__) */
