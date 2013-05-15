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

#include "CocoButton.h"
#include "DictionaryHelper.h"

namespace cs {
    
    CocoButton::CocoButton():
    m_pButtonNormal(NULL),
    m_pButtonClicked(NULL),
    m_pButtonDisable(NULL),
    m_bScale9Enable(false)
    {
        

    }
    
    CocoButton::~CocoButton()
    {
        
    }
    
    CocoButton* CocoButton::create()
    {
//        return CocoButton::create(NULL);
        CocoButton* widget = new CocoButton();
        if (widget && widget->init()) {
            return widget;
        }
        CC_SAFE_DELETE(widget);
        return NULL;
    }
    
    bool CocoButton::init()
    {
        if (CocoWidget::init()) {
            if (this->m_bScale9Enable) {
                this->m_pButtonNormal = new UIScale9Sprite();
                this->m_pButtonNormal->init();
                this->m_pButtonClicked = new UIScale9Sprite();
                this->m_pButtonClicked->init();
                this->m_pButtonDisable = new UIScale9Sprite();
                this->m_pButtonDisable->init();
            }else{
                this->m_pButtonNormal = new UISprite();
                this->m_pButtonNormal->init();
                this->m_pButtonClicked = new UISprite();
                this->m_pButtonClicked->init();
                this->m_pButtonDisable = new UISprite();
                this->m_pButtonDisable->init();
            }
            
            this->addUIElement(m_pButtonNormal);
            this->addUIElement(m_pButtonClicked);
            this->addUIElement(m_pButtonDisable);
            this->initPressState(0);
            return true;
        }
        return false;
    }
    
    void CocoButton::initPressState(int state)
    {
        CocoWidget::initPressState(state);
        
        this->m_pButtonNormal->setVisible(true);
        this->m_pButtonClicked->setVisible(false);
        this->m_pButtonDisable->setVisible(false);
    }
    
    void CocoButton::setScale9Enable(bool able)
    {
        if (this->m_bScale9Enable == able) {
            return;
        }
        this->m_nPrevPressstate = -1;
        this->m_nCurPressState = -1;
        this->m_bScale9Enable = able;
        this->removeAllUIElementsAndCleanUp(true);
        this->m_pButtonNormal = NULL;
        this->m_pButtonClicked = NULL;
        this->m_pButtonDisable = NULL;
        if (this->m_bScale9Enable) {
            this->m_pButtonNormal = new UIScale9Sprite();
            this->m_pButtonNormal->init();
            this->m_pButtonClicked = new UIScale9Sprite();
            this->m_pButtonClicked->init();
            this->m_pButtonDisable = new UIScale9Sprite();
            this->m_pButtonDisable->init();
        }else{
            this->m_pButtonNormal = new UISprite();
            this->m_pButtonNormal->init();
            this->m_pButtonClicked = new UISprite();
            this->m_pButtonClicked->init();
            this->m_pButtonDisable = new UISprite();
            this->m_pButtonDisable->init();
        }
        this->addUIElement(m_pButtonNormal);
        this->addUIElement(m_pButtonClicked);
        this->addUIElement(m_pButtonDisable);
        this->initPressState(0);
    }
    
    void CocoButton::setScale9Size(float width, float height)
    {
        if (!this->m_bScale9Enable) {
            return;
        }
        ((UIScale9Sprite*)(this->m_pButtonNormal))->setScaleSize(width,height);
        ((UIScale9Sprite*)(this->m_pButtonClicked))->setScaleSize(width,height);
        ((UIScale9Sprite*)(this->m_pButtonDisable))->setScaleSize(width,height);
    }
    
    void CocoButton::setTextures(const char* normal,const char* selected,const char* disabled,bool useSpriteFrame)
    {
        this->setNormalTexture(normal,useSpriteFrame);
        this->setPressedTexture(selected,useSpriteFrame);
        this->setDisabledTexture(disabled,useSpriteFrame);
    }
    
    void CocoButton::setTexturesScale9(const char *normal, const char *selected, const char *disabled, cocos2d::CCRect capInsets,bool useSpriteFrame)
    {
        this->setNormalTextureScale9(normal, capInsets,useSpriteFrame);
        this->setPressedTextureScale9(selected, capInsets,useSpriteFrame);
        this->setDisabledTextureScale9(disabled, capInsets,useSpriteFrame);
    }
    
