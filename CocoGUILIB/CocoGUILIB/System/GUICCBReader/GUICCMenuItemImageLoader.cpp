#include "GUICCMenuItemImageLoader.h"
#include "CocoButton.h"



#define PROPERTY_NORMALDISPLAYFRAME "normalSpriteFrame"
#define PROPERTY_SELECTEDDISPLAYFRAME "selectedSpriteFrame"
#define PROPERTY_DISABLEDDISPLAYFRAME "disabledSpriteFrame"

namespace cs
{
    void GUICCMenuItemImageLoader::onHandlePropTypeSpriteFrame(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCSpriteFrame * pCCSpriteFrame, GUICCBReader * pCCBReader) {
        if(strcmp(pPropertyName, PROPERTY_NORMALDISPLAYFRAME) == 0) {
            if(pCCSpriteFrame != NULL) {
                /**/
//                ((CCMenuItemImage *)pNode)->setNormalSpriteFrame(pCCSpriteFrame);
                dynamic_cast<CocoButton*>(pWidget)->setNormalSpriteFrame(pCCSpriteFrame);
                /**/
            }
        } else if(strcmp(pPropertyName, PROPERTY_SELECTEDDISPLAYFRAME) == 0) {
            if(pCCSpriteFrame != NULL) {
                /**/
//                ((CCMenuItemImage *)pNode)->setSelectedSpriteFrame(pCCSpriteFrame);
                dynamic_cast<CocoButton*>(pWidget)->setPressedSpriteFrame(pCCSpriteFrame);
                /**/
            }
        } else if(strcmp(pPropertyName, PROPERTY_DISABLEDDISPLAYFRAME) == 0) {
            if(pCCSpriteFrame != NULL) {
                /**/
//                ((CCMenuItemImage *)pNode)->setDisabledSpriteFrame(pCCSpriteFrame);
                dynamic_cast<CocoButton*>(pWidget)->setDisabledSpriteFrame(pCCSpriteFrame);
                /**/
            }
        } else {
            GUICCMenuItemLoader::onHandlePropTypeSpriteFrame(pWidget, pNode, pParent, pPropertyName, pCCSpriteFrame, pCCBReader);
        }
    }
}
