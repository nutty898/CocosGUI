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

#ifndef __UIINPUTMANAGER_H__
#define __UIINPUTMANAGER_H__

#include "cocos2d.h"
#include "../BaseClasses/CocoWidget.h"

NS_CC_EXT_BEGIN

class UIInputManager
{
public:
    UIInputManager();
    ~UIInputManager();
    void registWidget(CocoWidget* widget);
    void uiSceneHasChanged();
    void sortWidgets(CocoWidget* widget);
    void sortRootWidgets(CocoWidget* root);
    void removeManageredWidget(CocoWidget* widget);
    CocoWidget* checkEventWidget(cocos2d::CCPoint &touchPoint);
    void addCheckedDoubleClickWidget(CocoWidget* widget);
    void update(float dt);
    bool onTouchPressed(cocos2d::CCTouch* touch);
    bool onTouchMoved(cocos2d::CCTouch* touch);
    bool onTouchReleased(cocos2d::CCTouch* touch);
    bool onTouchCanceled(cocos2d::CCTouch* touch);
    
    void setRootWidget(CocoWidget* root);
    CocoWidget* getRootWidget();
    
protected:
    cocos2d::CCArray* m_manageredWidget;
    CocoWidget* m_pCurSelectedWidget;
    cocos2d::CCPoint touchBeganedPoint;
    cocos2d::CCPoint touchMovedPoint;
    cocos2d::CCPoint touchEndedPoint;
    cocos2d::CCPoint touchCanceledPoint;
    bool m_bWidgetBeSorted;
    bool m_bTouchDown;
    float m_fLongClickTime;
    float m_fLongClickRecordTime;
    cocos2d::CCArray* checkedDoubleClickWidget;
    CocoWidget* m_pRootWidget;
};

NS_CC_EXT_END

#endif /* defined(__CocoGUI__UIInputManager__) */
