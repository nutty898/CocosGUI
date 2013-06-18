#ifndef __GUI_CCBI__GUICCMenuLoader__
#define __GUI_CCBI__GUICCMenuLoader__

#include "GUICCLayerLoader.h"

namespace cs
{
    /* Forward declaration. */
    class GUICCBReader;
    
    class GUICCMenuLoader : public GUICCLayerLoader {
    public:
        virtual ~GUICCMenuLoader() {};
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GUICCMenuLoader, loader);
        
    protected:
        GUI_CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCMenu);
    };
}

#endif /* defined(__GUI_CCBI__GUICCMenuLoader__) */
