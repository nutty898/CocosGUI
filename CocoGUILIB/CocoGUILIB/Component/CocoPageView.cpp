//
//  CocoPageView.cpp
//  Test
//
//  Created by pipu on 13-6-6.
//
//

#include "CocoPageView.h"

namespace cs
{
    CocoPageView::CocoPageView()
    : state_(0)
    , stealTouches(true)
    , minimumTouchLengthToSlide(10.0)
    , minimumTouchLengthToChangePage(20.0)
    , marginOffset(0)
    , pagesWidthOffset(0)
    , currentScreen_(0)
    , isRunningAction(false)
    , m_fTouchStartLocation(0.0)
    , m_fTouchMoveStartLocation(0.0)
    , m_fTouchEndLocation(0.0)
    , m_fDisBoundaryToChild_0(0.0)
    , m_fDisBetweenChild(0.0)
    , m_fDragForce(0.0)
    , m_eDirection(PAGEVIEW_DIR_VERTICAL)
    {
        
    }
    
    CocoPageView::~CocoPageView()
    {
        
    }
    
    CocoPageView* CocoPageView::create()
    {
        CocoPageView* pRet = new CocoPageView();
        
        if (pRet && pRet->init())
        {
            return pRet;
        }
        CC_SAFE_DELETE(pRet);        
        return NULL;
    }
    
    bool CocoPageView::init()
    {
        if (CocoPanel::init())
        {
            return true;
        }        
        return false;
    }
    
    bool CocoPageView::addChild(cs::CocoWidget *widget)
    {
        CocoPanel::addChild(widget);
        
        initProperty();
        
        return true;
    }
    
    void CocoPageView::initProperty()
    {
        resetProperty();
    }
    
