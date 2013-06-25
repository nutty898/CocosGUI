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

#include "UIHelper.h"
#include "DictionaryHelper.h"
#include "../Component/CocoButton.h"
#include "../Component/CocoCheckBox.h"
#include "../Component/CocoImageView.h"
#include "../Component/CocoLabel.h"
#include "../Component/CocoLabelAtlas.h"
#include "../Component/CocoPanel.h"
#include "../Component/CocoScrollView.h"
#include "../Component/CocoLoadingBar.h"
#include "../Component/CocoSlider.h"
#include "../Component/CocoTextArea.h"
#include "../Component/CocoTextButton.h"
#include "../Component/CocoTextField.h"
#include "cocos2d.h"
#include "CCSReader.h"


NS_CC_EXT_BEGIN
    
static UIHelper* helperInstance = NULL;

UIHelper* UIHelper::instance()
{
    if (!helperInstance)
    {
        helperInstance = new UIHelper();
    }
    return helperInstance;
}

UIHelper::UIHelper():
m_textureFiles(NULL)
{
    cocos2d::CCSize winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
    this->m_fFileDesignWidth = winSize.width;
    this->m_fFileDesignHeight = winSize.height;
    this->init();
}

UIHelper::~UIHelper()
{
    
}

void UIHelper::init()
{
    this->m_textureFiles = cocos2d::CCArray::create();
    this->m_textureFiles->retain();
}

CocoWidget* UIHelper::createWidget(cocos2d::CCDictionary* data)
{
    return CCSReader::shareReader()->widgetFromCCDictionary(data);
}

CocoWidget* UIHelper::createWidgetFromFile(const char *fileName)
{
    return CCSReader::shareReader()->widgetFromPlistFile(fileName);
}

CocoWidget* UIHelper::createWidget_json(cs::CSJsonDictionary* data)
{
    return CCSReader::shareReader()->widgetFromJsonDictionary(data);
}

CocoWidget* UIHelper::createWidgetFromFile_json(const char *fileName)
{
    return CCSReader::shareReader()->widgetFromJsonFile(fileName);
}

CocoWidget* UIHelper::createWidgetFromFileWithAdapt_json(const char *fileName, bool scaleAdapt, bool equalProportions)
{
    CocoWidget* widget = this->createWidgetFromFile_json(fileName);
    cocos2d::CCSize winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
    this->adjustWidgetProperty(widget, winSize.width/this->getFileDesignWidth(),winSize.height/this->getFileDesignHeight(), scaleAdapt, equalProportions);
    return widget;
}

void UIHelper::adjustWidgetProperty(CocoWidget* root,float xProportion,float yProportion,bool scaleAdapt,bool equalProportions)
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

void UIHelper::addSpriteFrame(const char *fileName)
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

void UIHelper::removeSpriteFrame(const char *fileName)
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

void UIHelper::removeAllSpriteFrame()
{
    for (int i=0;i<this->m_textureFiles->count();i++)
    {
        cocos2d::CCString* file = (cocos2d::CCString*)(this->m_textureFiles->objectAtIndex(i));
        cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrameByName(file->m_sString.c_str());
    }
    this->m_textureFiles->removeAllObjects();
}

NS_CC_EXT_END