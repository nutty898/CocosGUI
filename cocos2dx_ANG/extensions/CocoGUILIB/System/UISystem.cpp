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

#include "UISystem.h"
#include "DictionaryHelper.h"
#include "InputLayer.h"
#include "CocoButton.h"
#include "CocoCheckBox.h"
#include "CocoImageView.h"
#include "CocoLabel.h"
#include "CocoLabelAtlas.h"
#include "CocoPanel.h"
#include "CocoScrollView.h"
#include "CocoLoadingBar.h"
#include "CocoSlider.h"
#include "CocoTextArea.h"
#include "CocoTextButton.h"
#include "CocoTextField.h"
#include "cocos2d.h"
#include "CCSReader.h"


NS_CC_EXT_BEGIN
    
static UISystem* sharedSystem = NULL;

UISystem* UISystem::shareSystem()
{
    if (!sharedSystem)
    {
        sharedSystem = new UISystem();
    }
    return sharedSystem;
}

UISystem::UISystem():
m_pCurScene(NULL),
m_pUIInputManager(NULL),
uiSystemInited(false),
m_pInputLayer(NULL),
m_textureFiles(NULL),
m_classTypeDic(NULL)
{
    cocos2d::CCSize winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
    this->m_fFileDesignWidth = winSize.width;
    this->m_fFileDesignHeight = winSize.height;
    this->init();
}

UISystem::~UISystem()
{
    
}

void UISystem::init()
{
    if (this->uiSystemInited)
    {
        return;
    }
    this->m_pUIInputManager = new UIInputManager();
#if VERSIONFORCOCOS2DX
    this->m_pCurScene = new UIScene();
    this->m_pCurScene->init();
    this->m_textureFiles = cocos2d::CCArray::create();
    this->m_textureFiles->retain();
    this->m_classTypeDic = CCDictionary::create();
    this->m_classTypeDic->retain();
#endif
    this->uiSystemInited = true;
}

CocoWidget* UISystem::createWidget(cocos2d::CCDictionary* data)
{
    return CCSReader::shareReader()->widgetFromCCDictionary(data);
}

CocoWidget* UISystem::createWidgetFromFile(const char *fileName)
{
    return CCSReader::shareReader()->widgetFromPlistFile(fileName);
}

CocoWidget* UISystem::createWidget_json(cs::CSJsonDictionary* data)
{
    return CCSReader::shareReader()->widgetFromJsonDictionary(data);
}

CocoWidget* UISystem::createWidgetFromFile_json(const char *fileName)
{
    return CCSReader::shareReader()->widgetFromJsonFile(fileName);
}

CocoWidget* UISystem::createWidgetFromFileWithAdapt_json(const char *fileName, bool scaleAdapt, bool equalProportions)
{
    CocoWidget* widget = this->createWidgetFromFile_json(fileName);
    cocos2d::CCSize winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
    this->adjustWidgetProperty(widget, winSize.width/this->getFileDesignWidth(),winSize.height/this->getFileDesignHeight(), scaleAdapt, equalProportions);
    return widget;
}

CocoWidget* UISystem::createWidgetFromCCBFile(const char *fileName, GUICCNodeLoaderLibrary *ccNodeLoaderLibrary)
{
    CocoWidget* widget = NULL;
    
    /* Create an autorelease GUICCBReader. */
    GUICCBReader* guiCCBReader = new GUICCBReader(ccNodeLoaderLibrary);
    widget = guiCCBReader->widgetFromCCBFile(fileName);
    CC_SAFE_DELETE(guiCCBReader);
    return widget;
}

CocoWidget* UISystem::createWidgetFromCCBFileWithAdapt(const char *fileName, GUICCNodeLoaderLibrary *ccNodeLoaderLibrary, bool scaleAdapt, bool equalProportions)
{
    CocoWidget* widget = this->createWidgetFromCCBFile(fileName, ccNodeLoaderLibrary);
    //        cocos2d::CCSize winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
    //        float compare_width = 480;
    //        float compare_height = 320;
    //        this->adjustWidgetProperty(widget, winSize.width / compare_width, winSize.height / compare_height, scaleAdapt, equalProportions);
    
    return widget;
}

