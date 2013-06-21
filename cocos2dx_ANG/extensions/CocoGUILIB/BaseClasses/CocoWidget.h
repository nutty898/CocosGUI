/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __COCOWIDGET_H__
#define __COCOWIDGET_H__

#include "cocos2d.h"
#include "ExtensionMacros.h"
#include "../CGraphics/GUINodeRGBA.h"





//#define DYNAMIC_CAST_CCNODE dynamic_cast<cocos2d::CCNode*>(this->m_pCCRenderNode)
//
//
//
//#define DYNAMIC_CAST_CCLAYER dynamic_cast<cocos2d::CCLayer*>(this->m_pCCRenderNode)
//
////#define DYNAMIC_CAST_CCSPRITE dynamic_cast<cocos2d::CCSprite*>(this->m_pCCRenderNode)
//
//#define DYNAMIC_CAST_CCLAYERCOLOR dynamic_cast<CCLayerColor*>(this->m_pCCRenderNode)
//
////#define DYNAMIC_CAST_CCLABELTTF dynamic_cast<cocos2d::CCLabelTTF*>(this->m_pCCRenderNode)
//
//#define DYNAMIC_CAST_CTEXTFIELD dynamic_cast<cocos2d::CTextfield*>(this->m_pCCRenderNode)
//
//#define DYNAMIC_CAST_CLIPSPRITE dynamic_cast<cocos2d::CClipSprite*>(this->m_pCCRenderNode)
//
//#define DYNAMIC_CAST_CLIPLAYERCOLOR dynamic_cast<CClipAbleLayerColor*>(this->m_pCCRenderNode)
//
//#define DYNAMIC_CAST_CLIPLAYERGRADIENT dynamic_cast<CClipAbleLayerGradient*>(this->m_pCCRenderNode)
//
////#define DYNAMIC_CAST_CLABELATLAS dynamic_cast<CLabelAtlas*>(this->m_pCCRenderNode)
//
////#define DYNAMIC_CAST_SCALE9SPRITE dynamic_cast<cocos2d::extension::CCScale9Sprite*>(this->m_pCCRenderNode)
//
//#define DYNAMIC_CAST_CCLABELBMFONT dynamic_cast<cocos2d::CCLabelBMFont*>(this->m_pCCRenderNode)



NS_CC_EXT_BEGIN

typedef enum
{
    WidgetEventTouchDown           = 1 << 0,
    WidgetEventTouchDragInside     = 1 << 1,
    WidgetEventTouchDragOutside    = 1 << 2,
    WidgetEventTouchDragEnter      = 1 << 3,
    WidgetEventTouchDragExit       = 1 << 4,
    WidgetEventTouchUpInside       = 1 << 5,
    WidgetEventTouchUpOutside      = 1 << 6,
    WidgetEventTouchCancel         = 1 << 7,
    WidgetEventDrop                = 1 << 8
}WidgetEvent;

typedef enum
{
    WidgetStateNone = -1,
    WidgetStateNormal,
    WidgetStateSelected,
    WidgetStateDisabled
}WidgetState;

typedef enum
{
    WidgetTypeWidget,
    WidgetTypeContainer
}WidgetType;

typedef void (cocos2d::CCObject::*SEL_PushEvent)(cocos2d::CCObject*);
typedef void (cocos2d::CCObject::*SEL_MoveEvent)(cocos2d::CCObject*);
typedef void (cocos2d::CCObject::*SEL_ReleaseEvent)(cocos2d::CCObject*);
typedef void (cocos2d::CCObject::*SEL_CancelEvent)(cocos2d::CCObject*);
#define coco_pushselector(_SELECTOR) (cocos2d::extension::SEL_PushEvent)(&_SELECTOR)
#define coco_moveselector(_SELECTOR) (cocos2d::extension::SEL_MoveEvent)(&_SELECTOR)
#define coco_releaseselector(_SELECTOR) (cocos2d::extension::SEL_ReleaseEvent)(&_SELECTOR)
#define coco_cancelselector(_SELECTOR) (cocos2d::extension::SEL_CancelEvent)(&_SELECTOR)

