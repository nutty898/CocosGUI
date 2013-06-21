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

#ifndef __COCOIMAGEVIEW_H__
#define __COCOIMAGEVIEW_H__

#include "../BaseClasses/CocoWidget.h"

NS_CC_EXT_BEGIN

class CocoImageView : public CocoWidget
{
public:
    CocoImageView();
    virtual ~CocoImageView();
    static CocoImageView* create();
    virtual void initNodes();
    virtual void setTexture(const char* fileName,bool useSpriteFrame = false);
    virtual void setTextureRect(const cocos2d::CCRect& rect);
    virtual bool onTouchPressed(cocos2d::CCPoint &touchPoint);
    virtual bool onTouchReleased(cocos2d::CCPoint &touchPoint);
    void doubleClickEvent();
    void checkDoubleClick(float dt);
    void setDoubleClickEnable(bool able);
    virtual void setFlipX(bool flipX);
    virtual void setFlipY(bool flipY);
    void setScale9Enable(bool able);
    void setScale9Size(float width,float height);
    void setDisplayFrame(cocos2d::CCSpriteFrame *pNewFrame);
    void setSpriteFrame(cocos2d::CCSpriteFrame *pNewFrame);
    void setPreferredSize(const cocos2d::CCSize& pSize);
    void setInsetLeft(float insetLeft);
    void setInsetTop(float insetTop);
    void setInsetRight(float insetRight);
    void setInsetBottom(float insetBottom);
    void setCapInset(const CCRect &capInset);
    virtual cocos2d::CCNode* getValidNode();
protected:
    int m_nViewType;
    int m_nClickCount;
    float m_fClickTimeInterval;
    bool m_bStartCheckDoubleClick;
    bool m_touchRelease;
    bool m_bDoubleClickEnable;
    
    bool m_bScale9Enable;
    CCNode* m_pImageRender;
    std::string m_strTextureFile;
};

NS_CC_EXT_END

#endif /* defined(__CocoGUI__CocoImageView__) */
