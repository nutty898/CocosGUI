#ifndef _HELLOCOCOSBUILDERLAYERLOADER_H_
#define _HELLOCOCOSBUILDERLAYERLOADER_H_

#include "HelloCocosBuilderLayer.h"
#include "GUICCLayerLoader.h"
#include "GUICCBReader.h"


/* gui mark */
/* Forward declaration. */
class GUICCBReader;

class HelloCocosBuilderLayerLoader : public cs::GUICCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(HelloCocosBuilderLayerLoader, loader);
    
protected:
    GUI_CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(HelloCocosBuilderLayer);
};
// before
/////* Forward declaration. */
//class CCBReader;
//
//class HelloCocosBuilderLayerLoader : public cocos2d::extension::CCLayerLoader {
//    public:
//        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(HelloCocosBuilderLayerLoader, loader);
//
//    protected:
//        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(HelloCocosBuilderLayer);
//};
/**/



#endif
