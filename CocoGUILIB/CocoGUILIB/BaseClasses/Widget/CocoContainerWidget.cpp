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
#include "CClipAbleLayerColor.h"
#include "CClipAbleLayerGradient.h"
#include "DictionaryHelper.h"

namespace cs {
    
    CocoContainerWidget::CocoContainerWidget():
    m_fWidth(0.0),
    m_fHeight(0.0),
    m_bClipAble(false),
    m_renderType(RENDER_TYPE_LAYERCOLOR)
    {
        this->m_nWidgetType = 1;
    }
    
    CocoContainerWidget::~CocoContainerWidget()
    {
        
    }
    
    CocoContainerWidget* CocoContainerWidget::create()
    {
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
        this->m_pCCRenderNode = CClipAbleLayerColor::create();
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
        switch (m_renderType) {
            case RENDER_TYPE_LAYERCOLOR:
                DYNAMIC_CAST_CLIPLAYERCOLOR->setClipAble(able);
                break;
            case RENDER_TYPE_LAYERGRADIENT:
                DYNAMIC_CAST_CLIPLAYERGRADIENT->setClipAble(able);
                break;
            default:
                break;
        }
        for (int i=0; i<this->m_children->count(); i++) {
            CocoWidget* child = (CocoWidget*)(this->m_children->objectAtIndex(i));
            child->setNeedCheckVisibleDepandParent(able);
        }
    }
    
    void CocoContainerWidget::setClipRect(const cocos2d::CCRect &rect)
    {
        switch (m_renderType) {
            case RENDER_TYPE_LAYERCOLOR:
                DYNAMIC_CAST_CLIPLAYERCOLOR->setClipRect(rect);
                break;
            case RENDER_TYPE_LAYERGRADIENT:
                DYNAMIC_CAST_CLIPLAYERGRADIENT->setClipRect(rect);
                break;
            default:
                break;
        }
    }
    
    void CocoContainerWidget::updateWidth()
    {

    }
    
    void CocoContainerWidget::updateHeight()
    {
        
    }

    void CocoContainerWidget::setSize(const cocos2d::CCSize &size)
    {
        switch (m_renderType) {
            case RENDER_TYPE_LAYERCOLOR:
                DYNAMIC_CAST_CLIPLAYERCOLOR->setContentSize(size);
                break;
            case RENDER_TYPE_LAYERGRADIENT:
                DYNAMIC_CAST_CLIPLAYERGRADIENT->setContentSize(size);
                break;
            default:
                break;
        }
        this->m_fWidth = size.width;
        this->m_fHeight = size.height;
        this->updateClipSize();
    }
    
    void CocoContainerWidget::setWidth(float width)
    {
        this->m_fWidth = width;
        this->setSize(cocos2d::CCSize(width,this->m_fHeight));
    }
    
    float CocoContainerWidget::getWidth()
    {
        return this->m_fWidth;
    }
    
    void CocoContainerWidget::setHeight(float height)
    {
        this->m_fHeight = height;
        this->setSize(cocos2d::CCSize(this->m_fWidth,height));
    }
    
    float CocoContainerWidget::getHeight()
    {
        return this->m_fHeight;
    }
    
    bool CocoContainerWidget::hitTest(cocos2d::CCNode *node, cocos2d::CCPoint &pt)
    {
        cocos2d::CCPoint nsp = node->convertToNodeSpace(pt);
        cocos2d::CCSize bb = node->getContentSize();
        if (nsp.x >= 0 && nsp.x <= bb.width && nsp.y >= 0 && nsp.y <= bb.height) {
            return true;
        }
        return false;
    }
    
    void CocoContainerWidget::onScaleDirtyChanged()
    {
        CocoWidget::onScaleDirtyChanged();
        this->updateClipSize();
    }
    
    void CocoContainerWidget::onScaleXDirtyChanged()
    {
        CocoWidget::onScaleXDirtyChanged();
        this->updateClipSize();
    }
    
    void CocoContainerWidget::onScaleYDirtyChanged()
    {
        CocoWidget::onScaleYDirtyChanged();
        this->updateClipSize();
    }
    
    void CocoContainerWidget::updateClipSize()
    {
        float asx = this->getAbsoluteScaleX();
        float asy = this->getAbsoluteScaleY();
        
        switch (m_renderType) {
            case RENDER_TYPE_LAYERCOLOR:
            {
                cocos2d::CCSize size = DYNAMIC_CAST_CLIPLAYERCOLOR->getContentSize();
                DYNAMIC_CAST_CLIPLAYERCOLOR->setClipSize(size.width*asx, size.height*asy);
                break;
            }
            case RENDER_TYPE_LAYERGRADIENT:
            {
                cocos2d::CCSize size = DYNAMIC_CAST_CLIPLAYERGRADIENT->getContentSize();
                DYNAMIC_CAST_CLIPLAYERGRADIENT->setClipSize(size.width*asx, size.height*asy);
                break;
            }
            default:
                break;
        }
    }        
}