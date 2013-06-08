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

#include "CocoContainerWidget.h"
#include "DictionaryHelper.h"

namespace cs {
    
    CocoContainerWidget::CocoContainerWidget():
    m_fWidth(0.0),
    m_fHeight(0.0),
    m_bClipAble(false)
    {
        this->m_nWidgetType = 1;
    }
    
    CocoContainerWidget::~CocoContainerWidget()
    {
        
    }
    
    CocoContainerWidget* CocoContainerWidget::create()
    {
//        return CocoContainerWidget::create(NULL);
        CocoContainerWidget* widget = new CocoContainerWidget();
        if (widget && widget->init()) {
            return widget;
        }
        CC_SAFE_DELETE(widget);
        return NULL;
    }
    
    void CocoContainerWidget::setLayoutParameter(/*LayoutParameter * parmeter*/)
    {
        
    }
    
    bool CocoContainerWidget::init()
    {
        if (CocoWidget::init()) {
            return true;
        }
        return false;
    }
    
    void CocoContainerWidget::initNodes()
    {
        this->m_pCContainerNode = new CRenderNode();
        this->m_pCContainerNode->initNode(8);
        this->m_pCContainerNode->setZOrder(this->m_nWidgetZOrder);
    }
    
    bool CocoContainerWidget::getClipAble()
    {
        return this->m_bClipAble;
    }
    
    bool CocoContainerWidget::addChild(CocoWidget* child)
    {   
        CocoWidget::addChild(child);
        bool needSetChildCheckAble = false;
        CocoWidget* parent = this;
        while (parent != 0){
            if (parent->getClipAble()){
                needSetChildCheckAble = true;
                break;
            }
            parent = parent->getWidgetParent();
        }
        
        if (needSetChildCheckAble){
            child->setNeedCheckVisibleDepandParent(true);
        }
        return true;
    }
    
    void CocoContainerWidget::setClipAble(bool able)
    {
        this->m_bClipAble = able;
        this->m_pCContainerNode->setClipAble(able);
        for (int i=0; i<this->m_children->count(); i++) {
            CocoWidget* child = (CocoWidget*)(this->m_children->objectAtIndex(i));
            child->setNeedCheckVisibleDepandParent(able);
        }
    }
    
    void CocoContainerWidget::setClipRect(cocos2d::CCRect rect)
    {
        this->m_pCContainerNode->setClipRect(rect.origin.x,rect.origin.y,rect.size.width,rect.size.height);
    }
    
    void CocoContainerWidget::updateWidth()
    {

    }
    
    void CocoContainerWidget::updateHeight()
    {
        
    }
    
    void CocoContainerWidget::setColorAndSize(int r,int g,int b,int o,float width,float height)
    {
        this->m_pCContainerNode->setColorAndSize(r,g,b,o,width,height);
        this->m_fWidth = width;
        this->m_fHeight = height;
        this->updateClipSize();
    }
    
    void CocoContainerWidget::setSize(float width,float height)
    {
        this->m_pCContainerNode->setSize(width,height);
        this->m_fWidth = width;
        this->m_fHeight = height;
        this->updateClipSize();
    }
    
    void CocoContainerWidget::setWidth(float width)
    {
        this->m_fWidth = width;
        this->setSize(this->m_fWidth,this->m_fHeight);
    }
    
    float CocoContainerWidget::getWidth()
    {
        return this->m_fWidth;
    }
    
    void CocoContainerWidget::setHeight(float height)
    {
        this->m_fHeight = height;
        this->setSize(this->m_fWidth,this->m_fHeight);
    }
    
    float CocoContainerWidget::getHeight()
    {
        return this->m_fHeight;
    }
    
    void CocoContainerWidget::setColor(int r, int g, int b)
    {
        this->m_pCContainerNode->setColor(r, g, b);
    }
    
    void CocoContainerWidget::setOpacity(int opacity)
    {
        this->m_pCContainerNode->setOpacity(opacity);
        this->m_bOpacityDirty = true;
        this->updateChildrenOpacityDirty(this->m_bOpacityDirty);
    }    

    bool CocoContainerWidget::pointAtSelfBody(cocos2d::CCPoint &pt)
    {
        if (!this->getAbsoluteVisible()) {
            return false;
        }
        CRenderNode* validNode = this->getValidNode();
        return validNode->hitTest2(pt);
    }
    
    void CocoContainerWidget::setScale(float scale)
    {
        CocoWidget::setScale(scale);
        this->updateClipSize();
    }
    
    void CocoContainerWidget::setScaleX(float scaleX)
    {
        CocoWidget::setScaleX(scaleX);
        this->updateClipSize();
    }
    
    void CocoContainerWidget::setScaleY(float scaleY)
    {
        CocoWidget::setScaleY(scaleY);
        this->updateClipSize();
    }
    
    void CocoContainerWidget::updateChildrenScaleXDirty(bool dirty)
    {
        CocoWidget::updateChildrenScaleXDirty(dirty);
        this->updateClipSize();
    }
    
    void CocoContainerWidget::updateChildrenScaleYDirty(bool dirty)
    {
        CocoWidget::updateChildrenScaleYDirty(dirty);
        this->updateClipSize();
    }
    
    void CocoContainerWidget::updateClipSize()
    {
        float asx = this->getAbsoluteScaleX();
        float asy = this->getAbsoluteScaleY();
        cocos2d::CCSize size = this->m_pCContainerNode->getContentSize();
        this->m_pCContainerNode->setClipSize(size.width*asx, size.height*asy);
    }
}