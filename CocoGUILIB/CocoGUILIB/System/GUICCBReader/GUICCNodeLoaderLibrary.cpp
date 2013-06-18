#include "GUICCNodeLoaderLibrary.h"

#include "GUICCNodeLoader.h"
#include "GUICCLayerLoader.h"
#include "GUICCLayerColorLoader.h"
#include "GUICCLayerGradientLoader.h"
#include "GUICCLabelBMFontLoader.h"
#include "GUICCLabelTTFLoader.h"
#include "GUICCSpriteLoader.h"
#include "GUICCScale9SpriteLoader.h"
#include "GUICCBFileLoader.h"
#include "GUICCMenuLoader.h"
#include "GUICCMenuItemLoader.h"
#include "GUICCMenuItemImageLoader.h"
#include "GUICCControlButtonLoader.h"
#include "GUICCParticleSystemQuadLoader.h"
#include "GUICCScrollViewLoader.h"

#include "CCLayerLoader.h"
#include "CCLayerColorLoader.h"
#include "CCLayerGradientLoader.h"
#include "CCLabelBMFontLoader.h"
#include "CCLabelTTFLoader.h"
#include "CCSpriteLoader.h"
#include "CCScale9SpriteLoader.h"
#include "CCBFileLoader.h"
#include "CCMenuLoader.h"
#include "CCMenuItemLoader.h"
#include "CCMenuItemImageLoader.h"
#include "CCControlButtonLoader.h"
#include "CCParticleSystemQuadLoader.h"
#include "CCScrollViewLoader.h"

namespace cs
{
    using namespace cocos2d;
    using namespace extension;
    
    GUICCNodeLoaderLibrary::GUICCNodeLoaderLibrary()
    {
        
    }
    
    GUICCNodeLoaderLibrary::~GUICCNodeLoaderLibrary()
    {
        this->purge(true);
    }
    
    void GUICCNodeLoaderLibrary::registerDefaultCCNodeLoaders() {
        this->registerCCNodeLoader("CCNode", GUICCNodeLoader::loader());
        this->registerCCNodeLoader("CCLayer", GUICCLayerLoader::loader());
        this->registerCCNodeLoader("CCLayerColor", GUICCLayerColorLoader::loader());
        this->registerCCNodeLoader("CCLayerGradient", GUICCLayerGradientLoader::loader());
        this->registerCCNodeLoader("CCSprite", GUICCSpriteLoader::loader());
        this->registerCCNodeLoader("CCLabelBMFont", GUICCLabelBMFontLoader::loader());
        this->registerCCNodeLoader("CCLabelTTF", GUICCLabelTTFLoader::loader());
        this->registerCCNodeLoader("CCScale9Sprite", GUICCScale9SpriteLoader::loader());
        this->registerCCNodeLoader("CCScrollView", GUICCScrollViewLoader::loader());
        this->registerCCNodeLoader("CCBFile", GUICCBFileLoader::loader());
        this->registerCCNodeLoader("CCMenu", GUICCMenuLoader::loader());
        this->registerCCNodeLoader("CCMenuItemImage", GUICCMenuItemImageLoader::loader());
        this->registerCCNodeLoader("CCControlButton", GUICCControlButtonLoader::loader());
        this->registerCCNodeLoader("CCParticleSystemQuad", GUICCParticleSystemQuadLoader::loader());
    }
    
    void GUICCNodeLoaderLibrary::registerCCNodeLoader(const char * pClassName, GUICCNodeLoader * pCCNodeLoader) {
        pCCNodeLoader->retain();
        this->mCCNodeLoaders.insert(CCNodeLoaderMapEntry(pClassName, pCCNodeLoader));
    }
    
    void GUICCNodeLoaderLibrary::unregisterCCNodeLoader(const char * pClassName) {
        CCNodeLoaderMap::iterator ccNodeLoadersIterator = this->mCCNodeLoaders.find(pClassName);
        if (ccNodeLoadersIterator != this->mCCNodeLoaders.end())
        {
            ccNodeLoadersIterator->second->release();
            mCCNodeLoaders.erase(ccNodeLoadersIterator);
        }
        else
        {
            CCLOG("The loader (%s) doesn't exist", pClassName);
        }
    }
    
    GUICCNodeLoader * GUICCNodeLoaderLibrary::getCCNodeLoader(const char* pClassName) {
        CCNodeLoaderMap::iterator ccNodeLoadersIterator = this->mCCNodeLoaders.find(pClassName);
        assert(ccNodeLoadersIterator != this->mCCNodeLoaders.end());
        return ccNodeLoadersIterator->second;
    }
    
    void GUICCNodeLoaderLibrary::purge(bool pReleaseCCNodeLoaders) {
        if(pReleaseCCNodeLoaders) {
            for(CCNodeLoaderMap::iterator it = this->mCCNodeLoaders.begin(); it != this->mCCNodeLoaders.end(); it++) {
                it->second->release();
            }
        }
        this->mCCNodeLoaders.clear();
    }
    
    
    
    static GUICCNodeLoaderLibrary * sSharedCCNodeLoaderLibrary = NULL;
    
    GUICCNodeLoaderLibrary * GUICCNodeLoaderLibrary::sharedCCNodeLoaderLibrary() {
        if(sSharedCCNodeLoaderLibrary == NULL) {
            sSharedCCNodeLoaderLibrary = new GUICCNodeLoaderLibrary();
            
            sSharedCCNodeLoaderLibrary->registerDefaultCCNodeLoaders();
        }
        return sSharedCCNodeLoaderLibrary;
    }
    
    void GUICCNodeLoaderLibrary::purgeSharedCCNodeLoaderLibrary() {
        CC_SAFE_DELETE(sSharedCCNodeLoaderLibrary);
    }
    
    GUICCNodeLoaderLibrary * GUICCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary() {
        GUICCNodeLoaderLibrary * ccNodeLoaderLibrary = GUICCNodeLoaderLibrary::library();
        
        ccNodeLoaderLibrary->registerDefaultCCNodeLoaders();
        
        return ccNodeLoaderLibrary;
    }
}
