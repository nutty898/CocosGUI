//
//  CCBTestScene.h
//  Test
//
//  Created by cai wenzhi on 13-6-17.
//
//

#ifndef __Test__CCBTestScene__
#define __Test__CCBTestScene__

#include "cocos2d.h"
#include "CocosGUI.h"

class CCBTest : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    CREATE_FUNC(CCBTest);
    
    void toHelloWorldScene(CCObject* pSender);
};

#endif /* defined(__Test__CCBTestScene__) */
