#include "GUICCControlButtonLoader.h"
#include "CocoControlButton.h"


namespace cs
{
    #define PROPERTY_ZOOMONTOUCHDOWN "zoomOnTouchDown"
    #define PROPERTY_TITLE_NORMAL "title|1"
    #define PROPERTY_TITLE_HIGHLIGHTED "title|2"
    #define PROPERTY_TITLE_DISABLED "title|3"
    #define PROPERTY_TITLECOLOR_NORMAL "titleColor|1"
    #define PROPERTY_TITLECOLOR_HIGHLIGHTED "titleColor|2"
    #define PROPERTY_TITLECOLOR_DISABLED "titleColor|3"
    #define PROPERTY_TITLETTF_NORMAL "titleTTF|1"
    #define PROPERTY_TITLETTF_HIGHLIGHTED "titleTTF|2"
    #define PROPERTY_TITLETTF_DISABLED "titleTTF|3"
    #define PROPERTY_TITLETTFSIZE_NORMAL "titleTTFSize|1"
    #define PROPERTY_TITLETTFSIZE_HIGHLIGHTED "titleTTFSize|2"
    #define PROPERTY_TITLETTFSIZE_DISABLED "titleTTFSize|3"
    #define PROPERTY_LABELANCHORPOINT "labelAnchorPoint"
    #define PROPERTY_PREFEREDSIZE "preferedSize" // TODO Should be "preferredSize". This is a typo in cocos2d-iphone, cocos2d-x and CocosBuilder!
    #define PROPERTY_BACKGROUNDSPRITEFRAME_NORMAL "backgroundSpriteFrame|1"
    #define PROPERTY_BACKGROUNDSPRITEFRAME_HIGHLIGHTED "backgroundSpriteFrame|2"
    #define PROPERTY_BACKGROUNDSPRITEFRAME_DISABLED "backgroundSpriteFrame|3"
    
    /**/
    #define PROPERTY_ENABLED "enabled"
    #define PROPERTY_SELECTED "selected"
    #define PROPERTY_CCCONTROL "ccControl"
    /**/
    
    void GUICCControlButtonLoader::onHandlePropTypeCheck(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, bool pCheck, GUICCBReader * pCCBReader) {
        if(strcmp(pPropertyName, PROPERTY_ZOOMONTOUCHDOWN) == 0) {
            /**/
//            ((CCControlButton *)pNode)->setZoomOnTouchDown(pCheck);
            dynamic_cast<CocoControlButton*>(pWidget)->setZoomOnTouchDown(pCheck);            
            /**/
        }
        /**/
        else if(strcmp(pPropertyName, PROPERTY_ENABLED) == 0) {
            /**/
            dynamic_cast<CocoControlButton*>(pWidget)->setBeTouchAble(pCheck);
            /**/
        } else if(strcmp(pPropertyName, PROPERTY_SELECTED) == 0) {
            //            ((CCControl *)pNode)->setSelected(pCheck);
        }
        /**/ else {
            GUICCControlLoader::onHandlePropTypeCheck(pWidget, pNode, pParent, pPropertyName, pCheck, pCCBReader);
        }
    }
    
    void GUICCControlButtonLoader::onHandlePropTypeString(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char * pString, GUICCBReader * pCCBReader) {
        if(strcmp(pPropertyName, PROPERTY_TITLE_NORMAL) == 0) {
            /**/
//            ((CCControlButton *)pNode)->setTitleForState(CCString::create(pString), CCControlStateNormal);
            dynamic_cast<CocoControlButton*>(pWidget)->setNormalTitle(pString);
            /**/
        } else if(strcmp(pPropertyName, PROPERTY_TITLE_HIGHLIGHTED) == 0) {
            /**/
//            ((CCControlButton *)pNode)->setTitleForState(CCString::create(pString), CCControlStateHighlighted);
            dynamic_cast<CocoControlButton*>(pWidget)->setPressedTitle(pString);
            /**/
        } else if(strcmp(pPropertyName, PROPERTY_TITLE_DISABLED) == 0) {
            /**/
//            ((CCControlButton *)pNode)->setTitleForState(CCString::create(pString), CCControlStateDisabled);
            dynamic_cast<CocoControlButton*>(pWidget)->setDisabledTitle(pString);
            /**/
        } else {
            GUICCControlLoader::onHandlePropTypeString(pWidget, pNode, pParent, pPropertyName, pString, pCCBReader);
        }
    }
    
