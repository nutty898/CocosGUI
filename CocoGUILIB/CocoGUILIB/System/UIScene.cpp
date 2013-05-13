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

#include "UIScene.h"

namespace cs {
    UIScene::UIScene():
    m_pRootWidget(NULL),
    m_bTouchAble(false),
    m_bVisible(true),
    m_bUpdateAble(true),
    m_pUISystem(NULL),
    m_updateEnableChildren(NULL)
    {
        
    }
    
    UIScene::~UIScene()
    {
        
    }
    
    void UIScene::init()
    {
        this->m_pRootWidget = CocoRootWidget::create();
        this->m_pRootWidget->setWidgetZOrder(0);
        this->m_pRootWidget->setUIScene(this);
        this->m_updateEnableChildren = cocos2d::CCArray::create();
        this->m_updateEnableChildren->retain();
    }
    
    void UIScene::addWidget(CocoWidget* widget)
    {
        this->m_pRootWidget->addChild(widget);
    }
    
    void UIScene::removeWidgetAndCleanUp(CocoWidget* widget,bool cleanup)
    {
        this->m_pRootWidget->removeChild(widget,cleanup);
    }
    
    void UIScene::setVisible(bool visible)
    {
        this->m_pRootWidget->setVisible(visible);
    }
    
    void UIScene::update(float dt)
    {
        for (int i=0;i<this->m_updateEnableChildren->count();i++){
            CocoWidget* widget = (CocoWidget*)(m_updateEnableChildren->objectAtIndex(i));
            widget->update(dt);
        }
    }
    
    void UIScene::addUpdateEnableWidget(CocoWidget* widget)
    {
        if (!widget){
            return;
        }
        if (this->m_updateEnableChildren->containsObject(widget)){
            return;
        }
        this->m_updateEnableChildren->addObject(widget);
    }
    
    void UIScene::removeUpdateEnableWidget(CocoWidget* widget)
    {
        if (!widget){
            return;
        }
        this->m_updateEnableChildren->removeObject(widget);
    }
    
    CocoWidget* UIScene::getWidgetByTag(int tag)
    {
        return this->checkWidgetByTag(this->m_pRootWidget,tag);
    }
    
    CocoWidget* UIScene::checkWidgetByTag(CocoWidget* root,int tag)
    {
        if (root->getWidgetTag() == tag){
            return root;
        }
        for (int i=0;i<root->getChildren()->count();i++){
            CocoWidget* child = (CocoWidget*)(root->getChildren()->objectAtIndex(i));
            CocoWidget* res = this->checkWidgetByTag(child,tag);
            if (res != NULL){
                return res;
            }
        }
        return NULL;
    }
    
    CocoWidget* UIScene::getWidgetByName(const char* name)
    {
        return this->checkWidgetByName(this->m_pRootWidget,name);
    }
    
    CocoWidget* UIScene::checkWidgetByName(CocoWidget* root,const char* name)
    {
        if (root->getName() == name){
            return root;
        }
        for (int i=0;i<root->getChildren()->count();i++){
            CocoWidget* child = (CocoWidget*)(root->getChildren()->objectAtIndex(i));
            CocoWidget* res = this->checkWidgetByName(child,name);
            if (res != NULL){
                return res;
            }
        }
        return NULL;
    }
    
    void UIScene::cleanScene()
    {
        if (this->m_pRootWidget){
            this->m_updateEnableChildren->removeAllObjects();
            this->m_pRootWidget->releaseResoures();
            delete this->m_pRootWidget;
            this->m_pRootWidget = NULL;
        }
    }
}