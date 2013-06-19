#include "GUICCLayerGradientLoader.h"
#include "CocoGradientPanel.h"


#define PROPERTY_STARTCOLOR "startColor"
#define PROPERTY_ENDCOLOR "endColor"
#define PROPERTY_STARTOPACITY "startOpacity"
#define PROPERTY_ENDOPACITY "endOpacity"
#define PROPERTY_VECTOR "vector"
#define PROPERTY_BLENDFUNC "blendFunc"

namespace cs
{
    void GUICCLayerGradientLoader::onHandlePropTypeColor3(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccColor3B pCCColor3B, GUICCBReader * pCCBReader) {
        if(strcmp(pPropertyName, PROPERTY_STARTCOLOR) == 0) {
            /**/
//            ((CCLayerGradient *)pNode)->setStartColor(pCCColor3B);
            dynamic_cast<CocoGradientPanel*>(pWidget)->setStartColor(pCCColor3B);
            dynamic_cast<CocoGradientPanel*>(pWidget)->setStartOpacity(255);
//            dynamic_cast<CocoContainerWidget*>(pWidget)->setOpacity(255);
            /**/
        } else if(strcmp(pPropertyName, PROPERTY_ENDCOLOR) == 0) {
            /**/
//            ((CCLayerGradient *)pNode)->setEndColor(pCCColor3B);
            dynamic_cast<CocoGradientPanel*>(pWidget)->setEndColor(pCCColor3B);
            dynamic_cast<CocoGradientPanel*>(pWidget)->setEndOpacity(255);
//            dynamic_cast<CocoContainerWidget*>(pWidget)->setOpacity(255);
            /**/
        } else {
            GUICCLayerLoader::onHandlePropTypeColor3(pWidget, pNode, pParent, pPropertyName, pCCColor3B, pCCBReader);
        }
    }
    
    void GUICCLayerGradientLoader::onHandlePropTypeByte(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, unsigned char pByte, GUICCBReader * pCCBReader) {
        if(strcmp(pPropertyName, PROPERTY_STARTOPACITY) == 0) {
            /**/
//            ((CCLayerGradient *)pNode)->setStartOpacity(pByte);
//            dynamic_cast<CocoContainerWidget*>(pWidget)->setStartOpacity(pByte);
            dynamic_cast<CocoContainerWidget*>(pWidget)->setOpacity(pByte);
            /**/
        } else if(strcmp(pPropertyName, PROPERTY_ENDOPACITY) == 0) {
            /**/
//            ((CCLayerGradient *)pNode)->setEndOpacity(pByte);
//            dynamic_cast<CocoContainerWidget*>(pWidget)->setEndOpacity(pByte);
            dynamic_cast<CocoContainerWidget*>(pWidget)->setOpacity(pByte);
            /**/
        } else {
            GUICCLayerLoader::onHandlePropTypeByte(pWidget, pNode, pParent, pPropertyName, pByte, pCCBReader);
        }
    }
    
    void GUICCLayerGradientLoader::onHandlePropTypeBlendFunc(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccBlendFunc pCCBlendFunc, GUICCBReader * pCCBReader) {
        if(strcmp(pPropertyName, PROPERTY_BLENDFUNC) == 0) {
            /**/
//            ((CCLayerGradient *)pNode)->setBlendFunc(pCCBlendFunc);
            pWidget->setBlendFunc(pCCBlendFunc);
            /**/
        } else {
            GUICCLayerLoader::onHandlePropTypeBlendFunc(pWidget, pNode, pParent, pPropertyName, pCCBlendFunc, pCCBReader);
        }
    }
    
    
    void GUICCLayerGradientLoader::onHandlePropTypePoint(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCPoint pPoint, GUICCBReader * pCCBReader) {
        if(strcmp(pPropertyName, PROPERTY_VECTOR) == 0) {
            ((CCLayerGradient *)pNode)->setVector(pPoint);
            
            // TODO Not passed along the ccbi file.
            // ((CCLayerGradient *)pNode)->setCompressedInterpolation(true);
        } else {
            GUICCLayerLoader::onHandlePropTypePoint(pWidget, pNode, pParent, pPropertyName, pPoint, pCCBReader);
        }
    }
}
