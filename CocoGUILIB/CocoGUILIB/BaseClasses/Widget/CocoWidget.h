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

#ifndef __CocoGUI__CocoWidget__
#define __CocoGUI__CocoWidget__

#include "CRenderNode.h"
#include "UIElement.h"
#include "CSContentJsonDictionary.h"


namespace cs{
    typedef void (cocos2d::CCObject::*SEL_PushEvent)(cocos2d::CCObject*); 
    typedef void (cocos2d::CCObject::*SEL_MoveEvent)(cocos2d::CCObject*);
    typedef void (cocos2d::CCObject::*SEL_ReleaseEvent)(cocos2d::CCObject*);
    typedef void (cocos2d::CCObject::*SEL_CancelEvent)(cocos2d::CCObject*);
    #define coco_pushselector(_SELECTOR) (cs::SEL_PushEvent)(&_SELECTOR)
    #define coco_moveselector(_SELECTOR) (cs::SEL_MoveEvent)(&_SELECTOR)
    #define coco_releaseselector(_SELECTOR) (cs::SEL_ReleaseEvent)(&_SELECTOR)
    #define coco_cancelselector(_SELECTOR) (cs::SEL_CancelEvent)(&_SELECTOR)
    class CocoWidget : public cocos2d::CCObject{
    public:
        CocoWidget();
        virtual ~CocoWidget();
        virtual void releaseResoures();
        static CocoWidget* create();
//        static CocoWidget* create(cocos2d::CCDictionary* options);
//        static CocoWidget* createWithJson(sp::SPJsonDictionary* options);
        virtual bool init();
//        virtual bool initWithOptions(cocos2d::CCDictionary* options);
//        virtual bool initWithOptions_json(sp::SPJsonDictionary* options);
        virtual void initNodes();
        virtual bool addChild(CocoWidget* child);
        virtual void addChildNode(CocoWidget* child);
        virtual void addElementNode(UIElement* element);
        virtual void activeToUIInputManager();
        virtual void cleanFromUIInputManager();
        virtual void setWidgetZOrder(int z);
        virtual int getWidgetZOrder();
        virtual void reorderChild(CocoWidget* child);
        virtual void setNeedCheckVisibleDepandParent(bool need);
        virtual void setVisibleTouch(bool visible);
        virtual void addUIElement(UIElement* element);
        virtual bool removeChild(CocoWidget* child,bool cleanup);
        virtual void removeChildMoveToTrash(CocoWidget* child);
        virtual void removeChildReferenceOnly(CocoWidget* child);
        virtual void removeFromParentAndCleanup(bool cleanup);
        virtual void removeAllChildrenAndCleanUp(bool cleanup);
        virtual void removeAllUIElementsAndCleanUp(bool cleanup);
        void removeUIElement(cs::UIElement *uiElement, bool cleanup);
        int checkContainedChild(CocoWidget* child);
        void setBeTouchAble(bool able);
        bool getBeTouchAble();
        void setUpdateEnable(bool able);
        bool getBeFocus();
        void setBeFocus(bool fucos);
        void didNotSelectSelf();
        virtual bool onTouchPressed(cocos2d::CCPoint &touchPoint);
        virtual bool onTouchMoved(cocos2d::CCPoint &touchPoint);
        virtual bool onTouchReleased(cocos2d::CCPoint &touchPoint);
        virtual bool onTouchCanceled(cocos2d::CCPoint &touchPoint);
        virtual bool onTouchLongClicked(cocos2d::CCPoint &touchPoint);
        void initPressState(int state);
        void setPressState(int state);
        virtual void disable();
        virtual void active();
        virtual bool getActive();
        virtual void onPressStateChangedToNormal();
        virtual void onPressStateChangedToPressed();
        virtual void onPressStateChangedToDisabled();
        virtual cocos2d::CCRect getRect();
        virtual cocos2d::CCRect getRelativeRect();
        void getLocationInWindow();
        virtual CRenderNode* getValidNode();
        CRenderNode* getContainerNode();
        virtual bool pointAtSelfBody(cocos2d::CCPoint &pt);
        bool checkVisibleDependParent(cocos2d::CCPoint &pt);
        bool checkBeVisibleInParent();
        virtual void checkChildInfo(int handleState,CocoWidget* sender,cocos2d::CCPoint &touchPoint);
        void setVisible(bool visible);
        bool getVisible();
        virtual float getRelativeLeftPos();
        virtual float getRelativeBottomPos();
        virtual float getRelativeRightPos();
        virtual float getRelativeTopPos();

        CocoWidget* getWidgetParent();
        virtual bool getClipAble(){return false;};
        virtual void update(float dt){};
        CocoWidget* getChildByName(const char* name);
        CocoWidget* getChildByTag(int tag);
        //event
        void pushDownEvent();
        void moveEvent();
        void releaseUpEvent();
        void cancelUpEvent();
        void longClickEvent();
        
