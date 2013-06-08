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
