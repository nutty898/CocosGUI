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
namespace cs{
    CocoScrollView::CocoScrollView():
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
    m_bAutoScroll(false),
    m_fAutoScrollOriginalSpeed(0.0),
    m_fAutoScrollAcceleration(600.0),
    m_bBePressed(false),
    m_fSlidTime(0.0),
    m_fChildrenSizeHeight(0.0),
    m_fChildrenSizeWidth(0.0),
    m_fChildFocusCancelOffset(5.0)
    {
        
    }
    
    CocoScrollView::~CocoScrollView()
    {
        
    }
    
    CocoScrollView* CocoScrollView::create()
    {
//        return CocoScrollView::create(NULL);
        CocoScrollView* widget = new CocoScrollView();
        if (widget && widget->init()) {
            return widget;
        }
        CC_SAFE_DELETE(widget);
        return NULL;
    }
    
    bool CocoScrollView::init()
    {
        if (CocoPanel::init()) {
            return true;
        }
        return false;
    }

    void CocoScrollView::setColorAndSize(int r, int g, int b, int o, float width, float height)
    {
        CocoPanel::setColorAndSize(r, g, b, o, width, height);
        this->m_fTopBoundary = height;
        this->m_fRightBoundary = width;
    }
    
    void CocoScrollView::setSize(float width, float height)
    {
        CocoPanel::setSize(width, height);
        this->m_fTopBoundary = height;
        this->m_fRightBoundary = width;
    }
    
    bool CocoScrollView::addChild(CocoWidget* widget)
    {
        if (this->m_children->count() <= 0){
            this->m_pTopChild = widget;
            this->m_pBottomChild = widget;
            this->m_pLeftChild = widget;
            this->m_pRightChild = widget;
        }else{
            if (widget->getRelativeRect().origin.y + widget->getRelativeRect().size.height > this->m_pTopChild->getRelativeRect().origin.y + this->m_pTopChild->getRelativeRect().size.height){
                this->m_pTopChild = widget;
            }
            if (widget->getRelativeRect().origin.y < this->m_pBottomChild->getRelativeRect().origin.y){
                this->m_pBottomChild = widget;
            }
            if (widget->getRelativeRect().origin.x + widget->getRelativeRect().size.width > this->m_pRightChild->getRelativeRect().origin.x + this->m_pRightChild->getRelativeRect().size.width){
                this->m_pRightChild = widget;
            }
            if (widget->getRelativeRect().origin.x < this->m_pLeftChild->getRelativeRect().origin.x){
                this->m_pLeftChild = widget;
            }
        }
        this->m_fChildrenSizeHeight = this->m_pTopChild->getRelativeTopPos()-this->m_pBottomChild->getRelativeBottomPos();
        this->m_fChildrenSizeWidth = this->m_pRightChild->getRelativeRightPos()-this->m_pLeftChild->getRelativeLeftPos();
        CocoPanel::addChild(widget);
        widget->setVisible(widget->checkBeVisibleInParent());
        return true;
    }
    
    void CocoScrollView::removeChildMoveToTrash(CocoWidget* child)
    {
        if (!child){
            return;
        }
        CocoPanel::removeChildMoveToTrash(child);
        this->resortChildren();
    }
    