        virtual void addPushDownEvent(cocos2d::CCObject* target,SEL_PushEvent selector);
        virtual void addMoveEvent(cocos2d::CCObject* target,SEL_MoveEvent selector);
        virtual void addReleaseEvent(cocos2d::CCObject* target,SEL_ReleaseEvent selector);
        virtual void addCancelEvent(cocos2d::CCObject* target,SEL_CancelEvent selector);
        
        
        //cocos2d property
        void setPosition(const cocos2d::CCPoint &pos);
        virtual void setAnchorPoint(const cocos2d::CCPoint &pt);
        void updateAnchorPoint();
        cocos2d::CCPoint getPosition();
        cocos2d::CCPoint getAnchorPoint();
        virtual void setScale(float scale);
        float getScale();
        virtual void setScaleX(float scaleX);
        float getScaleX();
        virtual void setScaleY(float scaleY);
        float getScaleY();
        void setRotation(float rotation);
        float getRotation();
        virtual void setFlipX(bool flipX){this->m_pCContainerNode->setFlipX(flipX);};
        virtual bool isFlipX(){return this->getValidNode()->isFlipX();};
        virtual void setFlipY(bool flipY){this->m_pCContainerNode->setFlipY(flipY);};
        virtual bool isFlipY(){return this->getValidNode()->isFlipY();};
        virtual void setColor(int r,int g,int b){this->m_pCContainerNode->setColor(r, g, b);};
        virtual cocos2d::ccColor3B getColor(){return this->getValidNode()->getColor();};
        virtual void setOpacity(int opacity){this->m_pCContainerNode->setOpacity(opacity);};
        virtual int getOpacity(){return this->getValidNode()->getOpacity();};
        
        //widget prop
        virtual float getAbsoluteScaleX();
        virtual float getAbsoluteScaleY();
        virtual void updateChildrenScaleXDirty(bool dirty);
        virtual void updateChildrenScaleYDirty(bool dirty);
        virtual bool getAbsoluteVisible();
        virtual void updateChildrenVisibleDirty(bool dirty);
        virtual void updateChildrenOpacityDirty(bool dirty);
        virtual void adaptSize(float xProportion,float yProportion);
        
        
        //cocos action
        virtual void setActionManager(cocos2d::CCActionManager* actionManager);
        /**
         * Gets the CCActionManager object that is used by all actions.
         * @see setActionManager(CCActionManager*)
         * @return A CCActionManager object.
         */
        virtual cocos2d::CCActionManager* getActionManager();
        
        /**
         * Executes an action, and returns the action that is executed.
         *
         * This node becomes the action's target. Refer to CCAction::getTarget()
         * @warning Actions don't retain their target.
         *
         * @return An Action pointer
         */
        cocos2d::CCAction* runAction(cocos2d::CCAction* action);
        
        /**
         * Stops and removes all actions from the running action list .
         */
        void stopAllActions(void);
        
        /**
         * Stops and removes an action from the running action list.
         *
         * @param An action object to be removed.
         */
        void stopAction(cocos2d::CCAction* action);
        
        /**
         * Removes an action from the running action list by its tag.
         *
         * @param A tag that indicates the action to be removed.
         */
        void stopActionByTag(int tag);
        
        /**
         * Gets an action from the running action list by its tag.
         *
         * @see setTag(int), getTag().
         *
         * @return The action object with the given tag.
         */
        cocos2d::CCAction* getActionByTag(int tag);
    protected:
        
        
        bool m_bEnabled;
        bool m_bVisible;
        bool m_bActived;
        bool m_bFocus;
        bool m_bBeTouchEnabled;
        int m_nWidgetZOrder;
        
        cocos2d::CCPoint m_anchorPoint;
        

        
        CocoWidget* m_pWidgetParent;
        
        int m_nCurPressState;
        int m_nPrevPressstate;
        bool m_bUpdateAble;
        CRenderNode* m_pCContainerNode;
        float m_fContentSizeWidth;
        float m_fContentSizeHeight;
        
        
        cocos2d::CCPoint m_locationInWindow;
        cocos2d::CCSize m_contentSize;
        cocos2d::CCRect m_rect;
        cocos2d::CCRect m_relativeRect;
        
        cocos2d::CCArray* m_UIElements;
        bool m_bNeedCheckVisibleDependParent;
        bool m_bVisibleTouch;
        CC_SYNTHESIZE_READONLY(cocos2d::CCArray*, m_children, Children);
        CC_SYNTHESIZE_READONLY(cocos2d::CCPoint,m_touchStartPos,TouchStartPos)
        CC_SYNTHESIZE_READONLY(cocos2d::CCPoint,m_touchMovePos,TouchMovePos)
        CC_SYNTHESIZE_READONLY(cocos2d::CCPoint,m_touchEndPos,TouchEndPos)
        CC_SYNTHESIZE(int, m_nWidgetTag, WidgetTag)
        CC_SYNTHESIZE(std::string, m_strName, Name)
        CC_SYNTHESIZE(bool,m_bUseMergedTexture,UseMergedTexture)
        CC_SYNTHESIZE_READONLY(int, m_nWidgetType, WidgetType)
        cocos2d::CCObject*       m_pPushListener;
        SEL_PushEvent    m_pfnPushSelector;
        cocos2d::CCObject*       m_pMoveListener;
        SEL_MoveEvent    m_pfnMoveSelector;
        cocos2d::CCObject*       m_pReleaseListener;
        SEL_ReleaseEvent    m_pfnReleaseSelector;
        cocos2d::CCObject*       m_pCancelListener;
        SEL_ReleaseEvent    m_pfnCancelSelector;
        float m_fAbsoluteScaleX;
        float m_fAbsoluteScaleY;
        bool m_bAbsoluteVisible;
        bool m_bScaleXDirty;
        bool m_bScaleYDirty;
        bool m_bVisibleDirty;
        bool m_bOpacityDirty;
        float m_fAdaptScaleX;
        float m_fAdaptScaleY;
    };
    
    
}

#endif /* defined(__CocoGUI__CocoWidget__) */
