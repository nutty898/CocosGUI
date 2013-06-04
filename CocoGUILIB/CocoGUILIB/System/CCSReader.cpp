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

#include "CocosGUI.h"
#include "DictionaryHelper.h"
#include <fstream>
#include <iostream>


namespace cs {
    
    static CCSReader* sharedReader = NULL;
    
    CCSReader::CCSReader()
    {
        
    }
    
    CCSReader::~CCSReader()
    {
        
    }
    
    CCSReader* CCSReader::shareReader()
    {
        if (!sharedReader) {
            sharedReader = new CCSReader();
        }
        return sharedReader;
    }
    
    CocoWidget* CCSReader::widgetFromCCDictionary(cocos2d::CCDictionary* data)
    {
        CocoWidget* widget = NULL;
        
        const char* classname = DICTOOL->getStringValue(data, "classname");
        cocos2d::CCDictionary* uiOptions = DICTOOL->getSubDictionary(data, "options");
        if (classname && strcmp(classname, "Button") == 0) {
            widget = CocoButton::create();
            this->setPropsForButtonFromCCDictionary(widget, uiOptions);
        }else if (classname && strcmp(classname, "CheckBox") == 0){
            widget = CocoCheckBox::create();
            this->setPropsForCheckBoxFromCCDictionary(widget, uiOptions);
        }else if (classname && strcmp(classname, "Label") == 0){
            widget = CocoLabel::create();
            this->setPropsForLabelFromCCDictionary(widget, uiOptions);
        }else if (classname && strcmp(classname, "LabelAtlas") == 0){
            widget = CocoLabelAtlas::create();
            this->setPropsForLabelAtlasFromCCDictionary(widget, uiOptions);
        }else if (classname && strcmp(classname, "LoadingBar") == 0){
            widget = CocoLoadingBar::create();
            this->setPropsForLoadingBarFromCCDictionary(widget, uiOptions);
        }else if (classname && strcmp(classname, "ScrollView") == 0){
            widget = CocoScrollView::create();
            this->setPropsForScrollViewFromCCDictionary(widget, uiOptions);
        }else if (classname && strcmp(classname, "TextArea") == 0){
            widget = CocoTextArea::create();
            this->setPropsForTextAreaFromCCDictionary(widget, uiOptions);
        }else if (classname && strcmp(classname, "TextButton") == 0){
            widget = CocoTextButton::create();
            this->setPropsForTextButtonFromCCDictionary(widget, uiOptions);
        }else if (classname && strcmp(classname, "TextField") == 0){
            widget = CocoTextField::create();
            this->setPropsForTextFieldFromCCDictionary(widget, uiOptions);
        }else if (classname && strcmp(classname, "ImageView") == 0){
            widget = CocoImageView::create();
            this->setPropsForImageViewFromCCDictionary(widget, uiOptions);
        }else if (classname && strcmp(classname, "Panel") == 0){
            widget = CocoPanel::create();
            this->setPropsForPanelFromCCDictionary(widget, uiOptions);
        }else if (classname && strcmp(classname, "Slider") == 0){
            widget = CocoSlider::create();
            this->setPropsForSliderFromCCDictionary(widget, uiOptions);
        }else if (classname && strcmp(classname, "ImageButton") == 0){
            widget = CocoImageButton::create();
            this->setPropsForImageButtonFromCCDictionary(widget, uiOptions);
        }
        cocos2d::CCArray* arr = DICTOOL->getArrayValue(data, "children");
        if (arr) {
            for (int i=0;i<arr->count();i++){
                cocos2d::CCDictionary* subData = (cocos2d::CCDictionary*)(arr->objectAtIndex(i));
                CocoWidget* child = this->widgetFromCCDictionary(subData);
                if (child) {
                    widget->addChild(child);
                }
            }
        }
        return widget;
    }
    
    CocoWidget* CCSReader::widgetFromJsonDictionary(cs::CSJsonDictionary* data)
    {
        CocoWidget* widget = NULL;
        const char* classname = DICTOOL->getStringValue_json(data, "classname");
        cs::CSJsonDictionary* uiOptions = DICTOOL->getSubDictionary_json(data, "options");
        if (classname && strcmp(classname, "Button") == 0) {
            widget = CocoButton::create();
            this->setPropsForButtonFromJsonDictionary(widget, uiOptions);
        }else if (classname && strcmp(classname, "CheckBox") == 0){
            widget = CocoCheckBox::create();
            this->setPropsForCheckBoxFromJsonDictionary(widget, uiOptions);
        }else if (classname && strcmp(classname, "Label") == 0){
            widget = CocoLabel::create();
            this->setPropsForLabelFromJsonDictionary(widget, uiOptions);
        }else if (classname && strcmp(classname, "LabelAtlas") == 0){
            widget = CocoLabelAtlas::create();
            this->setPropsForLabelAtlasFromJsonDictionary(widget, uiOptions);
        }else if (classname && strcmp(classname, "LoadingBar") == 0){
            widget = CocoLoadingBar::create();
            this->setPropsForLoadingBarFromJsonDictionary(widget, uiOptions);
        }else if (classname && strcmp(classname, "ScrollView") == 0){
            widget = CocoScrollView::create();
            this->setPropsForScrollViewFromJsonDictionary(widget, uiOptions);
        }else if (classname && strcmp(classname, "TextArea") == 0){
            widget = CocoTextArea::create();
            this->setPropsForTextAreaFromJsonDictionary(widget, uiOptions);
        }else if (classname && strcmp(classname, "TextButton") == 0){
            widget = CocoTextButton::create();
            this->setPropsForTextButtonFromJsonDictionary(widget, uiOptions);
        }else if (classname && strcmp(classname, "TextField") == 0){
            widget = CocoTextField::create();
            this->setPropsForTextFieldFromJsonDictionary(widget, uiOptions);
        }else if (classname && strcmp(classname, "ImageView") == 0){
            widget = CocoImageView::create();
            this->setPropsForImageViewFromJsonDictionary(widget, uiOptions);
        }else if (classname && strcmp(classname, "Panel") == 0){
            widget = CocoPanel::create();
            this->setPropsForPanelFromJsonDictionary(widget, uiOptions);
        }else if (classname && strcmp(classname, "Slider") == 0){
            widget = CocoSlider::create();
            this->setPropsForSliderFromJsonDictionary(widget, uiOptions);
        }else if (classname && strcmp(classname, "ImageButton") == 0){
            widget = CocoImageButton::create();
            this->setPropsForImageButtonFromJsonDictionary(widget, uiOptions);
        }
        int childrenCount = DICTOOL->getArrayCount_json(data, "children");
        for (int i=0;i<childrenCount;i++){
            cs::CSJsonDictionary* subData = DICTOOL->getDictionaryFromArray_json(data, "children", i);
            CocoWidget* child = this->widgetFromJsonDictionary(subData);
            if (child) {
                widget->addChild(child);
            }
        }
        return widget;
    }
    
