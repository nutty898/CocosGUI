/*
 * Copyright (c) 2012 Chukong Technologies, Inc.
 *
 * http://www.sweetpome.com
 * http://tools.cocoachina.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to permit
 * persons to whom the Software is furnished to do so, subject to the
 * following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "CocoWidget.h"
#include "DictionaryHelper.h"
#include "UISystem.h"

namespace cs {
    
    CocoWidget::CocoWidget():
    m_bEnabled(true),
    m_bActived(true),
    m_bFocus(false),
    m_nWidgetZOrder(0),
    m_pWidgetParent(NULL),
    m_nCurPressState(-1),
    m_nPrevPressstate(-1),
    m_bBeTouchEnabled(false),
    m_nWidgetTag(-1),
    m_bUpdateAble(false),
    m_pCContainerNode(NULL),
    m_strName("default"),
    m_children(NULL),
    m_UIElements(NULL),
    m_nWidgetType(0),
    m_bVisible(true),
    m_bNeedCheckVisibleDependParent(false),
    m_pPushListener(NULL),
    m_pfnPushSelector(NULL),
    m_pMoveListener(NULL),
    m_pfnMoveSelector(NULL),
    m_pReleaseListener(NULL),
    m_pfnReleaseSelector(NULL),
    m_pCancelListener(NULL),
    m_pfnCancelSelector(NULL),
    m_fContentSizeHeight(0),
    m_fContentSizeWidth(0),
    m_bUseMergedTexture(false),
    m_fAbsoluteScaleX(1.0),
    m_fAbsoluteScaleY(1.0),
    m_bScaleXDirty(true),
    m_bScaleYDirty(true),
    m_bAbsoluteVisible(true),
    m_bVisibleDirty(true),
    m_fAdaptScaleX(1.0f),
    m_fAdaptScaleY(1.0f),
    m_anchorPoint(ccp(0.5f, 0.5f))
    {
        
    }
    
    CocoWidget::~CocoWidget()
    {
        
    }
    
    CocoWidget* CocoWidget::create()
    {
//        return CocoWidget::create(NULL);
        CocoWidget* widget = new CocoWidget();
        if (widget && widget->init()) {
            return widget;
        }
        CC_SAFE_DELETE(widget);
        return NULL;
    }
    
    bool CocoWidget::init()
    {
        this->m_children = cocos2d::CCArray::create();
        this->m_children->retain();
        this->m_UIElements = cocos2d::CCArray::create();
        this->m_UIElements->retain();
        this->initNodes();
        return true;
    }
    
    void CocoWidget::releaseResoures()
    {
        this->setUpdateEnable(false);
        this->removeAllChildrenAndCleanUp(true);
        this->removeAllUIElementsAndCleanUp(true);
        this->m_pCContainerNode->removeFromParentAndCleanUp(true);
        this->m_children->release();
        this->m_UIElements->release();
    }
    
    void CocoWidget::initNodes()
    {
        this->m_pCContainerNode = new CRenderNode();
        this->m_pCContainerNode->initNode(1);
        this->m_pCContainerNode->setZOrder(this->m_nWidgetZOrder);
    }
    
    bool CocoWidget::addChild(CocoWidget *child)
    {
        if (!child) {
            return false;
        }
        if (this->m_children->containsObject(child)) {
            return false;
        }
        child->m_pWidgetParent = this;
        int childrenCount = this->m_children->count();
        if (childrenCount <= 0) {
            this->m_children->addObject(child);
        }else{
            bool seekSucceed = false;
            for (int i=childrenCount-1; i>=0; --i) {
                CocoWidget* widget = (CocoWidget*)(this->m_children->objectAtIndex(i));
                if (child->getWidgetZOrder() >= widget->getWidgetZOrder()) {
                    if (i == childrenCount-1) {
                        this->m_children->addObject(child);
                        seekSucceed = true;
                        break;
                    }else{
                        this->m_children->insertObject(child, i+1);
                        seekSucceed = true;
                        break;
                    }
                }
            }
            if (!seekSucceed) {
                this->m_children->insertObject(child,0);
            }
        }
        this->addChildNode(child);
        this->activeToUIInputManager();
        return true;
    }
    
    void CocoWidget::addChildNode(cs::CocoWidget *child)
    {
        child->m_pCContainerNode->setZOrder(child->getWidgetZOrder());
        this->m_pCContainerNode->addRenderNode(child->m_pCContainerNode);
    }
    
    bool CocoWidget::removeChild(CocoWidget *child, bool cleanup)
    {
        if (!child){
            return false;
        }
        if (cleanup){
            this->removeChildMoveToTrash(child);
        }else{
            this->removeChildReferenceOnly(child);
        }
        return true;
    }
    
    void CocoWidget::removeChildMoveToTrash(cs::CocoWidget *child)
    {
        if (!child)
        {
            return;
        }
        if (this->m_children->containsObject(child))
        {
            this->m_children->removeObject(child);
            child->cleanFromUIInputManager();
            child->setUpdateEnable(false);
            child->releaseResoures();
            child->m_pWidgetParent = NULL;
            delete child;
        }
    }
    
    void CocoWidget::removeChildReferenceOnly(cs::CocoWidget *child)
    {
        if (!child)
        {
            return;
        }
        if (this->m_children->containsObject(child)){
            child->cleanFromUIInputManager();
            this->m_pCContainerNode->removeRenderNodeAndCleanUp(child->m_pCContainerNode,false);
            child->setNeedCheckVisibleDepandParent(false);
            this->m_children->removeObject(child);
            child->m_pWidgetParent = NULL;
        }
    }
    
    void CocoWidget::removeFromParentAndCleanup(bool cleanup)
    {
        if (this->m_pWidgetParent) {
            this->m_pWidgetParent->removeChild(this, cleanup);
        }
    }
    
    void CocoWidget::removeAllChildrenAndCleanUp(bool cleanup)
    {
        int times = this->m_children->count();
        for (int i=0;i<times;i++){
            CocoWidget* child = (CocoWidget*)(m_children->lastObject());
            m_children->removeObject(child);
            child->cleanFromUIInputManager();
            child->releaseResoures();
            delete child;
            child = NULL;
        }
    }
    
    void CocoWidget::removeAllUIElementsAndCleanUp(bool cleanup)
    {
        int times = this->m_UIElements->count();
        for (int i=0;i<times;i++){
            UIElement* element = (UIElement*)(this->m_UIElements->lastObject());
            this->m_UIElements->removeObject(element);
            element->releaseResoures();
            delete element;
            element = NULL;
        }
    }
    
    void CocoWidget::removeUIElement(cs::UIElement *uiElement, bool cleanup)
    {
        if (this->m_UIElements->containsObject(uiElement))
        {
            this->m_UIElements->removeObject(uiElement);
            uiElement->releaseResoures();
            delete uiElement;
            uiElement = NULL;
        }
    }
    
    void CocoWidget::activeToUIInputManager()
    {
        COCOUISYSTEM->getUIInputManager()->uiSceneHasChanged();
    }
    
    void CocoWidget::cleanFromUIInputManager()
    {
        COCOUISYSTEM->getUIInputManager()->removeManageredWidget(this);
        COCOUISYSTEM->getUIInputManager()->uiSceneHasChanged();
    }
    
    void CocoWidget::setWidgetZOrder(int z)
    {
        this->m_nWidgetZOrder = z;
        this->m_pCContainerNode->setZOrder(z);
        if (this->m_pWidgetParent) {
            this->m_pWidgetParent->reorderChild(this);
        }
    }
    
    int CocoWidget::getWidgetZOrder()
    {
        return this->m_nWidgetZOrder;
    }
    
    void CocoWidget::reorderChild(CocoWidget* child)
    {
        this->m_children->removeObject(child);
        int childrenCount = this->m_children->count();
        if (childrenCount <= 0) {
            this->m_children->addObject(child);
        }else{
            bool seekSucceed = false;
            for (int i=childrenCount-1; i>=0; --i) {
                CocoWidget* widget = (CocoWidget*)(this->m_children->objectAtIndex(i));
                if (child->getWidgetZOrder() >= widget->getWidgetZOrder()) {
                    if (i == childrenCount-1) {
                        this->m_children->addObject(child);
                        seekSucceed = true;
                        break;
                    }else{
                        this->m_children->insertObject(child, i+1);
                        seekSucceed = true;
                        break;
                    }
                }
            }
            if (!seekSucceed) {
                this->m_children->insertObject(child,0);
            }
        }
        COCOUISYSTEM->getUIInputManager()->uiSceneHasChanged();
    }
    
    void CocoWidget::setNeedCheckVisibleDepandParent(bool need)
    {
        this->m_bNeedCheckVisibleDependParent = need;
        if (this->m_children){
            for (int i=0;i<this->m_children->count();i++)
            {
                CocoWidget* child = (CocoWidget*)(this->m_children->objectAtIndex(i));
                child->setNeedCheckVisibleDepandParent(need);
            }
        }
    }
    
    void CocoWidget::setVisibleTouch(bool visible)
    {
        this->m_bVisibleTouch = visible;
        if (this->m_children){
            for (int i=0;i<this->m_children->count();i++)
            {
                CocoWidget* child = (CocoWidget*)(this->m_children->objectAtIndex(i));
                child->setVisibleTouch(visible);
            }
        }
    }
    
    void CocoWidget::addUIElement(UIElement* element)
    {
        if (!element) {
            return;
        }
        if (this->m_UIElements->containsObject(element)) {
            return;
        }
        this->m_UIElements->addObject(element);
        this->addElementNode(element);
    }
    
    void CocoWidget::addElementNode(cs::UIElement *element)
    {
        this->m_pCContainerNode->addRenderNode(element->getCRenderNode());
    }
    
    int CocoWidget::checkContainedChild(CocoWidget* child)
    {
        if (!child){
            return -1;
        }
        for (int i=0;i<this->m_children->count();i++){
            if (child == this->m_children->objectAtIndex(i)){
                return i;
            }
        }
        return -1;
    }
    
    void CocoWidget::setBeTouchAble(bool able)
    {
        this->m_bBeTouchEnabled = able;
        COCOUISYSTEM->getUIInputManager()->uiSceneHasChanged();
    }
    
    bool CocoWidget::getBeTouchAble()
    {
        return this->m_bBeTouchEnabled;
    }
    
    void CocoWidget::setUpdateEnable(bool able)
    {
        if (able)
        {
            COCOUISYSTEM->getCurScene()->addUpdateEnableWidget(this);
        }
        else
        {
            COCOUISYSTEM->getCurScene()->removeUpdateEnableWidget(this);
        }
    }
    
    bool CocoWidget::getBeFocus()
    {
        return this->m_bFocus;
    }
    
    void CocoWidget::setBeFocus(bool fucos)
    {
        if (fucos == this->m_bFocus){
            return;
        }
        this->m_bFocus = fucos;
        if (this->m_bFocus){
            this->setPressState(1);
        }else{
            this->setPressState(0);
        }
    }
    
    void CocoWidget::initPressState(int state)
    {
        if (this->m_nCurPressState == state)
        {
            return;
        }
        this->m_nPrevPressstate = this->m_nCurPressState;
        this->m_nCurPressState = state;
    }
    
    void CocoWidget::setPressState(int state)
    {
        if (this->m_nCurPressState == state){
            return;
        }
        this->m_nPrevPressstate = this->m_nCurPressState;
        this->m_nCurPressState = state;
        switch (this->m_nCurPressState){
            case 0:
                this->onPressStateChangedToNormal();
                break;
            case 1:
                this->onPressStateChangedToPressed();
                break;
            case 2:
                this->onPressStateChangedToDisabled();
                break;
        }
    }
    
    void CocoWidget::disable()
    {
        this->m_bActived = false;
        this->setPressState(2);
    }
    
    void CocoWidget::active()
    {
        this->m_bActived = true;
        this->setPressState(0);
    }
    
    bool CocoWidget::getActive()
    {
        return this->m_bActived;
    }
    
    void CocoWidget::onPressStateChangedToNormal()
    {
        
    }
    
    void CocoWidget::onPressStateChangedToPressed()
    {
        
    }
    
    void CocoWidget::onPressStateChangedToDisabled()
    {
        
    }
    
    void CocoWidget::didNotSelectSelf()
    {
        
    }
    
    bool CocoWidget::onTouchPressed(cocos2d::CCPoint &touchPoint)
    {
        this->setBeFocus(true);
        this->m_touchStartPos.x = touchPoint.x;
        this->m_touchStartPos.y = touchPoint.y;
        if (this->m_pWidgetParent){
            this->m_pWidgetParent->checkChildInfo(0,this,touchPoint);
        }
        this->pushDownEvent();
        return true;
    }
    
    bool CocoWidget::onTouchMoved(cocos2d::CCPoint &touchPoint)
    {
        this->setBeFocus(this->pointAtSelfBody(touchPoint));
        if (this->m_pWidgetParent){
            this->m_pWidgetParent->checkChildInfo(1,this,touchPoint);
        }
        return true;
    }
    
    bool CocoWidget::onTouchReleased(cocos2d::CCPoint &touchPoint)
    {
        this->m_touchEndPos.x = touchPoint.x;
        this->m_touchEndPos.y = touchPoint.y;
        bool focus = this->m_bFocus;
        this->setBeFocus(false);
        if (this->m_pWidgetParent){
            this->m_pWidgetParent->checkChildInfo(2,this,touchPoint);
        }
        if (focus){
            this->releaseUpEvent();
        }else{
            this->cancelUpEvent();
        }
        return true;
    }
    
    bool CocoWidget::onTouchCanceled(cocos2d::CCPoint &touchPoint)
    {
        this->setPressState(0);
        return true;
    }
    
    bool CocoWidget::onTouchLongClicked(cocos2d::CCPoint &touchPoint)
    {
        this->longClickEvent();
        return true;
    }
    
    void CocoWidget::pushDownEvent()
    {
        if (m_pPushListener && m_pfnPushSelector) {
            (m_pPushListener->*m_pfnPushSelector)(this);
        }
    }
    
    void CocoWidget::releaseUpEvent()
    {
        if (m_pReleaseListener && m_pfnReleaseSelector) {
            (m_pReleaseListener->*m_pfnReleaseSelector)(this);
        }
    }
    
    void CocoWidget::cancelUpEvent()
    {
        if (m_pCancelListener && m_pfnCancelSelector) {
            (m_pCancelListener->*m_pfnCancelSelector)(this);
        }
    }
    
    void CocoWidget::longClickEvent()
    {
        
    }
    
    void CocoWidget::addPushDownEvent(cocos2d::CCObject*target, SEL_PushEvent selector)
    {
        this->m_pPushListener = target;
        this->m_pfnPushSelector = selector;
    }
    
    void CocoWidget::addMoveEvent(cocos2d::CCObject* target,SEL_MoveEvent selector)
    {
        this->m_pMoveListener = target;
        this->m_pfnMoveSelector = selector;
    }
    
    void CocoWidget::addReleaseEvent(cocos2d::CCObject* target,SEL_ReleaseEvent selector)
    {
        this->m_pReleaseListener = target;
        this->m_pfnReleaseSelector = selector;
    }
    
    void CocoWidget::addCancelEvent(cocos2d::CCObject *target, SEL_CancelEvent selector)
    {
        this->m_pCancelListener = target;
        this->m_pfnCancelSelector = selector;
    }
    
    void CocoWidget::getLocationInWindow()
    {
        this->m_locationInWindow = this->m_pCContainerNode->convertToWorldSpace();
    }
    
    cocos2d::CCRect CocoWidget::getRect()
    {
        CRenderNode* validNode = this->getValidNode();
        float width = 0.0;
        float height = 0.0;
        float anchorPointX = 0.0;
        float anchorPointY = 0.0;
        this->getLocationInWindow();
        width = validNode->getContentSizeWidth()*this->getAbsoluteScaleX();
        height = validNode->getContentSizeHeight()*this->getAbsoluteScaleY();
        anchorPointX = validNode->getAnchorPoint().x;
        anchorPointY = validNode->getAnchorPoint().y;
        switch (this->m_nWidgetType){
            case 0:
                this->m_rect.origin.x = this->m_locationInWindow.x - width * anchorPointX;
                this->m_rect.origin.y = this->m_locationInWindow.y - height * anchorPointY;
                break;
            case 1:
                this->m_rect.origin.x = this->m_locationInWindow.x;
                this->m_rect.origin.y = this->m_locationInWindow.y;
                break;
        }
        this->m_rect.size.width = width;
        this->m_rect.size.height = height;
        
        return this->m_rect;
    }
    
    cocos2d::CCRect CocoWidget::getRelativeRect()
    {
        CRenderNode* validNode = this->getValidNode();
        float width = 0.0;
        float height = 0.0;
        float anchorPointX = 0.0;
        float anchorPointY = 0.0;
        width = validNode->getContentSizeWidth()*this->getScaleX();
        height = validNode->getContentSizeHeight()*this->getScaleY();
        anchorPointX = validNode->getAnchorPoint().x;
        anchorPointY = validNode->getAnchorPoint().y;
        switch (this->m_nWidgetType){
            case 0:
                this->m_relativeRect.origin.x = this->getPosition().x - width * anchorPointX;
                this->m_relativeRect.origin.y = this->getPosition().y - height * anchorPointY;
                break;
            case 1:
                this->m_relativeRect.origin.x = this->getPosition().x;
                this->m_relativeRect.origin.y = this->getPosition().y;
                break;
        }
        this->m_relativeRect.size.width = width;
        this->m_relativeRect.size.height = height;
        return this->m_relativeRect;
    }
    
    CRenderNode* CocoWidget::getValidNode()
    {
        return this->m_pCContainerNode;
    }
    
    CRenderNode* CocoWidget::getContainerNode()
    {
        return this->m_pCContainerNode;
    }
    
    bool CocoWidget::pointAtSelfBody(cocos2d::CCPoint &pt)
    {
        if (!this->getAbsoluteVisible()) {
            return false;
        }
        CRenderNode* validNode = this->getValidNode();
        return validNode->hitTest(pt);
    }
    
    bool CocoWidget::checkVisibleDependParent(cocos2d::CCPoint &pt)
    {
        if (!this->m_bNeedCheckVisibleDependParent){
            return true;
        }
        if (this->m_pWidgetParent){
            bool bRet = false;
            if (this->m_pWidgetParent->pointAtSelfBody(pt)){
                bRet = true;
            }
            if (bRet){
                return this->m_pWidgetParent->checkVisibleDependParent(pt);
            }
            return false;
        }
        return true;
    }
    
    bool CocoWidget::checkBeVisibleInParent()
    {   
        cocos2d::CCRect parentRect = this->m_pWidgetParent->getRect();
        cocos2d::CCRect selfRect = this->getRect();
//        printf("parent rect x %f y %f w %f h %f \n",parentRect.origin.x,parentRect.origin.y,parentRect.size.width,parentRect.size.height);
//        printf("self rect x %f y %f w %f h %f \n",selfRect.origin.x,selfRect.origin.y,selfRect.size.width,selfRect.size.height);
        
//        cocos2d::CCAffineTransform t = this->getContainerNode()->getRenderNode()->nodeToParentTransform();
        
//        printf(" scalex: %f  scaleY: %f\n", t.a, t.d);
        
        bool res = !((selfRect.origin.x+selfRect.size.width) < parentRect.origin.x ||
                    (parentRect.origin.x+parentRect.size.width) <   selfRect.origin.x ||
                    (selfRect.origin.y+selfRect.size.height) < parentRect.origin.y ||
                    parentRect.origin.y+parentRect.size.height <    selfRect.origin.y);
        return res;
    }
    
    void CocoWidget::checkChildInfo(int handleState, cs::CocoWidget *sender, cocos2d::CCPoint &touchPoint)
    {
        if (this->m_pWidgetParent){
            this->m_pWidgetParent->checkChildInfo(handleState,sender,touchPoint);
        }
    }
    
    void CocoWidget::setPosition(const cocos2d::CCPoint &pos)
    {
        this->m_pCContainerNode->setPosition(pos);
    }
    
    void CocoWidget::setAnchorPoint(const cocos2d::CCPoint &pt)
    {
        this->m_anchorPoint = pt;
        this->m_pCContainerNode->setAnchorPoint(pt);
    }
    
    void CocoWidget::updateAnchorPoint()
    {
        this->setAnchorPoint(this->m_anchorPoint);
    }
    
    cocos2d::CCPoint CocoWidget::getPosition()
    {
        return this->m_pCContainerNode->getPosition();
    }
    
    cocos2d::CCPoint CocoWidget::getAnchorPoint()
    {
        return this->m_anchorPoint;
    }
    
    void CocoWidget::setScale(float scale)
    {
        this->m_bScaleXDirty = this->m_bScaleYDirty = true;
        this->updateChildrenScaleXDirty(this->m_bScaleXDirty);
        this->updateChildrenScaleYDirty(this->m_bScaleYDirty);
        this->m_pCContainerNode->setScale(scale);
    }
    
    float CocoWidget::getScale()
    {
        return this->m_pCContainerNode->getScale();
    }
    
    void CocoWidget::setScaleX(float scaleX)
    {
        this->m_bScaleXDirty = true;
        this->updateChildrenScaleXDirty(this->m_bScaleXDirty);
        this->m_pCContainerNode->setScaleX(scaleX);
    }
    
    float CocoWidget::getScaleX()
    {
        return this->m_pCContainerNode->getScaleX();
    }
    
    void CocoWidget::setScaleY(float scaleY)
    {
        this->m_bScaleYDirty = true;
        this->updateChildrenScaleYDirty(this->m_bScaleYDirty);
        this->m_pCContainerNode->setScaleY(scaleY);
    }
    
    float CocoWidget::getScaleY()
    {
        return this->m_pCContainerNode->getScaleY();
    }
    
    void CocoWidget::setRotation(float rotation)
    {
        this->m_pCContainerNode->setRotation(rotation);
    }
    
    float CocoWidget::getRotation()
    {
        return this->m_pCContainerNode->getRotation();
    }
    
    void CocoWidget::setVisible(bool visible)
    {
        this->m_bVisibleDirty = true;
        this->updateChildrenVisibleDirty(this->m_bVisibleDirty);
        this->m_bVisible = visible;
        this->m_pCContainerNode->setVisible(visible);
    }
    
    bool CocoWidget::getVisible()
    {
        return this->m_bVisible;
    }
    
    float CocoWidget::getRelativeLeftPos()
    {
        return this->getRelativeRect().origin.x;
    }
    
    float CocoWidget::getRelativeBottomPos()
    {
        return this->getRelativeRect().origin.y;
    }
    
    float CocoWidget::getRelativeRightPos()
    {
        cocos2d::CCRect rect = this->getRelativeRect();
        return rect.origin.x + rect.size.width;
    }
    
    float CocoWidget::getRelativeTopPos()
    {
        cocos2d::CCRect rect = this->getRelativeRect();
        return rect.origin.y + rect.size.height;
    }
    
    CocoWidget* CocoWidget::getWidgetParent()
    {
        return this->m_pWidgetParent;
    }
    
    CocoWidget* CocoWidget::getChildByName(const char *name)
    {
        for (int i=0; i<this->m_children->count(); i++) {
            CocoWidget* child = (CocoWidget*)(this->m_children->objectAtIndex(i));
            if (strcmp(child->getName().c_str(), name) == 0) {
                return child;
            }
        }
        return NULL;
    }
    
    CocoWidget* CocoWidget::getChildByTag(int tag)
    {
        for (int i=0; i<this->m_children->count(); i++) {
            CocoWidget* child = (CocoWidget*)(this->m_children->objectAtIndex(i));
            if (child->getWidgetTag() == tag) {
                return child;
            }
        }
        return NULL;
    }
    
    cocos2d::CCAction* CocoWidget::runAction(cocos2d::CCAction *action)
    {
        return this->m_pCContainerNode->getRenderNode()->runAction(action);
    }
    
    void CocoWidget::setActionManager(cocos2d::CCActionManager *actionManager)
    {
        this->m_pCContainerNode->getRenderNode()->setActionManager(actionManager);
    }
    
    cocos2d::CCActionManager* CocoWidget::getActionManager()
    {
        return this->m_pCContainerNode->getRenderNode()->getActionManager();
    }
    
    void CocoWidget::stopAllActions()
    {
        this->m_pCContainerNode->getRenderNode()->stopAllActions();
    }
    
    void CocoWidget::stopAction(cocos2d::CCAction *action)
    {
        this->m_pCContainerNode->getRenderNode()->stopAction(action);
    }
    
    void CocoWidget::stopActionByTag(int tag)
    {
        this->m_pCContainerNode->getRenderNode()->stopActionByTag(tag);
    }
    
    cocos2d::CCAction* CocoWidget::getActionByTag(int tag)
    {
        return this->m_pCContainerNode->getRenderNode()->getActionByTag(tag);
    }
    
    float CocoWidget::getAbsoluteScaleX()
    {
        if (this->m_bScaleXDirty) {
            float scaleX = this->getScaleX();
            CocoWidget* parent = this->getWidgetParent();
            while (parent){
                scaleX *= parent->getScaleX();
                parent = parent->getWidgetParent();
            }
            this->m_fAbsoluteScaleX = scaleX;
            this->m_bScaleXDirty = false;
        }
        return this->m_fAbsoluteScaleX;
    }
    
    float CocoWidget::getAbsoluteScaleY()
    {
        if (this->m_bScaleYDirty) {
            float scaleY = this->getScaleY();
            CocoWidget* parent = this->getWidgetParent();
            while (parent){
                scaleY *= parent->getScaleY();
                parent = parent->getWidgetParent();
            }
            this->m_fAbsoluteScaleY = scaleY;
            this->m_bScaleYDirty = false;
        }
        return this->m_fAbsoluteScaleY;
    }
    
    void CocoWidget::updateChildrenScaleXDirty(bool dirty)
    {
        for (int i=0; i<this->getChildren()->count(); i++) {
            CocoWidget* child = (CocoWidget*)(this->getChildren()->objectAtIndex(i));
            child->m_bScaleXDirty = dirty;
            child->updateChildrenScaleXDirty(dirty);
        }
    }
    
    void CocoWidget::updateChildrenScaleYDirty(bool dirty)
    {
        for (int i=0; i<this->getChildren()->count(); i++) {
            CocoWidget* child = (CocoWidget*)(this->getChildren()->objectAtIndex(i));
            child->m_bScaleYDirty = dirty;
            child->updateChildrenScaleYDirty(dirty);
        }
    }
    
    bool CocoWidget::getAbsoluteVisible()
    {
        if (this->m_bVisibleDirty) {
            CocoWidget* parent = this;
            bool visible = this->getVisible();
            while (parent){
                visible &= parent->getVisible();
                if (!visible) {
                    break;
                }
                parent = parent->getWidgetParent();
            }
            this->m_bAbsoluteVisible = visible;
            this->m_bVisibleDirty = false;
        }
        return this->m_bAbsoluteVisible;
    }
    
    void CocoWidget::updateChildrenVisibleDirty(bool dirty)
    {
        for (int i=0; i<this->getChildren()->count(); i++) {
            CocoWidget* child = (CocoWidget*)(this->getChildren()->objectAtIndex(i));
            child->m_bVisibleDirty = dirty;
            child->updateChildrenVisibleDirty(dirty);
        }
    }
    
    void CocoWidget::adaptSize(float xProportion,float yProportion)
    {
        this->m_fAdaptScaleX = xProportion;
        this->m_fAdaptScaleY = yProportion;
        this->setScaleX(m_fAdaptScaleX*this->getScaleX());
        this->setScaleY(m_fAdaptScaleY*this->getScaleY());
    }
}
