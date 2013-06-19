#include "HelloWorldScene.h"
#include "CCEditBox.h"
#include "PageViewScene.h"
#include "CCBTestScene.h"

#include "CClipAbleLayerGradient.h"
using namespace cocos2d;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object    
    HelloWorld *layer = HelloWorld::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }    
    COCOUISYSTEM->resetSystem(this);
    
//    COCOUISYSTEM->replaceUISceneWithFile(this, "UIRES/CocoGUISample.json", 1, true,true,true);
    
    COCOUISYSTEM->getCurScene()->addWidget(COCOUISYSTEM->createWidgetFromFileWithAdapt_json("UIRES/CocoGUISample.json", true, true));
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    float x_proportion = winSize.width / COCOUISYSTEM->getFileDesignWidth();
    float y_proportion = winSize.height / COCOUISYSTEM->getFileDesignHeight();
    
    cs::CocoScrollView* sc = (cs::CocoScrollView*)(COCOUISYSTEM->getWidgetByName("scrollview"));
    sc->setUpdateEnable(true);
    sc->setMoveMode(cs::SCROLLVIEW_MOVE_MODE_ACTION);
    sc->setWidgetTag(10000);
    CCFadeOut* fadeOut = CCFadeOut::create(2);
    CCFadeIn* fadeIn = CCFadeIn::create(1);
    /*
    CCDelayTime* delayTime = CCDelayTime::create(1);
    CCCallFuncO* callFunc0 = CCCallFuncO::create(this, callfuncO_selector(HelloWorld::removeWidget), sc);
     */
    CCSequence* seq = CCSequence::create(fadeOut, fadeIn, /*delayTime, callFunc0,*/ NULL);
    sc->runAction(seq);

    cs::CocoTextButton* bt = (cs::CocoTextButton*)(COCOUISYSTEM->getWidgetByName("backtotopbutton"));
    bt->addReleaseEvent(this, coco_releaseselector(HelloWorld::backToTop));
    
    cs::CocoSlider* sld = (cs::CocoSlider*)(COCOUISYSTEM->getWidgetByName("slider"));
    sld->addPercentChangedEvent(this, coco_percentchangedselector(HelloWorld::sliderPercentChanged));
    
    cs::CocoButton* anib = (cs::CocoButton*)(COCOUISYSTEM->getWidgetByName("animationbutton"));
    anib->addReleaseEvent(this, coco_releaseselector(HelloWorld::playUIAnimation));
    
    cs::CocoTextField* tfd = dynamic_cast<cs::CocoTextField*>(COCOUISYSTEM->getWidgetByName("textfield"));
    tfd->setCharacterLength(4);
//    tfd->setIsPassWord(true);
    tfd->addAttachWithIMEEvent(this, coco_TextFieldAttachWithIMESelector(HelloWorld::textFieldAttachWithIME));
    tfd->addDetachWithIMEEvent(this, coco_TextFieldDetachWithIMESelector(HelloWorld::textFieldDetachWithIME));
    tfd->addInsertTextEvent(this, coco_TextFieldInsertTextSelector(HelloWorld::textFieldInsertText));
    tfd->addDeleteBackwardEvent(this, coco_TextFieldDeleteBackwardSelector(HelloWorld::textFieldDeleteBackward));
    
    // listview
    count = 0;
    array = CCArray::create();
    array->retain();
    for (int i = 0; i < 20; ++i)
    {
        CCString* ccstr = CCString::createWithFormat("object_%d", i);
        array->addObject(ccstr);
    }
    cs::CocoListView* list = dynamic_cast<cs::CocoListView*>(COCOUISYSTEM->getWidgetByName("listview"));    
    list->setUpdateEnable(true);
    list->setMoveMode(cs::SCROLLVIEW_MOVE_MODE_ACTION);    
    for (int i = 0; i < 4; ++i)
    {
        cs::CocoTextButton* tbtn = cs::CocoTextButton::create();
        tbtn->setTextures("UIRES/backtotoppressed.png", "UIRES/backtotopnormal.png", "");
        tbtn->setPosition(ccp(75, 80 - i * (tbtn->getRect().size.height + 5)));
        list->addChild(tbtn);
        COCOUISYSTEM->adjustWidgetProperty(tbtn, x_proportion, y_proportion, true, true);
    }
