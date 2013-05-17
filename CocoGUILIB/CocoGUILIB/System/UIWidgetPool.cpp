//
//  ObjectPool.cpp
//  Test
//
//  Created by pipu on 13-5-15.
//
//

#include "UIWidgetPool.h"

namespace cs
{
    UIWidgetPool::UIWidgetPool()
    {
        m_widgets = cocos2d::CCArray::create();
        m_widgets->retain();
    }
    
    UIWidgetPool::~UIWidgetPool()
    {
        m_widgets->release();
        delete m_widgets;
    }
    
    void UIWidgetPool::push_back(cs::CocoWidget *widget)
    {
        m_widgets->addObject(widget);
    }
    
    void UIWidgetPool::pop_back()
    {
        m_widgets->removeLastObject();
    }
    
    void UIWidgetPool::push_front(cs::CocoWidget *widget)
    {
        m_widgets->insertObject(widget, 0);
    }
    
    void UIWidgetPool::pop_front()
    {
        m_widgets->removeObjectAtIndex(0);
    }
    
    CocoWidget* UIWidgetPool::begin()
    {
        return dynamic_cast<CocoWidget*>(m_widgets->objectAtIndex(0));
    }
    
    CocoWidget* UIWidgetPool::rbegin()
    {
        return dynamic_cast<CocoWidget*>(m_widgets->lastObject());
    }
    
    bool UIWidgetPool::empty()
    {
        return m_widgets->count() == 0;
    }
    
    int UIWidgetPool::size()
    {
        return m_widgets->count();
    }
    
    void UIWidgetPool::clear()
    {
        m_widgets->removeAllObjects();
    }
}
