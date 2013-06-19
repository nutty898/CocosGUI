/*
 * Copyright (c) 2012 Chukong Technologies, Inc.
 *
 * http://www.sweetpome.com
 * http://tools.cocoachina.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to permit
 * persons to whom the Software is furnished to do so, subject to the
 * following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef __CocoGUI__UISystem__
#define __CocoGUI__UISystem__

#include "UIInputManager.h"
#include "UIScene.h"
#include "CSContentJsonDictionary.h"
#include "GUICCNodeLoaderLibrary.h"

#define VERSIONFORCOCOS2DX 1

#define COCOUISYSTEM cs::UISystem::shareSystem()
namespace cs {
    class InputLayer;
    class UISystem
    {
    public:
        UISystem();
        ~UISystem();
        void init();
        CocoWidget* createWidget(cocos2d::CCDictionary* data);
        CocoWidget* createWidgetFromFile(const char* fileName);
        CocoWidget* createWidget_json(cs::CSJsonDictionary* data);
        CocoWidget* createWidgetFromFile_json(const char* fileName);
        CocoWidget* createWidgetFromFileWithAdapt_json(const char* fileName, bool scaleAdapt, bool equalProportions);
        CocoWidget* createWidgetFromCCBFile(const char* fileName, GUICCNodeLoaderLibrary* ccNodeLoaderLibrary);
        CocoWidget* createWidgetFromCCBFileWithAdapt(const char* fileName, GUICCNodeLoaderLibrary* ccNodeLoaderLibrary, bool scaleAdapt, bool equalProportions);
        void adjustWidgetProperty(CocoWidget* root,float xProportion,float yProportion,bool scaleAdapt,bool equalProportions);
        
        bool replaceUISceneWithFile(cocos2d::CCNode* container,const char* fileName,int fileType,bool enableAdapt,bool scaleAdapt,bool equalProportions,int nPriority = -1);
        
        void resetSystem(cocos2d::CCNode* container,int nPriority = -1);
        void setPriority(int nPriority);
        void cleanUIScene();
        void update(float dt);
        //interface for input
        bool onTouchPressed(cocos2d::CCTouch* touch);
        bool onTouchMoved(cocos2d::CCTouch* touch);
        bool onTouchReleased(cocos2d::CCTouch* touch);
        bool onTouchCanceled(cocos2d::CCTouch* touch);
        
        static UISystem* shareSystem();
        CocoWidget* checkWidgetByName(CocoWidget* root,const char* name);
        CocoWidget* checkWidgetByTag(CocoWidget* root,int tag);
        CocoWidget* getWidgetByName(const char* name);
        CocoWidget* getWidgetByTag(int tag);
        
        void addSpriteFrame(const char* fileName);
        void removeSpriteFrame(const char* fileName);
        void removeAllSpriteFrame();
        
    private:
        void initClassType();
        void removeAllClassType();
        void removeClassType(const char* key);
    public:
        void registerClassType(CCString* classType, const char* key);
        void setClassType(CCString* classType, const char* key);
        cocos2d::CCString* getClassType(const char* key);
        
    protected:
        CC_SYNTHESIZE(UIScene*, m_pCurScene, CurScene)
        CC_SYNTHESIZE(UIInputManager*, m_pUIInputManager, UIInputManager)
        CC_SYNTHESIZE(float, m_fFileDesignWidth, FileDesignWidth)
        CC_SYNTHESIZE(float, m_fFileDesignHeight, FileDesignHeight)
        bool uiSystemInited;
        InputLayer* m_pInputLayer;
        //texture
        cocos2d::CCArray* m_textureFiles;
        
        cocos2d::CCDictionary* m_classTypeDic;
    };
}

#endif /* defined(__CocoGUI__UISystem__) */