//    COCOUISYSTEM->adjustWidgetProperty(list, x_proportion, y_proportion, true, true);
    list->resetProperty();
    list->addInitChildEvent(this, coco_InitChildSelector(HelloWorld::initListViewChild));
    list->addUpdateChildEvent(this, coco_UpdateChildSelector(HelloWorld::updateListViewChild));
    list->initChildWithDataLength(array->count());
    /**/
    
    cs::CocoLabel* cleanUI = cs::CocoLabel::create();
    cleanUI->setTouchScaleChangeAble(true);
    cleanUI->setPosition(ccp(200, 40));
    cleanUI->setText("Click to clean UI Scene!");
    cleanUI->setBeTouchAble(true);
    cleanUI->addReleaseEvent(this, coco_releaseselector(HelloWorld::cleanUIWidgets));
    COCOUISYSTEM->getCurScene()->addWidget(cleanUI);
    
    cs::CocoNodeContainer* container = cs::CocoNodeContainer::create();
    extension::CCEditBox* eb = extension::CCEditBox::create(CCSizeMake(150, 50), extension::CCScale9Sprite::create("UIRES/sliderballnormal.png")); // 200 50
    eb->setPlaceHolder("EditBox");
    container->addCCNode(eb);
    container->setPosition(ccp(240, 195)); // 330 150
    COCOUISYSTEM->getCurScene()->addWidget(container);
    COCOUISYSTEM->adjustWidgetProperty(container, x_proportion, y_proportion, true, true);
    
    cs::CocoButton* exit = (cs::CocoButton*)(COCOUISYSTEM->getWidgetByName("exitbutton"));
//    exit->addReleaseEvent(this, coco_releaseselector(HelloWorld::toPageViewScene));
    exit->addReleaseEvent(this, coco_releaseselector(HelloWorld::menuCloseCallback));
//    exit->addCancelEvent(this, coco_cancelselector(HelloWorld::cancelTouch));
    
    
    cs::CocoGradientPanel * gp = cs::CocoGradientPanel::create();
    COCOUISYSTEM->getCurScene()->addWidget(gp);
    gp->setBackGroundColorEnable(true);
    gp->setSize(CCSizeMake(100, 100));
    gp->setStartColor(ccc3(0, 255, 0));
    gp->setEndColor(ccc3(0, 0, 255));
    gp->setOpacity(255);

//    CCLayerGradient* lg = CCLayerGradient::create();
//    this->addChild(lg);
//    lg->setContentSize(CCSizeMake(100, 100));
//    lg->setStartColor(ccc3(0, 255, 0));
//    lg->setEndColor(ccc3(0, 0, 255));
//    lg->setPosition(ccp(100, 0));
    
//    cs::CClipAbleLayerGradient* c = cs::CClipAbleLayerGradient::create();
//    this->addChild(c);
//    c->setContentSize(CCSizeMake(100, 100));
//    c->setStartColor(ccc3(0, 255, 0));
//    c->setEndColor(ccc3(0, 0, 255));
//    c->setPosition(ccp(200, 0));
    
    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->replaceScene(CCBTest::scene());
//    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
#endif
}

void HelloWorld::backToTop(cocos2d::CCObject *pSender)
{
    cs::CocoScrollView* sc = (cs::CocoScrollView*)(COCOUISYSTEM->getWidgetByName("scrollview"));
    sc->scrollToTop();
}

void HelloWorld::sliderPercentChanged(cocos2d::CCObject *pSender)
{
    cs::CocoLoadingBar* lb = (cs::CocoLoadingBar*)(COCOUISYSTEM->getWidgetByName("loadingbar"));
    cs::CocoSlider* sld = (cs::CocoSlider*)pSender;
    int percent = sld->getPercent();
    lb->setPercent(percent);
}

void HelloWorld::playUIAnimation(cocos2d::CCObject *pSender)
{
    cs::CocoWidget* widget = (cs::CocoWidget*)pSender;
    widget->stopAllActions();
    widget->setColor(ccc3(0, 0, 255));
    CCTintTo* tt = CCTintTo::create(0.5f, 0, 255, 0);
    CCTintTo* tt2 = CCTintTo::create(0.5f, 255, 255, 255);
    CCFadeOut* fo = CCFadeOut::create(0.5f);
    CCFadeIn* fi = CCFadeIn::create(0.5f);
    CCSequence* seq = CCSequence::create(CCMoveTo::create(1.0, ccp(300, 300)),CCScaleTo::create(1, 0.5),CCMoveTo::create(1.0, ccp(127, 96)),CCScaleTo::create(1.0, 1.0),CCRotateTo::create(0.5, 720),CCRotateTo::create(0.5, 0),tt,tt2,fo,fi,NULL);
    widget->runAction(seq);
}