    void CocoButton::setNormalTexture(const char* normal,bool useSpriteFrame)
    {
        ((UISprite*)(this->m_pButtonNormal))->loadTexture(normal,useSpriteFrame);
        this->updateAnchorPoint();
    }
    
    void CocoButton::setPressedTexture(const char* selected,bool useSpriteFrame)
    {
        ((UISprite*)(this->m_pButtonClicked))->loadTexture(selected,useSpriteFrame);
        this->updateAnchorPoint();
    }
    
    void CocoButton::setDisabledTexture(const char* disabled,bool useSpriteFrame)
    {
        ((UISprite*)(this->m_pButtonDisable))->loadTexture(disabled,useSpriteFrame);
        this->updateAnchorPoint();
    }
    
    void CocoButton::setNormalTextureScale9(const char* normal,cocos2d::CCRect capInsets,bool useSpriteFrame)
    {
        ((UIScale9Sprite*)(this->m_pButtonNormal))->loadTexture(normal,capInsets.origin.x,capInsets.origin.y,capInsets.size.width,capInsets.size.height,useSpriteFrame);
        this->updateAnchorPoint();
    }
    
    void CocoButton::setPressedTextureScale9(const char* selected,cocos2d::CCRect capInsets,bool useSpriteFrame)
    {
        ((UIScale9Sprite*)(this->m_pButtonClicked))->loadTexture(selected,capInsets.origin.x,capInsets.origin.y,capInsets.size.width,capInsets.size.height,useSpriteFrame);
        this->updateAnchorPoint();
    }
    
    void CocoButton::setDisabledTextureScale9(const char* disabled,cocos2d::CCRect capInsets,bool useSpriteFrame)
    {
        ((UIScale9Sprite*)(this->m_pButtonDisable))->loadTexture(disabled,capInsets.origin.x,capInsets.origin.y,capInsets.size.width,capInsets.size.height,useSpriteFrame);
        this->updateAnchorPoint();
    }
    
    void CocoButton::onPressStateChangedToNormal()
    {
        this->m_pButtonNormal->setVisible(true);
        this->m_pButtonClicked->setVisible(false);
        this->m_pButtonDisable->setVisible(false);
    }
    
    void CocoButton::onPressStateChangedToPressed()
    {
        this->m_pButtonNormal->setVisible(false);
        this->m_pButtonClicked->setVisible(true);
        this->m_pButtonDisable->setVisible(false);
    }
    
    void CocoButton::onPressStateChangedToDisabled()
    {
        this->m_pButtonNormal->setVisible(false);
        this->m_pButtonClicked->setVisible(false);
        this->m_pButtonDisable->setVisible(true);
    }
    
    CRenderNode* CocoButton::getValidNode()
    {
        CRenderNode* res = NULL;
        switch (this->m_nCurPressState) {
            case 0:
                res = this->m_pButtonNormal->getCRenderNode();
                break;
            case 1:
                res = this->m_pButtonClicked->getCRenderNode();
                break;
            case 2:
                res = this->m_pButtonDisable->getCRenderNode();
                break;
            default:
                break;
        }
        return res;
    }
    
    void CocoButton::setColor(int r, int g, int b)
    {
        this->m_pButtonNormal->setColor(r, g, b);
        this->m_pButtonClicked->setColor(r, g, b);
        this->m_pButtonDisable->setColor(r, g, b);
    }

    void CocoButton::setOpacity(int opcity)
    {
        this->m_pButtonNormal->setOpacity(opcity);
        this->m_pButtonClicked->setOpacity(opcity);
        this->m_pButtonDisable->setOpacity(opcity);
    }
    
    void CocoButton::setFlipX(bool flipX)
    {
        this->m_pButtonNormal->setFlipX(flipX);
        this->m_pButtonClicked->setFlipX(flipX);
        this->m_pButtonDisable->setFlipX(flipX);
    }
    
    void CocoButton::setFlipY(bool flipY)
    {
        this->m_pButtonNormal->setFlipY(flipY);
        this->m_pButtonClicked->setFlipY(flipY);
        this->m_pButtonDisable->setFlipY(flipY);
    }
    
    void CocoButton::setAnchorPoint(const cocos2d::CCPoint &pt)
    {
        CocoWidget::setAnchorPoint(pt);
        this->m_pButtonNormal->setAnchorPoint(pt);
        this->m_pButtonClicked->setAnchorPoint(pt);
        this->m_pButtonDisable->setAnchorPoint(pt);
        
    }
}