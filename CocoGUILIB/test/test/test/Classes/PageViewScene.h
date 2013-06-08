

#ifndef __Test__PageViewScene__
#define __Test__PageViewScene__

#include "cocos2d.h"
#include "CocosGUI.h"

class PageView : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    CREATE_FUNC(PageView);
    
    void toHelloWorldScene(CCObject* pSender);
};

#endif /* defined(__Test__PageViewScene__) */