void HelloWorld::cancelTouch(cocos2d::CCObject *pSender)
{
    CCLOG("cancel touch");
}

void HelloWorld::cleanUIWidgets(cocos2d::CCObject *pSender)
{
    COCOUISYSTEM->getCurScene()->getRootWidget()->setScaleY(0.5);
    return;
    COCOUISYSTEM->getCurScene()->getRootWidget()->removeAllChildrenAndCleanUp(true);
    
//    cs::CocoControlButton* cb = cs::CocoControlButton::create();
//    cb->setTexture("CloseNormal.png");
//    cb->setTitle("ControlButton");
//    cb->setPosition(ccp(100, 100));
//    cb->setBeTouchAble(true);
//    COCOUISYSTEM->getCurScene()->addWidget(cb);
//    
//    CCLabelTTF* lttf = CCLabelTTF::create();
//    lttf->setString("ControlButton");
//    extension::CCControlButton* cbc = extension::CCControlButton::create(lttf, extension::CCScale9Sprite::create("CloseNormal.png"));
//    this->addChild(cbc);
//    cbc->setPosition(ccp(200, 200));
//    
//    CCLabelBMFont* lbbmf = CCLabelBMFont::create("dasjio", "arial-14.fnt");
//    lbbmf->setPosition(ccp(300, 300));
//    this->addChild(lbbmf);
//
    cs::CocoLabelBMFont* lb = cs::CocoLabelBMFont::create();
    lb->setFntFile("arial-14.fnt");
    lb->setText("abcd");
    lb->setPosition(ccp(100, 100));
    COCOUISYSTEM->getCurScene()->addWidget(lb);
    
    return;
    COCOUISYSTEM->resetSystem(this);
    cs::CocoPanel* p = cs::CocoPanel::create();
    p->setSize(CCSizeMake(100, 100));
    p->setBackGroundColorEnable(true);
    p->setColor(ccc3(0, 255, 0));
    p->setOpacity(255);
    COCOUISYSTEM->getCurScene()->addWidget(p);
    p->setBackGroundColorEnable(false);
}

// listview
void HelloWorld::initListViewChild(cocos2d::CCObject *pSender)
{
    CCString* ccstr = static_cast<CCString*>(array->objectAtIndex(count));
    cs::CocoListView* list = dynamic_cast<cs::CocoListView*>(pSender);
    cs::CocoTextButton* tbtn = dynamic_cast<cs::CocoTextButton*>(list->getUpdateChild());
    tbtn->setText(ccstr->getCString());
    
    count++;
}

void HelloWorld::updateListViewChild(cocos2d::CCObject *pSender)
{
    cs::CocoListView* list = dynamic_cast<cs::CocoListView*>(pSender);
    int index = list->getUpdateDataIndex();
    
    if (index < 0 || index >= list->getDataLength())
    {
        list->setUpdateSuccess(false);
    }
    
    CCString* ccstr = static_cast<CCString*>(array->objectAtIndex(index));
    cs::CocoTextButton* tbtn = dynamic_cast<cs::CocoTextButton*>(list->getUpdateChild());
    tbtn->setText(ccstr->getCString());
    list->setUpdateSuccess(true);
}
//

// textfield
void HelloWorld::textFieldAttachWithIME(cocos2d::CCObject *pSender)
{
    CCLog("textfield AttachWithIME !");
}

void HelloWorld::textFieldDetachWithIME(cocos2d::CCObject *pSender)
{
    CCLog("textfield DetachWithIME !");
}

void HelloWorld::textFieldInsertText(cocos2d::CCObject *pSender)
{
    cs::CocoTextField* tfd = dynamic_cast<cs::CocoTextField*>(pSender);
    CCLog("textfield InsertText, text: %s", tfd->getStringValue());
}

void HelloWorld::textFieldDeleteBackward(cocos2d::CCObject *pSender)
{
    CCLog("textfield DeletBackward !");
}
//

void HelloWorld::removeWidget(CCObject* pSender)
{
    cs::CocoScrollView* sc = dynamic_cast<cs::CocoScrollView*>(pSender);
    sc->removeFromParentAndCleanup(true);
}

void HelloWorld::toPageViewScene(cocos2d::CCObject *pSender)
{
    COCOUISYSTEM->cleanUIScene();
    CCDirector::sharedDirector()->replaceScene(PageView::scene());
}
