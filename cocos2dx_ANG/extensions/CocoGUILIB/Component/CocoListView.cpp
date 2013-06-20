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

#include "CocoListView.h"

NS_CC_EXT_BEGIN

CocoListView::CocoListView() :    
m_pInitChildListener(NULL),
m_pfnInitChildSelector(NULL),
m_pUpdateChildListener(NULL),
m_pfnUpdateChildSelector(NULL),
m_pChildPool(NULL),
m_pUpdatePool(NULL),
m_nDataLength(0),
m_nBegin(0),
m_nEnd(0),
m_pUpdateChild(NULL),
m_nUpdateDataIndex(-1),
m_bUpdateSuccess(false),
m_overTopArray(NULL),
m_overBottomArray(NULL),
m_overLeftArray(NULL),
m_overRightArray(NULL)
{
    
}

CocoListView::~CocoListView()
{
    CC_SAFE_DELETE(m_pChildPool);
    CC_SAFE_DELETE(m_pUpdatePool);
    CC_SAFE_RELEASE_NULL(m_overTopArray);
    CC_SAFE_RELEASE_NULL(m_overBottomArray);
    CC_SAFE_RELEASE_NULL(m_overLeftArray);
    CC_SAFE_RELEASE_NULL(m_overRightArray);        
}

CocoListView* CocoListView::create()
{
    CocoListView* widget = new CocoListView();
    if (widget && widget->init())
    {
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

bool CocoListView::init()
{
    if (CocoScrollView::init())
    {
        m_pChildPool = new UIWidgetPool();
        m_pUpdatePool = new UIWidgetPool();
        m_overTopArray = cocos2d::CCArray::create();
        m_overBottomArray = cocos2d::CCArray::create();
        m_overLeftArray = cocos2d::CCArray::create();
        m_overRightArray = cocos2d::CCArray::create();
        CC_SAFE_RETAIN(m_overTopArray);
        CC_SAFE_RETAIN(m_overBottomArray);
        CC_SAFE_RETAIN(m_overLeftArray);
        CC_SAFE_RETAIN(m_overRightArray);
        
        return true;
    }
    return false;
}

bool CocoListView::addChild(CocoWidget *widget)
{
    CocoScrollView::addChild(widget);
    
    return true;
}

void CocoListView::removeChildMoveToTrash(CocoWidget *child)
{
    if (!child)
    {
        return;
    }
    CocoScrollView::removeChildMoveToTrash(child);
}

void CocoListView::removeChildReferenceOnly(CocoWidget *child)
{
    if (!child)
    {
        return;
    }
    CocoScrollView::removeChildReferenceOnly(child);
}

void CocoListView::removeAllChildrenAndCleanUp(bool cleanup)
{
    CocoScrollView::removeAllChildrenAndCleanUp(cleanup);
    
    m_pUpdatePool->clear();
    m_pChildPool->clear();
}

bool CocoListView::scrollChildren(float touchOffset)
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
                CocoScrollView::berthChildren(m_eDirection);
                return false;
            }                                
            
            switch (m_eMoveDirection)
            {
                case SCROLLVIEW_MOVE_DIR_UP: // up
                    {
                        CocoWidget* child_last = m_pChildPool->rbegin();
                        float child_last_bottom = child_last->getRelativeBottomPos();
                        float scroll_bottom = m_fBottomBoundary;
                        
                        switch (m_eMoveMode)
                        {
                            case SCROLLVIEW_MOVE_MODE_NORMAL: // move mode normal                                    
                                if (m_nEnd == m_nDataLength - 1)
                                {
                                    if (realOffset > scroll_bottom + m_fDisBoundaryToChild_0 - child_last_bottom)
                                    {
                                        realOffset = scroll_bottom + m_fDisBoundaryToChild_0 - child_last_bottom;
                                    }
                                }
                                CocoScrollView::moveChildren(realOffset);
                                if (m_nEnd == m_nDataLength - 1)
                                {
                                    return false;
                                }                                    
                                break;
                                
                            case SCROLLVIEW_MOVE_MODE_ACTION:
                                CocoScrollView::moveChildren(realOffset);
                                
                                if (m_nEnd == m_nDataLength - 1)
                                {
                                    child_last_bottom = child_last->getRelativeBottomPos();
                                    
                                    if (child_last_bottom > scroll_bottom)
                                    {
                                        return false;
                                    }
                                }                                    
                                break;
                                
                            default:
                                break;
                        }
                        if (m_nEnd < m_nDataLength - 1)
                        {
                            collectOverTopChild();
                            int count = m_overTopArray->count();
                            if (count > 0)
                            {
                                updateChild();
                                setLoopPosition();
                                m_overTopArray->removeAllObjects();
                            }
                        }
                    }
                    break;
                    
                case SCROLLVIEW_MOVE_DIR_DOWN: // down
                    {
                        CocoWidget* child_0 = m_pChildPool->begin();
                        float child_0_top = child_0->getRelativeTopPos();
                        float scroll_top = m_fTopBoundary;
                        
                        switch (m_eMoveMode)
                        {
                            case SCROLLVIEW_MOVE_MODE_NORMAL: // move mode normal
                                if (m_nBegin == 0)
                                {
                                    if (realOffset < scroll_top - m_fDisBoundaryToChild_0 - child_0_top)
                                    {
                                        realOffset = scroll_top - m_fDisBoundaryToChild_0 - child_0_top;
                                    }                                        
                                }
                                CocoScrollView::moveChildren(realOffset);
                                if (m_nBegin == 0)
                                {
                                    return false;
                                }                                    
                                break;
                                
                            case SCROLLVIEW_MOVE_MODE_ACTION: // move mode action
                                CocoScrollView::moveChildren(realOffset);                                    
                                
                                if (m_nBegin == 0)
                                {
                                    child_0_top = child_0->getRelativeTopPos();
                                    
                                    if (child_0_top < scroll_top)
                                    {
                                        return false;
                                    }
                                }                                    
                                break;
                                
                            default:
                                break;
                        }
                        if (m_nBegin > 0)
                        {
                            collectOverBottomChild();
                            int count = m_overBottomArray->count();
                            if (count > 0)
                            {
                                updateChild();
                                setLoopPosition();
                                m_overBottomArray->removeAllObjects();
                            }
                        }                            
                    }
                    break;
                    
                default:
                    break;
            }                                                                
            return true;
            break;
            
        case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
            if (m_fChildrenSizeWidth <= m_fWidth)
            {
                CocoScrollView::berthChildren(m_eDirection);
                return false;
            }                                
            
            switch (m_eMoveDirection)
            {
                case SCROLLVIEW_MOVE_DIR_LEFT: // left
                    {
                        CocoWidget* child_last = m_pChildPool->rbegin();
                        float child_last_right = child_last->getRelativeRightPos();
                        float scroll_right = m_fRightBoundary;
                        
                        switch (m_eMoveMode)
                        {
                            case SCROLLVIEW_MOVE_MODE_NORMAL:
                                if (m_nEnd == m_nDataLength - 1)
                                {
                                    if (realOffset < scroll_right - child_last_right)
                                    {
                                        realOffset = scroll_right - child_last_right;
                                    }
                                }
                                CocoScrollView::moveChildren(realOffset);
                                if (m_nEnd == m_nDataLength - 1)
                                {
                                    return false;
                                }
                                break;
                                
                            case SCROLLVIEW_MOVE_MODE_ACTION:
                                CocoScrollView::moveChildren(realOffset);
                                
                                if (m_nEnd == m_nDataLength - 1)
                                {
                                    child_last_right = child_last->getRelativeRightPos();
                                    
                                    if (child_last_right < scroll_right)
                                    {
                                        return false;
                                    }
                                }
                                break;
                                
                            default:
                                break;
                        }
                        if (m_nEnd < m_nDataLength - 1)
                        {
                            collectOverLeftChild();
                            int count = m_overLeftArray->count();
                            if (count > 0)
                            {
                                updateChild();
                                setLoopPosition();
                                m_overLeftArray->removeAllObjects();
                            }
                        }                                                                                                                
                    }
                    break;
                    
                case SCROLLVIEW_MOVE_DIR_RIGHT: // right
                    {
                        CocoWidget* child_0 = m_pChildPool->begin();
                        float child_0_left = child_0->getRelativeLeftPos();
                        float scroll_left = m_fLeftBoundary;
                        
                        switch (m_eMoveMode)
                        {
                            case SCROLLVIEW_MOVE_MODE_NORMAL:
                                if (m_nBegin == 0)
                                {
                                    if (realOffset > scroll_left - child_0_left)
                                    {
                                        realOffset = scroll_left - child_0_left;
                                    }
                                }
                                CocoScrollView::moveChildren(realOffset);
                                if (m_nBegin == 0)
                                {
                                    return false;
                                }
                                break;
                                
                            case SCROLLVIEW_MOVE_MODE_ACTION:
                                CocoScrollView::moveChildren(realOffset);
                                
                                if (m_nBegin == 0)
                                {
                                    child_0_left = child_0->getRelativeLeftPos();
                                    
                                    if (child_0_left > scroll_left)
                                    {
                                        return false;
                                    }
                                }
                                break;
                                
                            default:
                                break;
                        }
                        collectOverRightChild();
                        int count = m_overRightArray->count();
                        if (count > 0)
                        {
                            updateChild();
                            setLoopPosition();
                            m_overRightArray->removeAllObjects();
                        }                                                                                    
                    }
                    break;
                    
                default:
                    break;
            }                                                                                                      
            return true;
            break;
            
        default:
            break;
    }
    
    return false;
}        

