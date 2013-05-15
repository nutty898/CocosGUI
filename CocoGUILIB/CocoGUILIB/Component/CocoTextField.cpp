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

#include "CocoTextField.h"
#include "DictionaryHelper.h"
namespace cs {
    
    CocoTextField::CocoTextField():
    uiTextField(NULL),
    m_fTouchWidth(0.0),
    m_fTouchHeight(0.0),
    m_bUseTouchArea(false)
    {
        
    }
    
    CocoTextField::~CocoTextField()
    {
        
    }
    
    CocoTextField* CocoTextField::create()
    {
//        return CocoTextField::create(NULL);
        CocoTextField* widget = new CocoTextField();
        if (widget && widget->init()) {
            return widget;
        }
        CC_SAFE_DELETE(widget);
        return NULL;
    }
    
    bool CocoTextField::init()
    {
        if (CocoWidget::init()) {
            this->uiTextField = new UITextField();
            this->uiTextField->init();
            this->addUIElement(this->uiTextField);
            return true;
        }
        return false;
    }
        
    void CocoTextField::setTouchSize(float width,float height)
    {
        this->m_bUseTouchArea = true;
        this->m_fTouchWidth = width;
        this->m_fTouchHeight = height;
    }
    
    void CocoTextField::setText(const char* text)
    {
        this->uiTextField->setStringValue(text);
    }
    
    void CocoTextField::setSize(float width,float height)
    {
        this->uiTextField->setSize(width,height);
    }
    
    void CocoTextField::setPlaceHolder(const char *value)
    {
        this->uiTextField->setPlaceHolder(value);
    }
    
    void CocoTextField::setFontSize(int size)
    {
        this->uiTextField->setFontSize(size);
    }
    
    void CocoTextField::setTextColor(int r, int g, int b)
    {
        this->uiTextField->setTextColor(r, g, b);
    }
    
    void CocoTextField::didNotSelectSelf()
    {
        this->uiTextField->closeIME();
//        if (this.checkObjectUseable(this.events['onCloseIME'])){
//            this.events['onCloseIME'].apply(this,[this]);
//        }
    }
    
    const char* CocoTextField::getStringValue()
    {
        return this->uiTextField->getStringValue();
    }
    
    bool CocoTextField::onTouchPressed(cocos2d::CCPoint &touchPoint)
    {
        CocoWidget::onTouchPressed(touchPoint);
        this->uiTextField->openIME();
//        if (this.checkObjectUseable(this.events['onOpenIME'])){
//            this.events['onOpenIME'].apply(this,[this]);
//        }
        return true;
    }
    
    bool CocoTextField::pointAtSelfBody(cocos2d::CCPoint &pt)
    {
        if (!this->m_bUseTouchArea){
            return CocoWidget::pointAtSelfBody(pt);
        }
        if (!this->getAbsoluteVisible()) {
            return false;
        }
//        var rect = {origin:{x:this.getPosition().x-this._fTouchWidth/2,y:this.getPosition().y-this._fTouchHeight/2},size:{width:this._fTouchWidth,height:this._fTouchHeight}};
//        var bRet = false;
//        if (x >= rect.origin.x && x <= rect.origin.x+rect.size.width && y >= rect.origin.y && y <= rect.origin.y +rect.size.height){
//            bRet = true;
//        }
//        return bRet;
        return this->uiTextField->getCRenderNode()->hitTest(pt);
    }
    
    CRenderNode* CocoTextField::getValidNode()
    {
        return this->uiTextField->getCRenderNode();
    }
    
    void CocoTextField::setColor(int r, int g, int b)
    {
        this->uiTextField->setColor(r, g, b);
    }
    
    void CocoTextField::setOpacity(int opcity)
    {
        this->uiTextField->setOpacity(opcity);
    }
    
    void CocoTextField::setAnchorPoint(const cocos2d::CCPoint &pt)
    {
        CocoWidget::setAnchorPoint(pt);
        this->uiTextField->setAnchorPoint(pt);
    }
    
    void CocoTextField::setCharacterLength(int length)
    {
        this->uiTextField->setCharacterLength(length);
    }
    
    void CocoTextField::setIsPassWord(bool isPassword)
    {
        this->uiTextField->setIsPassWord(isPassword);
    }
}