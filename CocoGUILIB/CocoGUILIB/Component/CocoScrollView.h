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

#ifndef __CocoGUI__CocoScrollView__
#define __CocoGUI__CocoScrollView__

#include "CocoPanel.h"

namespace cs
{
    enum SCROLLVIEW_DIR
    {
        SCROLLVIEW_DIR_NONE,
        SCROLLVIEW_DIR_VERTICAL,
        SCROLLVIEW_DIR_HORIZONTAL
    };
    
    enum SCROLLVIEW_MOVE_DIR
    {
        SCROLLVIEW_MOVE_DIR_NONE,
        SCROLLVIEW_MOVE_DIR_UP,
        SCROLLVIEW_MOVE_DIR_DOWN,
        SCROLLVIEW_MOVE_DIR_LEFT,
        SCROLLVIEW_MOVE_DIR_RIGHT,
    };
    
    enum SCROLLVIEW_MOVE_MODE
    {
        SCROLLVIEW_MOVE_MODE_NONE,
        SCROLLVIEW_MOVE_MODE_NORMAL,
        SCROLLVIEW_MOVE_MODE_ACTION
    };
    
    enum SCROLLVIEW_BERTH_ORI
    {
        SCROLLVIEW_BERTH_ORI_NONE,
        SCROLLVIEW_BERTH_ORI_TOP,
        SCROLLVIEW_BERTH_ORI_BOTTOM,
        SCROLLVIEW_BERTH_ORI_VERTICAL_CENTER,
        SCROLLVIEW_BERTH_ORI_LEFT,
        SCROLLVIEW_BERTH_ORI_RIGHT,
        SCROLLVIEW_BERTH_ORI_HORIZONTAL_CENTER
    };
    
    typedef void (cocos2d::CCObject::*SEL_ScrollToTopEvent)(cocos2d::CCObject*);
    typedef void (cocos2d::CCObject::*SEL_ScrollToBottomEvent)(cocos2d::CCObject*);
    typedef void (cocos2d::CCObject::*SEL_ScrollToLeftEvent)(cocos2d::CCObject*);
    typedef void (cocos2d::CCObject::*SEL_ScrollToRightEvent)(cocos2d::CCObject*);
    #define coco_ScrollToTopSelector(_SELECTOR) (cs::SEL_ScrollToTopEvent)(&_SELECTOR)
    #define coco_ScrollToBottomSelector(_SELECTOR) (cs::SEL_ScrollToBottomEvent)(&_SELECTOR)
    #define coco_ScrollToLeftSelector(_SELECTOR) (cs::SEL_ScrollToLeftEvent)(&_SELECTOR)
    #define coco_ScrollToRightSelector(_SELECTOR) (cs::SEL_ScrollToRightEvent)(&_SELECTOR)
    
    typedef void (cocos2d::CCObject::*SEL_BerthToTopEvent)(cocos2d::CCObject*);
    typedef void (cocos2d::CCObject::*SEL_BerthToBottomEvent)(cocos2d::CCObject*);
    typedef void (cocos2d::CCObject::*SEL_BerthToVerticalCenterEvent)(cocos2d::CCObject*);
    typedef void (cocos2d::CCObject::*SEL_BerthToLeftEvent)(cocos2d::CCObject*);
    typedef void (cocos2d::CCObject::*SEL_BerthToRightEvent)(cocos2d::CCObject*);
    typedef void (cocos2d::CCObject::*SEL_BerthToHorizontalCenterEvent)(cocos2d::CCObject*);
    #define coco_BerthToTopSelector(_SELECTOR) (cs::SEL_BerthToTopEvent)(&_SELECTOR)
    #define coco_BerthToBottomSelector(_SELECTOR) (cs::SEL_BerthToBottomEvent)(&_SELECTOR)
    #define coco_BerthToVerticalCenterSelector(_SELECTOR) (cs::SEL_BerthToVerticalCenterEvent)(&_SELECTOR)
    #define coco_BerthToLeftSelector(_SELECTOR) (cs::SEL_BerthToLeftEvent)(&_SELECTOR)
    #define coco_BerthToRightSelector(_SELECTOR) (cs::SEL_BerthToRightEvent)(&_SELECTOR)
    #define coco_HorizontalCenterSelector(_SELECTOR) (cs::SEL_BerthToHorizontalCenterEvent)(&_SELECTOR)
    
