#include "GUICCLabelBMFontLoader.h"
#include "CocoLabelBMFont.h"



namespace cs
{
    #define PROPERTY_COLOR "color"
    #define PROPERTY_OPACITY "opacity"
    #define PROPERTY_BLENDFUNC "blendFunc"
    #define PROPERTY_FNTFILE "fntFile"
    #define PROPERTY_STRING "string"
    
    void GUICCLabelBMFontLoader::onHandlePropTypeColor3(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccColor3B pCCColor3B, GUICCBReader * pCCBReader) {
        if(strcmp(pPropertyName, PROPERTY_COLOR) == 0) {
            /**/
//            ((CCLabelBMFont *)pNode)->setColor(pCCColor3B);
            dynamic_cast<CocoLabelBMFont*>(pWidget)->setColor(pCCColor3B);
            /**/
        } else {
            GUICCNodeLoader::onHandlePropTypeColor3(pWidget, pNode, pParent, pPropertyName, pCCColor3B, pCCBReader);
        }
    }
    
    void GUICCLabelBMFontLoader::onHandlePropTypeByte(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, unsigned char pByte, GUICCBReader * pCCBReader) {
        if(strcmp(pPropertyName, PROPERTY_OPACITY) == 0) {
            /**/
//            ((CCLabelBMFont *)pNode)->setOpacity(pByte);
            dynamic_cast<CocoLabelBMFont*>(pWidget)->setOpacity(pByte);
            /**/
        } else {
            GUICCNodeLoader::onHandlePropTypeByte(pWidget, pNode, pParent, pPropertyName, pByte, pCCBReader);
        }
    }
    
    void GUICCLabelBMFontLoader::onHandlePropTypeBlendFunc(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccBlendFunc pCCBlendFunc, GUICCBReader * pCCBReader) {
        if(strcmp(pPropertyName, PROPERTY_BLENDFUNC) == 0) {
            /**/
//            ((CCLabelBMFont *)pNode)->setBlendFunc(pCCBlendFunc);
            dynamic_cast<CocoLabelBMFont*>(pWidget)->setBlendFunc(pCCBlendFunc);
            /**/
        } else {
            GUICCNodeLoader::onHandlePropTypeBlendFunc(pWidget, pNode, pParent, pPropertyName, pCCBlendFunc, pCCBReader);
        }
    }
    
    void GUICCLabelBMFontLoader::onHandlePropTypeFntFile(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char* pFntFile, GUICCBReader * pCCBReader) {
        if(strcmp(pPropertyName, PROPERTY_FNTFILE) == 0) {
            /**/
//            ((CCLabelBMFont *)pNode)->setFntFile(pFntFile);
            dynamic_cast<CocoLabelBMFont*>(pWidget)->setFntFile(pFntFile);
            /**/
        } else {
            GUICCNodeLoader::onHandlePropTypeFntFile(pWidget, pNode, pParent, pPropertyName, pFntFile, pCCBReader);
        }
    }
    
    void GUICCLabelBMFontLoader::onHandlePropTypeText(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char* pText, GUICCBReader * pCCBReader) {
        if(strcmp(pPropertyName, PROPERTY_STRING) == 0) {
            /**/
//            ((CCLabelBMFont *)pNode)->setString(pText);
            dynamic_cast<CocoLabelBMFont*>(pWidget)->setText(pText);
            /**/
        } else {
            GUICCNodeLoader::onHandlePropTypeText(pWidget, pNode, pParent, pPropertyName, pText, pCCBReader);
        }
    }
}