void UISystem::adjustWidgetProperty(CocoWidget* root,float xProportion,float yProportion,bool scaleAdapt,bool equalProportions)
{
    switch (root->getWidgetType())
    {
        case 0:
            if (root->getWidgetParent()->getWidgetType() == 1)
            {
                if (scaleAdapt)
                {
                    if (equalProportions)
                    {
//                            root->setScale(xProportion > yProportion ? xProportion : yProportion);
                        float res = xProportion > yProportion ? xProportion : yProportion;
                        root->adaptSize(res, res);
                    }
                    else
                    {
                        root->adaptSize(xProportion, yProportion);
                    }
                }
            }
            break;
        case 1:
        {
            CocoContainerWidget* cRoot = (CocoContainerWidget*)root;
            cRoot->setSize(cocos2d::CCSize(cRoot->getWidth()*xProportion,cRoot->getHeight()*yProportion));
        }
            break;
        default:
            break;
    }
    if (!root->getWidgetParent() || root->getWidgetParent()->getWidgetType() == 1)
    {
        root->setPosition(ccp(root->getPosition().x*xProportion, root->getPosition().y*yProportion));

    }
    for (int i=0; i<root->getChildren()->count(); i++)
    {
        CocoWidget* child = (CocoWidget*)(root->getChildren()->objectAtIndex(i));
        this->adjustWidgetProperty(child,xProportion,yProportion,scaleAdapt,equalProportions);
    }
}

void UISystem::resetSystem(cocos2d::CCNode* container,int nPriority)
{
#if VERSIONFORCOCOS2DX
    if (this->m_pInputLayer)
    {
        this->m_pInputLayer->setTouchEnabled(false);
        cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this->m_pInputLayer);
        this->m_pInputLayer->unscheduleUpdate();
        this->m_pInputLayer->removeFromParentAndCleanup(true);
        this->m_pInputLayer->release();
        this->m_pInputLayer = NULL;
    }
    this->m_pInputLayer = InputLayer::createWithUISystem(this);
    this->m_pInputLayer->setTag(10000);
    this->m_pInputLayer->retain();
    this->m_pInputLayer->setTouchEnabled(true);
    cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this->m_pInputLayer, nPriority, false);
    container->addChild(this->m_pInputLayer);
    this->cleanUIScene();
    this->m_pCurScene->init();
    container->addChild(this->m_pCurScene->getRootWidget()->getContainerNode());
    
    initClassType();
#endif
}

void UISystem::setPriority(int nPriority)
{
    if (!m_pInputLayer)
    {
        return;
    }
    cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->setPriority(nPriority, this->m_pInputLayer);
}

bool UISystem::replaceUISceneWithFile(cocos2d::CCNode* container,const char *fileName,int fileType,bool enableAdapt,bool scaleAdapt,bool equalProportions,int nPriority)
{
#if VERSIONFORCOCOS2DX
    if (!fileName || strcmp(fileName, "") == 0)
    {
        return false;
    }
    if (fileType < 0 || fileType > 1)
    {
        return false;
    }
    this->resetSystem(container,nPriority);
    CocoWidget* sceneRootWidget = NULL;
    switch (fileType)
    {
        case 0:
            sceneRootWidget = this->createWidgetFromFile(fileName);
            break;
        case 1:
            sceneRootWidget = this->createWidgetFromFile_json(fileName);
            break;
        default:
            break;
    }
    this->getCurScene()->addWidget(sceneRootWidget);
    this->m_pUIInputManager->sortWidgets();
    if (enableAdapt)
    {
        cocos2d::CCSize winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
        this->adjustWidgetProperty(sceneRootWidget,winSize.width/this->getFileDesignWidth(),winSize.height/this->getFileDesignHeight(),scaleAdapt,equalProportions);
    }
#endif
    return true;
}

void UISystem::cleanUIScene()
{
#if VERSIONFORCOCOS2DX
    this->m_pCurScene->cleanScene();
    this->removeAllSpriteFrame();
    this->removeAllClassType();
#endif
}

void UISystem::update(float dt)
{
#if VERSIONFORCOCOS2DX
    this->m_pCurScene->update(dt);
#endif
}

bool UISystem::onTouchPressed(cocos2d::CCTouch* touch)
{
    return this->m_pUIInputManager->onTouchPressed(touch);
}

bool UISystem::onTouchMoved(cocos2d::CCTouch* touch)
{
    return this->m_pUIInputManager->onTouchMoved(touch);
}

bool UISystem::onTouchReleased(cocos2d::CCTouch* touch)
{
   return this->m_pUIInputManager->onTouchReleased(touch);
}

bool UISystem::onTouchCanceled(cocos2d::CCTouch* touch)
{
    return this->m_pUIInputManager->onTouchCanceled(touch);
}

CocoWidget* UISystem::checkWidgetByName(CocoWidget* root,const char* name)
{
    if (!root)
    {
        return NULL;
    }
    if (strcmp(root->getName().c_str(), name) == 0)
    {
        return root;
    }
    for (int i=0;i<root->getChildren()->count();i++)
    {
        CocoWidget* child = (CocoWidget*)(root->getChildren()->objectAtIndex(i));
        CocoWidget* res = this->checkWidgetByName(child,name);
        if (res != NULL)
        {
            return res;
        }
    }
    return NULL;
}