    class CocoScrollView : public CocoPanel
    {
    public:
        CocoScrollView();
        virtual ~CocoScrollView();
        static CocoScrollView* create();
        virtual bool init();
        virtual bool addChild(CocoWidget* widget);
        virtual void removeChildMoveToTrash(CocoWidget* child);
        virtual void removeChildReferenceOnly(CocoWidget* child);
        virtual void removeAllChildrenAndCleanUp(bool cleanup);
        virtual void initProperty();
        virtual void resetProperty();
        void resortChildren();
        void moveChildren(float offset);
        void autoScrollChildren(float dt);
        void startAutoScrollChildren(float v);
        void stopAutoScrollChildren();
        float getCurAutoScrollDistance(float time);
        void resetPositionWithAction();
        virtual CocoWidget* getCheckPositionChild();
        float calculateOffsetWithDragForce(float moveOffset);
        void handleScrollActionEvent();
        void berthChildren(SCROLLVIEW_DIR direction);
        virtual bool scrollChildren(float touchOffset);
        void scrollToBottom();
        void scrollToTop();
        virtual void drag(float offset);
        void startRecordSlidAction();
        virtual void endRecordSlidAction();
        void handlePressLogic(cocos2d::CCPoint &touchPoint);
        void handleMoveLogic(cocos2d::CCPoint &touchPoint);
        void handleReleaseLogic(cocos2d::CCPoint &touchPoint);
        virtual bool onTouchPressed(cocos2d::CCPoint &touchPoint);
        virtual bool onTouchMoved(cocos2d::CCPoint &touchPoint);
        virtual bool onTouchReleased(cocos2d::CCPoint &touchPoint);
        virtual bool onTouchCanceled(cocos2d::CCPoint &touchPoint);
        virtual bool onTouchLongClicked(cocos2d::CCPoint &touchPoint);
        virtual void update(float dt);
        void recordSlidTime(float dt);
        virtual void checkChildInfo(int handleState,CocoWidget* sender,cocos2d::CCPoint &touchPoint);
//        virtual void setColorAndSize(int r,int g,int b,int o,float width,float height);
        virtual void setSize(const cocos2d::CCSize &size);
        
        void scrollToTopEvent();
        void scrollToBottomEvent();
        void scrollToLeftEvent();
        void scrollToRightEvent();
        
        void addScrollToTopEvent(cocos2d::CCObject* target, SEL_ScrollToTopEvent selector);
        void addScrollToBottomEvent(cocos2d::CCObject* target, SEL_ScrollToBottomEvent selector);
        void addScrollToLeftEvent(cocos2d::CCObject* target, SEL_ScrollToLeftEvent selector);
        void addScrollToRightEvent(cocos2d::CCObject* target, SEL_ScrollToRightEvent selector);
        
        void berthToTopEvent();
        void berthToBottomEvent();
        void berthToVerticalCenterEvent();
        void berthToLeftEvent();
        void berthToRightEvent();
        void berthToHorizontalCenterEvent();
        
        void addBerthToTopEvent(cocos2d::CCObject* target, SEL_BerthToTopEvent selector);
        void addBerthToBottomEvent(cocos2d::CCObject* target, SEL_BerthToBottomEvent selector);
        void addBerthToVerticalCenterEvent(cocos2d::CCObject* target, SEL_BerthToVerticalCenterEvent selector);
        void addBerthToLeftEvent(cocos2d::CCObject* target, SEL_BerthToLeftEvent selector);
        void addBerthToRightEvent(cocos2d::CCObject* target, SEL_BerthToRightEvent selector);
        void addBerthToHorizontalCenterEvent(cocos2d::CCObject* target, SEL_BerthToHorizontalCenterEvent selector);
        
