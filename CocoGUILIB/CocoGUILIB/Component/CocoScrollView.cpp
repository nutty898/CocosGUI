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

#include "CocoScrollView.h"
#include "DictionaryHelper.h"
namespace cs
{
    CocoScrollView::CocoScrollView():
    m_eDirection(SCROLLVIEW_DIR_VERTICAL),
    m_eMoveDirection(SCROLLVIEW_MOVE_DIR_NONE),
    m_nDirection(0),
    m_fTouchStartLocation(0.0),
    m_fTouchEndLocation(0.0),
    m_fTouchMoveStartLocation(0.0),
    m_fTopBoundary(0.0),
    m_fBottomBoundary(0.0),
    m_fLeftBoundary(0.0),
    m_fRightBoundary(0.0),
    m_pTopChild(NULL),
    m_pBottomChild(NULL),
    m_pLeftChild(NULL),
    m_pRightChild(NULL),
    m_nHandleState(0),
    m_nMoveDirection(0),
    m_bTopEnd(false),
    m_bBottomEnd(false),
    m_bLeftEnd(false),
    m_bRightEnd(false),
    m_bBerthToTop(false),
    m_bBerthToBottom(false),
    m_bBerthToLeft(false),
    m_bBerthToRight(false),
    m_bBerthToVerticalCenter(false),
    m_bBerthToHorizontalCenter(false),
    m_bAutoScroll(false),
    m_fAutoScrollOriginalSpeed(0.0),
    m_fAutoScrollAcceleration(600.0),
    m_bBePressed(false),
    m_fSlidTime(0.0),
    m_fChildrenSizeHeight(0.0),
    m_fChildrenSizeWidth(0.0),
    m_fChildFocusCancelOffset(5.0),
    m_eMoveMode(SCROLLVIEW_MOVE_MODE_NORMAL),
    isRunningAction(false),
    m_eBerthOrientation(SCROLLVIEW_BERTH_ORI_TOP),
    m_fDisBoundaryToChild_0(0.0),
    m_fDisBetweenChild(0.0),
    m_fDragForce(0.0),
    m_pScrollToTopListener(NULL),
    m_pfnScrollToTopSelector(NULL),
    m_pScrollToBottomListener(NULL),
    m_pfnScrollToBottomSelector(NULL),
    m_pScrollToLeftListener(NULL),
    m_pfnScrollToLeftSelector(NULL),
    m_pScrollToRightListener(NULL),
    m_pfnScrollToRightSelector(NULL),
    m_pBerthToTopListener(NULL),
    m_pfnBerthToTopSelector(NULL),
    m_pBerthToBottomListener(NULL),
    m_pfnBerthToBottomSelector(NULL),
    m_pBerthToVerticalCenterListener(NULL),
    m_pfnBerthToVerticalCenterSelector(NULL),
    m_pBerthToLeftListener(NULL),
    m_pfnBerthToLeftSelector(NULL),
    m_pBerthToRightListener(NULL),
    m_pfnBerthToRightSelector(NULL),
    m_pBerthToHorizontalCenterListener(NULL),
    m_pfnBerthToHorizontalCenterSelector(NULL)
    {
        
    }
    
    CocoScrollView::~CocoScrollView()
    {
        
    }
    
    CocoScrollView* CocoScrollView::create()
    {
//        return CocoScrollView::create(NULL);
        CocoScrollView* widget = new CocoScrollView();
        if (widget && widget->init())
        {
            return widget;
        }
        CC_SAFE_DELETE(widget);
        return NULL;
    }
    
    bool CocoScrollView::init()
    {
        if (CocoPanel::init())
        {
            return true;
        }
        return false;
    }

    void CocoScrollView::setColorAndSize(int r, int g, int b, int o, float width, float height)
    {
        CocoPanel::setColorAndSize(r, g, b, o, width, height);
        this->m_fTopBoundary = height;
        this->m_fRightBoundary = width;
        
        switch (m_eDirection)
        {
            case SCROLLVIEW_DIR_VERTICAL: // vertical
                m_fDragForce = height / 8 * 5;
                break;
                
            case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
                m_fDragForce = width / 8 * 5;
                break;
                
            default:
                break;
        }
    }
    
    void CocoScrollView::setSize(float width, float height)
    {
        CocoPanel::setSize(width, height);
        this->m_fTopBoundary = height;
        this->m_fRightBoundary = width;
        
        switch (m_eDirection)
        {
            case SCROLLVIEW_DIR_VERTICAL: // vertical
                m_fDragForce = height / 8 * 5;
                break;
                
            case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
                m_fDragForce = width / 8 * 5;
                break;
                
            default:
                break;
        }
    }
    