    void CocoScrollView::removeChildReferenceOnly(CocoWidget* child)
    {
        if (!child){
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
    
    void CocoScrollView::resortChildren()
    {
        if (!this->m_children || this->m_children->count() <= 0){
            return;
        }
        CocoWidget* leftChild = (CocoWidget*)(this->m_children->objectAtIndex(0));
        CocoWidget* rightChild = (CocoWidget*)(this->m_children->objectAtIndex(0));
        CocoWidget* topChild = (CocoWidget*)(this->m_children->objectAtIndex(0));
        CocoWidget* bottomChild = (CocoWidget*)(this->m_children->objectAtIndex(0));
        for (int i=0;i<this->m_children->count();i++){
            CocoWidget* child = (CocoWidget*)(this->m_children->objectAtIndex(i));
            if (leftChild->getRelativeRect().origin.x > child->getRelativeRect().origin.x){
                leftChild = child;
            }
            if (rightChild->getRelativeRect().origin.x + rightChild->getRelativeRect().size.width < child->getRelativeRect().origin.x + child->getRelativeRect().size.width){
                rightChild = child;
            }
            if (topChild->getRelativeRect().origin.y + topChild->getRelativeRect().size.height < child->getRelativeRect().origin.y + child->getRelativeRect().size.height){
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
        switch (this->m_nDirection){
            case 0:
                for (int i=0;i<this->m_children->count();i++){
                    CocoWidget* child = (CocoWidget*)(this->m_children->objectAtIndex(i));
                    this->moveChildPoint.x = child->getPosition().x;
                    this->moveChildPoint.y = child->getPosition().y+offset;
                    child->setPosition(this->moveChildPoint);
                    child->setVisible(child->checkBeVisibleInParent());
                }
                break;
            case 1:
                for (int i=0;i<this->m_children->count();i++){
                    CocoWidget* child = (CocoWidget*)(this->m_children->objectAtIndex(i));
                    this->moveChildPoint.x = child->getPosition().x+offset;
                    this->moveChildPoint.y = child->getPosition().y;
                    child->setPosition(this->moveChildPoint);
                    child->setVisible(child->checkBeVisibleInParent());
                }
                break;
        }
    }
    
    void CocoScrollView::autoScrollChildren(float dt)
    {
        switch (this->m_nDirection){
            case 0:
                switch (this->m_nMoveDirection){
                    case 0:
                    {
                        float curDis = this->getCurAutoScrollDistance(dt);
                        if (curDis <= 0){
                            curDis = 0;
                            this->stopAutoScrollChildren();
                        }
                        if (!this->scrollChildren(-curDis)){
                            this->stopAutoScrollChildren();
                        }
                    }
                        break;
                    case 1:
                    {
                        float curDis = this->getCurAutoScrollDistance(dt);
                        if (curDis <= 0){
                            curDis = 0;
                            this->stopAutoScrollChildren();
                        }
                        if (!this->scrollChildren(curDis)){
                            this->stopAutoScrollChildren();
                        }
                    }
                        break;
                }
                break;
            case 1:
                switch (this->m_nMoveDirection){
                    case 0:
                    {
                        float curDis = this->getCurAutoScrollDistance(dt);
                        if (curDis <= 0){
                            curDis = 0;
                            this->stopAutoScrollChildren();
                        }
                        if (!this->scrollChildren(-curDis)){
                            this->stopAutoScrollChildren();
                        }
                    }
                        break;
                    case 1:
                    {
                        float curDis = this->getCurAutoScrollDistance(dt);
                        if (curDis <= 0){
                            curDis = 0;
                            this->stopAutoScrollChildren();
                        }
                        if (!this->scrollChildren(curDis)){
                            this->stopAutoScrollChildren();
                        }
                    }
                        break;
                }
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
        return distance;
    }
    
    void CocoScrollView::setDirection(int direction)
    {
        if (this->m_nDirection == direction){
            return;
        }
        this->m_nDirection = direction;
    }
    
    bool CocoScrollView::scrollChildren(float touchOffset)
    {
        if (this->m_children->count() <= 0){
            return false;
        }
        
        switch (this->m_nDirection){
            case 0:
            {
                if (this->m_fChildrenSizeHeight <= this->m_fHeight){
                    this->moveChildren(this->m_fTopBoundary - this->m_pTopChild->getRelativeTopPos());
                    return false;
                }
                float realOffset = touchOffset;
                switch (this->m_nMoveDirection){
                    case 0:
                        if (!this->m_pTopChild){
                            return false;
                        }
                        if (this->m_pTopChild->getRelativeTopPos() + touchOffset <= this->m_fTopBoundary){
                            realOffset = this->m_fTopBoundary - this->m_pTopChild->getRelativeTopPos();
                            this->m_bTopEnd = true;
                            this->moveChildren(realOffset);
                            return false;
                        }
                        break;
                    case 1:
                        if (!this->m_pBottomChild){
                            return false;
                        }
                        if (this->m_pBottomChild->getRelativeBottomPos() + touchOffset >= this->m_fBottomBoundary){
                            realOffset = this->m_fBottomBoundary - this->m_pBottomChild->getRelativeBottomPos();
                            this->m_bBottomEnd = true;
                            this->moveChildren(realOffset);
                            return false;
                        }
                        break;
                }
                this->moveChildren(realOffset);
                this->m_bTopEnd = false;
                this->m_bBottomEnd = false;
                return true;
            }
                break;
            case 1:
            {
                if (this->m_fChildrenSizeWidth <= this->m_fWidth){
                    this->moveChildren(this->m_fLeftBoundary - this->m_pLeftChild->getRelativeLeftPos());
                    return false;
                }
                float realOffset = touchOffset;
                switch (this->m_nMoveDirection){
                    case 0:
                        if (!this->m_pRightChild){
                            return false;
                        }
                        if (this->m_pRightChild->getRelativeRightPos() + touchOffset <= this->m_fRightBoundary){
                            realOffset = this->m_fRightBoundary - this->m_pRightChild->getRelativeRightPos();
                            this->moveChildren(realOffset);
                            return false;
                        }
                        break;
                    case 1:
                        if (!this->m_pLeftChild){
                            return false;
                        }
                        if (this->m_pLeftChild->getRelativeLeftPos() + touchOffset >= this->m_fLeftBoundary){
                            realOffset = this->m_fLeftBoundary - this->m_pLeftChild->getRelativeLeftPos();
                            this->moveChildren(realOffset);
                            return false;
                        }
                        break;
                }
                this->moveChildren(realOffset);
                return true;
            }
                break;
        }
        return false;
    }
    
    void CocoScrollView::scrollToBottom()
    {
        this->m_nMoveDirection = 1;
        this->scrollChildren(this->m_fChildrenSizeHeight);
    }
    
    void CocoScrollView::scrollToTop()
    {
        this->m_nMoveDirection = 0;
        this->scrollChildren(-this->m_fChildrenSizeHeight);
    }
    
    void CocoScrollView::startRecordSlidAction()
    {
        if (this->m_bAutoScroll){
            this->stopAutoScrollChildren();
        }
        this->m_bBePressed = true;
        this->m_fSlidTime = 0.0;
    }
    
    void CocoScrollView::endRecordSlidAction()
    {
        if (this->m_fSlidTime <= 0.016f){
            return;
        }
        float totalDis = 0;
        totalDis = this->m_fTouchEndLocation-this->m_fTouchStartLocation;
        float orSpeed = fabs(totalDis)/(this->m_fSlidTime);
        this->startAutoScrollChildren(orSpeed);
    }
    
    void CocoScrollView::handlePressLogic(cocos2d::CCPoint &touchPoint)
    {
        cocos2d::CCPoint nsp = this->m_pCContainerNode->convertToNodeSpace(touchPoint);
        switch (this->m_nDirection){
            case 0:
                this->m_fTouchMoveStartLocation = nsp.y;
                this->m_fTouchStartLocation = nsp.y;
                break;
            case 1:
                this->m_fTouchMoveStartLocation = nsp.x;
                this->m_fTouchStartLocation = nsp.x;
                break;
        }
        this->startRecordSlidAction();
    }
    
    void CocoScrollView::handleMoveLogic(cocos2d::CCPoint &touchPoint)
    {
        cocos2d::CCPoint nsp = this->m_pCContainerNode->convertToNodeSpace(touchPoint);
        switch (this->m_nDirection){
            case 0:
            {
                float moveY = nsp.y;
                float offset = moveY - this->m_fTouchMoveStartLocation;
                this->m_fTouchMoveStartLocation = moveY;
                if (offset < 0){
                    this->m_nMoveDirection = 0;
                }else if (offset > 0){
                    this->m_nMoveDirection = 1;
                }
                this->scrollChildren(offset);
            }
                break;
            case 1:
            {
                float moveX = nsp.x;
                float offset = moveX - this->m_fTouchMoveStartLocation;
                this->m_fTouchMoveStartLocation = moveX;
                if (offset < 0){
                    this->m_nMoveDirection = 0;
                }else if (offset > 0){
                    this->m_nMoveDirection = 1;
                }
                this->scrollChildren(offset);
            }
                break;
        }
    }
    
    void CocoScrollView::handleReleaseLogic(cocos2d::CCPoint &touchPoint)
    {
        cocos2d::CCPoint nsp = this->m_pCContainerNode->convertToNodeSpace(touchPoint);
        switch (this->m_nDirection){
            case 0:
                this->m_fTouchEndLocation = nsp.y;
                break;
            case 1:
                this->m_fTouchEndLocation = nsp.x;
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
        if (this->m_bAutoScroll){
            this->autoScrollChildren(dt);
        }
        this->recordSlidTime(dt);
    }
    
    void CocoScrollView::recordSlidTime(float dt)
    {
        if (this->m_bBePressed){
            this->m_fSlidTime += dt;
        }
    }
    
    void CocoScrollView::checkChildInfo(int handleState,CocoWidget* sender,cocos2d::CCPoint &touchPoint)
    {
        switch (handleState){
            case 0:
                this->handlePressLogic(touchPoint);
                break;
            case 1:
            {
                float offset = 0;
                switch (this->m_nDirection) {
	                case 0:
                        offset = fabs(sender->getTouchStartPos().y - touchPoint.y);
		                break;
		            case 1:
                        offset = fabs(sender->getTouchStartPos().x - touchPoint.x);
			            break;
                }
                if (offset > this->m_fChildFocusCancelOffset) {
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
}