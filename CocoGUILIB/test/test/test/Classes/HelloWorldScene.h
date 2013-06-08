#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "CocosGUI.h"

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HelloWorld);
    
    void backToTop(CCObject* pSender);
    
    void sliderPercentChanged(CCObject* pSender);
    
    void playUIAnimation(CCObject* pSender);
    
    void cancelTouch(CCObject* pSender);
  
    void cleanUIWidgets(CCObject* pSender);
    
    void initListViewChild(CCObject* pSender);
    void updateListViewChild(CCObject* pSender);
    
    void textFieldAttachWithIME(CCObject* pSender);
    void textFieldDetachWithIME(CCObject* pSender);
    void textFieldInsertText(CCObject* pSender);
    void textFieldDeleteBackward(CCObject* pSender);
    
    void removeWidget(CCObject* pSender);
    
    void toPageViewScene(CCObject* pSender);
    
protected:
    int count;
    cocos2d::CCArray* array;
};

#endif // __HELLOWORLD_SCENE_H__