        void stopAction();
        
    protected:
        CC_SYNTHESIZE(SCROLLVIEW_DIR, m_eDirection, Direction);
        CC_SYNTHESIZE(SCROLLVIEW_MOVE_DIR, m_eMoveDirection, MoveDirection);
        int m_nDirection;
        float m_fTouchStartLocation;
        float m_fTouchEndLocation;
        float m_fTouchMoveStartLocation;
        float m_fTopBoundary;//test
        float m_fBottomBoundary;//test
        float m_fLeftBoundary;
        float m_fRightBoundary;
        CocoWidget* m_pTopChild;
        CocoWidget* m_pBottomChild;
        CocoWidget* m_pLeftChild;
        CocoWidget* m_pRightChild;
        
        float m_fDisBoundaryToChild_0;
        float m_fDisBetweenChild;
        float m_fDragForce;
        
        int m_nHandleState;//0 normal, 1 top boundary, 2 bottom boundary
        int m_nMoveDirection;//0 pull down, 1 push up
        
        CC_SYNTHESIZE(SCROLLVIEW_MOVE_MODE, m_eMoveMode, MoveMode);
        CC_SYNTHESIZE(SCROLLVIEW_BERTH_ORI, m_eBerthOrientation, BerthOrientation);
        bool isRunningAction;
        
        bool m_bTopEnd;
        bool m_bBottomEnd;
        bool m_bLeftEnd;
        bool m_bRightEnd;
        
        bool m_bBerthToTop;
        bool m_bBerthToBottom;
        bool m_bBerthToLeft;
        bool m_bBerthToRight;
        bool m_bBerthToVerticalCenter;
        bool m_bBerthToHorizontalCenter;
        
        bool m_bAutoScroll;
        
        float m_fAutoScrollOriginalSpeed;
        float m_fAutoScrollAcceleration;
        
        bool m_bBePressed;
        float m_fSlidTime;
        cocos2d::CCPoint moveChildPoint;
        float m_fChildrenSizeHeight;
        float m_fChildrenSizeWidth;
        float m_fChildFocusCancelOffset;
        
        cocos2d::CCObject* m_pScrollToTopListener;
        SEL_ScrollToTopEvent m_pfnScrollToTopSelector;
        cocos2d::CCObject* m_pScrollToBottomListener;
        SEL_ScrollToBottomEvent m_pfnScrollToBottomSelector;
        cocos2d::CCObject* m_pScrollToLeftListener;
        SEL_ScrollToLeftEvent m_pfnScrollToLeftSelector;
        cocos2d::CCObject* m_pScrollToRightListener;
        SEL_ScrollToRightEvent m_pfnScrollToRightSelector;
        
        cocos2d::CCObject* m_pBerthToTopListener;
        SEL_BerthToTopEvent m_pfnBerthToTopSelector;
        cocos2d::CCObject* m_pBerthToBottomListener;
        SEL_BerthToBottomEvent m_pfnBerthToBottomSelector;
        cocos2d::CCObject* m_pBerthToVerticalCenterListener;
        SEL_BerthToVerticalCenterEvent m_pfnBerthToVerticalCenterSelector;
        cocos2d::CCObject* m_pBerthToLeftListener;
        SEL_BerthToLeftEvent m_pfnBerthToLeftSelector;
        cocos2d::CCObject* m_pBerthToRightListener;
        SEL_BerthToRightEvent m_pfnBerthToRightSelector;
        cocos2d::CCObject* m_pBerthToHorizontalCenterListener;
        SEL_BerthToHorizontalCenterEvent m_pfnBerthToHorizontalCenterSelector;
    };
}

#endif /* defined(__CocoGUI__CocoScrollView__) */
