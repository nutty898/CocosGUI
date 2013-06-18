#include "GUICCLayerLoader.h"
#include "CocoContainerWidget.h"



/* pipu modify */
#define PROPERTY_TOUCH_ENABLED "touchEnabled"
#define PROPERTY_ACCELEROMETER_ENABLED "accelerometerEnabled"
#define PROPERTY_MOUSE_ENABLED "mouseEnabled"
#define PROPERTY_KEYBOARD_ENABLED "keyboardEnabled"
// before
/*
#define PROPERTY_TOUCH_ENABLED "isTouchEnabled"
#define PROPERTY_ACCELEROMETER_ENABLED "isAccelerometerEnabled"
#define PROPERTY_MOUSE_ENABLED "isMouseEnabled"
#define PROPERTY_KEYBOARD_ENABLED "isKeyboardEnabled"
 */
/**/
#define PROPERTY_CONTENTSIZE "contentSize"

namespace cs
{
    void GUICCLayerLoader::onHandlePropTypeCheck(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, bool pCheck, GUICCBReader * pCCBReader) {
        if(strcmp(pPropertyName, PROPERTY_TOUCH_ENABLED) == 0) {
            ((CCLayer *)pNode)->setTouchEnabled(pCheck);
            pWidget->setBeTouchAble(pCheck);
        } else if(strcmp(pPropertyName, PROPERTY_ACCELEROMETER_ENABLED) == 0) {
            ((CCLayer *)pNode)->setAccelerometerEnabled(pCheck);
        } else if(strcmp(pPropertyName, PROPERTY_MOUSE_ENABLED) == 0) {
            // TODO XXX
            CCLOG("The property '%s' is not supported!", PROPERTY_MOUSE_ENABLED);
        } else if(strcmp(pPropertyName, PROPERTY_KEYBOARD_ENABLED) == 0) {
            // TODO XXX
            CCLOG("The property '%s' is not supported!", PROPERTY_KEYBOARD_ENABLED);
            // This comes closest: ((CCLayer *)pNode)->setKeypadEnabled(pCheck);
        } else {
            GUICCNodeLoader::onHandlePropTypeCheck(pWidget, pNode, pParent, pPropertyName, pCheck, pCCBReader);
        }
    }
    
    void GUICCLayerLoader::onHandlePropTypeSize(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCSize pSize, GUICCBReader * pCCBReader) {
        if(strcmp(pPropertyName, PROPERTY_CONTENTSIZE) == 0) {
            dynamic_cast<CocoContainerWidget*>(pWidget)->setSize(pSize.width, pSize.height);
        } else {
            GUICCNodeLoader::onHandlePropTypeSize(pWidget, pNode, pParent, pPropertyName, pSize, pCCBReader);
        }
    }
}
