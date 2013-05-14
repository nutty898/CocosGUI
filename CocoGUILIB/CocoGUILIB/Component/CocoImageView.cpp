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

#include "CocoImageView.h"
#include "UISystem.h"
#include "DictionaryHelper.h"

namespace cs {
    CocoImageView::CocoImageView():
    m_nViewType(1),
    m_pImage(NULL),
    m_nClickCount(0),
    m_fClickTimeInterval(0.0),
    m_bStartCheckDoubleClick(false),
    m_touchRelease(false),
    m_bDoubleClickEnable(false),
    m_bScale9Enable(false)
    {

    }
    
    CocoImageView::~CocoImageView()
    {
        
    }
    
    CocoImageView* CocoImageView::create()
    {
//        return CocoImageView::create(NULL);
        CocoImageView* widget = new CocoImageView();
        if (widget && widget->init()) {
            return widget;
        }
        CC_SAFE_DELETE(widget);
        return NULL;
    }
    
    bool CocoImageView::init()
    {
        if (CocoWidget::init())
        {
            if (this->m_bScale9Enable)
            {
                this->m_pImage = new UIScale9Sprite();
            }
            else
            {
                this->m_pImage = new UISprite();
            }            
            this->m_pImage->init();
            this->addUIElement(this->m_pImage);
            return true;
        }
        return false;
    }

    void CocoImageView::setTexture(const char* fileName,bool useSpriteFrame)
    {
        dynamic_cast<UISprite*>(this->m_pImage)->loadTexture(fileName,useSpriteFrame);
    }
    
    void CocoImageView::setTextureRect(float x,float y,float width,float height)
    {
        dynamic_cast<UISprite*>(this->m_pImage)->setRect(x,y,width,height);        
    }
    
    CRenderNode* CocoImageView::getValidNode()
    {
        return this->m_pImage->getCRenderNode();
    }
    
    bool CocoImageView::onTouchPressed(cocos2d::CCPoint &touchPoint)
    {
        this->setBeFocus(true);
        this->m_touchStartPos.x = touchPoint.x;
        this->m_touchStartPos.y = touchPoint.y;
        this->m_pWidgetParent->checkChildInfo(0,this,touchPoint);
        this->pushDownEvent();
        
        if (this->m_bDoubleClickEnable){
            this->m_fClickTimeInterval = 0;
            this->m_bStartCheckDoubleClick = true;
            this->m_nClickCount++;
            this->m_touchRelease = false;
        }
        return true;
    }
    
    bool CocoImageView::onTouchReleased(cocos2d::CCPoint &touchPoint)
    {
        if (this->m_bDoubleClickEnable){
            if (this->m_nClickCount >= 2){
                this->doubleClickEvent();
                this->m_nClickCount = 0;
                this->m_bStartCheckDoubleClick = false;
            }else{
                this->m_touchRelease = true;
            }
        }else{
            CocoWidget::onTouchReleased(touchPoint);
        }
        return true;
    }
    
    void CocoImageView::doubleClickEvent()
    {
        
    }
    
    void CocoImageView::checkDoubleClick(float dt)
    {
        if (this->m_bStartCheckDoubleClick){
            this->m_fClickTimeInterval += dt;
            if (this->m_fClickTimeInterval >= 200 && this->m_nClickCount > 0){
                this->m_fClickTimeInterval = 0;
                this->m_nClickCount--;
                this->m_bStartCheckDoubleClick = false;
            }
        }else{
            if (this->m_nClickCount <= 1){
                if (this->m_touchRelease){
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
        if (able == this->m_bDoubleClickEnable){
            return;
        }
        this->m_bDoubleClickEnable = able;
        if (able){
            COCOUISYSTEM->getUIInputManager()->addCheckedDoubleClickWidget(this);
        }else{
            
        }
    }
    
    void CocoImageView::setFlipX(bool flipX)
    {
        this->m_pImage->setFlipX(flipX);
    }
    
    void CocoImageView::setFlipY(bool flipY)
    {
        this->m_pImage->setFlipY(flipY);
    }
    
    void CocoImageView::setColor(int r, int g, int b)
    {
        this->m_pImage->setColor(r, g, b);
    }
    
    void CocoImageView::setOpacity(int opcity)
    {
        this->m_pImage->setOpacity(opcity);
    }
    
    void CocoImageView::setAnchorPoint(const cocos2d::CCPoint &pt)
    {
        CocoWidget::setAnchorPoint(pt);
        this->m_pImage->setAnchorPoint(pt);
    }
    
    void CocoImageView::setScale9Enable(bool able)
    {
        if (this->m_bScale9Enable == able)
        {
            return;
        }
        
        this->m_nPrevPressstate = -1;
        this->m_nCurPressState = -1;
        this->m_bScale9Enable = able;
        this->removeAllUIElementsAndCleanUp(true);
        this->m_pImage = NULL;
        
        if (this->m_bScale9Enable)
        {
            this->m_pImage = new UIScale9Sprite();
        }
        else
        {
            this->m_pImage = new UISprite();
        }
        this->m_pImage->init();
        this->addUIElement(m_pImage);
    }
    
    void CocoImageView::setScale9Size(float width, float height)
    {
        if (!this->m_bScale9Enable)
        {
            return;
        }
        dynamic_cast<UIScale9Sprite*>(this->m_pImage)->setScaleSize(width, height);
    }
    
    void CocoImageView::setTexturesScale9(const char *fileName, cocos2d::CCRect capInsets, bool useSpriteFrame)
    {
        dynamic_cast<UIScale9Sprite*>(this->m_pImage)->loadTexture(fileName,
                                                                   capInsets.origin.x,
                                                                   capInsets.origin.y,
                                                                   capInsets.size.width,
                                                                   capInsets.size.height,
                                                                   useSpriteFrame);
    }
}