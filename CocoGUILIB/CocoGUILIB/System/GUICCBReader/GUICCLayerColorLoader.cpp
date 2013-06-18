#include "GUICCLayerColorLoader.h"
#include "CocoWidget.h"


    
namespace cs
{
    #define PROPERTY_COLOR "color"
    #define PROPERTY_OPACITY "opacity"
    #define PROPERTY_BLENDFUNC "blendFunc"
    
    void GUICCLayerColorLoader::onHandlePropTypeColor3(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccColor3B pCCColor3B, GUICCBReader * pCCBReader) {
        if(strcmp(pPropertyName, PROPERTY_COLOR) == 0) {
            /**/
//            ((CCLayerColor *)pNode)->setColor(pCCColor3B);
            pWidget->setColor(pCCColor3B);
            /**/
        } else {
            GUICCLayerLoader::onHandlePropTypeColor3(pWidget, pNode, pParent, pPropertyName, pCCColor3B, pCCBReader);
        }
    }
    
    void GUICCLayerColorLoader::onHandlePropTypeByte(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, unsigned char pByte, GUICCBReader * pCCBReader) {
        if(strcmp(pPropertyName, PROPERTY_OPACITY) == 0) {
            /**/
//            ((CCLayerColor *)pNode)->setOpacity(pByte);
            pWidget->setOpacity(pByte);
            /**/
        } else {
            GUICCLayerLoader::onHandlePropTypeByte(pWidget, pNode, pParent, pPropertyName, pByte, pCCBReader);
        }
    }
    
    void GUICCLayerColorLoader::onHandlePropTypeBlendFunc(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccBlendFunc pCCBlendFunc, GUICCBReader * pCCBReader) {
        if(strcmp(pPropertyName, PROPERTY_BLENDFUNC) == 0) {
            /**/
//            ((CCLayerColor *)pNode)->setBlendFunc(pCCBlendFunc);
            pWidget->setBlendFunc(pCCBlendFunc);
            /**/
        } else {
            GUICCLayerLoader::onHandlePropTypeBlendFunc(pWidget, pNode, pParent, pPropertyName, pCCBlendFunc, pCCBReader);
        }
    }
}
