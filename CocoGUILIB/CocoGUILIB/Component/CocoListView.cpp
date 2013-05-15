//
//  CocoListView.cpp
//  Test
//
//  Created by pipu on 13-5-15.
//
//

#include "CocoListView.h"

namespace cs
{
    CocoListView::CocoListView() :
    m_pInitChildListener(NULL),
    m_pfnInitChildSelector(NULL),
    m_pUpdateChildListener(NULL),
    m_pfnUpdateChildSelector(NULL)
    {
        
    }
    
    CocoListView::~CocoListView()
    {
        
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
            return true;
        }
        return false;
    }
    
    bool CocoListView::addChild(CocoWidget* widget)
    {
        
        
        return true;
    }
}