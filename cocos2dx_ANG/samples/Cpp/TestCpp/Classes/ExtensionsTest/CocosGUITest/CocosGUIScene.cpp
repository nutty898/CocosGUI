#include "CocosGUIScene.h"
#include "CocosGUI.h"

CocosGUITestScene::CocosGUITestScene(bool bPortrait)
{
	TestScene::init();
    
	CCSprite *bg = CCSprite::create("armature/bg.jpg");
	bg->setPosition(VisibleRect::center());
    
	float scaleX = VisibleRect::getVisibleRect().size.width / bg->getContentSize().width;
	float scaleY = VisibleRect::getVisibleRect().size.height / bg->getContentSize().height;
    
	bg->setScaleX(scaleX);
	bg->setScaleY(scaleY);
    
	addChild(bg);
}
void CocosGUITestScene::runThisTest()
{
    
	CCDirector::sharedDirector()->replaceScene(this);
    
    COCOUISYSTEM->replaceUISceneWithFile(this, "cocosgui/CocoGUISample.json", 1, false, false, false);
    CocoScrollView* sc = (CocoScrollView*)(COCOUISYSTEM->getWidgetByName("scrollview"));
    sc->setUpdateEnable(true);
    sc->setMoveMode(SCROLLVIEW_MOVE_MODE_NORMAL);
    
    CocoImageView* image = dynamic_cast<CocoImageView*>(COCOUISYSTEM->getWidgetByName("imageview"));
    image->setBeTouchAble(true);
    image->addReleaseEvent(this, coco_releaseselector(CocosGUITestScene::MainMenuCallback));
    
    
}
void CocosGUITestScene::MainMenuCallback(CCObject* pSender)
{
    CocoImageView* image = dynamic_cast<CocoImageView*>(COCOUISYSTEM->getWidgetByName("imageview"));
    static bool is = true;
    
    if (is) {
        image->setScale9Enable(true);
        image->setScale9Size(100, 100);
    }else{
        image->setScale9Enable(false);
    }
    is = !is;
//	TestScene::MainMenuCallback(pSender);
//    
//	removeAllChildren();
//	CCArmatureDataManager::sharedArmatureDataManager()->purgeArmatureSystem();
}