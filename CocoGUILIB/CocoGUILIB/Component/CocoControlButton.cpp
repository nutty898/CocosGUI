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
    
    void CocoControlButton::initNodes()
    {
        this->m_pTitle = cocos2d::CCLabelTTF::create();
        this->m_pBackGround = cocos2d::extension::CCScale9Sprite::create();
        this->m_pCCRenderNode->addChild(this->m_pBackGround);
        this->m_pCCRenderNode->addChild(m_pTitle);
    }
    
    void CocoControlButton::setTexture(const char* background)
    {
        this->m_pBackGround->initWithFile(background);
        m_pBackGround->setContentSize(cocos2d::CCSize(this->m_pTitle->boundingBox().size.width+8*2,this->m_pTitle->boundingBox().size.height+2*2));
    }
    
    void CocoControlButton::setTitle(const char* title)
    {
        this->m_pTitle->setString(title);
        m_pBackGround->setContentSize(cocos2d::CCSize(this->m_pTitle->boundingBox().size.width+8*2,this->m_pTitle->boundingBox().size.height+2*2));
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
    
    cocos2d::CCNode* CocoControlButton::getValidNode()
    {
        return this->m_pBackGround;
    }
    
    void CocoControlButton::setAnchorPoint(const cocos2d::CCPoint &pt)
    {
        CocoWidget::setAnchorPoint(pt);
        this->m_pBackGround->setAnchorPoint(pt);
        this->m_pTitle->setPosition(ccp(this->m_pBackGround->getContentSize().width*(0.5f-this->m_pBackGround->getAnchorPoint().x), this->m_pBackGround->getContentSize().height*(0.5f-this->m_pBackGround->getAnchorPoint().y)));
    }
    
    void CocoControlButton::setFlipX(bool flipX)
    {
        this->m_pTitle->setFlipX(flipX);
    }
    
    void CocoControlButton::setFlipY(bool flipY)
    {
        this->m_pTitle->setFlipY(flipY);
    }
}

