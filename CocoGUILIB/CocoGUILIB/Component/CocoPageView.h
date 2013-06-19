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

#ifndef __Test__CocoPageView__
#define __Test__CocoPageView__

#include "CocoPanel.h"

namespace cs
{
    enum PAGEVIEW_DIR
    {
        PAGEVIEW_DIR_NONE,
        PAGEVIEW_DIR_VERTICAL,
        PAGEVIEW_DIR_HORIZONTAL
    };
    
    enum
    {
        kCCScrollLayerStateIdle,
        kCCScrollLayerStateSliding,
    };
    
    using namespace cocos2d;
    
    class CocoPageView : public CocoPanel
    {
    public:
        CocoPageView();
        ~CocoPageView();
        static CocoPageView* create();
        virtual bool init();
        
        virtual bool addChild(CocoWidget* widget);
        virtual void initProperty();
        virtual void resetProperty();
//        virtual void setColorAndSize(int r,int g,int b,int o,float width,float height);
        virtual void setSize(const CCSize &size);
        virtual bool onTouchPressed(cocos2d::CCPoint &touchPoint);
        virtual bool onTouchMoved(cocos2d::CCPoint &touchPoint);
        virtual bool onTouchReleased(cocos2d::CCPoint &touchPoint);
        virtual bool onTouchCanceled(cocos2d::CCPoint &touchPoint);
        
        #pragma mark Updates
        
        /** Updates all pages positions & adds them as children if needed.
         * Can be used to update position of pages after screen reshape, or
         * for update after dynamic page add/remove.
         */
        void updatePages();
        
        #pragma mark Adding/Removing Pages
        
        /** Adds new page and reorders pages trying to set given number for newly added page.
         * If number > pages count - adds new page to the right end of the scroll layer.
         * If number <= 0 - adds new page to the left end of the scroll layer.
         * @attention Designated addPage method.
         */
        void addPage(CocoWidget* widget, int pageNumber);
        
        /** Adds new page to the right end of the scroll layer. */
        void addPage(CocoWidget* widget);
        
        /** Removes page if it's one of scroll layers pages (not children)
         * Does nothing if page not found.
         */
        void removePage(CocoWidget* widget);        
        
        /** Removes page with given number. Doesn nothing if there's no page for such number. */
        void removePageWithNumber(int page);        
        
        #pragma mark Moving/Selecting Pages    
        
        /* Moves scrollLayer to page with given number & invokes delegate
         * method scrollLayer:scrolledToPageNumber: at the end of CCMoveTo action.
         * Does nothing if number >= totalScreens or < 0.
         */
        void moveToPage(int page);
        
        /* Immedeatly moves scrollLayer to page with given number without running CCMoveTo. 
         * Does nothing if number >= totalScreens or < 0.
         */
        void selectPage(int page);
        
        void moveToPageEnded();
        int pageNumberForPosition(CCPoint position);
        CCPoint positionForPageWithNumber(int pageNumber);
        
        void moveChildren(float offset);
        void stopAction();
        
    protected:        
        // Holds the current page being displayed.
        int currentScreen_;
        
        // Number of previous page being displayed.
        int prevScreen_;
        
        // The x coord of initial point the user starts their swipe.
        float startSwipe_;
        
        // For what distance user must slide finger to start scrolling menu.
        float minimumTouchLengthToSlide;
        
        // For what distance user must slide finger to change the page.
        float minimumTouchLengthToChangePage;                
        
        // Internal state of scrollLayer (scrolling or idle).
        int state_;
        
        bool stealTouches;        
        
        // Holds current pages width offset.
        CC_SYNTHESIZE(float, pagesWidthOffset, PagesWidthOffset);
        
        // Holds current margin offset
        float marginOffset;
        
        /** Total pages available in scrollLayer. */
        int totalScreens;
        
        /** Returns array of pages CCLayer's  */
        cocos2d::CCArray* pages;        
        
        bool isRunningAction;
        
        float m_fTouchStartLocation;
        float m_fTouchEndLocation;
        float m_fTouchMoveStartLocation;
        
        float m_fDisBoundaryToChild_0;
        float m_fDisBetweenChild;
        float m_fDragForce;
        
        CC_SYNTHESIZE(PAGEVIEW_DIR, m_eDirection, Direction);
    };
}

#endif /* defined(__Test__CocoPageView__) */
