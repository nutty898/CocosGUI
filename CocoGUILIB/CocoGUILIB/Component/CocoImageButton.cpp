//
//  CocoImageButton.cpp
//  Test
//
//  Created by pipu on 13-5-14.
//
//

#include "CocoImageButton.h"
#include "GUIScale9Sprite.h"

namespace cs
{
    CocoImageButton::CocoImageButton() :
    m_pImageNormal(NULL),
    m_pImageClicked(NULL),
    m_pImageDisable(NULL),
    m_bScale9Enable(false)
    {
        
    }
    
    CocoImageButton::~CocoImageButton()
    {
        
    }
    
    CocoImageButton* CocoImageButton::create()
    {
        CocoImageButton* widget = new CocoImageButton();
        
        if (widget && widget->init())
        {
            return widget;
        }
        CC_SAFE_DELETE(widget);
        
        return NULL;
    }
    
    bool CocoImageButton::init()
    {
        if (CocoButton::init())
        {
            if (m_bScale9Enable)
            {
                m_pImageNormal = GUIScale9Sprite::create();
                m_pImageClicked = GUIScale9Sprite::create();
                m_pImageDisable = GUIScale9Sprite::create();
            }
            else
            {
                m_pImageNormal = cocos2d::CCSprite::create();
                m_pImageClicked = cocos2d::CCSprite::create();
                m_pImageDisable = cocos2d::CCSprite::create();
            }
            this->m_pCCRenderNode->addChild(m_pImageNormal);
            this->m_pCCRenderNode->addChild(m_pImageClicked);
            this->m_pCCRenderNode->addChild(m_pImageDisable);
            
            initPressState(0);
            return true;
        }
        
        return false;
    }
    
    void CocoImageButton::initPressState(int state)
    {
        CocoButton::initPressState(state);
        
        m_pImageNormal->setVisible(true);
        m_pImageClicked->setVisible(false);
        m_pImageDisable->setVisible(false);
    }
    
    void CocoImageButton::setImageScale9Enable(bool able)
    {
        if (m_bScale9Enable == able)
        {
            return;
        }
        m_bScale9Enable = able;
        this->m_pCCRenderNode->removeChild(m_pImageNormal, true);
        this->m_pCCRenderNode->removeChild(m_pImageClicked, true);
        this->m_pCCRenderNode->removeChild(m_pImageDisable, true);
        m_pImageNormal = NULL;
        m_pImageClicked = NULL;
        m_pImageDisable = NULL;
        
        if (m_bScale9Enable)
        {
            m_pImageNormal = GUIScale9Sprite::create();
            m_pImageClicked = GUIScale9Sprite::create();
            m_pImageDisable = GUIScale9Sprite::create();
        }
        else
        {
            m_pImageNormal = cocos2d::CCSprite::create();
            m_pImageClicked = cocos2d::CCSprite::create();
            m_pImageDisable = cocos2d::CCSprite::create();
        }
        this->m_pCCRenderNode->addChild(m_pImageNormal);
        this->m_pCCRenderNode->addChild(m_pImageClicked);
        this->m_pCCRenderNode->addChild(m_pImageDisable);
        
        m_pImageNormal->setVisible(true);
        m_pImageClicked->setVisible(false);
        m_pImageDisable->setVisible(false);
    }
    
    void CocoImageButton::setImageScale9Size(float width, float height)
    {
        if (!m_bScale9Enable)
        {
            return;
        }
        
//        dynamic_cast<UIScale9Sprite*>(m_pImageNormal)->setScaleSize(width, height);
//        dynamic_cast<UIScale9Sprite*>(m_pImageClicked)->setScaleSize(width, height);
//        dynamic_cast<UIScale9Sprite*>(m_pImageDisable)->setScaleSize(width, height);
    }
    
    void CocoImageButton::setImageTextures(const char *normal, const char *selected, const char *disabled, bool useSpriteFrame)
    {
        setImageNormalTexture(normal, useSpriteFrame);
        setImagePressedTexture(selected, useSpriteFrame);
        setImageDisabledTexture(disabled, useSpriteFrame);
    }
    
    void CocoImageButton::setImageTexturesScale9(const char *normal, const char *selected, const char *disabled, cocos2d::CCRect capInsets, bool useSpriteFrame)
    {
        setImageNormalTextureScale9(normal, capInsets, useSpriteFrame);
        setImagePressedTextureScale9(selected, capInsets, useSpriteFrame);
        setImageDisabledTextureScale9(disabled, capInsets, useSpriteFrame);
    }
    
    void CocoImageButton::setImageNormalTexture(const char *normal, bool useSpriteFrame)
    {
//        dynamic_cast<UISprite*>(m_pImageNormal)->loadTexture(normal, useSpriteFrame);
    }
    
    void CocoImageButton::setImagePressedTexture(const char *selected, bool useSpriteFrame)
    {
//        dynamic_cast<UISprite*>(m_pImageClicked)->loadTexture(selected, useSpriteFrame);
    }
    
    void CocoImageButton::setImageDisabledTexture(const char *disabled, bool useSpriteFrame)
    {
//        dynamic_cast<UISprite*>(m_pImageDisable)->loadTexture(disabled, useSpriteFrame);
    }
    
    void CocoImageButton::setImageNormalTextureScale9(const char *normal, cocos2d::CCRect capInsets, bool useSpriteFrame)
    {
//        dynamic_cast<UIScale9Sprite*>(m_pImageNormal)->loadTexture(normal, capInsets.origin.x, capInsets.origin.y, capInsets.size.width, capInsets.size.height, useSpriteFrame);
    }
    
