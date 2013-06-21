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

#include "CocoPanel.h"
#include "DictionaryHelper.h"
#include "CCScale9Sprite.h"
#include "CClipAbleLayerColor.h"

NS_CC_EXT_BEGIN

#define DYNAMIC_CAST_CLIPLAYERCOLOR dynamic_cast<CClipAbleLayerColor*>(this->m_pCCRenderNode)

CocoPanel::CocoPanel():
m_bBackGroundScale9Enable(false),
m_pBackGroundImage(NULL),
m_bBackGroundInited(false)
{

}

CocoPanel* CocoPanel::create()
{
    CocoPanel* widget = new CocoPanel();
    if (widget && widget->init())
    {
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

void CocoPanel::initBackGround(bool scale9)
{
    if (scale9)
    {
        this->m_pBackGroundImage = cocos2d::extension::CCScale9Sprite::create();
    }
    else
    {
        this->m_pBackGroundImage = cocos2d::CCSprite::create();
    }
    this->m_pCCRenderNode->addChild(this->m_pBackGroundImage);
    this->m_bBackGroundInited = true;
}

CocoPanel::~CocoPanel()
{
    
}

void CocoPanel::setBackGroundImageScale9Enable(bool able)
{
    if (this->m_bBackGroundScale9Enable == able)
    {
        return;
    }
    this->m_pCCRenderNode->removeChild(this->m_pBackGroundImage, true);
    this->m_pBackGroundImage = NULL;
    this->m_bBackGroundScale9Enable = able;
}
    
void CocoPanel::setSize(const cocos2d::CCSize &size)
{
    CocoContainerWidget::setSize(size);
    if (this->m_bBackGroundInited)
    {
        this->m_pBackGroundImage->setPosition(ccp(this->m_pCCRenderNode->getContentSize().width/2, this->m_pCCRenderNode->getContentSize().height/2));
        if (this->m_bBackGroundScale9Enable)
        {
            dynamic_cast<cocos2d::extension::CCScale9Sprite*>(this->m_pBackGroundImage)->setContentSize(this->m_pCCRenderNode->getContentSize());
        }
    }
}

void CocoPanel::setBackGroundImage(const char* fileName,bool useSpriteFrame)
{
    if (!fileName || strcmp(fileName, "") == 0)
    {
        return;
    }
    if (this->m_bBackGroundScale9Enable)
    {
        return;
    }
    if (!this->m_bBackGroundInited)
    {
        this->initBackGround(this->m_bBackGroundScale9Enable);
    }
    if (useSpriteFrame)
    {
        dynamic_cast<cocos2d::CCSprite*>(this->m_pBackGroundImage)->initWithSpriteFrameName(fileName);
    }
    else
    {
        dynamic_cast<cocos2d::CCSprite*>(this->m_pBackGroundImage)->initWithFile(fileName);
    }
    this->m_pBackGroundImage->setPosition(ccp(this->m_pCCRenderNode->getContentSize().width/2, this->m_pCCRenderNode->getContentSize().height/2));
}

void CocoPanel::setBackGroundImageScale9(const char *fileName,const cocos2d::CCRect &capInsets,bool useSpriteFrame)
{
    if (!this->m_bBackGroundScale9Enable)
    {
        return;
    }
    if (!this->m_bBackGroundInited)
    {
        this->initBackGround(this->m_bBackGroundScale9Enable);
    }
    if (useSpriteFrame)
    {
        dynamic_cast<cocos2d::extension::CCScale9Sprite*>(this->m_pBackGroundImage)->initWithSpriteFrameName(fileName,capInsets);
    }
    else
    {
        dynamic_cast<cocos2d::extension::CCScale9Sprite*>(this->m_pBackGroundImage)->initWithFile(fileName,capInsets);
    }
    this->m_pBackGroundImage->setPosition(ccp(this->m_pCCRenderNode->getContentSize().width/2, this->m_pCCRenderNode->getContentSize().height/2));
    dynamic_cast<cocos2d::extension::CCScale9Sprite*>(this->m_pBackGroundImage)->setContentSize(this->m_pCCRenderNode->getContentSize());
}

void CocoPanel::setBackGroundColorEnable(bool able)
{
    DYNAMIC_CAST_CLIPLAYERCOLOR->setColorEnable(able);
}

NS_CC_EXT_END