void CocoListView::drag(float offset)
{
    if (m_children->count() <= 0)
    {
        return;
    }
    
    switch (m_eMoveMode)
    {
        case SCROLLVIEW_MOVE_MODE_NORMAL: // normal
            scrollChildren(offset);
            break;
            
        case SCROLLVIEW_MOVE_MODE_ACTION: // action
            if (m_nBegin == 0 || m_nEnd == m_nDataLength - 1)
            {
                offset = calculateOffsetWithDragForce(offset);
            }
            scrollChildren(offset);
            break;
            
        default:
            break;
    }
}        

CocoWidget* CocoListView::getCheckPositionChild()
{
    CocoWidget* child = NULL;
    
    switch (m_eDirection)
    {
        case SCROLLVIEW_DIR_VERTICAL: // vertical
            switch (m_eMoveDirection)
            {
                case SCROLLVIEW_MOVE_DIR_UP: // up
                    child = m_pChildPool->rbegin();
                    break;
                    
                case SCROLLVIEW_MOVE_DIR_DOWN: // down
                    child = m_pChildPool->begin();
                    break;
                    
                default:
                    break;
            }
            break;
            
        case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
            switch (m_eMoveDirection)
            {
                case SCROLLVIEW_MOVE_DIR_LEFT: // left
                    child = m_pChildPool->rbegin();
                    break;
                    
                case SCROLLVIEW_MOVE_DIR_RIGHT: // right
                    child = m_pChildPool->begin();
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

void CocoListView::initChildWithDataLength(int length)
{
    m_nDataLength = length;
    m_nBegin = 0;
    m_nEnd = 0;        
    
    // init child pool
    int times = m_children->count();
    for (int i = 0; i < times; ++i)
    {
        CocoWidget* child = dynamic_cast<CocoWidget*>(m_children->objectAtIndex(i));
        setUpdateChild(child);
        setUpdateDataIndex(i);
        initChildEvent();
        m_pChildPool->push_back(child);
        m_nEnd = i;
    }
}

CocoWidget* CocoListView::getChildFromUpdatePool()
{
    CocoWidget* child = m_pUpdatePool->rbegin();
    m_pUpdatePool->pop_back();
    return child;
}

void CocoListView::pushChildToPool()
{
    switch (m_eDirection)
    {
        case SCROLLVIEW_DIR_VERTICAL: // vertical
            switch (m_eMoveDirection)
            {
                case SCROLLVIEW_MOVE_DIR_UP: // up
                    {
                        CocoWidget* child = m_pChildPool->begin();
                        m_pUpdatePool->push_front(child);
                        m_pChildPool->pop_front();
                    }
                    break;
                    
                case SCROLLVIEW_MOVE_DIR_DOWN: // down
                    {
                        CocoWidget* child = m_pChildPool->rbegin();
                        m_pUpdatePool->push_front(child);
                        m_pChildPool->pop_back();
                    }
                    break;
            }
            break;
            
        case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
            switch (m_eMoveDirection)
            {
                case SCROLLVIEW_MOVE_DIR_LEFT: // left
                    {
                        CocoWidget* child = m_pChildPool->begin();
                        m_pUpdatePool->push_front(child);
                        m_pChildPool->pop_front();
                    }
                    break;
                    
                case SCROLLVIEW_MOVE_DIR_RIGHT: // right
                    {
                        CocoWidget* child = m_pChildPool->rbegin();
                        m_pUpdatePool->push_front(child);
                        m_pChildPool->pop_back();                            
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

void CocoListView::getAndCallback()
{
    CocoWidget* child = getChildFromUpdatePool();
    
    if (child == NULL)
    {
        return;
    }
    
    switch (m_eDirection)
    {
        case SCROLLVIEW_DIR_VERTICAL: // vertical
            switch (m_eMoveDirection)
            {
                case SCROLLVIEW_MOVE_DIR_UP: // up
                    ++m_nEnd;
                    setUpdateChild(child);
                    setUpdateDataIndex(m_nEnd);
                    updateChildEvent();
                    
                    if (m_bUpdateSuccess == false)
                    {
                        --m_nEnd;
                        m_pChildPool->push_front(child);
                        return;
                    }
                    ++m_nBegin;
                    break;
                    
                case SCROLLVIEW_MOVE_DIR_DOWN: // down
                    --m_nBegin;
                    setUpdateChild(child);
                    setUpdateDataIndex(m_nBegin);
                    updateChildEvent();
                    
                    if (m_bUpdateSuccess == false)
                    {
                        ++m_nBegin;
                        m_pChildPool->push_back(child);
                        return;
                    }
                    --m_nEnd;
                    break;
                    
                default:
                    break;
            }
            break;
            
        case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
            switch (m_eMoveDirection)
            {
                case SCROLLVIEW_MOVE_DIR_LEFT: // left
                    ++m_nEnd;
                    setUpdateChild(child);
                    setUpdateDataIndex(m_nEnd);
                    updateChildEvent();
                    
                    if (m_bUpdateSuccess == false)
                    {
                        --m_nEnd;
                        m_pChildPool->push_front(child);
                        return;
                    }
                    ++m_nBegin;
                    break;
                    
                case SCROLLVIEW_MOVE_DIR_RIGHT: // right
                    --m_nBegin;
                    setUpdateChild(child);
                    setUpdateDataIndex(m_nBegin);
                    updateChildEvent();
                    
                    if (m_bUpdateSuccess == false)
                    {
                        ++m_nBegin;
                        m_pChildPool->push_back(child);
                        return;
                    }
                    --m_nEnd;
                    break;
                    
                default:
                    break;
            }
            break;
            
        default:
            break;
    }
    
    switch (m_eDirection)
    {
        case SCROLLVIEW_DIR_VERTICAL: // vertical
            switch (m_eMoveDirection)
            {
                case SCROLLVIEW_MOVE_DIR_UP: // up
                    m_pChildPool->push_back(child);
                    break;
                    
                case SCROLLVIEW_MOVE_DIR_DOWN: // down
                    m_pChildPool->push_front(child);
                    break;
            }
            break;
            
        case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
            switch (m_eMoveDirection)
            {
                case SCROLLVIEW_MOVE_DIR_LEFT: // left
                    m_pChildPool->push_back(child);
                    break;
                    
                case SCROLLVIEW_MOVE_DIR_RIGHT: // right
                    m_pChildPool->push_front(child);
                    break;
                    
                default:
                    break;
            }
            break;
            
        default:
            break;
    }
}

int CocoListView::getDataLength()
{
    return m_nDataLength;
}        

CocoWidget* CocoListView::getUpdateChild()
{
    return m_pUpdateChild;
}

void CocoListView::setUpdateChild(CocoWidget* child)
{
    m_pUpdateChild = child;
}

int CocoListView::getUpdateDataIndex()
{
    return m_nUpdateDataIndex;
}

void CocoListView::setUpdateDataIndex(int index)
{
    m_nUpdateDataIndex = index;
}

bool CocoListView::getUpdateSuccess()
{
    return m_bUpdateSuccess;
}

void CocoListView::setUpdateSuccess(bool sucess)
{
    m_bUpdateSuccess = sucess;
}

void CocoListView::collectOverTopChild()
{
    float scroll_top = m_fTopBoundary;
    
    if (m_overTopArray->count() > 0)
    {
        m_overTopArray->removeAllObjects();
    }
    
    int times = m_children->count();
    for (int i = 0; i < times; ++i)
    {
        CocoWidget* child = dynamic_cast<CocoWidget*>(m_children->objectAtIndex(i));
        float child_bottom = child->getRelativeBottomPos();
        
        if (child_bottom >= scroll_top)
        {
            m_overTopArray->addObject(child);                
        }
    }
}

void CocoListView::collectOverBottomChild()
{
    float scroll_bottom = m_fBottomBoundary;
    
    if (m_overBottomArray->count() > 0)
    {
        m_overBottomArray->removeAllObjects();
    }
    
    int times = m_children->count();
    for (int i = 0; i < times; ++i)
    {
        CocoWidget* child = dynamic_cast<CocoWidget*>(m_children->objectAtIndex(i));
        float child_top = child->getRelativeTopPos();
        
        if (child_top <= scroll_bottom)
        {
            m_overBottomArray->addObject(child);                
        }
    }
}

void CocoListView::collectOverLeftChild()
{
    float scroll_left = m_fLeftBoundary;
    
    if (m_overLeftArray->count() > 0)
    {
        m_overLeftArray->removeAllObjects();
    }
    
    int times = m_children->count();
    for (int i = 0; i < times; ++i)
    {
        CocoWidget* child = dynamic_cast<CocoWidget*>(m_children->objectAtIndex(i));
        float child_right = child->getRelativeRightPos();
        
        if (child_right <= scroll_left)
        {
            m_overLeftArray->addObject(child);                
        }
    }
}

void CocoListView::collectOverRightChild()
{
    float scroll_right = m_fRightBoundary;
    
    if (m_overRightArray->count() > 0)
    {
        m_overRightArray->removeAllObjects();
    }
    
    int times = m_children->count();
    for (int i = 0; i < times; ++i)
    {
        CocoWidget* child = dynamic_cast<CocoWidget*>(m_children->objectAtIndex(i));
        float child_left = child->getRelativeLeftPos();
        
        if (child_left >= scroll_right)
        {
            m_overRightArray->addObject(child);                
        }
    }
}

void CocoListView::setLoopPosition()
{
    switch (m_eDirection)
    {
        case SCROLLVIEW_DIR_VERTICAL: // vertical
            switch (m_eMoveDirection)
            {
                case SCROLLVIEW_MOVE_DIR_UP: // up
                    if (m_overTopArray->count() == m_children->count())
                    {
                        int count = m_overTopArray->count();
                        for (int i = 0; i < count; ++i)
                        {   
                            CocoWidget* child = dynamic_cast<CocoWidget*>(m_overTopArray->objectAtIndex(i));
                            
                            if (i == 0)
                            {
                                float y = (0 - m_fDisBetweenChild) + m_fDisBetweenChild * (count - 1);
                                child->setPosition(ccp(child->getPosition().x, y));
                            }
                            else
                            {
                                CocoWidget* prev_child = dynamic_cast<CocoWidget*>(m_overTopArray->objectAtIndex(i - 1));
                                child->setPosition(ccp(child->getPosition().x, prev_child->getPosition().y - m_fDisBetweenChild));
                            }
                        }
                    }
                    else
                    {
                        float scroll_top = m_fTopBoundary;
                        
                        int count = m_children->count();
                        for (int i = 0; i < count; ++i)
                        {
                            CocoWidget* child = dynamic_cast<CocoWidget*>(m_children->objectAtIndex(i));
                            float child_bottom = child->getRelativeBottomPos();
                            
                            if (child_bottom >= scroll_top)
                            {
                                int index = (i == 0) ? (count - 1) : (i - 1);
                                CocoWidget* prev_child = dynamic_cast<CocoWidget*>(m_children->objectAtIndex(index));
                                child->setPosition(ccp(child->getPosition().x, prev_child->getPosition().y - m_fDisBetweenChild));
                            }
                        }
                    }
                    break;
                    
                case SCROLLVIEW_MOVE_DIR_DOWN: // down
                    if (m_overBottomArray->count() == m_children->count())
                    {
                        int count = m_overBottomArray->count();
                        for (int i = 0; i < count; ++i)
                        {
                            CocoWidget* child = dynamic_cast<CocoWidget*>(m_overBottomArray->objectAtIndex(i));
                            
                            if (i == 0)
                            {
                                float y = (m_fTopBoundary) - m_fDisBetweenChild * (count - 1);
                                child->setPosition(ccp(child->getPosition().x, y));
                            }
                            else
                            {
                                CocoWidget* prev_child = dynamic_cast<CocoWidget*>(m_overBottomArray->objectAtIndex(i - 1));
                                child->setPosition(ccp(child->getPosition().x, prev_child->getPosition().y + m_fDisBetweenChild));                                    
                            }
                        }
                    }
                    else
                    {
                        float scroll_bottom = m_fBottomBoundary;
                        
                        int count = m_children->count();
                        for (int i = count - 1; i >= 0; --i)
                        {
                            CocoWidget* child = dynamic_cast<CocoWidget*>(m_children->objectAtIndex(i));
                            float child_top = child->getRelativeTopPos();
                            
                            if (child_top <= scroll_bottom)
                            {
                                int index = (i == count - 1) ? 0 : (i + 1);
                                CocoWidget* next_child = dynamic_cast<CocoWidget*>(m_children->objectAtIndex(index));
                                child->setPosition(ccp(child->getPosition().x, next_child->getPosition().y + m_fDisBetweenChild));                                    
                            }
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
                    if (m_overLeftArray->count() == m_children->count())
                    {
                        int count = m_overLeftArray->count();
                        for (int i = 0; i < count; ++i)
                        {
                            CocoWidget* child = dynamic_cast<CocoWidget*>(m_overLeftArray->objectAtIndex(i));
                            
                            if (i == 0)
                            {
                                float x = (m_fRightBoundary + m_fDisBetweenChild) - m_fDisBetweenChild * (count - 1);
                                child->setPosition(ccp(x, child->getPosition().y));
                            }
                            else
                            {
                                CocoWidget* prev_child = dynamic_cast<CocoWidget*>(m_overLeftArray->objectAtIndex(i - 1));
                                child->setPosition(ccp(prev_child->getPosition().x + m_fDisBetweenChild, child->getPosition().y));                                    
                            }
                        }
                    }
                    else
                    {
                        float scroll_left = m_fLeftBoundary;
                        
                        int count = m_children->count();
                        for (int i = 0; i < count; ++i)
                        {
                            CocoWidget* child = dynamic_cast<CocoWidget*>(m_children->objectAtIndex(i));
                            float child_right = child->getRelativeRightPos();
                            
                            if (child_right <= scroll_left)
                            {
                                int index = (i == 0) ? (count - 1) : (i - 1);
                                CocoWidget* prev_child = dynamic_cast<CocoWidget*>(m_children->objectAtIndex(index));
                                child->setPosition(ccp(prev_child->getPosition().x + m_fDisBetweenChild, child->getPosition().y));
                            }
                        }
                    }
                    break;
                    
                case SCROLLVIEW_MOVE_DIR_RIGHT: // right
                    if (m_overRightArray->count() == m_children->count())
                    {
                        int count = m_overRightArray->count();
                        for (int i = 0; i < count; ++i)
                        {
                            CocoWidget* child = dynamic_cast<CocoWidget*>(m_overRightArray->objectAtIndex(i));
                            
                            if (i == 0)
                            {
                                float x = (0 - m_fDisBetweenChild) + m_fDisBetweenChild * (count - 1);
                                child->setPosition(ccp(x, child->getPosition().y));
                            }
                            else
                            {
                                CocoWidget* prev_child = dynamic_cast<CocoWidget*>(m_overRightArray->objectAtIndex(i - 1));
                                child->setPosition(ccp(prev_child->getPosition().x - m_fDisBetweenChild, child->getPosition().y));                                    
                            }
                        }
                    }
                    else
                    {
                        float scroll_right = m_fRightBoundary;
                        
                        int count = m_children->count();
                        for (int i = count - 1; i >= 0; --i)
                        {
                            CocoWidget* child = dynamic_cast<CocoWidget*>(m_children->objectAtIndex(i));
                            float child_left = child->getRelativeLeftPos();
                            
                            if (child_left >= scroll_right)
                            {
                                int index = (i == count - 1) ? 0 : (i + 1);
                                CocoWidget* next_child = dynamic_cast<CocoWidget*>(m_children->objectAtIndex(index));
                                child->setPosition(ccp(next_child->getPosition().x - m_fDisBetweenChild, child->getPosition().y));
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

void CocoListView::updateChild()
{
    switch (m_eDirection)
    {
        case SCROLLVIEW_DIR_VERTICAL: // vertical
            switch (m_eMoveDirection)
            {
                case SCROLLVIEW_MOVE_DIR_UP: // up
                    {
                        int count = m_overTopArray->count();
                        for (int i = 0; i < count; ++i)
                        {
                            if (m_nEnd < m_nDataLength - 1)
                            {
                                pushChildToPool();
                                getAndCallback();
                            }
                        }                            
                    }
                    break;
                    
                case SCROLLVIEW_MOVE_DIR_DOWN: // down
                    {
                        int count = m_overBottomArray->count();
                        for (int i = 0; i < count; ++i)
                        {
                            if (m_nBegin > 0)
                            {
                                pushChildToPool();
                                getAndCallback();                                        
                            }
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
                        int count = m_overLeftArray->count();
                        for (int i = 0; i < count; ++i)
                        {
                            if (m_nEnd < m_nDataLength - 1)
                            {
                                pushChildToPool();
                                getAndCallback();
                            }
                        }
                    }
                    break;
                    
                case SCROLLVIEW_MOVE_DIR_RIGHT: // right
                    {
                        int count = m_overBottomArray->count();
                        for (int i = 0; i < count; ++i)
                        {
                            if (m_nBegin > 0)
                            {
                                pushChildToPool();
                                getAndCallback();
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

void CocoListView::initChildEvent()
{
    if (m_pInitChildListener && m_pfnInitChildSelector)
    {
        (m_pInitChildListener->*m_pfnInitChildSelector)(this);
    }
}

void CocoListView::updateChildEvent()
{
    if (m_pUpdateChildListener && m_pfnUpdateChildSelector)
    {
        (m_pUpdateChildListener->*m_pfnUpdateChildSelector)(this);
    }
}

void CocoListView::addInitChildEvent(cocos2d::CCObject *target, SEL_InitChildEvent seletor)
{
    m_pInitChildListener = target;
    m_pfnInitChildSelector = seletor;
}

void CocoListView::addUpdateChildEvent(cocos2d::CCObject *target, SEL_UpdateChildEvent selector)
{
    m_pUpdateChildListener = target;
    m_pfnUpdateChildSelector = selector;
}

NS_CC_EXT_END