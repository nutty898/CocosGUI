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

#include "UIElement.h"

namespace cs {
    UIElement::UIElement():
    m_bVisible(true),
    m_pCRenderNode(NULL),
    m_pParentWidget(NULL)
    {
        
    }
    
    UIElement::~UIElement()
    {
        this->m_pCRenderNode->removeFromParentAndCleanUp(true);
    }
    
    void UIElement::init()
    {
        this->m_pCRenderNode = new CRenderNode();
        this->m_pCRenderNode->initNode(1);
    }
    
    void UIElement::releaseResoures()
    {
        
    }
    
    void UIElement::setVisible(bool visible)
    {
        if (this->m_bVisible == visible){
            return;
        }
        this->m_bVisible = visible;
        this->m_pCRenderNode->setVisible(visible);
    }
    
    bool UIElement::getVisible()
    {
        return this->m_bVisible;
    }
    
    void UIElement::setScale(float scale)
    {
        this->m_pCRenderNode->setScale(scale);
    }
    
    float UIElement::getScale()
    {
        return this->m_pCRenderNode->getScale();
    }
    
    void UIElement::setScaleX(float scaleX)
    {
        this->m_pCRenderNode->setScaleX(scaleX);
    }
    
    float UIElement::getScaleX()
    {
        return this->m_pCRenderNode->getScaleX();
    }
    
    void UIElement::setScaleY(float scaleY)
    {
        this->m_pCRenderNode->setScaleY(scaleY);
    }
    
    float UIElement::getScaleY()
    {
        return this->m_pCRenderNode->getScaleY();
    }
    
    void UIElement::setFlipX(bool flipX)
    {
        this->m_pCRenderNode->setFlipX(flipX);
    }
    
    bool UIElement::isFlipX()
    {
        return this->m_pCRenderNode->isFlipX();
    }
    
    void UIElement::setFlipY(bool flipY)
    {
        this->m_pCRenderNode->setFlipY(flipY);
    }
    
    bool UIElement::isFlipY()
    {
        return this->m_pCRenderNode->isFlipY();
    }
    
    void UIElement::setColor(int r, int g, int b)
    {
        this->m_pCRenderNode->setColor(r, g, b);
    }
    
    cocos2d::ccColor3B UIElement::getColor()
    {
        return this->m_pCRenderNode->getColor();
    }
    
    void UIElement::setOpacity(int opcity)
    {
        this->m_pCRenderNode->setOpacity(opcity);
    }
    
    int UIElement::getOpacity()
    {
        return this->m_pCRenderNode->getOpacity();
    }
    
    void UIElement::setPosition(cocos2d::CCPoint position)
    {
        this->m_pCRenderNode->setPosition(position);
    }
    
    cocos2d::CCPoint UIElement::getPosition()
    {
        return this->m_pCRenderNode->getPosition();
    }
    
    void UIElement::setAnchorPoint(cocos2d::CCPoint point)
    {
        this->m_pCRenderNode->setAnchorPoint(point);
    }
    
    cocos2d::CCPoint UIElement::getAnchorPoint()
    {
        return this->m_pCRenderNode->getAnchorPoint();
    }
    
    cocos2d::CCSize UIElement::getContentSize()
    {
        this->m_contentSize.width = this->m_pCRenderNode->getContentSizeWidth();
        this->m_contentSize.height = this->m_pCRenderNode->getContentSizeHeight();
        return this->m_contentSize;
    }
    
    float UIElement::getContentSizeWidth()
    {
        this->m_contentSize.width = this->m_pCRenderNode->getContentSizeWidth();
        return this->m_contentSize.width;
    }
    
    float UIElement::getContentSizeHeight()
    {
        this->m_contentSize.height = this->m_pCRenderNode->getContentSizeHeight();
        return this->m_contentSize.height;
    }
    
    void UIElement::update(float dt)
    {
        
    }
    
    CRenderNode* UIElement::getCRenderNode()
    {
        return this->m_pCRenderNode;
    }
}