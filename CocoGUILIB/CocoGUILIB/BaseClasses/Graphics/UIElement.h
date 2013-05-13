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

#ifndef __CocoGUI__UIElement__
#define __CocoGUI__UIElement__


#include "cocos2d.h"
#include "CRenderNode.h"
namespace cs {
    class CocoWidget;
    class UIElement : public cocos2d::CCObject
    {
    public:
        UIElement();
        virtual ~UIElement();
        virtual void init();
        virtual void releaseResoures();
        void setVisible(bool visible);
        bool getVisible();
        void setScale(float scale);
        float getScale();
        void setScaleX(float scaleX);
        float getScaleX();
        void setScaleY(float scaleY);
        float getScaleY();
        void setFlipX(bool flipX);
        bool isFlipX();
        void setFlipY(bool flipY);
        bool isFlipY();
        void setColor(int r,int g,int b);
        cocos2d::ccColor3B getColor();
        void setOpacity(int opcity);
        int getOpacity();
        void setPosition(cocos2d::CCPoint position);
        cocos2d::CCPoint getPosition();
        cocos2d::CCPoint getAnchorPoint();
        void setAnchorPoint(cocos2d::CCPoint point);
        virtual cocos2d::CCSize getContentSize();
        virtual float getContentSizeWidth();
        virtual float getContentSizeHeight();
        
        virtual void update(float dt);
        CRenderNode* getCRenderNode();
    protected:
        bool m_bVisible;
        cocos2d::CCSize m_contentSize;
        CRenderNode* m_pCRenderNode;
        CocoWidget* m_pParentWidget;
    };
}

#endif /* defined(__CocoGUI__UIElement__) */
