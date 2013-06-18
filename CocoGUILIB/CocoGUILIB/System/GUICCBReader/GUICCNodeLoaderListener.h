#ifndef __GUI_CCBI__GUICCNodeLoaderListener__
#define __GUI_CCBI__GUICCNodeLoaderListener__

#include "cocos2d.h"
#include "GUICCNodeLoader.h"

namespace cs
{
    using namespace cocos2d;
    
    class GUICCNodeLoaderListener
    {
    public:
        virtual ~GUICCNodeLoaderListener() {};
        
        virtual void onNodeLoaded(CCNode * pNode, GUICCNodeLoader * pNodeLoader) = 0;
    };
}

#endif /* defined(__GUI_CCBI__GUICCNodeLoaderListener__) */