    void GUICCControlButtonLoader::onHandlePropTypeFontTTF(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char * pFontTTF, GUICCBReader * pCCBReader) {
        if(strcmp(pPropertyName, PROPERTY_TITLETTF_NORMAL) == 0) {
            /**/
//            ((CCControlButton *)pNode)->setTitleTTFForState(pFontTTF, CCControlStateNormal);
            dynamic_cast<CocoControlButton*>(pWidget)->setNormalFontName(pFontTTF);
            /**/
        } else if(strcmp(pPropertyName, PROPERTY_TITLETTF_HIGHLIGHTED) == 0) {
            /**/
//            ((CCControlButton *)pNode)->setTitleTTFForState(pFontTTF, CCControlStateHighlighted);
            dynamic_cast<CocoControlButton*>(pWidget)->setPressedFontName(pFontTTF);
            /**/
        } else if(strcmp(pPropertyName, PROPERTY_TITLETTF_DISABLED) == 0) {
            /**/
//            ((CCControlButton *)pNode)->setTitleTTFForState(pFontTTF, CCControlStateDisabled);
            dynamic_cast<CocoControlButton*>(pWidget)->setDisabledFontName(pFontTTF);
            /**/
        } else {
            GUICCControlLoader::onHandlePropTypeFontTTF(pWidget, pNode, pParent, pPropertyName, pFontTTF, pCCBReader);
        }
    }
    
    void GUICCControlButtonLoader::onHandlePropTypeFloatScale(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, float pFloatScale, GUICCBReader * pCCBReader) {
        if(strcmp(pPropertyName, PROPERTY_TITLETTFSIZE_NORMAL) == 0) {
            /**/
//            ((CCControlButton *)pNode)->setTitleTTFSizeForState(pFloatScale, CCControlStateNormal);
            dynamic_cast<CocoControlButton*>(pWidget)->setNormalFontSize(pFloatScale);
            /**/
        } else if(strcmp(pPropertyName, PROPERTY_TITLETTFSIZE_HIGHLIGHTED) == 0) {
            /**/
//            ((CCControlButton *)pNode)->setTitleTTFSizeForState(pFloatScale, CCControlStateHighlighted);
            dynamic_cast<CocoControlButton*>(pWidget)->setPressedFontSize(pFloatScale);
            /**/
        } else if(strcmp(pPropertyName, PROPERTY_TITLETTFSIZE_DISABLED) == 0) {
            /**/
//            ((CCControlButton *)pNode)->setTitleTTFSizeForState(pFloatScale, CCControlStateDisabled);
            dynamic_cast<CocoControlButton*>(pWidget)->setDisabledFontSize(pFloatScale);
            /**/
        } else {
            GUICCControlLoader::onHandlePropTypeFloatScale(pWidget, pNode, pParent, pPropertyName, pFloatScale, pCCBReader);
        }
    }
    
    void GUICCControlButtonLoader::onHandlePropTypePoint(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCPoint pPoint, GUICCBReader * pCCBReader) {
        if(strcmp(pPropertyName, PROPERTY_LABELANCHORPOINT) == 0) {
            /**/
//            ((CCControlButton *)pNode)->setLabelAnchorPoint(pPoint);
            dynamic_cast<CocoControlButton*>(pWidget)->setLabelAnchorPoint(pPoint);
            /**/
        } else {
            GUICCControlLoader::onHandlePropTypePoint(pWidget, pNode, pParent, pPropertyName, pPoint, pCCBReader);
        }
    }
    