    CocoWidget* CCSReader::widgetFromPlistFile(const char* fileName)
    {
        cocos2d::CCDictionary* dic = cocos2d::CCDictionary::createWithContentsOfFile(fileName);
        float fileVersion = DICTOOL->getFloatValue(dic, "version");
        if (fileVersion != kCCSVersion) {
            printf("WARNING! Incompatible json file version (file: %f reader: %f)\n", fileVersion, kCCSVersion);
            return NULL;
        }
        cocos2d::CCArray* textures = (cocos2d::CCArray*)(DICTOOL->getArrayValue(dic, "textures"));
        for (int i=0; textures->count(); i++) {
            cocos2d::CCString* file = (cocos2d::CCString*)(textures->objectAtIndex(i));
            COCOUISYSTEM->addSpriteFrame(file->m_sString.c_str());
        }
        float fileDesignWidth = DICTOOL->getFloatValue(dic, "designWidth");
        float fileDesignHeight = DICTOOL->getFloatValue(dic, "designHeight");
        if (fileDesignWidth <= 0 || fileDesignHeight <= 0) {
            printf("Read design size error!\n");
            cocos2d::CCSize winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
            UISystem::shareSystem()->setFileDesignWidth(winSize.width);
            UISystem::shareSystem()->setFileDesignHeight(winSize.height);
        }else{
            UISystem::shareSystem()->setFileDesignWidth(fileDesignWidth);
            UISystem::shareSystem()->setFileDesignHeight(fileDesignHeight);
        }
        cocos2d::CCDictionary* widgetTree = (cocos2d::CCDictionary*)(DICTOOL->getArrayValue(dic, "widgetTree"));
        return this->widgetFromCCDictionary(widgetTree);
    }
    
    CocoWidget* CCSReader::widgetFromJsonFile(const char *fileName)
    {
        const char *des = NULL;
		std::string jsonpath;
        cs::CSJsonDictionary *jsonDict = NULL;
        jsonpath = cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName);
        
