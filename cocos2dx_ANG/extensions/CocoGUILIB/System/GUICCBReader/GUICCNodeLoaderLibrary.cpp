/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

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

NS_CC_EXT_BEGIN
    
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
    this->mCCNodeLoaders.insert(GUICCNodeLoaderMapEntry(pClassName, pCCNodeLoader));
}

void GUICCNodeLoaderLibrary::unregisterCCNodeLoader(const char * pClassName) {
    GUICCNodeLoaderMap::iterator ccNodeLoadersIterator = this->mCCNodeLoaders.find(pClassName);
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
    GUICCNodeLoaderMap::iterator ccNodeLoadersIterator = this->mCCNodeLoaders.find(pClassName);
    assert(ccNodeLoadersIterator != this->mCCNodeLoaders.end());
    return ccNodeLoadersIterator->second;
}

void GUICCNodeLoaderLibrary::purge(bool pReleaseCCNodeLoaders) {
    if(pReleaseCCNodeLoaders) {
        for(GUICCNodeLoaderMap::iterator it = this->mCCNodeLoaders.begin(); it != this->mCCNodeLoaders.end(); it++) {
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

NS_CC_EXT_END
