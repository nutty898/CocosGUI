//
//  PageViewScene.cpp
//  Test
//
//  Created by pipu on 13-6-7.
//
//

#include "PageViewScene.h"
#include "HelloWorldScene.h"

using namespace cocos2d;

CCScene* PageView::scene()
{
    CCScene* scene = CCScene::create();
    PageView* layer = PageView::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool PageView::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    scheduleUpdate();
    
    using namespace cs;
    
    COCOUISYSTEM->resetSystem(this);
    
    COCOUISYSTEM->replaceUISceneWithFile(this, "UIRES/CocoGUI_PageView_Sample.json", 1, true, true, true);
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    float x_proportion = winSize.width / COCOUISYSTEM->getFileDesignWidth();
    float y_proportion = winSize.height / COCOUISYSTEM->getFileDesignHeight();
    
    CocoPanel* panel = dynamic_cast<CocoPanel*>(COCOUISYSTEM->getCurScene()->getRootWidget()->getChildByName("panel"));
    CocoPageView* pv = dynamic_cast<CocoPageView*>(panel->getChildByName("pageview"));    
    
//    CocoPageView* pv = CocoPageView::create();
//    pv->setColorAndSize(0, 0, 0, 255, 240, 160);
//    pv->setPosition(ccp(140, 80));
//    COCOUISYSTEM->getCurScene()->addWidget(pv);
    
    pv->setDirection(PAGEVIEW_DIR_HORIZONTAL);
//    pv->setPagesWidthOffset(40);
    
    float pv_w = pv->getRect().size.width;
    float pv_h = pv->getRect().size.height;
    for (int i = 0; i < 3; ++i)
    {
        CocoPanel* sub_panel = CocoPanel::create();
        sub_panel->setColorAndSize(0, 0, 0, 255, 180, 120);
        sub_panel->setBackGroundImageScale9Enable(true);
        sub_panel->setBackGroundImageScale9("UIRES/scrollviewbg.png", CCRectZero);
        float sub_panel_w = sub_panel->getRect().size.width;
        float sub_panel_h = sub_panel->getRect().size.height;
        float start_x = (pv_w - sub_panel_w) / 2;
        float start_y = (pv_h - sub_panel_h) / 2;
        float x = 0, y = 0;
        x = start_x + i * (pv_w - pv->getPagesWidthOffset());
        y = start_y;
        sub_panel->setPosition(ccp(x, y));
        pv->addChild(sub_panel);
        
        CocoLabel* label = CocoLabel::create();
        CCString* str = CCString::createWithFormat("page_%d", i);
        label->setText(str->getCString());
        label->setPosition(ccp(sub_panel->getRect().size.width / 2, sub_panel->getValidNode()->getContentSizeHeight() / 2));
        sub_panel->addChild(label);
        
        COCOUISYSTEM->adjustWidgetProperty(sub_panel, x_proportion, y_proportion, true, true);
    }
    
    cs::CocoButton* exit = (cs::CocoButton*)(COCOUISYSTEM->getWidgetByName("exitbutton"));
    exit->addReleaseEvent(this, coco_releaseselector(PageView::toHelloWorldScene));
    
    return true;
}

void PageView::toHelloWorldScene(cocos2d::CCObject *pSender)
{
    COCOUISYSTEM->cleanUIScene();
    CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
}
