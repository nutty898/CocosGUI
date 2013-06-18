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
#include "GUIScale9Sprite.h"
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
            
            this->initPressState(0);
            return true;
        }
        return false;
    }
    
    void CocoButton::initNodes()
    {
        CocoWidget::initNodes();
        if (this->m_bScale9Enable) {
            this->m_pButtonNormal = GUIScale9Sprite::create();
            this->m_pButtonClicked = GUIScale9Sprite::create();
            this->m_pButtonDisable = GUIScale9Sprite::create();
        }else{
            this->m_pButtonNormal = cocos2d::CCSprite::create();
            this->m_pButtonClicked = cocos2d::CCSprite::create();
            this->m_pButtonDisable = cocos2d::CCSprite::create();
        }
        this->m_pCCRenderNode->addChild(this->m_pButtonNormal);
        this->m_pCCRenderNode->addChild(this->m_pButtonClicked);
        this->m_pCCRenderNode->addChild(this->m_pButtonDisable);
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
        
        this->m_pCCRenderNode->removeChild(this->m_pButtonNormal, true);
        this->m_pCCRenderNode->removeChild(this->m_pButtonClicked, true);
        this->m_pCCRenderNode->removeChild(this->m_pButtonDisable, true);
        
        this->m_pButtonNormal = NULL;
        this->m_pButtonClicked = NULL;
        this->m_pButtonDisable = NULL;
        if (this->m_bScale9Enable) {
            this->m_pButtonNormal = GUIScale9Sprite::create();
            this->m_pButtonClicked = GUIScale9Sprite::create();
            this->m_pButtonDisable = GUIScale9Sprite::create();
        }else{
            this->m_pButtonNormal = cocos2d::CCSprite::create();
            this->m_pButtonClicked = cocos2d::CCSprite::create();
            this->m_pButtonDisable = cocos2d::CCSprite::create();
        }
        this->m_pCCRenderNode->addChild(this->m_pButtonNormal);
        this->m_pCCRenderNode->addChild(this->m_pButtonClicked);
        this->m_pCCRenderNode->addChild(this->m_pButtonDisable);
        this->initPressState(0);
    }
    
    void CocoButton::setScale9Size(float width, float height)
    {
        if (!this->m_bScale9Enable) {
            return;
        }
        cocos2d::CCSize size = cocos2d::CCSize(width,height);
        dynamic_cast<GUIScale9Sprite*>(this->m_pButtonNormal)->setContentSize(size);
        dynamic_cast<GUIScale9Sprite*>(this->m_pButtonClicked)->setContentSize(size);
        dynamic_cast<GUIScale9Sprite*>(this->m_pButtonDisable)->setContentSize(size);
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
        if (!normal || strcmp(normal, "") == 0) {
            return;
        }
        if (useSpriteFrame) {
            dynamic_cast<cocos2d::CCSprite*>(this->m_pButtonNormal)->initWithSpriteFrameName(normal);
        }else{
            dynamic_cast<cocos2d::CCSprite*>(this->m_pButtonNormal)->initWithFile(normal);
        }
        this->updateAnchorPoint();
    }
    
    void CocoButton::setPressedTexture(const char* selected,bool useSpriteFrame)
    {
        if (!selected || strcmp(selected, "") == 0) {
            return;
        }
        if (useSpriteFrame) {
            dynamic_cast<cocos2d::CCSprite*>(this->m_pButtonClicked)->initWithSpriteFrameName(selected);
        }else{
            dynamic_cast<cocos2d::CCSprite*>(this->m_pButtonClicked)->initWithFile(selected);
        }
        this->updateAnchorPoint();
    }
    
    void CocoButton::setDisabledTexture(const char* disabled,bool useSpriteFrame)
    {
        if (!disabled || strcmp(disabled, "") == 0) {
            return;
        }
        if (useSpriteFrame) {
            dynamic_cast<cocos2d::CCSprite*>(this->m_pButtonDisable)->initWithSpriteFrameName(disabled);
        }else{
            dynamic_cast<cocos2d::CCSprite*>(this->m_pButtonDisable)->initWithFile(disabled);
        }
        this->updateAnchorPoint();
    }
    
    void CocoButton::setNormalTextureScale9(const char* normal,cocos2d::CCRect capInsets,bool useSpriteFrame)
    {
        if (!normal || strcmp(normal, "") == 0) {
            return;
        }
        if (useSpriteFrame) {
            dynamic_cast<GUIScale9Sprite*>(this->m_pButtonNormal)->initWithSpriteFrameName(normal,capInsets);
        }else{
            dynamic_cast<GUIScale9Sprite*>(this->m_pButtonNormal)->initWithFile(normal,capInsets);
        }
        this->updateAnchorPoint();
    }
    
    void CocoButton::setPressedTextureScale9(const char* selected,cocos2d::CCRect capInsets,bool useSpriteFrame)
    {
        if (!selected || strcmp(selected, "") == 0) {
            return;
        }
        if (useSpriteFrame) {
            dynamic_cast<GUIScale9Sprite*>(this->m_pButtonClicked)->initWithSpriteFrameName(selected,capInsets);
        }else{
            dynamic_cast<GUIScale9Sprite*>(this->m_pButtonClicked)->initWithFile(selected,capInsets);
        }
        this->updateAnchorPoint();
    }
    
    void CocoButton::setDisabledTextureScale9(const char* disabled,cocos2d::CCRect capInsets,bool useSpriteFrame)
    {
        if (!disabled || strcmp(disabled, "") == 0) {
            return;
        }
        if (useSpriteFrame) {
            dynamic_cast<GUIScale9Sprite*>(this->m_pButtonDisable)->initWithSpriteFrameName(disabled,capInsets);
        }else{
            dynamic_cast<GUIScale9Sprite*>(this->m_pButtonDisable)->initWithFile(disabled,capInsets);
        }
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
    
    cocos2d::CCNode* CocoButton::getValidNode()
    {
        cocos2d::CCNode* res = NULL;
        switch (this->m_nCurPressState) {
            case 0:
                res = this->m_pButtonNormal;
                break;
            case 1:
                res = this->m_pButtonClicked;
                break;
            case 2:
                res = this->m_pButtonDisable;
                break;
            default:
                break;
        }
        return res;
    }
    
    void CocoButton::setFlipX(bool flipX)
    {
        dynamic_cast<cocos2d::CCSprite*>(this->m_pButtonNormal)->setFlipX(flipX);
        dynamic_cast<cocos2d::CCSprite*>(this->m_pButtonClicked)->setFlipX(flipX);
        dynamic_cast<cocos2d::CCSprite*>(this->m_pButtonDisable)->setFlipX(flipX);
    }
    
    void CocoButton::setFlipY(bool flipY)
    {
        dynamic_cast<cocos2d::CCSprite*>(this->m_pButtonNormal)->setFlipY(flipY);
        dynamic_cast<cocos2d::CCSprite*>(this->m_pButtonClicked)->setFlipY(flipY);
        dynamic_cast<cocos2d::CCSprite*>(this->m_pButtonDisable)->setFlipY(flipY);
    }
    
    void CocoButton::setAnchorPoint(const cocos2d::CCPoint &pt)
    {
        CocoWidget::setAnchorPoint(pt);
        this->m_pButtonNormal->setAnchorPoint(pt);
        this->m_pButtonClicked->setAnchorPoint(pt);
        this->m_pButtonDisable->setAnchorPoint(pt);
        
    }
    
    /* gui mark */
    void CocoButton::setNormalSpriteFrame(cocos2d::CCSpriteFrame *frame)
    {
        if (m_bScale9Enable)
        {
            dynamic_cast<GUIScale9Sprite*>(m_pButtonNormal)->setSpriteFrame(frame);
        }
        else
        {
            dynamic_cast<cocos2d::CCSprite*>(m_pButtonNormal)->setDisplayFrame(frame);
        }
    }
    
    void CocoButton::setPressedSpriteFrame(cocos2d::CCSpriteFrame *frame)
    {
        if (m_bScale9Enable)
        {
            dynamic_cast<GUIScale9Sprite*>(m_pButtonClicked)->setSpriteFrame(frame);
        }
        else
        {
            dynamic_cast<cocos2d::CCSprite*>(m_pButtonClicked)->setDisplayFrame(frame);
        }
    }
    
    void CocoButton::setDisabledSpriteFrame(cocos2d::CCSpriteFrame *frame)
    {
        if (m_bScale9Enable)
        {
            dynamic_cast<GUIScale9Sprite*>(m_pButtonDisable)->setSpriteFrame(frame);
        }
        else
        {
            dynamic_cast<cocos2d::CCSprite*>(m_pButtonDisable)->setDisplayFrame(frame);
        }
    }
    /**/
}