    void CocoPageView::resetProperty()
    {
        float scroll_top = getRect().size.height;
        float scroll_left = 0;
        
        switch (m_children->count())
        {
            case 1:
                {
                    CocoWidget* child_0 = dynamic_cast<CocoWidget*>(m_children->objectAtIndex(0));
                    
                    switch (m_eDirection)
                    {
                        case PAGEVIEW_DIR_VERTICAL: // vertical
                            {
                                float child_0_top = child_0->getRelativeTopPos();
                                float offset = scroll_top - child_0_top;
                                m_fDisBoundaryToChild_0 = (offset > 0) ? offset : 0;
                            }
                            break;
                            
                        case PAGEVIEW_DIR_HORIZONTAL: // horizontal
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
                        case PAGEVIEW_DIR_VERTICAL: // vertical
                            {
                                float child_0_top = child_0->getRelativeTopPos();
                                float offset = scroll_top - child_0_top;
                                m_fDisBoundaryToChild_0 = (offset > 0) ? offset : 0;
                                m_fDisBetweenChild = child_0->getPosition().y - child_1->getPosition().y;
                            }
                            break;
                            
                        case PAGEVIEW_DIR_HORIZONTAL: // horizontal
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
    
//    void CocoPageView::setColorAndSize(int r, int g, int b, int o, float width, float height)
//    {
//        CocoPanel::setColorAndSize(r, g, b, o, width, height);
//        marginOffset = width / 8 * 5;
//        m_fDragForce = width / 8 * 5;
////        marginOffset = m_fWidth;
//    }
    
    void CocoPageView::setSize(const CCSize &size)
    {
        CocoPanel::setSize(size);
        marginOffset = size.width / 8 * 5;
        m_fDragForce = size.width / 8 * 5;
//        marginOffset = m_fWidth;
    }
    
    void CocoPageView::updatePages()
    {
        // Loop through the array and add the screens if needed.
        CocoWidget* child_0 = dynamic_cast<CocoWidget*>(m_children->objectAtIndex(0));
        float child_0_x = child_0->getRelativeLeftPos();
        float child_0_y = child_0->getRelativeBottomPos();
        
        float w = getRect().size.width;
//        float h = getRect().size.height;
        
        for (int i = 0; i < m_children->count(); ++i)
        {
            CocoWidget* child = dynamic_cast<CocoWidget*>(m_children->objectAtIndex(i));
            child->setPosition(ccp(child_0_x + (i * (w - pagesWidthOffset)), child_0_y));
        }
    }
    
    void CocoPageView::addPage(cs::CocoWidget *widget, int pageNumber)
    {
        pageNumber = MIN(pageNumber, m_children->count());
        pageNumber = MAX(pageNumber, 0);
        
        addChild(widget);
        updatePages();
        moveToPage(currentScreen_);
    }
    
    void CocoPageView::addPage(cs::CocoWidget *widget)
    {
        addPage(widget, m_children->count());
    }
    
    void CocoPageView::removePage(cs::CocoWidget *widget)
    {
        removeChild(widget, true);
        updatePages();
        
        prevScreen_ = currentScreen_;
        currentScreen_ = MIN(currentScreen_, m_children->count() - 1);
        moveToPage(currentScreen_);        
    }
    
    void CocoPageView::removePageWithNumber(int page)
    {
        if (page >= 0 && page < m_children->count())
        {
            removePage(dynamic_cast<CocoWidget*>(m_children->objectAtIndex(page)));            
        }
    }
    
    #pragma mark Moving To / Selecting Pages
    void CocoPageView::moveToPage(int page)
    {
        if (page < 0 || page >= m_children->count())
        {
            CCLOGERROR("CocoPageView#moveToPage: %d - wrong page number, out of bounds. ", page);
            return;
        }
        
        CocoWidget* child_0 = dynamic_cast<CocoWidget*>(m_children->objectAtIndex(0));
        float child_0_x = child_0->getRelativeLeftPos();
        float child_0_y = child_0->getRelativeBottomPos();
        CCPoint des = positionForPageWithNumber(page);
        CCPoint delta = ccp(des.x + m_fDisBoundaryToChild_0 - child_0_x, des.y - child_0_y);
        
        int times = m_children->count();
        for (int i = 0; i < times - 1; ++i)
        {
            CocoWidget* child = dynamic_cast<CocoWidget*>(m_children->objectAtIndex(i));
            CCMoveBy* moveBy = CCMoveBy::create(0.3, delta);
            child->runAction(moveBy);
        }
        
        CocoWidget* child_last = dynamic_cast<CocoWidget*>(m_children->lastObject());
        CCMoveBy* moveBy = CCMoveBy::create(0.3, delta);
        CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(CocoPageView::moveToPageEnded));
        CCSequence* seq = CCSequence::create(moveBy, callFunc, NULL);
        child_last->runAction(seq);
        
        isRunningAction = true;
        
        currentScreen_ = page;        
    }
    
    void CocoPageView::selectPage(int page)
    {
        if (page < 0 || page >= m_children->count()) {
            CCLOGERROR("CocoPageView#selectPage: %d - wrong page number, out of bounds. ", page);
            return;
        }
        
        CocoWidget* child_0 = dynamic_cast<CocoWidget*>(m_children->objectAtIndex(0));
        float child_0_x = child_0->getPosition().x;
        float child_0_y = child_0->getPosition().y;
        CCPoint des = positionForPageWithNumber(page);
        CCPoint delta = ccp(des.x + m_fDisBoundaryToChild_0 - child_0_x, des.y - child_0_y);
        
        int times = m_children->count();
        for (int i = 0; i < times; ++i)
        {
            CocoWidget* child = dynamic_cast<CocoWidget*>(m_children->objectAtIndex(i));
            child->setPosition(ccp(child->getPosition().x + delta.x, child->getPosition().y + delta.y));
        }
                
        prevScreen_ = currentScreen_;
        currentScreen_ = page;
    }
    
    void CocoPageView::moveToPageEnded()
    {
        isRunningAction = false;
        // pipu later test
//        prevScreen_ = currentScreen_ = pageNumberForPosition(getPosition());
    }
    
    int CocoPageView::pageNumberForPosition(cocos2d::CCPoint position)
    {
        float w = getRect().size.width;
        float pageFloat = - position.x / (w - pagesWidthOffset);
        int pageNumber = ceilf(pageFloat);
        if ( (float)pageNumber - pageFloat  >= 0.5f)
        {
            pageNumber--;
        }
        
        pageNumber = MAX(0, pageNumber);
        pageNumber = MIN(m_children->count() - 1, pageNumber);
        
        return pageNumber;
    }
    
    CCPoint CocoPageView::positionForPageWithNumber(int pageNumber)
    {
        CocoWidget* child_0 = dynamic_cast<CocoWidget*>(m_children->objectAtIndex(0));
        float child_0_y = child_0->getRelativeBottomPos();
        
        float w = getRect().size.width;
        return ccp(-pageNumber * (w - pagesWidthOffset), child_0_y);
    }
    
    void CocoPageView::moveChildren(float offset)
    {
        for (int i=0;i<this->m_children->count();i++)
        {
            CocoWidget* child = dynamic_cast<CocoWidget*>(m_children->objectAtIndex(i));
            child->setPosition(ccp(child->getPosition().x + offset, child->getPosition().y));
            child->setVisible(child->checkBeVisibleInParent());
        }
    }
    
    void CocoPageView::stopAction()
    {
        int times = m_children->count();
        for (int i = 0; i < times; ++i)
        {
            CocoWidget* child = dynamic_cast<CocoWidget*>(m_children->objectAtIndex(i));
            child->stopAllActions();
        }
    }
    
    bool CocoPageView::onTouchPressed(cocos2d::CCPoint &touchPoint)
    {
        CocoPanel::onTouchPressed(touchPoint);
        
        cocos2d::CCPoint nsp = this->m_pCCRenderNode->convertToNodeSpace(touchPoint);
        m_fTouchMoveStartLocation = nsp.x;
        m_fTouchStartLocation = nsp.x;
        
        startSwipe_ = nsp.x;
        state_ = kCCScrollLayerStateIdle;
        
        if (isRunningAction)
        {
            isRunningAction = false;
            stopAction();
        }
        
        return true;
    }
    
    bool CocoPageView::onTouchMoved(cocos2d::CCPoint &touchPoint)
    {
        CocoPanel::onTouchMoved(touchPoint);
        
        cocos2d::CCPoint nsp = m_pCCRenderNode->convertToNodeSpace(touchPoint);
        float moveX = nsp.x;
        float distance = moveX - m_fTouchMoveStartLocation;
        m_fTouchMoveStartLocation = moveX;
        
        // If finger is dragged for more distance then minimum - start sliding and cancel pressed buttons.
        // Of course only if we not already in sliding mode
        if ( (state_ != kCCScrollLayerStateSliding)
            && (fabsf(nsp.x - startSwipe_) >= minimumTouchLengthToSlide) )
        {
            state_ = kCCScrollLayerStateSliding;
            
            // Avoid jerk after state change.
            startSwipe_ = moveX;
            
            // move page start event
            // later
        }
        
        if (state_ == kCCScrollLayerStateSliding)
        {
            float w = getRect().size.width;
            float desiredX = (-currentScreen_ * (w - pagesWidthOffset)) + moveX - startSwipe_;
            int page = pageNumberForPosition(ccp(desiredX, 0));
            float offset = distance;
//            float offset = desiredX - positionForPageWithNumber(page).x;
            
            if ((page == 0 && offset > 0) || (page == m_children->count() - 1 && offset < 0))
            {
                offset -= marginOffset * offset / m_fWidth;
            }
            moveChildren(offset);
        }
        
        return true;
    }
    
    bool CocoPageView::onTouchReleased(cocos2d::CCPoint &touchPoint)
    {
        CocoPanel::onTouchReleased(touchPoint);
        
        cocos2d::CCPoint nsp = this->m_pCCRenderNode->convertToNodeSpace(touchPoint);
        m_fTouchEndLocation = nsp.x;
        
        int selectedPage = currentScreen_;
        float delta = nsp.x - startSwipe_;
        
        if (fabsf(delta) >= minimumTouchLengthToChangePage)
        {
            CocoWidget* child_0 = dynamic_cast<CocoWidget*>(m_children->objectAtIndex(0));
            
            CCPoint point = ccp(child_0->getRelativeLeftPos(), child_0->getRelativeBottomPos());
            selectedPage = pageNumberForPosition(point);
            if (selectedPage == currentScreen_)
            {
                if (delta < 0.f && selectedPage < m_children->count() - 1)
                {
                    selectedPage++;                    
                }
                else if (delta > 0.f && selectedPage > 0)
                {
                    selectedPage--;
                }
            }
        }
        moveToPage(selectedPage);
        
        return true;
    }
    
    bool CocoPageView::onTouchCanceled(cocos2d::CCPoint &touchPoint)
    {
        CocoPanel::onTouchCanceled(touchPoint);        
//        selectPage(currentScreen_);
        return true;
    }
}