CocoWidget* UISystem::checkWidgetByTag(CocoWidget *root, int tag)
{
    if (!root)
    {
        return NULL;
    }
    if (root->getWidgetTag() == tag)
    {
        return root;
    }
    for (int i=0;i<root->getChildren()->count();i++)
    {
        CocoWidget* child = (CocoWidget*)(root->getChildren()->objectAtIndex(i));
        CocoWidget* res = this->checkWidgetByTag(child,tag);
        if (res != NULL)
        {
            return res;
        }
    }
    return NULL;
}

CocoWidget* UISystem::getWidgetByName(const char *name)
{
#if VERSIONFORCOCOS2DX
    return this->checkWidgetByName(this->getCurScene()->getRootWidget(), name);
#endif
}

CocoWidget* UISystem::getWidgetByTag(int tag)
{
#if VERSIONFORCOCOS2DX
    return this->checkWidgetByTag(this->getCurScene()->getRootWidget(), tag);
#endif
}

void UISystem::addSpriteFrame(const char *fileName)
{
    if (!fileName || strcmp(fileName, "") == 0)
    {
        return;
    }
    for (int i=0;i<this->m_textureFiles->count();i++)
    {
        cocos2d::CCString* file = (cocos2d::CCString*)(this->m_textureFiles->objectAtIndex(i));
        if (strcmp(file->m_sString.c_str(), fileName) == 0)
        {
            return;
        }
    }
    
    this->m_textureFiles->addObject(cocos2d::CCString::create(fileName));
    cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(fileName);
}

void UISystem::removeSpriteFrame(const char *fileName)
{
    if (!fileName || strcmp(fileName, "") == 0)
    {
        return;
    }
    for (int i=0;i<this->m_textureFiles->count();i++)
    {
        cocos2d::CCString* file = (cocos2d::CCString*)(this->m_textureFiles->objectAtIndex(i));
        if (strcmp(file->m_sString.c_str(), fileName) == 0)
        {
            cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrameByName(fileName);
            this->m_textureFiles->removeObject(file);
            return;
        }
    }
}

void UISystem::removeAllSpriteFrame()
{
    for (int i=0;i<this->m_textureFiles->count();i++)
    {
        cocos2d::CCString* file = (cocos2d::CCString*)(this->m_textureFiles->objectAtIndex(i));
        cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrameByName(file->m_sString.c_str());
    }
    this->m_textureFiles->removeAllObjects();
}

void UISystem::initClassType()
{
    setClassType(CCString::create("CCNode"), "CCNode");
    setClassType(CCString::create("CCLayer"), "CCLayer");
    setClassType(CCString::create("CCLayerColor"), "CCLayerColor");
    setClassType(CCString::create("CCLayerGradient"), "CCLayerGradient");
    setClassType(CCString::create("CCSprite"), "CCSprite");
    setClassType(CCString::create("CCLabelBMFont"), "CCLabelBMFont");
    setClassType(CCString::create("CCLabelTTF"), "CCLabelTTF");
    setClassType(CCString::create("CCScale9Sprite"), "CCScale9Sprite");
    setClassType(CCString::create("CCScrollView"), "CCScrollView");
    setClassType(CCString::create("CCMenu"), "CCMenu");
    setClassType(CCString::create("CCMenuItemImage"), "CCMenuItemImage");
    setClassType(CCString::create("CCControlButton"), "CCControlButton");
}

void UISystem::removeClassType(const char *key)
{
    if (!key || strcmp("", key) == 0)
    {
        return;
    }
    this->m_classTypeDic->removeObjectForKey(key);
}

void UISystem::removeAllClassType()
{
    this->m_classTypeDic->removeAllObjects();
}

void UISystem::registerClassType(CCString *classType, const char *key)
{
    if (!key || strcmp("", key) == 0 || !classType)
    {
        return;
    }
    this->m_classTypeDic->setObject(classType, key);
}

void UISystem::setClassType(CCString* classType, const char *key)
{
    if (!key || strcmp("", key) == 0 || !classType)
    {
        return;
    }
    this->m_classTypeDic->setObject(classType, key);
}

CCString* UISystem::getClassType(const char *key)
{
    if (!key || strcmp("", key) == 0)
    {
        return NULL;
    }
    return dynamic_cast<CCString*>(this->m_classTypeDic->objectForKey(key));
}

NS_CC_EXT_END