    bool CocoScrollView::addChild(CocoWidget* widget)
    {
        if (this->m_children->count() <= 0)
        {
            this->m_pTopChild = widget;
            this->m_pBottomChild = widget;
            this->m_pLeftChild = widget;
            this->m_pRightChild = widget;
        }
        else
        {
            if (widget->getRelativeRect().origin.y + widget->getRelativeRect().size.height > this->m_pTopChild->getRelativeRect().origin.y + this->m_pTopChild->getRelativeRect().size.height)
            {
                this->m_pTopChild = widget;
            }
            if (widget->getRelativeRect().origin.y < this->m_pBottomChild->getRelativeRect().origin.y)
            {
                this->m_pBottomChild = widget;
            }
            if (widget->getRelativeRect().origin.x + widget->getRelativeRect().size.width > this->m_pRightChild->getRelativeRect().origin.x + this->m_pRightChild->getRelativeRect().size.width)
            {
                this->m_pRightChild = widget;
            }
            if (widget->getRelativeRect().origin.x < this->m_pLeftChild->getRelativeRect().origin.x)
            {
                this->m_pLeftChild = widget;
            }
        }
        this->m_fChildrenSizeHeight = this->m_pTopChild->getRelativeTopPos()-this->m_pBottomChild->getRelativeBottomPos();
        this->m_fChildrenSizeWidth = this->m_pRightChild->getRelativeRightPos()-this->m_pLeftChild->getRelativeLeftPos();
        CocoPanel::addChild(widget);
        widget->setVisible(widget->checkBeVisibleInParent());
        
        this->initProperty();
        
        return true;
    }
    
    void CocoScrollView::removeChildMoveToTrash(CocoWidget* child)
    {
        if (!child)
        {
            return;
        }
        CocoPanel::removeChildMoveToTrash(child);
        this->resortChildren();
    }
    
    void CocoScrollView::removeChildReferenceOnly(CocoWidget* child)
    {
        if (!child)
        {
            return;
        }
        CocoPanel::removeChildReferenceOnly(child);
        this->resortChildren();
    }
    
    void CocoScrollView::removeAllChildrenAndCleanUp(bool cleanup)
    {
        CocoPanel::removeAllChildrenAndCleanUp(cleanup);
        this->m_pTopChild = NULL;
        this->m_pBottomChild = NULL;
        this->m_pLeftChild = NULL;
        this->m_pRightChild = NULL;
    }
    
    void CocoScrollView::initProperty()
    {
        switch (m_children->count())
        {
            case 1:
                {
                    CocoWidget* child_0 = dynamic_cast<CocoWidget*>(m_children->objectAtIndex(0));
                    
                    switch (m_eDirection)
                    {
                        case SCROLLVIEW_DIR_VERTICAL: // vertical
                            {
                                float scroll_top = m_fTopBoundary;
                                float child_0_top = child_0->getRelativeTopPos();
                                float offset = scroll_top - child_0_top;
                                m_fDisBoundaryToChild_0 = (offset > 0) ? offset : 0;
                            }
                            break;
                            
                        case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
                            {
                                float scroll_left = m_fLeftBoundary;
                                float child_0_left = child_0->getRelativeLeftPos();
                                float offset = child_0_left - scroll_left;
                                m_fDisBoundaryToChild_0 = (offset > 0) ? offset : 0;
                            }
                            break;
                            
                        default:
                            break;
                    }
                }
                break;
                
            default:
                resetProperty();
                break;
        }
    }
    
    void CocoScrollView::resetProperty()
    {
        float scroll_top = m_fTopBoundary;
        float scroll_left = m_fLeftBoundary;
        
        switch (m_children->count())
        {
            case 1:
                {
                    CocoWidget* child_0 = dynamic_cast<CocoWidget*>(m_children->objectAtIndex(0));
                    
                    switch (m_eDirection)
                    {
                        case SCROLLVIEW_DIR_VERTICAL: // vertical
                            {
                                float child_0_top = child_0->getRelativeTopPos();
                                float offset = scroll_top - child_0_top;
                                m_fDisBoundaryToChild_0 = (offset > 0) ? offset : 0;
                            }
                            break;
                            
                        case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
                            {
                                float child_0_left = child_0->getRelativeLeftPos();
                                float offset = child_0_left - scroll_left;
                                m_fDisBoundaryToChild_0 = (offset > 0) ? offset : 0;
                            }
                            break;
                            
                        default:
                            break;
                    }
                }
                break;
                
            default:
                {
                    CocoWidget* child_0 = dynamic_cast<CocoWidget*>(m_children->objectAtIndex(0));
                    CocoWidget* child_1 = dynamic_cast<CocoWidget*>(m_children->objectAtIndex(1));
                    
                    switch (m_eDirection)
                    {
                        case SCROLLVIEW_DIR_VERTICAL: // vertical
                            {
                                float child_0_top = child_0->getRelativeTopPos();
                                float offset = scroll_top - child_0_top;
                                m_fDisBoundaryToChild_0 = (offset > 0) ? offset : 0;
                                m_fDisBetweenChild = child_0->getPosition().y - child_1->getPosition().y;
                            }
                            break;
                            
                        case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
                            {
                                float child_0_left = child_0->getRelativeLeftPos();
                                float offset = child_0_left - scroll_left;
                                m_fDisBoundaryToChild_0 = (offset > 0) ? offset : 0;
                                m_fDisBetweenChild = child_1->getPosition().x - child_0->getPosition().x;
                            }
                            break;
                            
                        default:
                            break;
                    }
                }
                break;
        }
    }
    /**/
    
