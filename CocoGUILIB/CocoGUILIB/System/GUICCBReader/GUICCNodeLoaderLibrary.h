#ifndef __GUI_CCBI__GUICCNodeLoaderLibrary__
#define __GUI_CCBI__GUICCNodeLoaderLibrary__

#include "cocos2d.h"
#include "GUICCBReader.h"
#include "CCNodeLoaderLibrary.h"

using namespace cocos2d;
using namespace extension;

namespace cs
{
    class GUICCNodeLoader;
    
    typedef std::map<std::string, GUICCNodeLoader *> CCNodeLoaderMap;
    typedef std::pair<std::string, GUICCNodeLoader *> CCNodeLoaderMapEntry;
    
    class GUICCNodeLoaderLibrary : public CCObject
    {
    private:
        CCNodeLoaderMap mCCNodeLoaders;
        
    public:
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GUICCNodeLoaderLibrary, library);
        
        GUICCNodeLoaderLibrary();
        virtual ~GUICCNodeLoaderLibrary();
        
        void registerDefaultCCNodeLoaders();
        void registerCCNodeLoader(const char * pClassName, GUICCNodeLoader * pCCNodeLoader);
        //void registerCCNodeLoader(CCString * pClassName, CCNodeLoader * pCCNodeLoader);
        void unregisterCCNodeLoader(const char * pClassName);
        //void unregisterCCNodeLoader(CCString * pClassName);
        GUICCNodeLoader * getCCNodeLoader(const char * pClassName);
        //CCNodeLoader * getCCNodeLoader(CCString * pClassName);
        void purge(bool pDelete);
        
    public:
        static GUICCNodeLoaderLibrary * sharedCCNodeLoaderLibrary();
        static void purgeSharedCCNodeLoaderLibrary();
        
        static GUICCNodeLoaderLibrary * newDefaultCCNodeLoaderLibrary();
    };

}

#endif /* defined(__GUI_CCBI__GUICCNodeLoaderLibrary__) */
