#include "GUICCMenuItemLoader.h"
#include "CocoButton.h"



#define PROPERTY_BLOCK "block"
#define PROPERTY_ISENABLED "isEnabled"

namespace cs
{
    void GUICCMenuItemLoader::onHandlePropTypeBlock(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, BlockData * pBlockData, GUICCBReader * pCCBReader) {
        if(strcmp(pPropertyName, PROPERTY_BLOCK) == 0) {
            if (NULL != pBlockData) // Add this condition to allow CCMenuItemImage without target/selector predefined
            {
                ((CCMenuItem *)pNode)->setTarget(pBlockData->mTarget, pBlockData->mSELMenuHandler);
            }
        } else {
            GUICCNodeLoader::onHandlePropTypeBlock(pWidget, pNode, pParent, pPropertyName, pBlockData, pCCBReader);
        }
    }
    
    void GUICCMenuItemLoader::onHandlePropTypeCheck(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, bool pCheck, GUICCBReader * pCCBReader) {
        if(strcmp(pPropertyName, PROPERTY_ISENABLED) == 0) {
            /**/
//            ((CCMenuItem *)pNode)->setEnabled(pCheck);
            dynamic_cast<CocoButton*>(pWidget)->setBeTouchAble(pCheck);
            /**/
        } else {
            GUICCNodeLoader::onHandlePropTypeCheck(pWidget, pNode, pParent, pPropertyName, pCheck, pCCBReader);
        }
    }
}
