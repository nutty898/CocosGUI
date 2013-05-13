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

#ifndef __CocoGUI__UIScene__
#define __CocoGUI__UIScene__

#include "CocoRootWidget.h"

namespace cs {
    class UISystem;
    class UIScene
    {
    public:
        UIScene();
        ~UIScene();
        void init();
        
        void addWidget(CocoWidget* widget);
        void removeWidgetAndCleanUp(CocoWidget* widget,bool cleanup);
        void setVisible(bool visible);
        void update(float dt);
        void addUpdateEnableWidget(CocoWidget* widget);
        void removeUpdateEnableWidget(CocoWidget* widget);
        CocoWidget* getWidgetByTag(int tag);
        CocoWidget* checkWidgetByTag(CocoWidget* root,int tag);
        CocoWidget* getWidgetByName(const char* name);
        CocoWidget* checkWidgetByName(CocoWidget* root,const char* name);
        void cleanScene();
    protected:
        bool m_bTouchAble;
        bool m_bVisible;
        bool m_bUpdateAble;
        UISystem* m_pUISystem;
        cocos2d::CCArray* m_updateEnableChildren;
        CC_SYNTHESIZE(CocoRootWidget *, m_pRootWidget, RootWidget);
    };
}

#endif /* defined(__CocoGUI__UIScene__) */