    void CocoImageButton::setImagePressedTextureScale9(const char *selected, cocos2d::CCRect capInsets, bool useSpriteFrame)
    {
//        dynamic_cast<UIScale9Sprite*>(m_pImageClicked)->loadTexture(selected, capInsets.origin.x, capInsets.origin.y, capInsets.size.width, capInsets.size.height, useSpriteFrame);
    }
    
    void CocoImageButton::setImageDisabledTextureScale9(const char *disabled, cocos2d::CCRect capInsets, bool useSpriteFrame)
    {
//        dynamic_cast<UIScale9Sprite*>(m_pImageDisable)->loadTexture(disabled, capInsets.origin.x, capInsets.origin.y, capInsets.size.width, capInsets.size.height, useSpriteFrame);
    }
    
    void CocoImageButton::setImageColor(GLubyte r, GLubyte g, GLubyte b)
    {
//        m_pImageNormal->setColor(cocos2d::ccc3(r, g, b));
//        m_pImageClicked->setColor(r, g, b);
//        m_pImageClicked->setColor(r, g, b);
    }
    
    void CocoImageButton::setImageOpacity(GLubyte opacity)
    {
//        m_pImageNormal->setOpacity(opacity);
//        m_pImageClicked->setOpacity(opacity);
//        m_pImageDisable->setOpacity(opacity);
    }
    
    void CocoImageButton::setImageFlipX(bool flipX)
    {
//        m_pImageNormal->setFlipX(flipX);
//        m_pImageClicked->setFlipX(flipX);
//        m_pImageDisable->setFlipX(flipX);
    }
    
    void CocoImageButton::setImageFlipY(bool flipY)
    {
//        m_pImageNormal->setFlipY(flipY);
//        m_pImageClicked->setFlipY(flipY);
//        m_pImageDisable->setFlipY(flipY);
    }
    
    cocos2d::CCNode* CocoImageButton::getImageValidNode()
    {
        cocos2d::CCNode* res = NULL;
        
        switch (m_nCurPressState)
        {
            case 0:
                res = m_pImageNormal;
                break;
                
            case 1:
                res = m_pImageClicked;
                break;
                
            case 2:
                res = m_pImageDisable;
                break;
                
            default:
                break;
        }
        
        return res;
    }
    
    // override
    void CocoImageButton::setScale9Enable(bool able)
    {
        if (m_bScale9Enable == able)
        {
            return;
        }
        
        CocoButton::setScale9Enable(able);
        setImageScale9Enable(able);
    }
    
    void CocoImageButton::setScale9Size(float buttonWidth, float buttonHeight, float imageWidth, float imageHeight)
    {
        if (!m_bScale9Enable)
        {
            return;
        }
        
        CocoButton::setScale9Size(buttonWidth, buttonHeight);
        setImageScale9Size(imageWidth, imageHeight);
    }
    
    void CocoImageButton::setTextures(const char *buttonNormal, const char *buttonSelected, const char *buttonDisabled,
                                      const char* imageNormal, const char* imageSelected, const char* imageDisabled,
                                      bool useSpriteFrame)
    {
        CocoButton::setTextures(buttonNormal, buttonSelected, buttonDisabled, useSpriteFrame);
        setImageTextures(imageNormal, imageSelected, imageDisabled, useSpriteFrame);
    }
    
    void CocoImageButton::setTexturesScale9(const char* buttonNormal, const char* buttonSelected, const char* buttonDisabled,
                                            const char* imageNormal, const char* imageSelected, const char* imageDisabled,
                                            cocos2d::CCRect buttonCapInsets, cocos2d::CCRect imageCapInsets,
                                            bool useSpriteFrame)
    {
        CocoButton::setTexturesScale9(buttonNormal, buttonSelected, buttonDisabled, buttonCapInsets, useSpriteFrame);
        
        setImageTexturesScale9(imageNormal, imageSelected, imageDisabled, imageCapInsets, useSpriteFrame);
    }
    
    void CocoImageButton::setColor(GLubyte buttonR, GLubyte buttonG, GLubyte buttonB,
                                   GLubyte imageR, GLubyte imageG, GLubyte imageB)
    {
//        CocoButton::setColor(buttonR, buttonG, buttonB);
        setImageColor(imageR, imageG, imageB);
    }
    
    void CocoImageButton::setOpacity(GLubyte buttonOpacity, GLubyte imageOpacity)
    {
        CocoButton::setOpacity(buttonOpacity);
        setImageOpacity(imageOpacity);
    }
    
    void CocoImageButton::setFlipX(bool buttonFlipX, bool imageFlipX)
    {
        CocoButton::setFlipX(buttonFlipX);
        setImageFlipX(imageFlipX);
    }
    
    void CocoImageButton::setFlipY(bool buttonFlipY, bool imageFlipY)
    {
        CocoButton::setFlipY(buttonFlipY);
        setImageFlipY(imageFlipY);
    }
    
    void CocoImageButton::onPressStateChangedToNormal()
    {
        CocoButton::onPressStateChangedToNormal();
        
        m_pImageNormal->setVisible(true);
        m_pImageClicked->setVisible(false);
        m_pImageDisable->setVisible(false);
    }
    
    void CocoImageButton::onPressStateChangedToPressed()
    {
        CocoButton::onPressStateChangedToPressed();
        
        m_pImageNormal->setVisible(false);
        m_pImageClicked->setVisible(true);
        m_pImageDisable->setVisible(false);
    }
    
    void CocoImageButton::onPressStateChangedToDisabled()
    {
        CocoButton::onPressStateChangedToDisabled();
        
        m_pImageNormal->setVisible(false);
        m_pImageNormal->setVisible(false);
        m_pImageNormal->setVisible(true);
    }
}