    void GUICCControlButtonLoader::onHandlePropTypeSize(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCSize pSize, GUICCBReader * pCCBReader) {
        if(strcmp(pPropertyName, PROPERTY_PREFEREDSIZE) == 0) {
            /**/
//            ((CCControlButton *)pNode)->setPreferredSize(pSize);
            dynamic_cast<CocoControlButton*>(pWidget)->setPreferredSize(pSize);
            /**/
        } else {
            GUICCControlLoader::onHandlePropTypeSize(pWidget, pNode, pParent, pPropertyName, pSize, pCCBReader);
        }
    }
    
    void GUICCControlButtonLoader::onHandlePropTypeSpriteFrame(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCSpriteFrame * pCCSpriteFrame, GUICCBReader * pCCBReader) {
        if(strcmp(pPropertyName, PROPERTY_BACKGROUNDSPRITEFRAME_NORMAL) == 0) {
            if(pCCSpriteFrame != NULL) {
                /**/
//                ((CCControlButton *)pNode)->setBackgroundSpriteFrameForState(pCCSpriteFrame, CCControlStateNormal);
                dynamic_cast<CocoControlButton*>(pWidget)->setNormalBackgroundSpriteFrame(pCCSpriteFrame);
                /**/
            }
        } else if(strcmp(pPropertyName, PROPERTY_BACKGROUNDSPRITEFRAME_HIGHLIGHTED) == 0) {
            if(pCCSpriteFrame != NULL) {
                /**/
//                ((CCControlButton *)pNode)->setBackgroundSpriteFrameForState(pCCSpriteFrame, CCControlStateHighlighted);
                dynamic_cast<CocoControlButton*>(pWidget)->setPressedBackgroundSpriteFrame(pCCSpriteFrame);
                /**/
            }
        } else if(strcmp(pPropertyName, PROPERTY_BACKGROUNDSPRITEFRAME_DISABLED) == 0) {
            if(pCCSpriteFrame != NULL) {
                /**/
//                ((CCControlButton *)pNode)->setBackgroundSpriteFrameForState(pCCSpriteFrame, CCControlStateDisabled);
                dynamic_cast<CocoControlButton*>(pWidget)->setDisabledBackgroundSpriteFrame(pCCSpriteFrame);
                /**/
            }
        } else {
            GUICCControlLoader::onHandlePropTypeSpriteFrame(pWidget, pNode, pParent, pPropertyName, pCCSpriteFrame, pCCBReader);
        }
    }
    
    void GUICCControlButtonLoader::onHandlePropTypeColor3(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccColor3B pCCColor3B, GUICCBReader * pCCBReader) {
        if(strcmp(pPropertyName, PROPERTY_TITLECOLOR_NORMAL) == 0) {
            /**/
//            ((CCControlButton *)pNode)->setTitleColorForState(pCCColor3B, CCControlStateNormal);
            dynamic_cast<CocoControlButton*>(pWidget)->setNormalFontColor(pCCColor3B);
            /**/
        } else if(strcmp(pPropertyName, PROPERTY_TITLECOLOR_HIGHLIGHTED) == 0) {
            /**/
//            ((CCControlButton *)pNode)->setTitleColorForState(pCCColor3B, CCControlStateHighlighted);
            dynamic_cast<CocoControlButton*>(pWidget)->setPressedFontColor(pCCColor3B);
            /**/
        } else if(strcmp(pPropertyName, PROPERTY_TITLECOLOR_DISABLED) == 0) {
            /**/
//            ((CCControlButton *)pNode)->setTitleColorForState(pCCColor3B, CCControlStateDisabled);
            dynamic_cast<CocoControlButton*>(pWidget)->setDisalbedFontColor(pCCColor3B);
            /**/
        } else {
            GUICCControlLoader::onHandlePropTypeColor3(pWidget, pNode, pParent, pPropertyName, pCCColor3B, pCCBReader);
        }
    }
}