class CocoWidget : public cocos2d::CCObject
{
public:
    CocoWidget();
    virtual ~CocoWidget();
    virtual void releaseResoures();
    static CocoWidget* create();
    virtual bool init();
    virtual void initNodes();
    virtual bool addChild(CocoWidget* child);
    virtual void addChildNode(CocoWidget* child);
    virtual void activeToUIInputManager();
    virtual void cleanFromUIInputManager();
    virtual void setWidgetZOrder(int z);
    virtual int getWidgetZOrder();
    virtual void reorderChild(CocoWidget* child);
    virtual void setNeedCheckVisibleDepandParent(bool need);
    virtual void setVisibleTouch(bool visible);
    virtual bool removeChild(CocoWidget* child,bool cleanup);
    virtual void removeChildMoveToTrash(CocoWidget* child);
    virtual void removeChildReferenceOnly(CocoWidget* child);
    virtual void removeFromParentAndCleanup(bool cleanup);
    virtual void removeAllChildrenAndCleanUp(bool cleanup);
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
    void initPressState(WidgetState state);
    void setPressState(WidgetState state);
    virtual void disable();
    virtual void active();
    virtual bool getActive();
    virtual void onPressStateChangedToNormal();
    virtual void onPressStateChangedToPressed();
    virtual void onPressStateChangedToDisabled();
    virtual cocos2d::CCRect getRect();
    virtual cocos2d::CCRect getRelativeRect();
    void getLocationInWindow();
    virtual cocos2d::CCNode* getValidNode();
    cocos2d::CCNode* getContainerNode();
    virtual bool pointAtSelfBody(cocos2d::CCPoint &pt);
    virtual bool hitTest(cocos2d::CCNode* node, cocos2d::CCPoint &pt);
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
    virtual void onScaleDirtyChanged();
    virtual void onScaleXDirtyChanged();
    virtual void onScaleYDirtyChanged();
    void setRotation(float rotation);
    float getRotation();
    void setRotationX(float rotationX);
    float getRotationX();
    void setRotationY(float rotationY);
    float getRotationY();
    virtual void setSkewX(float skewX);
    virtual float getSkewX();
    virtual void setSkewY(float skewY);
    virtual float getSkewY();
    virtual void setFlipX(bool flipX){};
    virtual bool isFlipX(){return false;};
    virtual void setFlipY(bool flipY){};
    virtual bool isFlipY(){return false;};
    virtual void setColor(const cocos2d::ccColor3B &color);
    virtual const cocos2d::ccColor3B& getColor();
    virtual void setOpacity(int opacity);
    virtual int getOpacity();
    void setBlendFunc(cocos2d::ccBlendFunc blendFunc);
    void ignoreAnchorPointForPosition(bool ignore);
    
    //widget prop
    virtual float getAbsoluteScaleX();
    virtual float getAbsoluteScaleY();
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
    
    WidgetState m_nCurPressState;
    WidgetState m_nPrevPressstate;
    bool m_bUpdateAble;
    cocos2d::CCNode* m_pCCRenderNode;
    float m_fContentSizeWidth;
    float m_fContentSizeHeight;
    
    
    cocos2d::CCPoint m_locationInWindow;
    cocos2d::CCSize m_contentSize;
    cocos2d::CCRect m_rect;
    cocos2d::CCRect m_relativeRect;
    
    bool m_bNeedCheckVisibleDependParent;
    bool m_bVisibleTouch;
    CC_SYNTHESIZE_READONLY(cocos2d::CCArray*, m_children, Children);
    CC_SYNTHESIZE_READONLY(cocos2d::CCPoint,m_touchStartPos,TouchStartPos)
    CC_SYNTHESIZE_READONLY(cocos2d::CCPoint,m_touchMovePos,TouchMovePos)
    CC_SYNTHESIZE_READONLY(cocos2d::CCPoint,m_touchEndPos,TouchEndPos)
    CC_SYNTHESIZE(int, m_nWidgetTag, WidgetTag)
    CC_SYNTHESIZE(std::string, m_strName, Name)
    CC_SYNTHESIZE(bool,m_bUseMergedTexture,UseMergedTexture)
    CC_SYNTHESIZE_READONLY(WidgetType, m_nWidgetType, WidgetType)
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

NS_CC_EXT_END

#endif /* defined(__CocoGUI__CocoWidget__) */