        unsigned long size = 0;
        des = (char*)(cocos2d::CCFileUtils::sharedFileUtils()->getFileData(jsonpath.c_str(),"r" , &size));
        jsonDict = new cs::CSJsonDictionary();
        jsonDict->initWithDescription(des);
		if(NULL == des || strcmp(des, "") == 0)
		{
			printf("read json file[%s] error!\n", fileName);
		}
//        float fileVersion = DICTOOL->getFloatValue_json(jsonDict, "version");
//        if (fileVersion != kCCSVersion) {
//            printf("WARNING! Incompatible json file version (file: %f reader: %f)\n", fileVersion, kCCSVersion);
//            return NULL;
//        }
        int texturesCount = DICTOOL->getArrayCount_json(jsonDict, "textures");
        int pos = jsonpath.find_last_of('/');
        std::string pPath = jsonpath.substr(0,pos+1);
        for (int i=0; i<texturesCount; i++) {
            const char* file = DICTOOL->getStringValueFromArray_json(jsonDict, "textures", i);
            std::string tp = pPath;
            tp.append(file);
            COCOUISYSTEM->addSpriteFrame(tp.c_str());
        }
        float fileDesignWidth = DICTOOL->getFloatValue_json(jsonDict, "designWidth");
        float fileDesignHeight = DICTOOL->getFloatValue_json(jsonDict, "designHeight");
        if (fileDesignWidth <= 0 || fileDesignHeight <= 0) {
            printf("Read design size error!\n");
            cocos2d::CCSize winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
            UISystem::shareSystem()->setFileDesignWidth(winSize.width);
            UISystem::shareSystem()->setFileDesignHeight(winSize.height);
        }else{
            UISystem::shareSystem()->setFileDesignWidth(fileDesignWidth);
            UISystem::shareSystem()->setFileDesignHeight(fileDesignHeight);
        }
        cs::CSJsonDictionary* widgetTree = DICTOOL->getSubDictionary_json(jsonDict, "widgetTree");
        cs::CocoWidget* widget = this->widgetFromJsonDictionary(widgetTree);
        delete jsonDict;
        jsonDict = NULL;
        delete[] des;
        return widget;
    }
    
    void CCSReader::setPropsForWidgetFromCCDictionary(CocoWidget*widget,cocos2d::CCDictionary *options)
    {
        widget->setWidgetTag(DICTOOL->getIntValue(options, "tag"));
        widget->setBeTouchAble(DICTOOL->getBooleanValue(options, "touchAble"));
        const char* name = DICTOOL->getStringValue(options, "name");
        const char* widgetName = name?name:"default";
        widget->setName(widgetName);
        float x = DICTOOL->getFloatValue(options, "x");
        float y = DICTOOL->getFloatValue(options, "y");
        widget->setPosition(ccp(x,y));
        CCObject* sx = DICTOOL->checkObjectExist(options, "scaleX");
        if (sx) {
            widget->setScaleX(DICTOOL->objectToFloatValue(sx));
        }
        CCObject* sy = DICTOOL->checkObjectExist(options, "scaleY");
        if (sy) {
            widget->setScaleY(DICTOOL->objectToFloatValue(sy));
        }
        CCObject* rt = DICTOOL->checkObjectExist(options, "rotation");
        if (rt) {
            widget->setRotation(DICTOOL->objectToFloatValue(rt));
        }
        CCObject* vb = DICTOOL->checkObjectExist(options, "visible");
        if (vb) {
            widget->setVisible(DICTOOL->objectToBooleanValue(vb));
        }
        widget->setUseMergedTexture(DICTOOL->getBooleanValue(options, "useMergedTexture"));
        int z = DICTOOL->getIntValue(options, "ZOrder");
        widget->setWidgetZOrder(z);
    }
    
    void CCSReader::setColorPropsForWidgetFromCCDictionary(cs::CocoWidget *widget, cocos2d::CCDictionary *options)
    {
        CCObject * op = DICTOOL->checkObjectExist(options, "opacity");
        if (op) {
            widget->setOpacity(DICTOOL->objectToIntValue(op));
        }
        CCObject * cr = DICTOOL->checkObjectExist(options, "colorR");
        CCObject * cg = DICTOOL->checkObjectExist(options, "colorG");
        CCObject * cb = DICTOOL->checkObjectExist(options, "colorB");
        int colorR = cr ? DICTOOL->objectToIntValue(cr) : 255;
        int colorG = cg ? DICTOOL->objectToIntValue(cg) : 255;
        int colorB = cb ? DICTOOL->objectToIntValue(cb) : 255;
        widget->setColor(colorR, colorG, colorB);
        CCObject * apx = DICTOOL->checkObjectExist(options, "anchorPointX");
        float apxf = apx ? DICTOOL->objectToFloatValue(apx) : 0.5f;
        CCObject * apy = DICTOOL->checkObjectExist(options, "anchorPointY");
        float apyf = apy ? DICTOOL->objectToFloatValue(apy) : 0.5f;
        widget->setAnchorPoint(ccp(apxf, apyf));
    }
    
    void CCSReader::setPropsForButtonFromCCDictionary(CocoWidget*widget,cocos2d::CCDictionary* options)
    {
        this->setPropsForWidgetFromCCDictionary(widget, options);
        CocoButton* button = (CocoButton*)widget;
        bool scale9Enable = DICTOOL->getBooleanValue(options, "scale9Enable");
        button->setScale9Enable(scale9Enable);
        
        const char* normalFileName = DICTOOL->getStringValue(options, "normal");
        const char* pressedFileName = DICTOOL->getStringValue(options, "pressed");
        const char* disabledFileName = DICTOOL->getStringValue(options, "disabled");
        
        if (scale9Enable) {
            float cx = DICTOOL->getFloatValue(options, "capInsetsX");
            float cy = DICTOOL->getFloatValue(options, "capInsetsY");
            float cw = DICTOOL->getFloatValue(options, "capInsetsWidth");
            float ch = DICTOOL->getFloatValue(options, "capInsetsHeight");
            
            button->setTexturesScale9(normalFileName, pressedFileName, disabledFileName, cocos2d::CCRect(cx, cy, cw, ch),widget->getUseMergedTexture());
            cocos2d::CCObject* sw = DICTOOL->checkObjectExist(options, "scale9Width");
            cocos2d::CCObject* sh = DICTOOL->checkObjectExist(options, "scale9Height");
            if (sw && sh) {
                float swf = DICTOOL->objectToFloatValue(sw);
                float shf = DICTOOL->objectToFloatValue(sh);
                button->setScale9Size(swf, shf);
             }
        }else{
            button->setTextures(normalFileName, pressedFileName, disabledFileName,widget->getUseMergedTexture());
        }
        this->setColorPropsForWidgetFromCCDictionary(widget, options);
    }
    
    void CCSReader::setPropsForCheckBoxFromCCDictionary(CocoWidget*widget,cocos2d::CCDictionary* options)
    {
        this->setPropsForWidgetFromCCDictionary(widget, options);
        CocoCheckBox* checkBox = (CocoCheckBox*)widget;
        const char* backGroundFileName = DICTOOL->getStringValue(options, "backGroundBox");
        const char* backGroundSelectedFileName = DICTOOL->getStringValue(options, "backGroundBoxSelected");
        const char* frontCrossFileName = DICTOOL->getStringValue(options, "frontCross");
        const char* backGroundDisabledFileName = DICTOOL->getStringValue(options, "backGroundBoxDisabled");
        const char* frontCrossDisabledFileName = DICTOOL->getStringValue(options, "frontCrossDisabled");
        
        checkBox->setTextures(backGroundFileName, backGroundSelectedFileName, frontCrossFileName,backGroundDisabledFileName,frontCrossDisabledFileName,widget->getUseMergedTexture());
        this->setColorPropsForWidgetFromCCDictionary(widget, options);
    }
    
    void CCSReader::setPropsForImageViewFromCCDictionary(CocoWidget*widget,cocos2d::CCDictionary* options)
    {
        this->setPropsForWidgetFromCCDictionary(widget, options);
        
        CocoImageView* imageView = (CocoImageView*)widget;
        const char* imageFileName = DICTOOL->getStringValue(options, "fileName");
        cocos2d::CCObject*  scale9EnableExist = DICTOOL->checkObjectExist(options, "scale9Enable");
        bool scale9Enable = false;
        if (scale9EnableExist)
        {
            scale9Enable = DICTOOL->getBooleanValue(options, "scale9Enable");
        }
        imageView->setScale9Enable(scale9Enable);
        if (scale9Enable)
        {
            float cx = DICTOOL->getFloatValue(options, "capInsetsX");
            float cy = DICTOOL->getFloatValue(options, "capInsetsY");
            float cw = DICTOOL->getFloatValue(options, "capInsetsWidth");
            float ch = DICTOOL->getFloatValue(options, "capInsetsHeight");
            
            imageView->setTexturesScale9(imageFileName, cocos2d::CCRect(cx, cy, cw, ch), widget->getUseMergedTexture());
            bool sw = DICTOOL->checkObjectExist(options, "scale9Width");
            bool sh = DICTOOL->checkObjectExist(options, "scale9Height");
            if (sw && sh)
            {
                float swf = DICTOOL->getFloatValue(options, "scale9Width");
                float shf = DICTOOL->getFloatValue(options, "scale9Height");
                imageView->setScale9Size(swf, shf);
            }
        }
        else
        {
            imageView->setTexture(imageFileName, widget->getUseMergedTexture());
        }
        bool flipX = DICTOOL->getBooleanValue(options, "flipX");
        bool flipY = DICTOOL->getBooleanValue(options, "flipY");
        imageView->setFlipX(flipX);
        imageView->setFlipY(flipY);
        
        this->setColorPropsForWidgetFromCCDictionary(widget, options);
    }
    
    void CCSReader::setPropsForLabelFromCCDictionary(CocoWidget*widget,cocos2d::CCDictionary* options)
    {
        this->setPropsForWidgetFromCCDictionary(widget, options);
        CocoLabel* label = (CocoLabel*)widget;
        bool touchScaleChangeAble = DICTOOL->getBooleanValue(options, "touchSacleEnable");
        label->setTouchScaleChangeAble(touchScaleChangeAble);
        const char* text = DICTOOL->getStringValue(options, "text");
        label->setText(text);
        CCObject* fs = DICTOOL->checkObjectExist(options, "fontSize");
        if (fs) {
            label->setFontSize(DICTOOL->objectToIntValue(fs));
        }
        CCObject* fn = DICTOOL->checkObjectExist(options, "fontName");
        if (fn) {
            label->setFontName(DICTOOL->objectToStringValue(fn));
        }
        CCObject* cro = DICTOOL->checkObjectExist(options, "colorR");
        CCObject* cgo = DICTOOL->checkObjectExist(options, "colorG");
        CCObject* cbo = DICTOOL->checkObjectExist(options, "colorB");
        int cr = cro?DICTOOL->objectToIntValue(cro):255;
        int cg = cgo?DICTOOL->objectToIntValue(cgo):255;
        int cb = cbo?DICTOOL->objectToIntValue(cbo):255;
        label->setTextColor(cr, cg, cb);
        label->setFlipX(DICTOOL->getBooleanValue(options, "flipX"));
        label->setFlipY(DICTOOL->getBooleanValue(options, "flipY"));
        this->setColorPropsForWidgetFromCCDictionary(widget, options);
        int gravity = DICTOOL->getIntValue(options, "gravity");
        label->setGravity(gravity);
    }
    
    void CCSReader::setPropsForLabelAtlasFromCCDictionary(CocoWidget*widget,cocos2d::CCDictionary* options)
    {
        this->setPropsForWidgetFromCCDictionary(widget, options);
        CocoLabelAtlas* labelAtlas = (CocoLabelAtlas*)widget;
        cocos2d::CCObject* sv = DICTOOL->checkObjectExist(options, "stringValue");
        cocos2d::CCObject* cmf = DICTOOL->checkObjectExist(options, "charMapFile");
        cocos2d::CCObject* iw = DICTOOL->checkObjectExist(options, "itemWidth");
        cocos2d::CCObject* ih = DICTOOL->checkObjectExist(options, "itemHeight");
        cocos2d::CCObject* scm = DICTOOL->checkObjectExist(options, "startCharMap");
        if (sv && cmf && iw && ih && scm) {
            labelAtlas->setProperty(DICTOOL->objectToStringValue(sv),DICTOOL->objectToStringValue(cmf),DICTOOL->objectToIntValue(iw),DICTOOL->objectToIntValue(ih),DICTOOL->objectToStringValue(scm),widget->getUseMergedTexture());
        }
        this->setColorPropsForWidgetFromCCDictionary(widget, options);
    }
    
    void CCSReader::setPropsForContainerWidgetFromCCDictionary(cs::CocoWidget *widget, cocos2d::CCDictionary *options)
    {
        this->setPropsForWidgetFromCCDictionary(widget, options);
        CocoContainerWidget* containerWidget = (CocoContainerWidget*)widget;
        containerWidget->setClipAble(DICTOOL->getBooleanValue(options, "clipAble"));
        this->setColorPropsForWidgetFromCCDictionary(widget, options);
    }
    
    void CCSReader::setPropsForPanelFromCCDictionary(CocoWidget*widget,cocos2d::CCDictionary* options)
    {
        this->setPropsForContainerWidgetFromCCDictionary(widget, options);
        CocoPanel* panel = (CocoPanel*)widget;
        bool backGroundScale9Enable = DICTOOL->getBooleanValue(options, "backGroundScale9Enable");
        panel->setBackGroundImageScale9Enable(backGroundScale9Enable);
        int cr = DICTOOL->getIntValue(options, "colorR");
        int cg = DICTOOL->getIntValue(options, "colorG");
        int cb = DICTOOL->getIntValue(options, "colorB");
        int co = DICTOOL->getIntValue(options, "colorO");
        float w = DICTOOL->getFloatValue(options, "width");
        float h = DICTOOL->getFloatValue(options, "height");
        panel->setColorAndSize(cr, cg, cb, co, w, h);
        if (backGroundScale9Enable) {
            float cx = DICTOOL->getFloatValue(options, "capInsetsX");
            float cy = DICTOOL->getFloatValue(options, "capInsetsY");
            float cw = DICTOOL->getFloatValue(options, "capInsetsWidth");
            float ch = DICTOOL->getFloatValue(options, "capInsetsHeight");
            panel->setBackGroundImageScale9(DICTOOL->getStringValue(options, "backGroundImage"), cocos2d::CCRect(cx, cy, cw, ch),widget->getUseMergedTexture());
        }else{
            panel->setBackGroundImage(DICTOOL->getStringValue(options, "backGroundImage"),widget->getUseMergedTexture());
        }
        this->setColorPropsForWidgetFromCCDictionary(widget, options);
    }
    
    void CCSReader::setPropsForScrollViewFromCCDictionary(CocoWidget*widget,cocos2d::CCDictionary* options)
    {
        this->setPropsForPanelFromCCDictionary(widget, options);
        this->setColorPropsForWidgetFromCCDictionary(widget, options);
    }
    
    void CCSReader::setPropsForSliderFromCCDictionary(CocoWidget*widget,cocos2d::CCDictionary* options)
    {
        this->setPropsForWidgetFromCCDictionary(widget, options);
        CocoSlider* slider = (CocoSlider*)widget;
        
        bool barTextureScale9Enable = DICTOOL->getBooleanValue(options, "barTextureScale9Enable");
        slider->setBarTextureScale9Enable(barTextureScale9Enable);
        CCObject* bt = DICTOOL->checkObjectExist(options, "barFileName");
        float barLength = DICTOOL->getFloatValue(options, "length");
        if (bt) {
            if (barTextureScale9Enable) {
                slider->setBarTextureScale9(DICTOOL->objectToStringValue(bt), 0, 0, 0, 0,widget->getUseMergedTexture());
                slider->setBarLength(barLength);
            }else{
                slider->setBarTexture(DICTOOL->objectToStringValue(bt),widget->getUseMergedTexture());
            }
        }
        slider->setSlidBallTextures(DICTOOL->getStringValue(options, "ballNormal"), DICTOOL->getStringValue(options, "ballPressed"), DICTOOL->getStringValue(options, "ballDisabled"),widget->getUseMergedTexture());
        slider->setSlidBallPercent(DICTOOL->getIntValue(options, "percent"));
        
        cocos2d::CCObject* showProgressBarExist = DICTOOL->checkObjectExist(options, "showProgressBar");
        bool showProgressBar = false;
        if (showProgressBarExist)
        {
            showProgressBar = DICTOOL->getBooleanValue(options, "showProgressBar");
        }
        if (showProgressBar)
        {
            slider->setShowProgressBar(showProgressBar);
            slider->setProgressBarTextureScale9(DICTOOL->getStringValue(options, "progressBarFileName"), 0, 0, 0, 0, widget->getUseMergedTexture());
            slider->setProgressBarScale(barLength);
        }
        
        this->setColorPropsForWidgetFromCCDictionary(widget, options);
    }
    
    void CCSReader::setPropsForTextAreaFromCCDictionary(CocoWidget*widget,cocos2d::CCDictionary* options)
    {
        this->setPropsForWidgetFromCCDictionary(widget, options);
        CocoTextArea* textArea = (CocoTextArea*)widget;
        textArea->setText(DICTOOL->getStringValue(options, "text"));
        CCObject* fs = DICTOOL->checkObjectExist(options, "fontSize");
        if (fs) {
            textArea->setFontSize(DICTOOL->objectToIntValue(fs));
        }
        int cr = DICTOOL->getIntValue(options, "colorR");
        int cg = DICTOOL->getIntValue(options, "colorG");
        int cb = DICTOOL->getIntValue(options, "colorB");
        textArea->setTextColor(cr, cg, cb);
        textArea->setFontName(DICTOOL->getStringValue(options, "fontName"));
        CCObject* aw = DICTOOL->checkObjectExist(options, "areaWidth");
        CCObject* ah = DICTOOL->checkObjectExist(options, "areaHeight");
        if (aw && ah) {
            textArea->setTextAreaSize(DICTOOL->objectToFloatValue(aw),DICTOOL->objectToFloatValue(ah));
        }
        CCObject* ha = DICTOOL->checkObjectExist(options, "hAlignment");
        if (ha) {
            textArea->setTextHorizontalAlignment(DICTOOL->objectToIntValue(ha));
        }
        CCObject* va = DICTOOL->checkObjectExist(options, "vAlignment");
        if (va) {
            textArea->setTextVerticalAlignment(DICTOOL->objectToIntValue(va));
        }
        this->setColorPropsForWidgetFromCCDictionary(widget, options);
    }
    
    void CCSReader::setPropsForTextButtonFromCCDictionary(CocoWidget*widget,cocos2d::CCDictionary* options)
    {
        this->setPropsForButtonFromCCDictionary(widget, options);
        CocoTextButton* textButton = (CocoTextButton*)widget;
        textButton->setText(DICTOOL->getStringValue(options, "text"));
        textButton->setFlipX(DICTOOL->getBooleanValue(options, "flipX"));
        textButton->setFlipY(DICTOOL->getBooleanValue(options, "flipY"));
        int cr = DICTOOL->getIntValue(options, "textColorR");
        int cg = DICTOOL->getIntValue(options, "textColorG");
        int cb = DICTOOL->getIntValue(options, "textColorB");
        textButton->setTextColor(cr,cg,cb);
        CCObject* fs = DICTOOL->checkObjectExist(options, "fontSize");
        if (fs) {
            textButton->setFontSize(DICTOOL->objectToIntValue(fs));
        }
        CCObject* fn = DICTOOL->checkObjectExist(options, "fontName");
        if (fn) {
            textButton->setFontName(DICTOOL->objectToStringValue(fn));
        }
        this->setColorPropsForWidgetFromCCDictionary(widget, options);
    }
    
    void CCSReader::setPropsForTextFieldFromCCDictionary(CocoWidget*widget,cocos2d::CCDictionary* options)
    {
        this->setPropsForWidgetFromCCDictionary(widget, options);
        CocoTextField* textField = (CocoTextField*)widget;
        cocos2d::CCObject * ph = DICTOOL->checkObjectExist(options, "placeHolder");
        if (ph) {
            textField->setPlaceHolder(DICTOOL->objectToStringValue(ph));
        }
        textField->setText(DICTOOL->getStringValue(options, "text"));
        cocos2d::CCObject * fs = DICTOOL->checkObjectExist(options, "fontSize");
        if (fs) {
            textField->setFontSize(DICTOOL->objectToIntValue(fs));
        }
        cocos2d::CCObject* tsw = DICTOOL->checkObjectExist(options, "touchSizeWidth");
        cocos2d::CCObject* tsh = DICTOOL->checkObjectExist(options, "touchSizeHeight");
        if (tsw && tsh) {
            textField->setTouchSize(DICTOOL->objectToFloatValue(tsw), DICTOOL->objectToFloatValue(tsh));
        }
        
        int cr = DICTOOL->getIntValue(options, "colorR");
        int cg = DICTOOL->getIntValue(options, "colorG");
        int cb = DICTOOL->getIntValue(options, "colorB");
        textField->setTextColor(cr,cg,cb);
        this->setColorPropsForWidgetFromCCDictionary(widget, options);
    }
    
    void CCSReader::setPropsForLoadingBarFromCCDictionary(cs::CocoWidget *widget, cocos2d::CCDictionary *options)
    {
        this->setPropsForWidgetFromCCDictionary(widget, options);
        CocoLoadingBar* loadingBar = (CocoLoadingBar*)widget;
        loadingBar->setTexture(DICTOOL->getStringValue(options, "texture"),widget->getUseMergedTexture());
        loadingBar->setDirection(DICTOOL->getIntValue(options, "direction"));
        loadingBar->setPercent(DICTOOL->getIntValue(options, "percent"));
        this->setColorPropsForWidgetFromCCDictionary(widget, options);
    }
    
    void CCSReader::setPropsForImageButtonFromCCDictionary(cs::CocoWidget *widget, cocos2d::CCDictionary *options)
    {
        this->setPropsForButtonFromCCDictionary(widget, options);
        
        CocoImageButton* imageButton = dynamic_cast<CocoImageButton*>(widget);
        
        const char* imageNormalFileName = DICTOOL->getStringValue(options, "imageNormal");
        const char* imagePressedFileName = DICTOOL->getStringValue(options, "imagePressed");
        const char* imageDisabledFileName = DICTOOL->getStringValue(options, "imageDisabled");
        
        bool imageScale9Enable = DICTOOL->getBooleanValue(options, "imageScale9Enable");
        imageButton->setImageScale9Enable(imageScale9Enable);
        if (imageScale9Enable)
        {
            float cx = DICTOOL->getFloatValue(options, "imageCapInsetsX");
            float cy = DICTOOL->getFloatValue(options, "imageCapInsetsY");
            float cw = DICTOOL->getFloatValue(options, "imageCapInsetsWidth");
            float ch = DICTOOL->getFloatValue(options, "imageCapInsetsHeight");
            imageButton->setImageTexturesScale9(imageNormalFileName, imagePressedFileName, imageDisabledFileName,
                                                cocos2d::CCRect(cx, cy, cw, ch),
                                                widget->getUseMergedTexture());
            bool imageSw = DICTOOL->checkObjectExist(options, "imageScale9Width");
            bool imageSh = DICTOOL->checkObjectExist(options, "imageScale9Height");
            if (imageSw && imageSh)
            {
                float imageSwf = DICTOOL->getFloatValue(options, "imageScale9Width");
                float imageShf = DICTOOL->getFloatValue(options, "imageScale9Height");
                imageButton->setImageScale9Size(imageSwf, imageShf);
            }
        }
        else
        {
            imageButton->setImageTextures(imageNormalFileName, imagePressedFileName, imageDisabledFileName, widget->getUseMergedTexture());
        }
        
        bool imageFlipX = DICTOOL->getBooleanValue(options, "imageFlipX");
        bool imageFlipY = DICTOOL->getBooleanValue(options, "imageFlipY");
        imageButton->setImageFlipX(imageFlipX);
        imageButton->setImageFlipY(imageFlipY);
        
        bool imageOp = DICTOOL->checkObjectExist(options, "imageOpacity");
        if (imageOp)
        {
            GLubyte imageOpbyte = DICTOOL->getIntValue(options, "imageOpacity");
            imageButton->setImageOpacity(imageOpbyte);
        }
        bool imageCr = DICTOOL->checkObjectExist(options, "imageColorR");
        bool imageCg = DICTOOL->checkObjectExist(options, "imageColorG");
        bool imageCb = DICTOOL->checkObjectExist(options, "imageColorB");
        GLubyte imageColorR = imageCr ? DICTOOL->getIntValue(options, "imageColorR") : 255;
        GLubyte imageColorG = imageCg ? DICTOOL->getIntValue(options, "imageColorG") : 255;
        GLubyte imageColorB = imageCb ? DICTOOL->getIntValue(options, "imageColorB") : 255;
        imageButton->setImageColor(imageColorR, imageColorG, imageColorB);
    }
    
    /****************************************************json**************************************************/
    
    void CCSReader::setPropsForWidgetFromJsonDictionary(CocoWidget*widget,cs::CSJsonDictionary *options)
    {
        widget->setWidgetTag(DICTOOL->getIntValue_json(options, "tag"));
        widget->setBeTouchAble(DICTOOL->getBooleanValue_json(options, "touchAble"));
        const char* name = DICTOOL->getStringValue_json(options, "name");
        const char* widgetName = name?name:"default";
        widget->setName(widgetName);
        float x = DICTOOL->getFloatValue_json(options, "x");
        float y = DICTOOL->getFloatValue_json(options, "y");
        widget->setPosition(ccp(x,y));
        bool sx = DICTOOL->checkObjectExist_json(options, "scaleX");
        if (sx) {
            widget->setScaleX(DICTOOL->getFloatValue_json(options, "scaleX"));
        }
        bool sy = DICTOOL->checkObjectExist_json(options, "scaleY");
        if (sy) {
            widget->setScaleY(DICTOOL->getFloatValue_json(options, "scaleY"));
        }
        bool rt = DICTOOL->checkObjectExist_json(options, "rotation");
        if (rt) {
            widget->setRotation(DICTOOL->getFloatValue_json(options, "rotation"));
        }
        bool vb = DICTOOL->checkObjectExist_json(options, "visible");
        if (vb) {
            widget->setVisible(DICTOOL->getBooleanValue_json(options, "visible"));
        }
        widget->setUseMergedTexture(DICTOOL->getBooleanValue_json(options, "useMergedTexture"));
        int z = DICTOOL->getIntValue_json(options, "ZOrder");
        widget->setWidgetZOrder(z);
    }
    
    void CCSReader::setColorPropsForWidgetFromJsonDictionary(cs::CocoWidget *widget, cs::CSJsonDictionary *options)
    {
        bool op = DICTOOL->checkObjectExist_json(options, "opacity");
        if (op) {
            widget->setOpacity(DICTOOL->getIntValue_json(options, "opacity"));
        }
        bool cr = DICTOOL->checkObjectExist_json(options, "colorR");
        bool cg = DICTOOL->checkObjectExist_json(options, "colorG");
        bool cb = DICTOOL->checkObjectExist_json(options, "colorB");
        int colorR = cr ? DICTOOL->getIntValue_json(options, "colorR") : 255;
        int colorG = cg ? DICTOOL->getIntValue_json(options, "colorG") : 255;
        int colorB = cb ? DICTOOL->getIntValue_json(options, "colorB") : 255;
        widget->setColor(colorR, colorG, colorB);
        bool apx = DICTOOL->checkObjectExist_json(options, "anchorPointX");
        float apxf = apx ? DICTOOL->getFloatValue_json(options, "anchorPointX") : 0.5f;
        bool apy = DICTOOL->checkObjectExist_json(options, "anchorPointY");
        float apyf = apy ? DICTOOL->getFloatValue_json(options, "anchorPointY") : 0.5f;
        widget->setAnchorPoint(ccp(apxf, apyf));
    }

    void CCSReader::setPropsForButtonFromJsonDictionary(CocoWidget*widget,cs::CSJsonDictionary* options)
    {
        this->setPropsForWidgetFromJsonDictionary(widget, options);
        CocoButton* button = (CocoButton*)widget;
        bool scale9Enable = DICTOOL->getBooleanValue_json(options, "scale9Enable");
        button->setScale9Enable(scale9Enable);
        
        const char* normalFileName = DICTOOL->getStringValue_json(options, "normal");
        const char* pressedFileName = DICTOOL->getStringValue_json(options, "pressed");
        const char* disabledFileName = DICTOOL->getStringValue_json(options, "disabled");
        
        if (scale9Enable) {
            float cx = DICTOOL->getFloatValue_json(options, "capInsetsX");
            float cy = DICTOOL->getFloatValue_json(options, "capInsetsY");
            float cw = DICTOOL->getFloatValue_json(options, "capInsetsWidth");
            float ch = DICTOOL->getFloatValue_json(options, "capInsetsHeight");
            
            button->setTexturesScale9(normalFileName, pressedFileName, disabledFileName, cocos2d::CCRect(cx, cy, cw, ch),widget->getUseMergedTexture());
            bool sw = DICTOOL->checkObjectExist_json(options, "scale9Width");
            bool sh = DICTOOL->checkObjectExist_json(options, "scale9Height");
            if (sw && sh) {
                float swf = DICTOOL->getFloatValue_json(options, "scale9Width");
                float shf = DICTOOL->getFloatValue_json(options, "scale9Height");
                button->setScale9Size(swf, shf);
            }
        }else{
            button->setTextures(normalFileName, pressedFileName, disabledFileName,widget->getUseMergedTexture());
        }
        this->setColorPropsForWidgetFromJsonDictionary(widget,options);
    }
    
    void CCSReader::setPropsForCheckBoxFromJsonDictionary(CocoWidget*widget,cs::CSJsonDictionary* options)
    {
        this->setPropsForWidgetFromJsonDictionary(widget, options);
        CocoCheckBox* checkBox = (CocoCheckBox*)widget;
        const char* backGroundFileName = DICTOOL->getStringValue_json(options, "backGroundBox");
        const char* backGroundSelectedFileName = DICTOOL->getStringValue_json(options, "backGroundBoxSelected");
        const char* frontCrossFileName = DICTOOL->getStringValue_json(options, "frontCross");
        const char* backGroundDisabledFileName = DICTOOL->getStringValue_json(options, "backGroundBoxDisabled");
        const char* frontCrossDisabledFileName = DICTOOL->getStringValue_json(options, "frontCrossDisabled");
        
        checkBox->setTextures(backGroundFileName, backGroundSelectedFileName, frontCrossFileName,backGroundDisabledFileName,frontCrossDisabledFileName,widget->getUseMergedTexture());
        this->setColorPropsForWidgetFromJsonDictionary(widget,options);
    }
    
    void CCSReader::setPropsForImageViewFromJsonDictionary(CocoWidget*widget,cs::CSJsonDictionary* options)
    {
        this->setPropsForWidgetFromJsonDictionary(widget, options);
        
        CocoImageView* imageView = (CocoImageView*)widget;
        const char* imageFileName = DICTOOL->getStringValue_json(options, "fileName");
        bool scale9EnableExist = DICTOOL->checkObjectExist_json(options, "scale9Enable");
        bool scale9Enable = false;
        if (scale9EnableExist)
        {
            scale9Enable = DICTOOL->getBooleanValue_json(options, "scale9Enable");
        }
        imageView->setScale9Enable(scale9Enable);
        if (scale9Enable)
        {
            float cx = DICTOOL->getFloatValue_json(options, "capInsetsX");
            float cy = DICTOOL->getFloatValue_json(options, "capInsetsY");
            float cw = DICTOOL->getFloatValue_json(options, "capInsetsWidth");
            float ch = DICTOOL->getFloatValue_json(options, "capInsetsHeight");
            
            imageView->setTexturesScale9(imageFileName, cocos2d::CCRect(cx, cy, cw, ch), widget->getUseMergedTexture());
            bool sw = DICTOOL->checkObjectExist_json(options, "scale9Width");
            bool sh = DICTOOL->checkObjectExist_json(options, "scale9Height");
            if (sw && sh)
            {
                float swf = DICTOOL->getFloatValue_json(options, "scale9Width");
                float shf = DICTOOL->getFloatValue_json(options, "scale9Height");
                imageView->setScale9Size(swf, shf);
            }
        }
        else
        {
            imageView->setTexture(imageFileName, widget->getUseMergedTexture());
        }
        bool flipX = DICTOOL->getBooleanValue_json(options, "flipX");
        bool flipY = DICTOOL->getBooleanValue_json(options, "flipY");
        imageView->setFlipX(flipX);
        imageView->setFlipY(flipY);
        
        this->setColorPropsForWidgetFromJsonDictionary(widget,options);
    }
    
    void CCSReader::setPropsForLabelFromJsonDictionary(CocoWidget*widget,cs::CSJsonDictionary* options)
    {
        this->setPropsForWidgetFromJsonDictionary(widget, options);
        CocoLabel* label = (CocoLabel*)widget;
        bool touchScaleChangeAble = DICTOOL->getBooleanValue_json(options, "touchSacleEnable");
        label->setTouchScaleChangeAble(touchScaleChangeAble);
        const char* text = DICTOOL->getStringValue_json(options, "text");
        label->setText(text);
        bool fs = DICTOOL->checkObjectExist_json(options, "fontSize");
        if (fs) {
            label->setFontSize(DICTOOL->getIntValue_json(options, "fontSize"));
        }
        bool fn = DICTOOL->checkObjectExist_json(options, "fontName");
        if (fn) {
            label->setFontName(DICTOOL->getStringValue_json(options, "fontName"));
        }
        bool cro = DICTOOL->checkObjectExist_json(options, "colorR");
        bool cgo = DICTOOL->checkObjectExist_json(options, "colorG");
        bool cbo = DICTOOL->checkObjectExist_json(options, "colorB");
        int cr = cro?DICTOOL->getIntValue_json(options, "colorR"):255;
        int cg = cgo?DICTOOL->getIntValue_json(options, "colorG"):255;
        int cb = cbo?DICTOOL->getIntValue_json(options, "colorB"):255;
        label->setTextColor(cr, cg, cb);
        label->setFlipX(DICTOOL->getBooleanValue_json(options, "flipX"));
        label->setFlipY(DICTOOL->getBooleanValue_json(options, "flipY"));
        this->setColorPropsForWidgetFromJsonDictionary(widget,options);
        int gravity = DICTOOL->getIntValue_json(options, "gravity");
        label->setGravity(gravity);
    }
    
    void CCSReader::setPropsForLabelAtlasFromJsonDictionary(CocoWidget*widget,cs::CSJsonDictionary* options)
    {
        this->setPropsForWidgetFromJsonDictionary(widget, options);
        CocoLabelAtlas* labelAtlas = (CocoLabelAtlas*)widget;
        bool sv = DICTOOL->checkObjectExist_json(options, "stringValue");
        bool cmf = DICTOOL->checkObjectExist_json(options, "charMapFile");
        bool iw = DICTOOL->checkObjectExist_json(options, "itemWidth");
        bool ih = DICTOOL->checkObjectExist_json(options, "itemHeight");
        bool scm = DICTOOL->checkObjectExist_json(options, "startCharMap");
        if (sv && cmf && iw && ih && scm) {
            labelAtlas->setProperty(DICTOOL->getStringValue_json(options, "stringValue"),DICTOOL->getStringValue_json(options, "charMapFile"),DICTOOL->getIntValue_json(options, "itemWidth"),DICTOOL->getIntValue_json(options,"itemHeight"),DICTOOL->getStringValue_json(options, "startCharMap"),widget->getUseMergedTexture());
        }
        this->setColorPropsForWidgetFromJsonDictionary(widget,options);
    }
    
    void CCSReader::setPropsForContainerWidgetFromJsonDictionary(cs::CocoWidget *widget, cs::CSJsonDictionary *options)
    {
        this->setPropsForWidgetFromJsonDictionary(widget, options);
        CocoContainerWidget* containerWidget = (CocoContainerWidget*)widget;
        containerWidget->setClipAble(DICTOOL->getBooleanValue_json(options, "clipAble"));
        this->setColorPropsForWidgetFromJsonDictionary(widget,options);
    }
    
    void CCSReader::setPropsForPanelFromJsonDictionary(CocoWidget*widget,cs::CSJsonDictionary* options)
    {
        this->setPropsForContainerWidgetFromJsonDictionary(widget, options);
        CocoPanel* panel = (CocoPanel*)widget;
        bool backGroundScale9Enable = DICTOOL->getBooleanValue_json(options, "backGroundScale9Enable");
        panel->setBackGroundImageScale9Enable(backGroundScale9Enable);
        int cr = DICTOOL->getIntValue_json(options, "colorR");
        int cg = DICTOOL->getIntValue_json(options, "colorG");
        int cb = DICTOOL->getIntValue_json(options, "colorB");
        int co = DICTOOL->getIntValue_json(options, "colorO");
        float w = DICTOOL->getFloatValue_json(options, "width");
        float h = DICTOOL->getFloatValue_json(options, "height");
        panel->setColorAndSize(cr, cg, cb, co, w, h);
        if (backGroundScale9Enable) {
            float cx = DICTOOL->getFloatValue_json(options, "capInsetsX");
            float cy = DICTOOL->getFloatValue_json(options, "capInsetsY");
            float cw = DICTOOL->getFloatValue_json(options, "capInsetsWidth");
            float ch = DICTOOL->getFloatValue_json(options, "capInsetsHeight");
            panel->setBackGroundImageScale9(DICTOOL->getStringValue_json(options, "backGroundImage"), cocos2d::CCRect(cx, cy, cw, ch),widget->getUseMergedTexture());
        }else{
            panel->setBackGroundImage(DICTOOL->getStringValue_json(options, "backGroundImage"),widget->getUseMergedTexture());
        }
        this->setColorPropsForWidgetFromJsonDictionary(widget,options);
    }
    
    void CCSReader::setPropsForScrollViewFromJsonDictionary(CocoWidget*widget,cs::CSJsonDictionary* options)
    {
        this->setPropsForPanelFromJsonDictionary(widget, options);
        this->setColorPropsForWidgetFromJsonDictionary(widget,options);
    }
    
    void CCSReader::setPropsForSliderFromJsonDictionary(CocoWidget*widget,cs::CSJsonDictionary* options)
    {
        this->setPropsForWidgetFromJsonDictionary(widget, options);
        CocoSlider* slider = (CocoSlider*)widget;
        
        bool barTextureScale9Enable = DICTOOL->getBooleanValue_json(options, "barTextureScale9Enable");
        slider->setBarTextureScale9Enable(barTextureScale9Enable);
        bool bt = DICTOOL->checkObjectExist_json(options, "barFileName");
        float barLength = DICTOOL->getFloatValue_json(options, "length");
        if (bt) {
            if (barTextureScale9Enable) {
                slider->setBarTextureScale9(DICTOOL->getStringValue_json(options, "barFileName"), 0, 0, 0, 0,widget->getUseMergedTexture());
                slider->setBarLength(barLength);
            }else{
                slider->setBarTexture(DICTOOL->getStringValue_json(options, "barFileName"),widget->getUseMergedTexture());
            }
        }
        slider->setSlidBallTextures(DICTOOL->getStringValue_json(options, "ballNormal"), DICTOOL->getStringValue_json(options, "ballPressed"), DICTOOL->getStringValue_json(options, "ballDisabled"),widget->getUseMergedTexture());
        slider->setSlidBallPercent(DICTOOL->getIntValue_json(options, "percent"));
        
        bool showProgressBarExist = DICTOOL->checkObjectExist_json(options, "showProgressBar");
        bool showProgressBar = false;
        if (showProgressBarExist)
        {
            showProgressBar = DICTOOL->getBooleanValue_json(options, "showProgressBar");
        }
        if (showProgressBar)
        {
            slider->setShowProgressBar(showProgressBar);
            slider->setProgressBarTextureScale9(DICTOOL->getStringValue_json(options, "progressBarFileName"), 0, 0, 0, 0, widget->getUseMergedTexture());
            slider->setProgressBarScale(barLength);
        }
        
        this->setColorPropsForWidgetFromJsonDictionary(widget,options);
    }
    
    void CCSReader::setPropsForTextAreaFromJsonDictionary(CocoWidget*widget,cs::CSJsonDictionary* options)
    {
        this->setPropsForWidgetFromJsonDictionary(widget, options);
        CocoTextArea* textArea = (CocoTextArea*)widget;
        textArea->setText(DICTOOL->getStringValue_json(options, "text"));
        bool fs = DICTOOL->checkObjectExist_json(options, "fontSize");
        if (fs) {
            textArea->setFontSize(DICTOOL->getIntValue_json(options, "fontSize"));
        }
        int cr = DICTOOL->getIntValue_json(options, "colorR");
        int cg = DICTOOL->getIntValue_json(options, "colorG");
        int cb = DICTOOL->getIntValue_json(options, "colorB");
        textArea->setTextColor(cr, cg, cb);
        textArea->setFontName(DICTOOL->getStringValue_json(options, "fontName"));
        bool aw = DICTOOL->checkObjectExist_json(options, "areaWidth");
        bool ah = DICTOOL->checkObjectExist_json(options, "areaHeight");
        if (aw && ah) {
            textArea->setTextAreaSize(DICTOOL->getFloatValue_json(options, "areaWidth"),DICTOOL->getFloatValue_json(options,"areaHeight"));
        }
        bool ha = DICTOOL->checkObjectExist_json(options, "hAlignment");
        if (ha) {
            textArea->setTextHorizontalAlignment(DICTOOL->getIntValue_json(options, "hAlignment"));
        }
        bool va = DICTOOL->checkObjectExist_json(options, "vAlignment");
        if (va) {
            textArea->setTextVerticalAlignment(DICTOOL->getIntValue_json(options, "vAlignment"));
        }
        this->setColorPropsForWidgetFromJsonDictionary(widget,options);
    }
    
    void CCSReader::setPropsForTextButtonFromJsonDictionary(CocoWidget*widget,cs::CSJsonDictionary* options)
    {
        this->setPropsForButtonFromJsonDictionary(widget, options);
        CocoTextButton* textButton = (CocoTextButton*)widget;
        textButton->setText(DICTOOL->getStringValue_json(options, "text"));
        textButton->setFlipX(DICTOOL->getBooleanValue_json(options, "flipX"));
        textButton->setFlipY(DICTOOL->getBooleanValue_json(options, "flipY"));
        int cr = DICTOOL->getIntValue_json(options, "textColorR");
        int cg = DICTOOL->getIntValue_json(options, "textColorG");
        int cb = DICTOOL->getIntValue_json(options, "textColorB");
        textButton->setTextColor(cr,cg,cb);
        bool fs = DICTOOL->checkObjectExist_json(options, "fontSize");
        if (fs) {
            textButton->setFontSize(DICTOOL->getIntValue_json(options, "fontSize"));
        }
        bool fn = DICTOOL->checkObjectExist_json(options, "fontName");
        if (fn) {
            textButton->setFontName(DICTOOL->getStringValue_json(options, "fontName"));
        }
        this->setColorPropsForWidgetFromJsonDictionary(widget,options);
    }
    
    void CCSReader::setPropsForTextFieldFromJsonDictionary(CocoWidget*widget,cs::CSJsonDictionary* options)
    {
        this->setPropsForWidgetFromJsonDictionary(widget, options);
        CocoTextField* textField = (CocoTextField*)widget;
        bool ph = DICTOOL->checkObjectExist_json(options, "placeHolder");
        if (ph) {
            textField->setPlaceHolder(DICTOOL->getStringValue_json(options, "placeHolder"));
        }
        textField->setText(DICTOOL->getStringValue_json(options, "text"));
        bool fs = DICTOOL->checkObjectExist_json(options, "fontSize");
        if (fs) {
            textField->setFontSize(DICTOOL->getIntValue_json(options, "fontSize"));
        }
        bool tsw = DICTOOL->checkObjectExist_json(options, "touchSizeWidth");
        bool tsh = DICTOOL->checkObjectExist_json(options, "touchSizeHeight");
        if (tsw && tsh) {
            textField->setTouchSize(DICTOOL->getFloatValue_json(options, "touchSizeWidth"), DICTOOL->getFloatValue_json(options,"touchSizeHeight"));
        }
        
        int cr = DICTOOL->getIntValue_json(options, "colorR");
        int cg = DICTOOL->getIntValue_json(options, "colorG");
        int cb = DICTOOL->getIntValue_json(options, "colorB");
        textField->setTextColor(cr,cg,cb);
        this->setColorPropsForWidgetFromJsonDictionary(widget,options);
    }
    
    void CCSReader::setPropsForLoadingBarFromJsonDictionary(cs::CocoWidget *widget, cs::CSJsonDictionary *options)
    {
        this->setPropsForWidgetFromJsonDictionary(widget, options);
        CocoLoadingBar* loadingBar = (CocoLoadingBar*)widget;
        loadingBar->setTexture(DICTOOL->getStringValue_json(options, "texture"),widget->getUseMergedTexture());
        loadingBar->setDirection(DICTOOL->getIntValue_json(options, "direction"));
        loadingBar->setPercent(DICTOOL->getIntValue_json(options, "percent"));
        this->setColorPropsForWidgetFromJsonDictionary(widget,options);
    }
    
    void CCSReader::setPropsForImageButtonFromJsonDictionary(cs::CocoWidget *widget, cs::CSJsonDictionary *options)
    {
        this->setPropsForButtonFromJsonDictionary(widget, options);
        
        CocoImageButton* imageButton = dynamic_cast<CocoImageButton*>(widget);
        
        const char* imageNormalFileName = DICTOOL->getStringValue_json(options, "imageNormal");
        const char* imagePressedFileName = DICTOOL->getStringValue_json(options, "imagePressed");
        const char* imageDisabledFileName = DICTOOL->getStringValue_json(options, "imageDisabled");
        
        bool imageScale9Enable = DICTOOL->getBooleanValue_json(options, "imageScale9Enable");
        imageButton->setImageScale9Enable(imageScale9Enable);
        if (imageScale9Enable)
        {
            float cx = DICTOOL->getFloatValue_json(options, "imageCapInsetsX");
            float cy = DICTOOL->getFloatValue_json(options, "imageCapInsetsY");
            float cw = DICTOOL->getFloatValue_json(options, "imageCapInsetsWidth");
            float ch = DICTOOL->getFloatValue_json(options, "imageCapInsetsHeight");
            imageButton->setImageTexturesScale9(imageNormalFileName, imagePressedFileName, imageDisabledFileName,
                                                cocos2d::CCRect(cx, cy, cw, ch),
                                                widget->getUseMergedTexture());
            bool imageSw = DICTOOL->checkObjectExist_json(options, "imageScale9Width");
            bool imageSh = DICTOOL->checkObjectExist_json(options, "imageScale9Height");
            if (imageSw && imageSh)
            {
                float imageSwf = DICTOOL->getFloatValue_json(options, "imageScale9Width");
                float imageShf = DICTOOL->getFloatValue_json(options, "imageScale9Height");
                imageButton->setImageScale9Size(imageSwf, imageShf);
            }
        }
        else
        {
            imageButton->setImageTextures(imageNormalFileName, imagePressedFileName, imageDisabledFileName, widget->getUseMergedTexture());
        }
        
        bool imageFlipX = DICTOOL->getBooleanValue_json(options, "imageFlipX");
        bool imageFlipY = DICTOOL->getBooleanValue_json(options, "imageFlipY");
        imageButton->setImageFlipX(imageFlipX);
        imageButton->setImageFlipY(imageFlipY);
        
        bool imageOp = DICTOOL->checkObjectExist_json(options, "imageOpacity");
        if (imageOp)
        {
            GLubyte imageOpbyte = DICTOOL->getIntValue_json(options, "imageOpacity");
            imageButton->setImageOpacity(imageOpbyte);
        }
        bool imageCr = DICTOOL->checkObjectExist_json(options, "imageColorR");
        bool imageCg = DICTOOL->checkObjectExist_json(options, "imageColorG");
        bool imageCb = DICTOOL->checkObjectExist_json(options, "imageColorB");
        GLubyte imageColorR = imageCr ? DICTOOL->getIntValue_json(options, "imageColorR") : 255;
        GLubyte imageColorG = imageCg ? DICTOOL->getIntValue_json(options, "imageColorG") : 255;
        GLubyte imageColorB = imageCb ? DICTOOL->getIntValue_json(options, "imageColorB") : 255;
        imageButton->setImageColor(imageColorR, imageColorG, imageColorB);
    }
}