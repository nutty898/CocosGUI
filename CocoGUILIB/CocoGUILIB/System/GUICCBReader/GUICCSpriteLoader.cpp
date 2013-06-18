#include "GUICCSpriteLoader.h"
#include "CocoImageView.h"

#define PROPERTY_FLIP "flip"
#define PROPERTY_DISPLAYFRAME "displayFrame"
#define PROPERTY_COLOR "color"
#define PROPERTY_OPACITY "opacity"
#define PROPERTY_BLENDFUNC "blendFunc"

namespace cs
{
    void GUICCSpriteLoader::onHandlePropTypeSpriteFrame(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCSpriteFrame * pCCSpriteFrame, GUICCBReader * pCCBReader) {
        if(strcmp(pPropertyName, PROPERTY_DISPLAYFRAME) == 0) {
            /**/
//            ((CCSprite *)pNode)->setDisplayFrame(pCCSpriteFrame);
            dynamic_cast<CocoImageView*>(pWidget)->setDisplayFrame(pCCSpriteFrame);
            /**/
        } else {
            GUICCNodeLoader::onHandlePropTypeSpriteFrame(pWidget, pNode, pParent, pPropertyName, pCCSpriteFrame, pCCBReader);
        }
    }
    
    void GUICCSpriteLoader::onHandlePropTypeFlip(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, bool * pFlip, GUICCBReader * pCCBReader) {
        if(strcmp(pPropertyName, PROPERTY_FLIP) == 0) {
            /**/
            /*
            ((CCSprite *)pNode)->setFlipX(pFlip[0]);
            ((CCSprite *)pNode)->setFlipY(pFlip[1]);
             */
            pWidget->setFlipX(pFlip[0]);
            pWidget->setFlipY(pFlip[1]);
            /*
            dynamic_cast<CocoImageView*>(pWidget)->setFlipX(pFlip[0]);
            dynamic_cast<CocoImageView*>(pWidget)->setFlipY(pFlip[1]);
             */
            /**/
        } else {
            GUICCNodeLoader::onHandlePropTypeFlip(pWidget, pNode, pParent, pPropertyName, pFlip, pCCBReader);
        }
    }
    
    void GUICCSpriteLoader::onHandlePropTypeColor3(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccColor3B pCCColor3B, GUICCBReader * pCCBReader) {
        if(strcmp(pPropertyName, PROPERTY_COLOR) == 0) {
            /**/
//            ((CCSprite *)pNode)->setColor(pCCColor3B);
            pWidget->setColor(pCCColor3B);
            /**/
        } else {
            GUICCNodeLoader::onHandlePropTypeColor3(pWidget, pNode, pParent, pPropertyName, pCCColor3B, pCCBReader);
        }
    }
    
    void GUICCSpriteLoader::onHandlePropTypeByte(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, unsigned char pByte, GUICCBReader * pCCBReader) {
        if(strcmp(pPropertyName, PROPERTY_OPACITY) == 0) {
            /**/
//            ((CCSprite *)pNode)->setOpacity(pByte);
            pWidget->setOpacity(pByte);
            /**/
        } else {
            GUICCNodeLoader::onHandlePropTypeByte(pWidget, pNode, pParent, pPropertyName, pByte, pCCBReader);
        }
    }
    
    void GUICCSpriteLoader::onHandlePropTypeBlendFunc(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccBlendFunc pCCBlendFunc, GUICCBReader * pCCBReader) {
        if(strcmp(pPropertyName, PROPERTY_BLENDFUNC) == 0) {
            /**/
//            ((CCSprite *)pNode)->setBlendFunc(pCCBlendFunc);
            pWidget->setBlendFunc(pCCBlendFunc);
            /**/
        } else {
            GUICCNodeLoader::onHandlePropTypeBlendFunc(pWidget, pNode, pParent, pPropertyName, pCCBlendFunc, pCCBReader);
        }
    }
}
