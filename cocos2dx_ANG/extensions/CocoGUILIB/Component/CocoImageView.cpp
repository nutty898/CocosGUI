/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "CocoImageView.h"
#include "../System/UIHelper.h"
#include "CCScale9Sprite.h"

NS_CC_EXT_BEGIN

#define DYNAMIC_CAST_CCSPRITE dynamic_cast<cocos2d::CCSprite*>(this->m_pImageRender)
#define DYNAMIC_CAST_SCALE9SPRITE dynamic_cast<cocos2d::extension::CCScale9Sprite*>(this->m_pImageRender)

CocoImageView::CocoImageView():
m_nViewType(1),
m_nClickCount(0),
m_fClickTimeInterval(0.0),
m_bStartCheckDoubleClick(false),
m_touchRelease(false),
m_bDoubleClickEnable(false),
m_bScale9Enable(false),
m_pImageRender(NULL),
m_strTextureFile("")
{

}

CocoImageView::~CocoImageView()
{
    
}

CocoImageView* CocoImageView::create()
{
    CocoImageView* widget = new CocoImageView();
    if (widget && widget->init())
    {
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

void CocoImageView::initNodes()
{
    CocoWidget::initNodes();
    this->m_pImageRender = cocos2d::CCSprite::create();
    this->m_pCCRenderNode->addChild(m_pImageRender);
}

void CocoImageView::setTexture(const char* fileName,bool useSpriteFrame)
{
    this->m_strTextureFile = fileName;
    if (useSpriteFrame)
    {
        if (this->m_bScale9Enable)
        {
            DYNAMIC_CAST_CCSPRITE->initWithSpriteFrameName(fileName);
        }
        else
        {
            DYNAMIC_CAST_CCSPRITE->initWithSpriteFrameName(fileName);
        }
    }
    else
    {
        if (this->m_bScale9Enable)
        {
            DYNAMIC_CAST_SCALE9SPRITE->initWithFile(fileName);
        }
        else
        {
            DYNAMIC_CAST_CCSPRITE->initWithFile(fileName);
        }
    }
    
}

void CocoImageView::setTextureRect(const cocos2d::CCRect &rect)
{
    if (this->m_bScale9Enable)
    {
//        DYNAMIC_CAST_SCALE9SPRITE->setTextureRect(rect);
    }
    else
    {
        DYNAMIC_CAST_CCSPRITE->setTextureRect(rect);
    }
}

bool CocoImageView::onTouchPressed(cocos2d::CCPoint &touchPoint)
{
    this->setBeFocus(true);
    this->m_touchStartPos.x = touchPoint.x;
    this->m_touchStartPos.y = touchPoint.y;
    this->m_pWidgetParent->checkChildInfo(0,this,touchPoint);
    this->pushDownEvent();
    
    if (this->m_bDoubleClickEnable)
    {
        this->m_fClickTimeInterval = 0;
        this->m_bStartCheckDoubleClick = true;
        this->m_nClickCount++;
        this->m_touchRelease = false;
    }
    return true;
}

bool CocoImageView::onTouchReleased(cocos2d::CCPoint &touchPoint)
{
    if (this->m_bDoubleClickEnable)
    {
        if (this->m_nClickCount >= 2)
        {
            this->doubleClickEvent();
            this->m_nClickCount = 0;
            this->m_bStartCheckDoubleClick = false;
        }
        else
        {
            this->m_touchRelease = true;
        }
    }
    else
    {
        CocoWidget::onTouchReleased(touchPoint);
    }
    return true;
}

void CocoImageView::doubleClickEvent()
{
    
}

void CocoImageView::checkDoubleClick(float dt)
{
    if (this->m_bStartCheckDoubleClick)
    {
        this->m_fClickTimeInterval += dt;
        if (this->m_fClickTimeInterval >= 200 && this->m_nClickCount > 0)
        {
            this->m_fClickTimeInterval = 0;
            this->m_nClickCount--;
            this->m_bStartCheckDoubleClick = false;
        }
    }
    else
    {
        if (this->m_nClickCount <= 1)
        {
            if (this->m_touchRelease)
            {
                this->releaseUpEvent();
                this->m_fClickTimeInterval = 0;
                this->m_nClickCount = 0;
                this->m_touchRelease = false;
            }
        }
    }
}

void CocoImageView::setDoubleClickEnable(bool able)
{
    if (able == this->m_bDoubleClickEnable)
    {
        return;
    }
    this->m_bDoubleClickEnable = able;
    if (able)
    {
//        COCOUISYSTEM->getUIInputManager()->addCheckedDoubleClickWidget(this);
    }
    else
    {
        
    }
}

void CocoImageView::setFlipX(bool flipX)
{
    if (this->m_bScale9Enable)
    {
//            dynamic_cast<GUIScale9Sprite*>(this->m_pImage)->setFlipX(flipX);
    }
    else
    {
        DYNAMIC_CAST_CCSPRITE->setFlipX(flipX);
    }
}

void CocoImageView::setFlipY(bool flipY)
{
    if (this->m_bScale9Enable)
    {
//            dynamic_cast<GUIScale9Sprite*>(this->m_pImage)->setFlipX(flipX);
    }
    else
    {
        DYNAMIC_CAST_CCSPRITE->setFlipY(flipY);
    }
}

void CocoImageView::setScale9Enable(bool able)
{
    if (this->m_bScale9Enable == able)
    {
        return;
    }
    
    this->m_nPrevPressstate = WidgetStateNone;
    this->m_nCurPressState = WidgetStateNone;
    this->m_bScale9Enable = able;
    this->m_pCCRenderNode->removeChild(this->m_pImageRender, true);
    this->m_pImageRender = NULL;
    if (this->m_bScale9Enable)
    {
        this->m_pImageRender = cocos2d::extension::CCScale9Sprite::create();
        if (m_strTextureFile != "") {
            DYNAMIC_CAST_SCALE9SPRITE->initWithFile(m_strTextureFile.c_str());
        }
    }
    else
    {
        this->m_pImageRender = cocos2d::CCSprite::create();
        if (m_strTextureFile != "") {
            DYNAMIC_CAST_CCSPRITE->initWithFile(m_strTextureFile.c_str());
        }
    }

    this->m_pCCRenderNode->addChild(m_pImageRender);
}

void CocoImageView::setScale9Size(float width, float height)
{
    if (!this->m_bScale9Enable)
    {
        return;
    }
    DYNAMIC_CAST_SCALE9SPRITE->setContentSize(cocos2d::CCSize(width,height));
}

void CocoImageView::setDisplayFrame(cocos2d::CCSpriteFrame *pNewFrame)
{
    if (this->m_bScale9Enable)
    {
//        DYNAMIC_CAST_SCALE9SPRITE->setDisplayFrame(pNewFrame);
    }
    else
    {
        DYNAMIC_CAST_CCSPRITE->setDisplayFrame(pNewFrame);
    }
}

void CocoImageView::setSpriteFrame(cocos2d::CCSpriteFrame *pNewFrame)
{
    if (this->m_bScale9Enable)
    {
        DYNAMIC_CAST_SCALE9SPRITE->setSpriteFrame(pNewFrame);
    }
    else
    {
//        DYNAMIC_CAST_CCSPRITE->setSpriteFrame(pNewFrame);
    }
}

void CocoImageView::setPreferredSize(const cocos2d::CCSize &pSize)
{
    if (!this->m_bScale9Enable)
    {
        return;
    }
    DYNAMIC_CAST_SCALE9SPRITE->setPreferredSize(pSize);
}

void CocoImageView::setInsetLeft(float insetLeft)
{
    if (!this->m_bScale9Enable)
    {
        return;
    }
    DYNAMIC_CAST_SCALE9SPRITE->setInsetLeft(insetLeft);
}

void CocoImageView::setInsetTop(float insetTop)
{
    if (!this->m_bScale9Enable)
    {
        return;
    }
    DYNAMIC_CAST_SCALE9SPRITE->setInsetTop(insetTop);
}

void CocoImageView::setInsetRight(float insetRight)
{
    if (!this->m_bScale9Enable)
    {
        return;
    }
    DYNAMIC_CAST_SCALE9SPRITE->setInsetRight(insetRight);
}

void CocoImageView::setInsetBottom(float insetBottom)
{
    if (!this->m_bScale9Enable)
    {
        return;
    }
    DYNAMIC_CAST_SCALE9SPRITE->setInsetBottom(insetBottom);
}

void CocoImageView::setCapInset(const cocos2d::CCRect &capInset)
{
    if (!m_bScale9Enable) {
        return;
    }
    DYNAMIC_CAST_SCALE9SPRITE->setCapInsets(capInset);
}

CCNode* CocoImageView::getValidNode()
{
    return this->m_pImageRender;
}

NS_CC_EXT_END