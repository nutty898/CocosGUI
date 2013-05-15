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

#ifndef __CocoStudioGUITest__CCSReader__
#define __CocoStudioGUITest__CCSReader__

#include "CocoWidget.h"
#include "CSContentJsonDictionary.h"

namespace cs {
    #define kCCSVersion 1.0
    class CCSReader : cocos2d::CCObject
    {
    public:
        CCSReader();
        ~CCSReader();
        static CCSReader* shareReader();
        
        CocoWidget* widgetFromPlistFile(const char* fileName);
        CocoWidget* widgetFromJsonFile(const char* fileName);
        CocoWidget* widgetFromCCDictionary(cocos2d::CCDictionary* data);
        CocoWidget* widgetFromJsonDictionary(cs::CSJsonDictionary* data);
        
        void setPropsForWidgetFromCCDictionary(CocoWidget*widget,cocos2d::CCDictionary* options);
        void setColorPropsForWidgetFromCCDictionary(CocoWidget*widget,cocos2d::CCDictionary* options);
        void setPropsForButtonFromCCDictionary(CocoWidget*widget,cocos2d::CCDictionary* options);
        void setPropsForCheckBoxFromCCDictionary(CocoWidget*widget,cocos2d::CCDictionary* options);
        void setPropsForImageViewFromCCDictionary(CocoWidget*widget,cocos2d::CCDictionary* options);
        void setPropsForLabelFromCCDictionary(CocoWidget*widget,cocos2d::CCDictionary* options);
        void setPropsForLabelAtlasFromCCDictionary(CocoWidget*widget,cocos2d::CCDictionary* options);
        void setPropsForContainerWidgetFromCCDictionary(CocoWidget*widget,cocos2d::CCDictionary* options);
        void setPropsForPanelFromCCDictionary(CocoWidget*widget,cocos2d::CCDictionary* options);
        void setPropsForScrollViewFromCCDictionary(CocoWidget*widget,cocos2d::CCDictionary* options);
        void setPropsForSliderFromCCDictionary(CocoWidget*widget,cocos2d::CCDictionary* options);
        void setPropsForTextAreaFromCCDictionary(CocoWidget*widget,cocos2d::CCDictionary* options);
        void setPropsForTextButtonFromCCDictionary(CocoWidget*widget,cocos2d::CCDictionary* options);
        void setPropsForTextFieldFromCCDictionary(CocoWidget*widget,cocos2d::CCDictionary* options);
        void setPropsForLoadingBarFromCCDictionary(CocoWidget*widget,cocos2d::CCDictionary* options);
        void setPropsForImageButtonFromCCDictionary(CocoWidget* widget, cocos2d::CCDictionary* options);
        
        void setPropsForWidgetFromJsonDictionary(CocoWidget*widget,cs::CSJsonDictionary* options);
        void setColorPropsForWidgetFromJsonDictionary(CocoWidget*widget,cs::CSJsonDictionary* options);
        void setPropsForButtonFromJsonDictionary(CocoWidget*widget,cs::CSJsonDictionary* options);
        void setPropsForCheckBoxFromJsonDictionary(CocoWidget*widget,cs::CSJsonDictionary* options);
        void setPropsForImageViewFromJsonDictionary(CocoWidget*widget,cs::CSJsonDictionary* options);
        void setPropsForLabelFromJsonDictionary(CocoWidget*widget,cs::CSJsonDictionary* options);
        void setPropsForLabelAtlasFromJsonDictionary(CocoWidget*widget,cs::CSJsonDictionary* options);
        void setPropsForContainerWidgetFromJsonDictionary(CocoWidget*widget,cs::CSJsonDictionary* options);
        void setPropsForPanelFromJsonDictionary(CocoWidget*widget,cs::CSJsonDictionary* options);
        void setPropsForScrollViewFromJsonDictionary(CocoWidget*widget,cs::CSJsonDictionary* options);
        void setPropsForSliderFromJsonDictionary(CocoWidget*widget,cs::CSJsonDictionary* options);
        void setPropsForTextAreaFromJsonDictionary(CocoWidget*widget,cs::CSJsonDictionary* options);
        void setPropsForTextButtonFromJsonDictionary(CocoWidget*widget,cs::CSJsonDictionary* options);
        void setPropsForTextFieldFromJsonDictionary(CocoWidget*widget,cs::CSJsonDictionary* options);
        void setPropsForLoadingBarFromJsonDictionary(CocoWidget*widget,cs::CSJsonDictionary* options);
        void setPropsForImageButtonFromJsonDictionary(CocoWidget* widget, cs::CSJsonDictionary* options);
        
    protected:
    };
}


#endif /* defined(__CocoStudioGUITest__CCSReader__) */
