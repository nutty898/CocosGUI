#include "GUICCScrollViewLoader.h"
#include "CocoScrollView.h"



#define PROPERTY_CONTAINER "container"
#define PROPERTY_DIRECTION "direction"
#define PROPERTY_CLIPSTOBOUNDS "clipsToBounds"
#define PROPERTY_BOUNCES "bounces"
#define PROPERTY_SCALE "scale"

namespace cs
{
    void GUICCScrollViewLoader::onHandlePropTypeSize(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCSize pSize, GUICCBReader * pCCBReader) {
        if(strcmp(pPropertyName, PROPERTY_CONTENTSIZE) == 0) {
            ((CCScrollView *)pNode)->setViewSize(pSize);
            dynamic_cast<CocoScrollView*>(pWidget)->setSize(pSize.width, pSize.height);
        } else {
            GUICCNodeLoader::onHandlePropTypeSize(pWidget, pNode, pParent, pPropertyName, pSize, pCCBReader);
        }
    }
    
    void GUICCScrollViewLoader::onHandlePropTypeCheck(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, bool pCheck, GUICCBReader * pCCBReader) {
        if(strcmp(pPropertyName, PROPERTY_CLIPSTOBOUNDS) == 0) {
            ((CCScrollView *)pNode)->setClippingToBounds(pCheck);
            dynamic_cast<CocoScrollView*>(pWidget)->setClipAble(pCheck);
        } else if(strcmp(pPropertyName, PROPERTY_BOUNCES) == 0) {
            ((CCScrollView *)pNode)->setBounceable(pCheck);
        } else {
            GUICCNodeLoader::onHandlePropTypeCheck(pWidget, pNode, pParent, pPropertyName, pCheck, pCCBReader);
        }
    }
    
    void GUICCScrollViewLoader::onHandlePropTypeCCBFile(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCNode * pCCBFileNode, GUICCBReader * pCCBReader) {
        if(strcmp(pPropertyName, PROPERTY_CONTAINER) == 0) {
            ((CCScrollView *)pNode)->setContainer(pCCBFileNode);
            ((CCScrollView *)pNode)->updateInset();
        } else {
            GUICCNodeLoader::onHandlePropTypeCCBFile(pWidget, pNode, pParent, pPropertyName, pCCBFileNode, pCCBReader);
        }
    }
    
    void GUICCScrollViewLoader::onHandlePropTypeFloat(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, float pFloat, GUICCBReader * pCCBReader) {
        if(strcmp(pPropertyName, PROPERTY_SCALE) == 0) {
            ((CCScrollView *)pNode)->setScale(pFloat);
            dynamic_cast<CocoScrollView*>(pWidget)->setScale(pFloat);            
        } else {
            GUICCNodeLoader::onHandlePropTypeFloat(pWidget, pNode, pParent, pPropertyName, pFloat, pCCBReader);
        }
    }
    
    void GUICCScrollViewLoader::onHandlePropTypeIntegerLabeled(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, int pIntegerLabeled, GUICCBReader * pCCBReader) {
        if(strcmp(pPropertyName, PROPERTY_DIRECTION) == 0) {
            ((CCScrollView *)pNode)->setDirection(CCScrollViewDirection(pIntegerLabeled));
            
            cs::SCROLLVIEW_DIR eDirection;
            switch (CCScrollViewDirection(pIntegerLabeled))
            {
                case cocos2d::extension::kCCScrollViewDirectionVertical:
                    eDirection = cs::SCROLLVIEW_DIR_VERTICAL;
                    break;
                    
                case cocos2d::extension::kCCScrollViewDirectionHorizontal:
                    eDirection = cs::SCROLLVIEW_DIR_HORIZONTAL;
                    break;
                    
                default:
                    eDirection = cs::SCROLLVIEW_DIR_VERTICAL;
                    break;
            }
            dynamic_cast<CocoScrollView*>(pWidget)->setDirection(eDirection);
        } else {
            GUICCNodeLoader::onHandlePropTypeFloatScale(pWidget, pNode, pParent, pPropertyName, pIntegerLabeled, pCCBReader);
        }
    }
}
