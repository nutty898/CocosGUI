#include "GUICCScale9SpriteLoader.h"
#include "CocoImageViewScale9.h"



#define PROPERTY_CONTENTSIZE "contentSize"
#define PROPERTY_SPRITEFRAME "spriteFrame"
#define PROPERTY_COLOR "color"
#define PROPERTY_OPACITY "opacity"
#define PROPERTY_BLENDFUNC "blendFunc"
#define PROPERTY_PREFEREDSIZE "preferedSize" // TODO Should be "preferredSize". This is a typo in cocos2d-iphone, cocos2d-x and CocosBuilder!
#define PROPERTY_INSETLEFT "insetLeft"
#define PROPERTY_INSETTOP "insetTop"
#define PROPERTY_INSETRIGHT "insetRight"
#define PROPERTY_INSETBOTTOM "insetBottom"

namespace cs
{
    void GUICCScale9SpriteLoader::onHandlePropTypeSpriteFrame(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCSpriteFrame * pCCSpriteFrame, GUICCBReader * pCCBReader) {
        if(strcmp(pPropertyName, PROPERTY_SPRITEFRAME) == 0) {
            /**/
//            ((CCScale9Sprite *)pNode)->setSpriteFrame(pCCSpriteFrame);
            dynamic_cast<CocoImageViewScale9*>(pWidget)->setSpriteFrame(pCCSpriteFrame);
            /**/
        } else {
            GUICCNodeLoader::onHandlePropTypeSpriteFrame(pWidget, pNode, pParent, pPropertyName, pCCSpriteFrame, pCCBReader);
        }
    }
    
    void GUICCScale9SpriteLoader::onHandlePropTypeColor3(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccColor3B pCCColor3B, GUICCBReader * pCCBReader) {
        if(strcmp(pPropertyName, PROPERTY_COLOR) == 0) {
            /**/
//            ((CCScale9Sprite *)pNode)->setColor(pCCColor3B);
            pWidget->setColor(pCCColor3B);
            /**/
        } else {
            GUICCNodeLoader::onHandlePropTypeColor3(pWidget, pNode, pParent, pPropertyName, pCCColor3B, pCCBReader);
        }
    }
    
    void GUICCScale9SpriteLoader::onHandlePropTypeByte(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, unsigned char pByte, GUICCBReader * pCCBReader) {
        if(strcmp(pPropertyName, PROPERTY_OPACITY) == 0) {
            /**/
//            ((CCScale9Sprite *)pNode)->setOpacity(pByte);
            pWidget->setOpacity(pByte);
            /**/
        } else {
            GUICCNodeLoader::onHandlePropTypeByte(pWidget, pNode, pParent, pPropertyName, pByte, pCCBReader);
        }
    }
    
    void GUICCScale9SpriteLoader::onHandlePropTypeBlendFunc(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccBlendFunc pCCBlendFunc, GUICCBReader * pCCBReader) {
        if(strcmp(pPropertyName, PROPERTY_BLENDFUNC) == 0) {
            // TODO Not exported by CocosBuilder yet!
            // ((CCScale9Sprite *)pNode)->setBlendFunc(pCCBlendFunc);
        } else {
            GUICCNodeLoader::onHandlePropTypeBlendFunc(pWidget, pNode, pParent, pPropertyName, pCCBlendFunc, pCCBReader);
        }
    }
    
    void GUICCScale9SpriteLoader::onHandlePropTypeSize(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCSize pSize, GUICCBReader * pCCBReader) {
        if(strcmp(pPropertyName, PROPERTY_CONTENTSIZE) == 0) {
            //((CCScale9Sprite *)pNode)->setContentSize(pSize);
        } else if(strcmp(pPropertyName, PROPERTY_PREFEREDSIZE) == 0) {
            /**/
//            ((CCScale9Sprite *)pNode)->setPreferredSize(pSize);
            dynamic_cast<CocoImageViewScale9*>(pWidget)->setPreferredSize(pSize);
            /**/
        } else {
            GUICCNodeLoader::onHandlePropTypeSize(pWidget, pNode, pParent, pPropertyName, pSize, pCCBReader);
        }
    }
    
    void GUICCScale9SpriteLoader::onHandlePropTypeFloat(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, float pFloat, GUICCBReader * pCCBReader) {
        if(strcmp(pPropertyName, PROPERTY_INSETLEFT) == 0) {
            /**/
//            ((CCScale9Sprite *)pNode)->setInsetLeft(pFloat);
            dynamic_cast<CocoImageViewScale9*>(pWidget)->setInsetLeft(pFloat);
            /**/
        } else if(strcmp(pPropertyName, PROPERTY_INSETTOP) == 0) {
            /**/
//            ((CCScale9Sprite *)pNode)->setInsetTop(pFloat);
            dynamic_cast<CocoImageViewScale9*>(pWidget)->setInsetTop(pFloat);
            /**/
        } else if(strcmp(pPropertyName, PROPERTY_INSETRIGHT) == 0) {
            /**/
//            ((CCScale9Sprite *)pNode)->setInsetRight(pFloat);
            dynamic_cast<CocoImageViewScale9*>(pWidget)->setInsetRight(pFloat);
            /**/
        } else if(strcmp(pPropertyName, PROPERTY_INSETBOTTOM) == 0) {
            /**/
//            ((CCScale9Sprite *)pNode)->setInsetBottom(pFloat);
            dynamic_cast<CocoImageViewScale9*>(pWidget)->setInsetBottom(pFloat);
            /**/
        } else {
            GUICCNodeLoader::onHandlePropTypeFloat(pWidget, pNode, pParent, pPropertyName, pFloat, pCCBReader);
        }
    }
}
