//
//  ObjectPool.h
//  Test
//
//  Created by pipu on 13-5-15.
//
//

#ifndef __Test__UIObjectPool__
#define __Test__UIObjectPool__

#include <iostream>
#include "cocos2d.h"
#include "CocoWidget.h"

namespace cs
{
    class UIWidgetPool
    {
    public:
        UIWidgetPool();
        ~UIWidgetPool();
        void push_back(CocoWidget* widget);
        void pop_back();
        void push_front(CocoWidget* widget);
        void pop_front();
        CocoWidget* begin();
        CocoWidget* rbegin();
        bool empty();
        int size();
        void clear();
        
    protected:
        cocos2d::CCArray* m_widgets;
    };
}

#endif /* defined(__Test__ObjectPool__) */
