//
//  CCBTestScene.cpp
//  Test
//
//  Created by cai wenzhi on 13-6-17.
//
//

#include "CCBTestScene.h"
#include "HelloWorldScene.h"



CCScene* CCBTest::scene()
{
    CCScene* scene = CCScene::create();
    CCBTest* layer = CCBTest::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool CCBTest::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    using namespace cocos2d;
    using namespace extension;
    using namespace cs;
    
    COCOUISYSTEM->resetSystem(this);
    
    /* register custom classType */
    COCOUISYSTEM->registerClassType(CCString::create("CCLayer"), "HelloCocosBuilderLayer");
    
    //    /* Create an autorelease GUICCNodeLoaderLibrary. */
    GUICCNodeLoaderLibrary* ccNodeLoaderLibrary = GUICCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    CocoWidget* widget = COCOUISYSTEM->createWidgetFromCCBFileWithAdapt("ccb/HelloCocosBuilder.ccbi", ccNodeLoaderLibrary, true, true);
    COCOUISYSTEM->getCurScene()->addWidget(widget);
    
    
    CocoButton* exit = CocoButton::create();
    exit->setPosition(ccp(430, 30));
    exit->setTextures("UIRES/CloseNormal.png", "UIRES/CloseSelected.png", "");
    exit->setBeTouchAble(true);
    exit->addReleaseEvent(this, coco_releaseselector(CCBTest::toHelloWorldScene));
    COCOUISYSTEM->getCurScene()->addWidget(exit);
//
    return true;
}

void CCBTest::toHelloWorldScene(cocos2d::CCObject *pSender)
{    
    CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
}
