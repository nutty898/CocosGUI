#include "GUICCBFileLoader.h"
#include "CocoWidget.h"



namespace cs
{
    #define PROPERTY_CCBFILE "ccbFile"
    
    void GUICCBFileLoader::onHandlePropTypeCCBFile(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCNode * pCCBFileNode, GUICCBReader * pCCBReader) {
        if(strcmp(pPropertyName, PROPERTY_CCBFILE) == 0) {
            ((CCBFile*)pNode)->setCCBFileNode(pCCBFileNode);
        } else {
            GUICCNodeLoader::onHandlePropTypeCCBFile(pWidget, pNode, pParent, pPropertyName, pCCBFileNode, pCCBReader);
        }
    }
    
    void GUICCBFileLoader::onHandlePropTypeCCBFile(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char* pPropertyName, CCNode * pCCBFileNode, CocoWidget* pCCBFileWidget,  GUICCBReader * pCCBReader) {
        if(strcmp(pPropertyName, PROPERTY_CCBFILE) == 0) {
            ((CCBFile*)pNode)->setCCBFileNode(pCCBFileWidget->getContainerNode());
        } else {
            GUICCNodeLoader::onHandlePropTypeCCBFile(pWidget, pNode, pParent, pPropertyName, pCCBFileNode, pCCBReader);
        }
    }
}