    void CocoScrollView::resortChildren()
    {
        if (!this->m_children || this->m_children->count() <= 0)
        {
            return;
        }
        CocoWidget* leftChild = (CocoWidget*)(this->m_children->objectAtIndex(0));
        CocoWidget* rightChild = (CocoWidget*)(this->m_children->objectAtIndex(0));
        CocoWidget* topChild = (CocoWidget*)(this->m_children->objectAtIndex(0));
        CocoWidget* bottomChild = (CocoWidget*)(this->m_children->objectAtIndex(0));
        for (int i = 0; i < this->m_children->count(); i++)
        {
            CocoWidget* child = (CocoWidget*)(this->m_children->objectAtIndex(i));
            if (leftChild->getRelativeRect().origin.x > child->getRelativeRect().origin.x)
            {
                leftChild = child;
            }
            if (rightChild->getRelativeRect().origin.x + rightChild->getRelativeRect().size.width < child->getRelativeRect().origin.x + child->getRelativeRect().size.width)
            {
                rightChild = child;
            }
            if (topChild->getRelativeRect().origin.y + topChild->getRelativeRect().size.height < child->getRelativeRect().origin.y + child->getRelativeRect().size.height)
            {
                topChild = child;
            }
            if (bottomChild->getRelativeRect().origin.y > child->getRelativeRect().origin.y){
                bottomChild = child;
            }
        }
        this->m_pTopChild = topChild;
        this->m_pBottomChild = bottomChild;
        this->m_pLeftChild = leftChild;
        this->m_pRightChild = rightChild;
    }
    
    void CocoScrollView::moveChildren(float offset)
    {
        switch (this->m_eDirection)
        {
            case SCROLLVIEW_DIR_VERTICAL: // vertical
                for (int i = 0; i < this->m_children->count(); i++)
                {
                    CocoWidget* child = (CocoWidget*)(this->m_children->objectAtIndex(i));
                    this->moveChildPoint.x = child->getPosition().x;
                    this->moveChildPoint.y = child->getPosition().y + offset;
                    child->setPosition(this->moveChildPoint);
                    child->setVisible(child->checkBeVisibleInParent());
                }
                break;
                
            case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
                for (int i=0;i<this->m_children->count();i++)
                {
                    CocoWidget* child = (CocoWidget*)(this->m_children->objectAtIndex(i));
                    this->moveChildPoint.x = child->getPosition().x + offset;
                    this->moveChildPoint.y = child->getPosition().y;
                    child->setPosition(this->moveChildPoint);
                    child->setVisible(child->checkBeVisibleInParent());
                }
                break;
                
            default:
                break;
        }
    }
    
