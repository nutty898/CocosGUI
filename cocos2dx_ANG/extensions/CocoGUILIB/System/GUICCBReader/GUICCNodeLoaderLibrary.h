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

#ifndef __GUI_CCBI__GUICCNodeLoaderLibrary__
#define __GUI_CCBI__GUICCNodeLoaderLibrary__

#include "cocos2d.h"
#include "GUICCBReader.h"
#include "CCNodeLoaderLibrary.h"

NS_CC_EXT_BEGIN

class GUICCNodeLoader;

typedef std::map<std::string, GUICCNodeLoader *> GUICCNodeLoaderMap;
typedef std::pair<std::string, GUICCNodeLoader *> GUICCNodeLoaderMapEntry;

class GUICCNodeLoaderLibrary : public CCObject
{
private:
    GUICCNodeLoaderMap mCCNodeLoaders;
    
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

NS_CC_EXT_END

#endif /* defined(__GUI_CCBI__GUICCNodeLoaderLibrary__) */
