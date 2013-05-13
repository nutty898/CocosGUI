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

#ifndef __CocoGUI__CocoCheckBox__
#define __CocoGUI__CocoCheckBox__

#include "CocoWidget.h"
#include "UISprite.h"

namespace cs {
    typedef void (cocos2d::CCObject::*SEL_SelectEvent)(cocos2d::CCObject*);
    typedef void (cocos2d::CCObject::*SEL_UnSelectEvent)(cocos2d::CCObject*);
    #define coco_selectselector(_SELECTOR) (CocoGUI::SEL_SelectEvent)(&_SELECTOR)
    #define coco_unselectselector(_SELECTOR) (CocoGUI::SEL_UnSelectEvent)(&_SELECTOR)
    class CocoCheckBox : public CocoWidget
    {
    public:
        CocoCheckBox();
        virtual ~CocoCheckBox();
        static CocoCheckBox* create();
//        static CocoCheckBox* create(cocos2d::CCDictionary* options);
//        static CocoCheckBox* createWithJson(sp::SPJsonDictionary* options);
        virtual bool init();
//        virtual bool initWithOptions(cocos2d::CCDictionary* options);
//        virtual bool initWithOptions_json(sp::SPJsonDictionary* options);
        void setTextures(const char* backGround,const char* backGroundSelected,const char* cross,const char* backGroundDisabled,const char* frontCrossDisabled,bool useSpriteFrame = false);
        void setBackGroundTexture(const char* backGround,bool useSpriteFrame = false);
        void setBackGroundSelectedTexture(const char* backGroundSelected,bool useSpriteFrame = false);
        void setFrontCrossTexture(const char* cross,bool useSpriteFrame = false);
        void setBackGroundDisabledTexture(const char* backGroundDisabled,bool useSpriteFrame = false);
        void setFrontCrossDisabledTexture(const char* frontCrossDisabled,bool useSpriteFrame = false);
        
        virtual bool onTouchReleased(cocos2d::CCPoint &touchPoint);
        virtual void onPressStateChangedToNormal();
        virtual void onPressStateChangedToPressed();
        virtual void onPressStateChangedToDisabled();
        void setSelectedState(bool selected);
        bool getSelectedState();
        void selectedEvent();
        void unSelectedEvent();
        virtual CRenderNode* getValidNode();
        virtual void setAnchorPoint(const cocos2d::CCPoint &pt);
        virtual void setColor(int r,int g,int b);
        virtual void setOpacity(int opcity);
        virtual void addSelectEvent(cocos2d::CCObject* target,SEL_SelectEvent selector);
        virtual void addUnSelectEvent(cocos2d::CCObject* target,SEL_UnSelectEvent selector);
        virtual void setFlipX(bool flipX);
        virtual void setFlipY(bool flipY);
    protected:
        UISprite* m_pBackGroundBox;
        UISprite* m_pBackGroundSelectedBox;
        UISprite* m_pFrontCross;
        UISprite* m_pBackGroundBoxDisabled;
        UISprite* m_pFrontCrossDisabled;
        bool m_bIsSelected;
        cocos2d::CCObject*       m_pSelectListener;
        SEL_SelectEvent    m_pfnSelectSelector;
        cocos2d::CCObject*       m_pUnSelectListener;
        SEL_UnSelectEvent    m_pfnUnSelectSelector;
    };
}

#endif /* defined(__CocoGUI__CocoCheckBox__) */
