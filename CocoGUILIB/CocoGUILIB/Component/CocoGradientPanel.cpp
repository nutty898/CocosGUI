//
//  CocoGradientPanel.cpp
//  Test
//
//  Created by cai wenzhi on 13-6-18.
//
//

#include "CocoGradientPanel.h"
#include "CClipAbleLayerGradient.h"

namespace cs {
    CocoGradientPanel::CocoGradientPanel()
    {
        m_renderType = RENDER_TYPE_LAYERGRADIENT;
    }
    
    CocoGradientPanel* CocoGradientPanel::create()
    {
        CocoGradientPanel* widget = new CocoGradientPanel();
        if (widget && widget->init()) {
            return widget;
        }
        CC_SAFE_DELETE(widget);
        return NULL;
    }
    
    CocoGradientPanel::~CocoGradientPanel()
    {
        
    }
    
    void CocoGradientPanel::initNodes()
    {
        this->m_pCCRenderNode = CClipAbleLayerGradient::create();
    }
    
    void CocoGradientPanel::setStartColor(const cocos2d::ccColor3B &color)
    {
        DYNAMIC_CAST_CLIPLAYERGRADIENT->setStartColor(color);
    }
    
    void CocoGradientPanel::setEndColor(const cocos2d::ccColor3B &color)
    {
        DYNAMIC_CAST_CLIPLAYERGRADIENT->setEndColor(color);
    }
    
    void CocoGradientPanel::setBackGroundColorEnable(bool able)
    {
        DYNAMIC_CAST_CLIPLAYERGRADIENT->setColorEnable(able);
    }
    
    void CocoGradientPanel::setStartOpacity(int opacity)
    {
        DYNAMIC_CAST_CLIPLAYERGRADIENT->setStartOpacity(opacity);
    }
    
    void CocoGradientPanel::setEndOpacity(int opacity)
    {
        DYNAMIC_CAST_CLIPLAYERGRADIENT->setEndOpacity(opacity);
    }
}