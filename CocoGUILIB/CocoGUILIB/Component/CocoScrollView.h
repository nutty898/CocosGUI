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

namespace cs {
    class CocoScrollView : public CocoPanel
    {
    public:
        CocoScrollView();
        virtual ~CocoScrollView();
        static CocoScrollView* create();
//        static CocoScrollView* create(cocos2d::CCDictionary* options);
//        static CocoScrollView* createWithJson(sp::SPJsonDictionary* options);
        virtual bool init();
//        virtual bool initWithOptions(cocos2d::CCDictionary* options);
//        virtual bool initWithOptions_json(sp::SPJsonDictionary* options);
        virtual bool addChild(CocoWidget* widget);
        virtual void removeChildMoveToTrash(CocoWidget* child);
        virtual void removeChildReferenceOnly(CocoWidget* child);
        virtual void removeAllChildrenAndCleanUp(bool cleanup);
        void resortChildren();
        void moveChildren(float offset);
        void autoScrollChildren(float dt);
        void startAutoScrollChildren(float v);
        void stopAutoScrollChildren();
        float getCurAutoScrollDistance(float time);
        void setDirection(int direction);
        bool scrollChildren(float touchOffset);
        void scrollToBottom();
        void scrollToTop();
        void startRecordSlidAction();
        void endRecordSlidAction();
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
//        virtual CRenderNode* getValidNode();
        virtual void setColorAndSize(int r,int g,int b,int o,float width,float height);
        virtual void setSize(float width,float height);
    protected:
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
        
        int m_nHandleState;//0 normal, 1 top boundary, 2 bottom boundary
        int m_nMoveDirection;//0 pull down, 1 push up
        
        bool m_bTopEnd;
        bool m_bBottomEnd;
        
        bool m_bAutoScroll;
        
        float m_fAutoScrollOriginalSpeed;
        float m_fAutoScrollAcceleration;
        
        bool m_bBePressed;
        float m_fSlidTime;
        cocos2d::CCPoint moveChildPoint;
        float m_fChildrenSizeHeight;
        float m_fChildrenSizeWidth;
        float m_fChildFocusCancelOffset;
    };
}

#endif /* defined(__CocoGUI__CocoScrollView__) */