    void CocoScrollView::autoScrollChildren(float dt)
    {
        switch (this->m_eDirection)
        {
            case SCROLLVIEW_DIR_VERTICAL: // vertical
                switch (this->m_eMoveDirection)
                {                        
                    case SCROLLVIEW_MOVE_DIR_UP: // up
                        {
                            float curDis = this->getCurAutoScrollDistance(dt);
                            if (curDis <= 0)
                            {
                                curDis = 0;
                                this->stopAutoScrollChildren();
                            }
                            if (!this->scrollChildren(curDis))
                            {
                                this->stopAutoScrollChildren();
                                
                                if (m_eMoveMode == SCROLLVIEW_MOVE_MODE_ACTION)
                                {
                                    resetPositionWithAction();
                                }
                            }
                        }
                        break;
                        
                    case SCROLLVIEW_MOVE_DIR_DOWN: // down
                        {
                            float curDis = this->getCurAutoScrollDistance(dt);
                            if (curDis <= 0)
                            {
                                curDis = 0;
                                this->stopAutoScrollChildren();
                            }
                            if (!this->scrollChildren(-curDis))
                            {
                                this->stopAutoScrollChildren();
                                
                                if (m_eMoveMode == SCROLLVIEW_MOVE_MODE_ACTION)
                                {
                                    resetPositionWithAction();
                                }
                            }
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
                switch (this->m_eMoveDirection)
                {
                    case SCROLLVIEW_MOVE_DIR_LEFT: // left
                        {
                            float curDis = this->getCurAutoScrollDistance(dt);
                            if (curDis <= 0)
                            {
                                curDis = 0;
                                this->stopAutoScrollChildren();
                            }
                            if (!this->scrollChildren(-curDis))
                            {
                                this->stopAutoScrollChildren();
                                
                                if (m_eMoveMode == SCROLLVIEW_MOVE_MODE_ACTION)
                                {
                                    resetPositionWithAction();
                                }
                            }
                        }
                        break;
                        
                    case SCROLLVIEW_MOVE_DIR_RIGHT: // right
                        {
                            float curDis = this->getCurAutoScrollDistance(dt);
                            if (curDis <= 0)
                            {
                                curDis = 0;
                                this->stopAutoScrollChildren();
                            }
                            if (!this->scrollChildren(curDis))
                            {
                                this->stopAutoScrollChildren();
                                
                                if (m_eMoveMode == SCROLLVIEW_MOVE_MODE_ACTION)
                                {
                                    resetPositionWithAction();
                                }
                            }
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            default:
                break;
        }
    }
    
    void CocoScrollView::startAutoScrollChildren(float v)
    {
        this->m_fAutoScrollOriginalSpeed = v;
        this->m_bAutoScroll = true;
    }
    
    void CocoScrollView::stopAutoScrollChildren()
    {
        this->m_bAutoScroll = false;
        this->m_fAutoScrollOriginalSpeed = 0.0;
    }
    
    float CocoScrollView::getCurAutoScrollDistance(float time)
    {
        float dt = time;
        this->m_fAutoScrollOriginalSpeed -= this->m_fAutoScrollAcceleration*dt;
        float distance = this->m_fAutoScrollOriginalSpeed*dt;
        distance = MIN(distance, m_fDisBetweenChild);
        return distance;
    }
    
    void CocoScrollView::resetPositionWithAction()
    {
        using namespace cocos2d;
        CCPoint delta = CCPointZero;
        CocoWidget* child = getCheckPositionChild();
        
        switch (m_eDirection)
        {
            case SCROLLVIEW_DIR_VERTICAL: // vertical
                switch (m_eMoveDirection)
                {
                    case SCROLLVIEW_MOVE_DIR_UP: // up
                        delta.y = m_fBottomBoundary + m_fDisBoundaryToChild_0 - child->getRelativeBottomPos();;
                        break;
                        
                    case SCROLLVIEW_MOVE_DIR_DOWN: // down
                        delta.y = m_fTopBoundary - m_fDisBoundaryToChild_0 - child->getRelativeTopPos();
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
                switch (m_eMoveDirection)
                {
                    case SCROLLVIEW_MOVE_DIR_LEFT: // left
                        delta.x = m_fRightBoundary - m_fDisBoundaryToChild_0 - child->getRelativeRightPos();
                        break;
                        
                    case SCROLLVIEW_MOVE_DIR_RIGHT: // right
                        delta.x = m_fLeftBoundary + m_fDisBoundaryToChild_0 - child->getRelativeLeftPos();
                        break;
                        
                    default:
                        break;
                }
                break;
                
            default:
                break;
        }
        
        int times = m_children->count();
        for (int i = 0; i < times - 1; ++i)
        {
            CocoWidget* child = dynamic_cast<CocoWidget*>(m_children->objectAtIndex(i));
            CCMoveBy* moveBy = CCMoveBy::create(0.25, delta);
            CCEaseOut* ease = CCEaseOut::create(moveBy, 0.5);
            child->runAction(ease);
        }
        
        CocoWidget* child_last = dynamic_cast<CocoWidget*>(m_children->lastObject());
        CCMoveBy* moveBy = CCMoveBy::create(0.25, delta);
        CCEaseOut* ease = CCEaseOut::create(moveBy, 0.5);
        CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(CocoScrollView::handleScrollActionEvent));
        CCSequence* seq = CCSequence::create(ease, callFunc, NULL);
        child_last->runAction(seq);
        
        isRunningAction = true;
    }
    
    CocoWidget* CocoScrollView::getCheckPositionChild()
    {
        CocoWidget* child = NULL;
        
        switch (m_eDirection)
        {
            case SCROLLVIEW_DIR_VERTICAL: // vertical
                switch (m_eMoveDirection)
                {
                    case SCROLLVIEW_MOVE_DIR_UP: // up
                        child = dynamic_cast<CocoWidget*>(m_children->lastObject());
                        break;
                        
                    case SCROLLVIEW_MOVE_DIR_DOWN: // down
                        child = dynamic_cast<CocoWidget*>(m_children->objectAtIndex(0));
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
                switch (m_eMoveDirection)
                {
                    case SCROLLVIEW_MOVE_DIR_LEFT: // left
                        child = dynamic_cast<CocoWidget*>(m_children->lastObject());
                        break;
                        
                    case SCROLLVIEW_MOVE_DIR_RIGHT: // right
                        child = dynamic_cast<CocoWidget*>(m_children->objectAtIndex(0));
                        break;
                        
                    default:
                        break;
                }
                break;
                
            default:
                break;
        }
        
        return child;
    }
    
    void CocoScrollView::handleScrollActionEvent()
    {
        switch (m_eDirection)
        {
            case SCROLLVIEW_DIR_VERTICAL: // vertical
                switch (m_eMoveDirection)
                {
                    case SCROLLVIEW_MOVE_DIR_UP: // up
                        scrollToBottomEvent();
                        break;
                        
                    case SCROLLVIEW_MOVE_DIR_DOWN: // down
                        scrollToTopEvent();
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
                switch (m_eMoveDirection)
                {
                    case SCROLLVIEW_MOVE_DIR_LEFT: // left
                        scrollToRightEvent();
                        break;
                        
                    case SCROLLVIEW_MOVE_DIR_RIGHT: // right
                        scrollToLeftEvent();
                        break;
                        
                    default:
                        break;
                }
                break;
                
            default:
                break;
        }
        
        isRunningAction = false;
    }
    
    float CocoScrollView::calculateOffsetWithDragForce(float moveOffset)
    {
        float offset = moveOffset;
        CocoWidget* child = getCheckPositionChild();
        
        switch (m_eDirection)
        {
            case SCROLLVIEW_DIR_VERTICAL: // vertical
                switch (m_eMoveDirection)
                {
                    case SCROLLVIEW_MOVE_DIR_UP: // up
                        {
                            float scroll_bottom = m_fBottomBoundary;
                            float child_bottom = child->getRelativeBottomPos();
                            
                            if (child_bottom > scroll_bottom)
                            {
                                offset -= m_fDragForce * offset / m_fHeight;
                            }
                        }
                        break;
                        
                    case SCROLLVIEW_MOVE_DIR_DOWN: // down
                        {
                            float scroll_top = m_fTopBoundary;
                            float child_top = child->getRelativeTopPos();
                            
                            if (child_top < scroll_top)
                            {
                                offset -= m_fDragForce * offset / m_fHeight;
                            }
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
                switch (m_eMoveDirection)
                {
                    case SCROLLVIEW_MOVE_DIR_LEFT: // left
                        {
                            float scroll_right = m_fRightBoundary;
                            float child_right = child->getRelativeRightPos();
                            
                            if (child_right < scroll_right)
                            {
                                offset -= m_fDragForce * offset / m_fWidth;
                            }
                        }
                        break;
                        
                    case SCROLLVIEW_MOVE_DIR_RIGHT: // right
                        {
                            float scroll_left = m_fLeftBoundary;
                            float child_left = child->getRelativeLeftPos();
                            
                            if (child_left > scroll_left)
                            {
                                offset -= m_fDragForce * offset / m_fWidth;
                            }
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            default:
                break;
        }
        
        offset = MIN(offset, m_fDisBetweenChild);
        
        return offset;
    }
    
    void CocoScrollView::berthChildren(SCROLLVIEW_DIR direction)
    {
        switch (direction)
        {
            case SCROLLVIEW_DIR_VERTICAL: // vertical
                switch (m_eBerthOrientation)
                {
                    case SCROLLVIEW_BERTH_ORI_TOP : // berth top
                        moveChildren(m_fTopBoundary - m_pTopChild->getRelativeTopPos());
                        
                        if (!m_bBerthToTop)
                        {
                            berthToTopEvent();
                        }
                        m_bBerthToTop = true;
                        break;
                        
                    case SCROLLVIEW_BERTH_ORI_BOTTOM: // berth bottom
                        moveChildren(m_fBottomBoundary - m_pBottomChild->getRelativeBottomPos());
                        
                        if (!m_bBerthToBottom)
                        {
                            berthToBottomEvent();
                        }
                        m_bBerthToBottom = true;
                        break;
                        
                    case SCROLLVIEW_BERTH_ORI_VERTICAL_CENTER: // berth vertical center
                        {
                            float offset = (m_fHeight - m_fChildrenSizeHeight) * 0.5;
                            float distance = (m_fHeight - offset) - m_pTopChild->getRelativeTopPos();
                            moveChildren(distance);
                            
                            if (!m_bBerthToVerticalCenter)
                            {
                                berthToVerticalCenterEvent();
                            }
                            m_bBerthToVerticalCenter = true;
                        }
                        break;
                        
                    default:
                        break;
                }
                m_bBerthToTop = false;
                m_bBerthToBottom = false;
                m_bBerthToVerticalCenter = false;
                break;
                
            case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
                switch (m_eBerthOrientation)
                {
                    case SCROLLVIEW_BERTH_ORI_LEFT: // berth left
                        moveChildren(m_fLeftBoundary - m_pLeftChild->getRelativeLeftPos());
                        
                        if (!m_bBerthToLeft)
                        {
                            berthToLeftEvent();
                        }
                        m_bBerthToLeft = true;
                        break;
                        
                    case SCROLLVIEW_BERTH_ORI_RIGHT: // berth right
                        moveChildren(m_fRightBoundary - m_pRightChild->getRelativeRightPos());
                        
                        if (!m_bBerthToRight)
                        {
                            berthToRightEvent();
                        }
                        m_bBerthToRight = true;
                        break;
                        
                    case SCROLLVIEW_BERTH_ORI_HORIZONTAL_CENTER: // berth horizontal center
                        {
                            float offset = (m_fWidth - m_fChildrenSizeWidth) * 0.5;
                            float distance = (m_fWidth - offset) - m_pRightChild->getRelativeRightPos();
                            moveChildren(distance);
                            
                            if (!m_bBerthToHorizontalCenter)
                            {
                                berthToHorizontalCenterEvent();
                            }
                            m_bBerthToHorizontalCenter = true;
                        }
                        break;
                        
                    default:
                        break;
                }
                m_bBerthToLeft = false;
                m_bBerthToRight = false;
                m_bBerthToHorizontalCenter = false;
                break;
                
            default:
                break;
        }
    }
    
    bool CocoScrollView::scrollChildren(float touchOffset)
    {
        if (m_children->count() <= 0)
        {
            return false;
        }
        
        float realOffset = touchOffset;
        
        switch (m_eDirection)
        {
            case SCROLLVIEW_DIR_VERTICAL: // vertical
                if (m_fChildrenSizeHeight <= m_fHeight)
                {
                    berthChildren(m_eDirection);
                    
                    return false;
                }
                
                switch (m_eMoveDirection)
                {                        
                    case SCROLLVIEW_MOVE_DIR_UP: // up
                        if (!m_pBottomChild)
                        {
                            return false;
                        }
                        
                        switch (m_eMoveMode)
                        {
                            case SCROLLVIEW_MOVE_MODE_NORMAL: // normal
                                if (m_pBottomChild->getRelativeBottomPos() + touchOffset >= m_fBottomBoundary)
                                {
                                    realOffset = m_fBottomBoundary - m_pBottomChild->getRelativeBottomPos();
                                    moveChildren(realOffset);
                                    
                                    if (!m_bBottomEnd)
                                    {
                                        scrollToBottomEvent();
                                    }
                                    m_bBottomEnd = true;
                                    return false;
                                }
                                break;
                                
                            case SCROLLVIEW_MOVE_MODE_ACTION: // action
                                if (m_pBottomChild->getRelativeBottomPos() > m_fBottomBoundary)
                                {
                                    return false;
                                }
                                break;
                                
                            default:
                                break;
                        }
                        break;
                        
                    case SCROLLVIEW_MOVE_DIR_DOWN: // down
                        if (!m_pTopChild)
                        {
                            return false;
                        }
                        
                        switch (m_eMoveMode)
                        {
                            case SCROLLVIEW_MOVE_MODE_NORMAL: // normal
                                if (m_pTopChild->getRelativeTopPos() + touchOffset <= m_fTopBoundary)
                                {
                                    realOffset = m_fTopBoundary - m_pTopChild->getRelativeTopPos();
                                    moveChildren(realOffset);
                                    
                                    if (!m_bTopEnd)
                                    {
                                        scrollToTopEvent();
                                    }
                                    m_bTopEnd = true;
                                    return false;
                                }
                                break;
                                
                            case SCROLLVIEW_MOVE_MODE_ACTION: // action
                                if (m_pTopChild->getRelativeTopPos() < m_fTopBoundary)
                                {
                                    return false;
                                }
                                break;
                                
                            default:
                                break;
                        }
                        break;
                        
                    default:
                        break;
                }
                
                moveChildren(realOffset);
                m_bTopEnd = false;
                m_bBottomEnd = false;
                return true;
                break;
                
            case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
                if (m_fChildrenSizeWidth <= m_fWidth)
                {
                    berthChildren(m_eDirection);
                    
                    return false;
                }
                
                switch (m_eMoveDirection)
                {
                    case SCROLLVIEW_MOVE_DIR_LEFT: // left
                        if (!m_pRightChild)
                        {
                            berthChildren(m_eDirection);
                            
                            return false;
                        }
                        
                        switch (m_eMoveMode)
                        {
                            case SCROLLVIEW_MOVE_MODE_NORMAL: // normal
                                if (m_pRightChild->getRelativeRightPos() + touchOffset <= m_fRightBoundary)
                                {
                                    realOffset = m_fRightBoundary - m_pRightChild->getRelativeRightPos();
                                    moveChildren(realOffset);
                                    
                                    if (!m_bRightEnd)
                                    {
                                        scrollToRightEvent();
                                    }
                                    m_bRightEnd = true;
                                    return false;
                                }
                                break;
                                
                            case SCROLLVIEW_MOVE_MODE_ACTION: // action
                                if (m_pRightChild->getRelativeRightPos() < m_fRightBoundary)
                                {
                                    return false;
                                }
                                break;
                                
                            default:
                                break;
                        }
                        break;
                        
                    case SCROLLVIEW_MOVE_DIR_RIGHT: // right
                        if (!m_pLeftChild)
                        {
                            berthChildren(m_eDirection);

                            return false;
                        }
                        
                        switch (m_eMoveMode)
                        {
                            case SCROLLVIEW_MOVE_MODE_NORMAL: // normal
                                if (m_pLeftChild->getRelativeLeftPos() + touchOffset >= m_fLeftBoundary)
                                {
                                    realOffset = m_fLeftBoundary - m_pLeftChild->getRelativeLeftPos();
                                    moveChildren(realOffset);
                                    
                                    if (!m_bLeftEnd)
                                    {
                                        scrollToLeftEvent();
                                    }
                                    m_bLeftEnd = true;
                                    return false;
                                }
                                break;
                                
                            case SCROLLVIEW_MOVE_MODE_ACTION: // action
                                if (m_pLeftChild->getRelativeLeftPos() > m_fLeftBoundary)
                                {
                                    return false;
                                }
                                break;
                                
                            default:
                                break;
                        }
                        break;
                        
                    default:
                        break;
                }
                
                moveChildren(realOffset);
                m_bLeftEnd = false;
                m_bRightEnd = false;
                return true;
                break;
                
            default:
                break;
        }
        
        return false;
    }
    
    void CocoScrollView::scrollToBottom()
    {
        this->m_eMoveDirection = SCROLLVIEW_MOVE_DIR_UP; // up
        this->scrollChildren(this->m_fChildrenSizeHeight);
    }
    
    void CocoScrollView::scrollToTop()
    {
        this->m_eMoveDirection = SCROLLVIEW_MOVE_DIR_DOWN; // down
        this->scrollChildren(-this->m_fChildrenSizeHeight);
    }
    
    void CocoScrollView::drag(float offset)
    {
        switch (m_eMoveMode)
        {
            case SCROLLVIEW_MOVE_MODE_NORMAL: // normal
                scrollChildren(offset);
                break;
                
            case SCROLLVIEW_MOVE_MODE_ACTION: // action
                offset = calculateOffsetWithDragForce(offset);
                moveChildren(offset);
                break;
                
            default:
                break;
        }
    }
    
    void CocoScrollView::startRecordSlidAction()
    {
        if (this->m_bAutoScroll){
            this->stopAutoScrollChildren();
        }
        this->m_bBePressed = true;
        this->m_fSlidTime = 0.0;
        
        if (m_eMoveMode == SCROLLVIEW_MOVE_MODE_ACTION)
        {
            if (isRunningAction)
            {
                isRunningAction = false;
                stopAction();
            }
        }
    }
    
    void CocoScrollView::endRecordSlidAction()
    {
        if (this->m_fSlidTime <= 0.016f)
        {
            return;
        }
        float totalDis = 0;
        totalDis = this->m_fTouchEndLocation-this->m_fTouchStartLocation;
        float orSpeed = fabs(totalDis)/(this->m_fSlidTime);
        this->startAutoScrollChildren(orSpeed);
        
        this->m_bBePressed = false;
        this->m_fSlidTime = 0.0;
    }
    
    void CocoScrollView::handlePressLogic(cocos2d::CCPoint &touchPoint)
    {
        cocos2d::CCPoint nsp = this->m_pCContainerNode->convertToNodeSpace(touchPoint);
        switch (this->m_eDirection)
        {
            case SCROLLVIEW_DIR_VERTICAL: // vertical
                this->m_fTouchMoveStartLocation = nsp.y;
                this->m_fTouchStartLocation = nsp.y;
                break;
                
            case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
                this->m_fTouchMoveStartLocation = nsp.x;
                this->m_fTouchStartLocation = nsp.x;
                break;
                
            default:
                break;
        }
        this->startRecordSlidAction();
    }
    
    void CocoScrollView::handleMoveLogic(cocos2d::CCPoint &touchPoint)
    {
        cocos2d::CCPoint nsp = m_pCContainerNode->convertToNodeSpace(touchPoint);
        float offset = 0.0;
        
        switch (m_eDirection)
        {
            case SCROLLVIEW_DIR_VERTICAL: // vertical
                {
                    float moveY = nsp.y;
                    offset = moveY - m_fTouchMoveStartLocation;
                    m_fTouchMoveStartLocation = moveY;
                    
                    if (offset < 0)
                    {
                        m_eMoveDirection = SCROLLVIEW_MOVE_DIR_DOWN; // down
                    }
                    else if (offset > 0)
                    {
                        m_eMoveDirection = SCROLLVIEW_MOVE_DIR_UP; // up
                    }
                }
                break;
                
            case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
                {
                    float moveX = nsp.x;
                    offset = moveX - m_fTouchMoveStartLocation;
                    m_fTouchMoveStartLocation = moveX;
                    
                    if (offset < 0)
                    {
                        m_eMoveDirection = SCROLLVIEW_MOVE_DIR_LEFT; // left
                    }
                    else if (offset > 0)
                    {
                        m_eMoveDirection = SCROLLVIEW_MOVE_DIR_RIGHT; // right
                    }
                }
                break;
                
            default:
                break;
        }
        
        this->drag(offset);
    }
    
    void CocoScrollView::handleReleaseLogic(cocos2d::CCPoint &touchPoint)
    {
        cocos2d::CCPoint nsp = this->m_pCContainerNode->convertToNodeSpace(touchPoint);
        switch (this->m_eDirection)
        {
            case SCROLLVIEW_DIR_VERTICAL: // vertical
                this->m_fTouchEndLocation = nsp.y;
                break;
                
            case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
                this->m_fTouchEndLocation = nsp.x;
                break;
                
            default:
                break;
        }
        this->endRecordSlidAction();
    }    
    
    bool CocoScrollView::onTouchPressed(cocos2d::CCPoint &touchPoint)
    {
        CocoPanel::onTouchPressed(touchPoint);
        this->handlePressLogic(touchPoint);
        return true;
    }
    
    bool CocoScrollView::onTouchMoved(cocos2d::CCPoint &touchPoint)
    {
        CocoPanel::onTouchMoved(touchPoint);
        this->handleMoveLogic(touchPoint);
        return true;
    }
    
    bool CocoScrollView::onTouchReleased(cocos2d::CCPoint &touchPoint)
    {
        CocoPanel::onTouchReleased(touchPoint);
        this->handleReleaseLogic(touchPoint);
        return true;
    }
    
    bool CocoScrollView::onTouchCanceled(cocos2d::CCPoint &touchPoint)
    {
        return CocoPanel::onTouchCanceled(touchPoint);
    }
    
    bool CocoScrollView::onTouchLongClicked(cocos2d::CCPoint &touchPoint)
    {
        return true;
    }
    
    void CocoScrollView::update(float dt)
    {
        if (this->m_bAutoScroll)
        {
            this->autoScrollChildren(dt);
        }
        this->recordSlidTime(dt);
        
        if (m_eMoveMode == SCROLLVIEW_MOVE_MODE_ACTION)
        {
            if (isRunningAction)
            {
                int times = m_children->count();
                
                for (int i = 0; i < times; ++i)
                {
                    CocoWidget* child = dynamic_cast<CocoWidget*>(m_children->objectAtIndex(i));
                    child->setVisible(child->checkBeVisibleInParent());
                }
            }
        }
    }
    
    void CocoScrollView::recordSlidTime(float dt)
    {
        if (this->m_bBePressed)
        {
            this->m_fSlidTime += dt;
        }
    }
    
    void CocoScrollView::checkChildInfo(int handleState,CocoWidget* sender,cocos2d::CCPoint &touchPoint)
    {
        switch (handleState)
        {
            case 0:
                this->handlePressLogic(touchPoint);
                break;
                
            case 1:
                {
                    float offset = 0;
                    switch (this->m_eDirection)
                    {
                        case SCROLLVIEW_DIR_VERTICAL: // vertical
                            offset = fabs(sender->getTouchStartPos().y - touchPoint.y);
                            break;
                            
                        case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
                            offset = fabs(sender->getTouchStartPos().x - touchPoint.x);
                            break;
                            
                        default:
                            break;
                    }
                    if (offset > this->m_fChildFocusCancelOffset)
                    {
                        sender->setBeFocus(false);
                        this->handleMoveLogic(touchPoint);
                    }
                }
                break;
                
            case 2:
                this->handleReleaseLogic(touchPoint);
                break;
                
            case 3:
                break;
        }
    }
    
    void CocoScrollView::scrollToTopEvent()
    {
        if (m_pScrollToTopListener && m_pfnScrollToTopSelector)
        {
            (m_pScrollToTopListener->*m_pfnScrollToTopSelector)(this);
        }
    }
    
    void CocoScrollView::scrollToBottomEvent()
    {
        if (m_pScrollToBottomListener && m_pfnScrollToBottomSelector)
        {
            (m_pScrollToBottomListener->*m_pfnScrollToBottomSelector)(this);
        }
    }
    
    void CocoScrollView::scrollToLeftEvent()
    {
        if (m_pScrollToLeftListener && m_pfnScrollToLeftSelector)
        {
            (m_pScrollToLeftListener->*m_pfnScrollToLeftSelector)(this);
        }
    }
    
    void CocoScrollView::scrollToRightEvent()
    {
        if (m_pScrollToRightListener && m_pfnScrollToRightSelector)
        {
            (m_pScrollToRightListener->*m_pfnScrollToRightSelector)(this);
        }
    }
    
    void CocoScrollView::addScrollToTopEvent(cocos2d::CCObject *target, SEL_ScrollToTopEvent selector)
    {
        m_pScrollToTopListener = target;
        m_pfnScrollToTopSelector = selector;
    }
    
    void CocoScrollView::addScrollToBottomEvent(cocos2d::CCObject *target, SEL_ScrollToBottomEvent selector)
    {
        m_pScrollToBottomListener = target;
        m_pfnScrollToBottomSelector = selector;
    }
    
    void CocoScrollView::addScrollToLeftEvent(cocos2d::CCObject *target, SEL_ScrollToLeftEvent selector)
    {
        m_pScrollToLeftListener = target;
        m_pfnScrollToLeftSelector = selector;
    }
    
    void CocoScrollView::addScrollToRightEvent(cocos2d::CCObject *target, SEL_ScrollToRightEvent selector)
    {
        m_pScrollToRightListener = target;
        m_pfnScrollToRightSelector = selector;
    }
    
    void CocoScrollView::berthToTopEvent()
    {
        if (m_pBerthToTopListener && m_pfnBerthToTopSelector)
        {
            (m_pBerthToTopListener->*m_pfnBerthToTopSelector)(this);
        }
    }
    
    void CocoScrollView::berthToBottomEvent()
    {
        if (m_pBerthToBottomListener && m_pfnBerthToBottomSelector)
        {
            (m_pBerthToBottomListener->*m_pfnBerthToBottomSelector)(this);
        }
    }
    
    void CocoScrollView::berthToVerticalCenterEvent()
    {
        if (m_pBerthToVerticalCenterListener && m_pfnBerthToVerticalCenterSelector)
        {
            (m_pBerthToVerticalCenterListener->*m_pfnBerthToVerticalCenterSelector)(this);
        }
    }
    
    void CocoScrollView::berthToLeftEvent()
    {
        if (m_pBerthToLeftListener && m_pfnBerthToLeftSelector)
        {
            (m_pBerthToLeftListener->*m_pfnBerthToLeftSelector)(this);
        }
    }
    
    void CocoScrollView::berthToRightEvent()
    {
        if (m_pBerthToRightListener && m_pfnBerthToRightSelector)
        {
            (m_pBerthToLeftListener->*m_pfnBerthToRightSelector)(this);
        }
    }
    
    void CocoScrollView::berthToHorizontalCenterEvent()
    {
        if (m_pBerthToHorizontalCenterListener && m_pfnBerthToHorizontalCenterSelector)
        {
            (m_pBerthToHorizontalCenterListener->*m_pfnBerthToHorizontalCenterSelector)(this);
        }
    }
    
    void CocoScrollView::addBerthToTopEvent(cocos2d::CCObject *target, SEL_BerthToTopEvent selector)
    {
        m_pBerthToTopListener = target;
        m_pfnBerthToTopSelector = selector;
    }
    
    void CocoScrollView::addBerthToBottomEvent(cocos2d::CCObject *target, SEL_BerthToBottomEvent selector)
    {
        m_pBerthToBottomListener = target;
        m_pfnBerthToBottomSelector = selector;
    }
    
    void CocoScrollView::addBerthToVerticalCenterEvent(cocos2d::CCObject *target, SEL_BerthToVerticalCenterEvent selector)
    {
        m_pBerthToVerticalCenterListener = target;
        m_pfnBerthToVerticalCenterSelector = selector;
    }
    
    void CocoScrollView::addBerthToLeftEvent(cocos2d::CCObject *target, SEL_BerthToLeftEvent selector)
    {
        m_pBerthToLeftListener = target;
        m_pfnBerthToLeftSelector = selector;
    }
    
    void CocoScrollView::addBerthToRightEvent(cocos2d::CCObject *target, SEL_BerthToRightEvent selector)
    {
        m_pBerthToRightListener = target;
        m_pfnBerthToRightSelector = selector;
    }
    
    void CocoScrollView::addBerthToHorizontalCenterEvent(cocos2d::CCObject *target, SEL_BerthToHorizontalCenterEvent selector)
    {
        m_pBerthToHorizontalCenterListener = target;
        m_pfnBerthToHorizontalCenterSelector = selector;
    }
    
    void CocoScrollView::stopAction()
    {
        int times = m_children->count();
        
        for (int i = 0; i < times; ++i)
        {
            CocoWidget* child = dynamic_cast<CocoWidget*>(m_children->objectAtIndex(i));
            child->stopAllActions();
        }
    }
}