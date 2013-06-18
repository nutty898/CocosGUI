#include "GUICCControlLoader.h"


namespace cs
{
    #define PROPERTY_ENABLED "enabled"
    #define PROPERTY_SELECTED "selected"
    #define PROPERTY_CCCONTROL "ccControl"
    
    void GUICCControlLoader::onHandlePropTypeCheck(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, bool pCheck, GUICCBReader * pCCBReader) {
        if(strcmp(pPropertyName, PROPERTY_ENABLED) == 0) {
            ((CCControl *)pNode)->setEnabled(pCheck);
        } else if(strcmp(pPropertyName, PROPERTY_SELECTED) == 0) {
            ((CCControl *)pNode)->setSelected(pCheck);
        } else {
            GUICCNodeLoader::onHandlePropTypeCheck(pWidget, pNode, pParent, pPropertyName, pCheck, pCCBReader);
        }
    }
    
    void GUICCControlLoader::onHandlePropTypeBlockCCControl(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, BlockCCControlData * pBlockCCControlData, GUICCBReader * pCCBReader) {
        if(strcmp(pPropertyName, PROPERTY_CCCONTROL) == 0) {
            ((CCControl *)pNode)->addTargetWithActionForControlEvents(pBlockCCControlData->mTarget, pBlockCCControlData->mSELCCControlHandler, pBlockCCControlData->mControlEvents);
        } else {
            GUICCNodeLoader::onHandlePropTypeBlockCCControl(pWidget, pNode, pParent, pPropertyName, pBlockCCControlData, pCCBReader);
        }
    }
}
