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

#include "CocoPanel.h"
#include "DictionaryHelper.h"

namespace cs {
    CocoPanel::CocoPanel():
    m_bBackGroundScale9Enable(false),
    m_pBackGroundImage(NULL),
    m_bBackGroundInited(false)
    {

    }
    
    CocoPanel* CocoPanel::create()
    {
//        return CocoPanel::create(NULL);
        CocoPanel* widget = new CocoPanel();
        if (widget && widget->init()) {
            return widget;
        }
        CC_SAFE_DELETE(widget);
        return NULL;
    }
    
    bool CocoPanel::init()
    {
        if (CocoContainerWidget::init()) {
//            if (this->m_bBackGroundScale9Enable) {
//                this->m_pBackGroundImage = new UIScale9Sprite();
//                this->m_pBackGroundImage->init();
//            }else{
//                this->m_pBackGroundImage = new UISprite();
//                this->m_pBackGroundImage->init();
//            }
//            this->addUIElement(this->m_pBackGroundImage);
//            this->m_pBackGroundImage->setPosition(ccp(this->m_pCContainerNode->getContentSizeWidth()/2, this->m_pCContainerNode->getContentSizeHeight()/2));
            return true;
        }
        return false;
    }
    
    void CocoPanel::initBackGround(bool scale9)
    {
        if (scale9) {
            this->m_pBackGroundImage = new UIScale9Sprite();
            this->m_pBackGroundImage->init();
        }else{
            this->m_pBackGroundImage = new UISprite();
            this->m_pBackGroundImage->init();
        }
        this->addUIElement(this->m_pBackGroundImage);
        this->m_bBackGroundInited = true;
    }
    
    CocoPanel::~CocoPanel()
    {
        
    }
    
    void CocoPanel::setBackGroundImageScale9Enable(bool able)
    {
        if (this->m_bBackGroundScale9Enable == able) {
            return;
        }
        this->removeAllUIElementsAndCleanUp(true);
        this->m_pBackGroundImage = NULL;
        this->m_bBackGroundScale9Enable = able;
//        this->initBackGround(this->m_bBackGroundScale9Enable);
    }
    
    void CocoPanel::setColorAndSize(int r,int g,int b,int o,float width,float height)
    {
        CocoContainerWidget::setColorAndSize(r, g, b, o, width, height);
        if (this->m_bBackGroundInited) {
            this->m_pBackGroundImage->setPosition(ccp(this->m_pCContainerNode->getContentSizeWidth()/2, this->m_pCContainerNode->getContentSizeHeight()/2));
            if (this->m_bBackGroundScale9Enable) {
                ((UIScale9Sprite*)(this->m_pBackGroundImage))->setScaleSize(this->m_pCContainerNode->getContentSizeWidth(), this->m_pCContainerNode->getContentSizeHeight());
            }
        }
    }
    
    void CocoPanel::setSize(float width,float height)
    {
        CocoContainerWidget::setSize(width, height);
        if (this->m_bBackGroundInited) {
            this->m_pBackGroundImage->setPosition(ccp(this->m_pCContainerNode->getContentSizeWidth()/2, this->m_pCContainerNode->getContentSizeHeight()/2));
            if (this->m_bBackGroundScale9Enable) {
                ((UIScale9Sprite*)(this->m_pBackGroundImage))->setScaleSize(this->m_pCContainerNode->getContentSizeWidth(), this->m_pCContainerNode->getContentSizeHeight());
            }
        }
    }
    
    void CocoPanel::setBackGroundImage(const char* fileName,bool useSpriteFrame)
    {
        if (this->m_bBackGroundScale9Enable) {
            return;
        }
        if (!this->m_bBackGroundInited) {
            this->initBackGround(this->m_bBackGroundScale9Enable);
        }
        ((UISprite*)(this->m_pBackGroundImage))->loadTexture(fileName,useSpriteFrame);
        this->m_pBackGroundImage->setPosition(ccp(this->m_pCContainerNode->getContentSizeWidth()/2, this->m_pCContainerNode->getContentSizeHeight()/2));
    }
    
    void CocoPanel::setBackGroundImageScale9(const char *fileName, cocos2d::CCRect capInsets,bool useSpriteFrame)
    {
        if (!this->m_bBackGroundScale9Enable) {
            return;
        }
        if (!this->m_bBackGroundInited) {
            this->initBackGround(this->m_bBackGroundScale9Enable);
        }
        ((UIScale9Sprite*)(this->m_pBackGroundImage))->loadTexture(fileName,capInsets.origin.x,capInsets.origin.y,capInsets.size.width,capInsets.size.height,useSpriteFrame);
        this->m_pBackGroundImage->setPosition(ccp(this->m_pCContainerNode->getContentSizeWidth()/2, this->m_pCContainerNode->getContentSizeHeight()/2));
        ((UIScale9Sprite*)(this->m_pBackGroundImage))->setScaleSize(this->m_pCContainerNode->getContentSizeWidth(), this->m_pCContainerNode->getContentSizeHeight());
    }
    
    void CocoPanel::setBackGroundColorEnable(bool able)
    {
        this->m_pCContainerNode->setColorEnable(able);
    }
    
//    CRenderNode* CocoPanel::getValidNode()
//    {
//        return CocoContainerWidget::getValidNode();
//    }
    
    void CocoPanel::setColor(int r, int g, int b)
    {
        CocoContainerWidget::setColor(r, g, b);
        if (this->m_bBackGroundInited) {
            this->m_pBackGroundImage->setColor(r, g, b);
        }
    }
    
    void CocoPanel::setOpacity(int opcity)
    {
        CocoContainerWidget::setOpcity(opcity);
        if (this->m_bBackGroundInited) {
            this->m_pBackGroundImage->setOpacity(opcity);
        }
    }
}