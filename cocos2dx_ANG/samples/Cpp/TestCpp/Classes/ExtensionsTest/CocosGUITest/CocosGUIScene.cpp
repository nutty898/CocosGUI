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
    sc->setMoveMode(SCROLLVIEW_MOVE_MODE_ACTION);
    
}
void CocosGUITestScene::MainMenuCallback(CCObject* pSender)
{
	TestScene::MainMenuCallback(pSender);
    
	removeAllChildren();
	CCArmatureDataManager::sharedArmatureDataManager()->purgeArmatureSystem();
}