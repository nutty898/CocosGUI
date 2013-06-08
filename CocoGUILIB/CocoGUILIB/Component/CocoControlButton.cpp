//
//  CocoControlButton.cpp
//  Test
//
//  Created by cai wenzhi on 13-6-7.
//
//

#include "CocoControlButton.h"

namespace cs {
    CocoControlButton::CocoControlButton():
    m_pTitle(NULL),
    m_pBackGround(NULL)
    {
        
    }
    
    CocoControlButton::~CocoControlButton()
    {
        
    }
    
    CocoControlButton* CocoControlButton::create()
    {
        CocoControlButton* widget = new CocoControlButton();
        if (widget && widget->init()) {
            return widget;
        }
        CC_SAFE_DELETE(widget);
        return NULL;
    }
    
    bool CocoControlButton::init()
    {
        if (CocoWidget::init()) {
            this->m_pTitle = new UIText();
            this->m_pTitle->init();
            this->m_pBackGround = new UIScale9Sprite();
            this->m_pBackGround->init();
            this->addUIElement(this->m_pBackGround);
            this->addUIElement(m_pTitle);
            return true;
        }
        return false;
    }
    
    void CocoControlButton::setTexture(const char* background)
    {
        this->m_pBackGround->loadTexture(background, 0, 0, 0, 0, false);
        m_pBackGround->setScaleSize(this->m_pTitle->getCRenderNode()->getRenderNode()->boundingBox().size.width+8*2,this->m_pTitle->getCRenderNode()->getRenderNode()->boundingBox().size.height+2*2);
    }
    
    void CocoControlButton::setTitle(const char* title)
    {
        this->m_pTitle->setStringValue(title);
        m_pBackGround->setScaleSize(this->m_pTitle->getCRenderNode()->getRenderNode()->boundingBox().size.width+8*2,this->m_pTitle->getCRenderNode()->getRenderNode()->boundingBox().size.height+2*2);
    }
    
    void CocoControlButton::onPressStateChangedToNormal()
    {
        cocos2d::CCAction *zoomAction = cocos2d::CCScaleTo::create(0.05f, 1.0f);
        runAction(zoomAction);
    }
    
    void CocoControlButton::onPressStateChangedToPressed()
    {
        cocos2d::CCAction *zoomAction = cocos2d::CCScaleTo::create(0.05f, 1.1f);
        runAction(zoomAction);
    }
    
    void CocoControlButton::onPressStateChangedToDisabled()
    {
        
    }
    
    CRenderNode* CocoControlButton::getValidNode()
    {
        return this->m_pBackGround->getCRenderNode();
    }
    
    void CocoControlButton::setAnchorPoint(const cocos2d::CCPoint &pt)
    {
        
    }
    
    void CocoControlButton::setColor(int r,int g,int b)
    {
        
    }
    
    void CocoControlButton::setOpacity(int opcity)
    {
        
    }
    
    void CocoControlButton::setFlipX(bool flipX)
    {
        
    }
    
    void CocoControlButton::setFlipY(bool flipY)
    {
        
    }
}

