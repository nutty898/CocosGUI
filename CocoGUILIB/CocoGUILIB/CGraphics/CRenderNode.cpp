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

#include "CRenderNode.h"
#include "CTextField.h"
#include "CClipAbleSprite.h"
#include "CClipAbleLayerColor.h"
#include "CLabelAtlas.h"
#include "GUINodeRGBA.h"
#include "GUIScale9Sprite.h"

using namespace cocos2d;

namespace cs{
    
    CRenderNode::CRenderNode() :
    m_nodeType(NODE_NONE),
    m_bVisible(true),
    m_nZOrder(1),
    m_pParent(NULL),
    m_pRenderNode(NULL)
    {
        this->m_pRenderNode = cocos2d::CCNode::create();
        m_pRenderNode->retain();
        this->m_contentSize = CCPointZero;
        this->m_worldPosition = CCPointZero;
    }
    
    CRenderNode::~CRenderNode()
    {
        removeAllRenderNodeAndCleanUp(true);
        m_pRenderNode->removeFromParentAndCleanup(true);
        m_pRenderNode->release();
    }
    
    void CRenderNode::initNode(int nodeType)
    {
        this->setNodeType(nodeType);
        switch (nodeType) {
            case NODE_CCNODE://1
                this->m_pRenderNode = GUINodeRGBA::create();
                break;
            case NODE_CCLAYER://2
                this->m_pRenderNode = cocos2d::CCLayer::create();
                break;
            case NODE_CCSPRITE://3
                this->m_pRenderNode = cocos2d::CCSprite::create();
                break;
            case NODE_CCCOLORLAYER://4
                this->m_pRenderNode = cocos2d::CCLayerColor::create();
                break;
            case NODE_TEXT://5
                this->m_pRenderNode = cocos2d::CCLabelTTF::create();
                break;
            case NODE_TEXTFIELD://6
                this->m_pRenderNode = CTextField::create("input words here", "Thonburi", 20);
                break;
            case NODE_CLIPSPRITE://7
                this->m_pRenderNode = CClipAbleSprite::create();
                break;
            case NODE_CLIPLAYERCOLOR://8
                this->m_pRenderNode = CClipAbleLayerColor::create();
                break;
            case NODE_LABELATLAS://9
                this->m_pRenderNode = CLabelAtlas::create();
                break;
            case NODE_SCALE9SPRITE://10
                this->m_pRenderNode = GUIScale9Sprite::create();
                break;
            case NODE_TEXTAREA://11
                this->m_pRenderNode = cocos2d::CCLabelTTF::create("", "Thonburi", 20, CCSizeMake(0, 0), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
                break;
            case NODE_EDITBOX:
                //            this->m_pRenderNode = cocos2d::extension::cced
                break;
            default:
                break;
        }
        this->m_pRenderNode->retain();
    }
    
    bool CRenderNode::addRenderNode(CRenderNode *node)
    {
        if (node == NULL) {
            return false;
        }
        for (std::vector<CRenderNode*>::iterator i = m_children.begin(); i!=m_children.end(); i++) {
            if(*i == node)
                return false;
        }
        
        m_children.push_back(node);
        node->setParent(this);
        this->m_pRenderNode->addChild(node->getRenderNode());
        return true;
    }
    
    bool CRenderNode::removeRenderNodeAndCleanUp(CRenderNode *node,bool cleanUp)
    {
        if (node == NULL) {
            return NULL;
        }
        if (cleanUp) {
            for (std::vector<CRenderNode*>::iterator i = m_children.begin(); i!=m_children.end(); i++) {
                if(*i == node) {
                    this->m_children.erase(i);
                    node->setParent(NULL);
                    delete node;
                    node = NULL;
                    return true;
                }
            }
        }
        else {
            for (std::vector<CRenderNode*>::iterator i = m_children.begin(); i!=m_children.end(); i++) {
                if(*i == node) {
                    this->m_children.erase(i);
                    node->getRenderNode()->removeFromParentAndCleanup(false);
                    node->setParent(NULL);
                    return true;
                }
            }
        }
        return false;
    }
    
    bool CRenderNode::removeAllRenderNodeAndCleanUp(bool cleanUp)
    {
        if (cleanUp) {
            for (std::vector<CRenderNode*>::iterator i = m_children.begin(); i!=m_children.end(); i++) {
                CRenderNode* child = *i;
                child->setParent(NULL);
                delete child;
                child = NULL;
            }
        }
        else {
            for (std::vector<CRenderNode*>::iterator i = m_children.begin(); i!=m_children.end(); i++) {
                CRenderNode* child = *i;
                child->getRenderNode()->removeFromParentAndCleanup(false);
                child->setParent(NULL);
            }
        }
        m_children.clear();
        return true;
    }
    
    bool CRenderNode::removeFromParentAndCleanUp(bool cleanUp)
    {
        if (this->m_pParent) {
            return this->m_pParent->removeRenderNodeAndCleanUp(this,cleanUp);
        }else{
            delete this;
        }
        return false;
    }
    
    //cocos property
    void CRenderNode::setVisible(bool visible)
    {
        if (this->m_bVisible == visible) {
            return;
        }
        this->m_bVisible = visible;
        if (this->m_pRenderNode) {
            this->m_pRenderNode->setVisible(visible);
        }
    }
    
    bool CRenderNode::getVisible()
    {
        return this->m_bVisible;
    }
    
    void CRenderNode::setOpacity(int opacity)
    {
        switch (this->m_nodeType) {
            case NODE_NONE:
                ((GUINodeRGBA*)(this->m_pRenderNode))->setOpacity(opacity);
                break;
            case NODE_CCLAYER:
            case NODE_CCNODE:
                break;
            case NODE_CCSPRITE:
                ((CCSprite*)(this->m_pRenderNode))->setOpacity(opacity);
                break;
            case NODE_CCCOLORLAYER:
                ((CCLayerColor*)(this->m_pRenderNode))->setOpacity(opacity);
                break;
            case NODE_TEXT:
            case NODE_TEXTAREA:
                ((CCLabelTTF*)(this->m_pRenderNode))->setOpacity(opacity);
                break;
            case NODE_TEXTFIELD:
                dynamic_cast<CTextField*>(this->m_pRenderNode)->setOpacity(opacity);
                break;
            case NODE_CLIPSPRITE:
                ((CClipAbleSprite*)(this->m_pRenderNode))->setOpacity(opacity);
                break;
            case NODE_CLIPLAYERCOLOR:
                ((CClipAbleLayerColor*)(this->m_pRenderNode))->setOpacity(opacity);
                break;
            case NODE_LABELATLAS:
                ((CCLabelAtlas*)(this->m_pRenderNode))->setOpacity(opacity);
                break;
            case NODE_SCALE9SPRITE:
                ((extension::CCScale9Sprite*)(this->m_pRenderNode))->setOpacity(opacity);
                break;
            case NODE_EDITBOX:
                break;
            default:
                break;
        }
    }
    
    
    
    int CRenderNode::getOpacity()
    {
        int opacity = 0;
        switch (this->m_nodeType) {
            case NODE_NONE:
            case NODE_CCLAYER:
            case NODE_CCNODE:
                break;
            case NODE_CCSPRITE:
                opacity = ((CCSprite*)(this->m_pRenderNode))->getOpacity();
                break;
            case NODE_CCCOLORLAYER:
                opacity = ((CCLayerColor*)(this->m_pRenderNode))->getOpacity();
                break;
            case NODE_TEXT:
            case NODE_TEXTAREA:
                opacity = ((CCLabelTTF*)(this->m_pRenderNode))->getOpacity();
                break;
            case NODE_TEXTFIELD:
                opacity = dynamic_cast<CTextField*>(this->m_pRenderNode)->getOpacity();
                break;
            case NODE_CLIPSPRITE:
                opacity = ((CClipAbleSprite*)(this->m_pRenderNode))->getOpacity();
                break;
            case NODE_CLIPLAYERCOLOR:
                opacity = ((CClipAbleLayerColor*)(this->m_pRenderNode))->getOpacity();
                break;
            case NODE_LABELATLAS:
                opacity = ((CCLabelAtlas*)(this->m_pRenderNode))->getOpacity();
                break;
            case NODE_SCALE9SPRITE:
                opacity = ((extension::CCScale9Sprite*)(this->m_pRenderNode))->getOpacity();
                break;
            case NODE_EDITBOX:
                break;
            default:
                break;
        }
        return opacity;
    }
    
    void CRenderNode::setScale(float scale)
    {
        this->m_pRenderNode->setScale(scale);
    }
    
    float CRenderNode::getScale()
    {
        return this->m_pRenderNode->getScale();
    }
    
    void CRenderNode::setScaleX(float scaleX)
    {
        this->m_pRenderNode->setScaleX(scaleX);
    }
    
    float CRenderNode::getScaleX()
    {
        return this->m_pRenderNode->getScaleX();
    }
    
    void CRenderNode::setScaleY(float scaleY)
    {
        this->m_pRenderNode->setScaleY(scaleY);
    }
    
    float CRenderNode::getScaleY()
    {
        return this->m_pRenderNode->getScaleY();
    }
    
    void CRenderNode::setFlipX(bool flipX){
        switch (this->m_nodeType) {
            case NODE_NONE:
            case NODE_CCNODE:
            case NODE_CCLAYER:
            case NODE_CCCOLORLAYER:
            case NODE_CLIPLAYERCOLOR:
            case NODE_LABELATLAS:
            case NODE_SCALE9SPRITE:
                break;
            case NODE_CCSPRITE:
                ((CCSprite*)(this->m_pRenderNode))->setFlipX(flipX);
                break;
            case NODE_TEXT:
            case NODE_TEXTAREA:
                ((CCLabelTTF*)(this->m_pRenderNode))->setFlipX(flipX);
                break;
            case NODE_TEXTFIELD:
                dynamic_cast<CTextField*>(this->m_pRenderNode)->setFlipX(flipX);
                break;
            case NODE_CLIPSPRITE:
                ((CClipAbleSprite*)(this->m_pRenderNode))->setFlipX(flipX);
                break;
            case NODE_EDITBOX:
                break;
            default:
                break;
        }
    }
    
    bool CRenderNode::isFlipX()
    {
        bool isFlipX = false;
        switch (this->m_nodeType) {
            case NODE_NONE:
            case NODE_CCNODE:
            case NODE_CCLAYER:
            case NODE_CCCOLORLAYER:
            case NODE_CLIPLAYERCOLOR:
            case NODE_LABELATLAS:
            case NODE_SCALE9SPRITE:
                break;
            case NODE_CCSPRITE:
                isFlipX = ((CCSprite*)(this->m_pRenderNode))->isFlipX();
                break;
            case NODE_TEXT:
            case NODE_TEXTAREA:
                isFlipX = ((CCLabelTTF*)(this->m_pRenderNode))->isFlipX();
                break;
            case NODE_TEXTFIELD:
                isFlipX = dynamic_cast<CTextField*>(this->m_pRenderNode)->isFlipX();
                break;
            case NODE_CLIPSPRITE:
                isFlipX = ((CClipAbleSprite*)(this->m_pRenderNode))->isFlipX();
                break;
            case NODE_EDITBOX:
                break;
            default:
                break;
        }
        return isFlipX;
    }
    
    void CRenderNode::setFlipY(bool flipY){
        switch (this->m_nodeType) {
            case NODE_NONE:
            case NODE_CCNODE:
            case NODE_CCLAYER:
            case NODE_CCCOLORLAYER:
            case NODE_CLIPLAYERCOLOR:
            case NODE_LABELATLAS:
            case NODE_SCALE9SPRITE:
                break;
            case NODE_CCSPRITE:
                ((CCSprite*)(this->m_pRenderNode))->setFlipY(flipY);
                break;
            case NODE_TEXT:
            case NODE_TEXTAREA:
                ((CCLabelTTF*)(this->m_pRenderNode))->setFlipY(flipY);
                break;
            case NODE_TEXTFIELD:
                dynamic_cast<CTextField*>(this->m_pRenderNode)->setFlipY(flipY);
                break;
            case NODE_CLIPSPRITE:
                ((CClipAbleSprite*)(this->m_pRenderNode))->setFlipY(flipY);
                break;
            case NODE_EDITBOX:
                break;
            default:
                break;
        }
    }
    
    bool CRenderNode::isFlipY()
    {
        bool flipY = false;
        switch (this->m_nodeType) {
            case NODE_NONE:
            case NODE_CCNODE:
            case NODE_CCLAYER:
            case NODE_CCCOLORLAYER:
            case NODE_CLIPLAYERCOLOR:
            case NODE_LABELATLAS:
            case NODE_SCALE9SPRITE:
                break;
            case NODE_CCSPRITE:
                flipY = ((CCSprite*)(this->m_pRenderNode))->isFlipY();
                break;
            case NODE_TEXT:
            case NODE_TEXTAREA:
                flipY = ((CCLabelTTF*)(this->m_pRenderNode))->isFlipY();
                break;
            case NODE_TEXTFIELD:
                flipY = dynamic_cast<CTextField*>(this->m_pRenderNode)->isFlipY();
                break;
            case NODE_CLIPSPRITE:
                flipY = ((CClipAbleSprite*)(this->m_pRenderNode))->isFlipY();
                break;
            case NODE_EDITBOX:
                break;
            default:
                break;
        }
        return flipY;
    }
    
    void CRenderNode::setRotation(float rotation)
    {
        this->m_pRenderNode->setRotation(rotation);
    }
    
    float CRenderNode::getRotation()
    {
        return this->m_pRenderNode->getRotation();
    }
    
    void CRenderNode::setPosition(const CCPoint &pos)
    {
        if (this->m_pRenderNode) {
            this->m_pRenderNode->setPosition(pos);
        }
    }
    
    void CRenderNode::setPositionXY(float x,float y)
    {   
        if (this->m_pRenderNode) {
            this->m_pRenderNode->setPosition(ccp(x,y));
        }
    }
    
    CCPoint CRenderNode::getPosition()
    {
        return this->m_pRenderNode->getPosition();
    }
    
    void CRenderNode::setAnchorPoint(const CCPoint &point)
    {
        if (this->m_pRenderNode) {
            this->m_pRenderNode->setAnchorPoint(point);
        }
    }
    
    void CRenderNode::setAnchorPointXY(float x,float y)
    {
        if (this->m_pRenderNode) {
            this->m_pRenderNode->setAnchorPoint(ccp(x,y));
        }
    }
    
    CCPoint CRenderNode::getAnchorPoint()
    {
        return this->m_pRenderNode->getAnchorPoint();
    }
    
    void CRenderNode::setZOrder(int z)
    {
        this->m_nZOrder = z;
        if (this->m_pRenderNode) {
            this->m_pRenderNode->setZOrder(z);
        }
    }
    
    int CRenderNode::getZOrder()
    {
        return this->m_nZOrder;
    }
    
    cocos2d::CCNode* CRenderNode::getRenderNode()
    {
        return this->m_pRenderNode;
    }
    
    void CRenderNode::setParent(CRenderNode *parent)
    {
        this->m_pParent = parent;
    }
    
    CRenderNode* CRenderNode::getParent()
    {
        return this->m_pParent;
    }
    
    void CRenderNode::setNodeType(int type)
    {
        if (this->m_nodeType == type) {
            return;
        }
        this->m_nodeType = (NodeType)type;
    }
    
    int CRenderNode::getNodeType()
    {
        return (int)(this->m_nodeType);
    }
    
    CCSize CRenderNode::getContentSize()
    {
        return this->m_pRenderNode->getContentSize();
    }
    
    float CRenderNode::getContentSizeWidth()
    {
        CCSize nodeSize = this->m_pRenderNode->getContentSize();
        return nodeSize.width;
    }
    
    float CRenderNode::getContentSizeHeight()
    {
        CCSize nodeSize = this->m_pRenderNode->getContentSize();
        return nodeSize.height;
    }
    
    void CRenderNode::setTextureWithFile(const char *fileName,bool useSpriteFrame)
    {
        if(NULL == fileName || strcmp(fileName, "") == 0)
        {
            return;
        }
        m_strTextureName = fileName;
        switch (this->m_nodeType) {
            case NODE_CCSPRITE:
                if (useSpriteFrame) {
                    ((cocos2d::CCSprite*)(this->m_pRenderNode))->initWithSpriteFrameName(fileName);
                }else{
                    ((cocos2d::CCSprite*)(this->m_pRenderNode))->initWithFile(fileName);
                }
                break;
            case NODE_CLIPSPRITE:
                if (useSpriteFrame) {
                    ((CClipAbleSprite*)(this->m_pRenderNode))->initWithSpriteFrameName(fileName);
                }else{
                    ((CClipAbleSprite*)(this->m_pRenderNode))->initWithFile(fileName);
                }
                break;
            case NODE_SCALE9SPRITE:
                //            ((cocos2d::extension::CCScale9Sprite*)(this->m_pRenderNode))->initWithFile(fileName);
                break;
            default:
                break;
        }
    }
    
    void CRenderNode::setColor(int r, int g, int b)
    {
        switch (this->m_nodeType) {
            case NODE_NONE:
                ((GUINodeRGBA*)(this->m_pRenderNode))->setColor(ccc3(r, g, b));
                break;
            case NODE_CCNODE:
            case NODE_CCLAYER:
                break;
            case NODE_CCSPRITE:
                ((CCSprite*)(this->m_pRenderNode))->setColor(ccc3(r, g, b));
                break;
            case NODE_CCCOLORLAYER:
                ((CCLayerColor*)(this->m_pRenderNode))->setColor(ccc3(r, g, b));
                break;
            case NODE_TEXT:
            case NODE_TEXTAREA:
                ((CCLabelTTF*)(this->m_pRenderNode))->setColor(ccc3(r, g, b));
                break;
            case NODE_SCALE9SPRITE:
                ((extension::CCScale9Sprite*)(this->m_pRenderNode))->setColor(ccc3(r, g, b));
                break;
            case NODE_TEXTFIELD:
                dynamic_cast<CTextField*>(this->m_pRenderNode)->setColor(ccc3(r, g, b));
            case NODE_CLIPSPRITE:
                ((CClipAbleSprite*)(this->m_pRenderNode))->setColor(ccc3(r, g, b));
                break;
            case NODE_CLIPLAYERCOLOR:
                ((CClipAbleLayerColor*)(this->m_pRenderNode))->setColor(ccc3(r, g, b));
                break;
            case NODE_LABELATLAS:
                ((CCLabelAtlas*)(this->m_pRenderNode))->setColor(ccc3(r, g, b));
                break;
            case NODE_EDITBOX:
                break;
            default:
                break;
        }
    }
    
    cocos2d::ccColor3B CRenderNode::getColor()
    {
        ccColor3B color;
        switch (this->m_nodeType) {
            case NODE_NONE:
            case NODE_CCNODE:
            case NODE_CCLAYER:
                break;
            case NODE_CCSPRITE:
                color = ((CCSprite*)(this->m_pRenderNode))->getColor();
                break;
            case NODE_CCCOLORLAYER:
                color = ((CCLayerColor*)(this->m_pRenderNode))->getColor();
                break;
            case NODE_TEXT:
            case NODE_TEXTAREA:
                color = ((CCLabelTTF*)(this->m_pRenderNode))->getColor();
                break;
            case NODE_SCALE9SPRITE:
                color = ((extension::CCScale9Sprite*)(this->m_pRenderNode))->getColor();
                break;
            case NODE_TEXTFIELD:
                color = dynamic_cast<CTextField*>(this->m_pRenderNode)->getColor();
            case NODE_CLIPSPRITE:
                color = ((CClipAbleSprite*)(this->m_pRenderNode))->getColor();
                break;
            case NODE_CLIPLAYERCOLOR:
                color = ((CClipAbleLayerColor*)(this->m_pRenderNode))->getColor();
                break;
            case NODE_LABELATLAS:
                color = ((CCLabelAtlas*)(this->m_pRenderNode))->getColor();
                break;
            case NODE_EDITBOX:
                break;
            default:
                break;
        }
        return color;
    }
    
    void CRenderNode::setScale9FileAndCapInsets(const char *fileName, float x, float y, float width, float height,bool useSpriteFrame)
    {
        if(NULL == fileName || strcmp(fileName, "") == 0)
        {
            return;
        }
        if (this->m_nodeType != NODE_SCALE9SPRITE){
            return;
        }
        if (useSpriteFrame) {
            ((cocos2d::extension::CCScale9Sprite*)(this->m_pRenderNode))->initWithSpriteFrameName(fileName, CCRectMake(x, y, width, height));
        }else{
            ((cocos2d::extension::CCScale9Sprite*)(this->m_pRenderNode))->initWithFile(fileName, CCRectZero, CCRectMake(x, y, width, height));
        }
    }
    
    void CRenderNode::setClipAble(bool able)
    {
        switch (this->m_nodeType) {
            case NODE_CLIPSPRITE:
                ((CClipAbleSprite*)(this->m_pRenderNode))->setClipAble(able);
                break;
            case NODE_CLIPLAYERCOLOR:
                ((CClipAbleLayerColor*)(this->m_pRenderNode))->setClipAble(able);
                break;
            default:
                break;
        }
    }
    
    void CRenderNode::setClipRect(float x, float y, float width, float height)
    {
        switch (this->m_nodeType) {
            case NODE_CLIPSPRITE:
                ((CClipAbleSprite*)(this->m_pRenderNode))->setClipRect(x, y, width, height);
                break;
            case NODE_CLIPLAYERCOLOR:
                ((CClipAbleLayerColor*)(this->m_pRenderNode))->setClipRect(x, y, width, height);
                break;
            default:
                break;
        }
    }
    
    void CRenderNode::setClipSize(float width, float height)
    {
        switch (this->m_nodeType) {
            case NODE_CLIPLAYERCOLOR:
                ((CClipAbleLayerColor*)(this->m_pRenderNode))->setClipSize(width, height);
                break;
            default:
                break;
        }
    }
    
    void CRenderNode::setColorAndSize(int r, int g, int b, int o, float width, float height)
    {
        switch (this->m_nodeType) {
            case NODE_CLIPLAYERCOLOR:
                ((CClipAbleLayerColor*)(this->m_pRenderNode))->initWithColor(ccc4(r, g, b, o), width, height);
                break;
            default:
                break;
        }
    }
    
    void CRenderNode::setSize(float width,float height)
    {
        switch (this->m_nodeType) {
            case NODE_CLIPLAYERCOLOR:
                ((CClipAbleLayerColor*)(this->m_pRenderNode))->setContentSize(CCSizeMake(width, height));
                break;
            default:
                break;
        }
    }
    
    void CRenderNode::setLabelAtlasProperty(const char *string, const char *charMapFile, int itemWidth, int itemHeight, const char* startCharMap,bool useSpriteFrame)
    {
        if (this->m_nodeType != NODE_LABELATLAS) {
            return;
        }
        if (useSpriteFrame) {
            CCSprite* sprite = CCSprite::createWithSpriteFrameName(charMapFile);
            ((CLabelAtlas*)(this->m_pRenderNode))->setProperty(string, sprite->getTexture(), itemWidth, itemHeight, (int)(startCharMap[0]));    
        }else{
            ((CLabelAtlas*)(this->m_pRenderNode))->setProperty(string, charMapFile, itemWidth, itemHeight, (int)(startCharMap[0]));    
        }
    }
    
    CCPoint CRenderNode::convertToWorldSpace()
    {
        m_worldPosition = this->m_pRenderNode->convertToWorldSpace(ccp(0,0));
        return m_worldPosition;
    }
    
    void CRenderNode::setStringValue(const char *value)
    {
        if(NULL == value || strcmp(value, "") == 0)
        {
            return;
        }
        m_strTextValue = value;
        
        switch (this->m_nodeType) {
            case NODE_TEXT:
            case NODE_TEXTAREA:
                ((cocos2d::CCLabelTTF*)(this->m_pRenderNode))->setString(value);
                break;
            case NODE_TEXTFIELD:
                dynamic_cast<CTextField*>(this->m_pRenderNode)->setString(value);
                break;
            case NODE_LABELATLAS:
                ((CCLabelAtlas*)(this->m_pRenderNode))->setString(value);
                break;
            default:
                break;
        }
    }
    
    const char* CRenderNode::getStringValue()
    {
        const char* res = NULL;
        switch (this->m_nodeType) {
            case NODE_TEXT:
            case NODE_TEXTAREA:
                res = ((cocos2d::CCLabelTTF*)(this->m_pRenderNode))->getString();
                break;
            case NODE_TEXTFIELD:
                res = dynamic_cast<CTextField*>(this->m_pRenderNode)->getString();
                break;
            case NODE_LABELATLAS:
                res = ((CCLabelAtlas *)(this->m_pRenderNode))->getString();
                break;
            default:
                break;
        }
        return res;
    }
    
    void CRenderNode::setTextColor(int r, int g, int b)
    {
        switch (this->m_nodeType) {
            case NODE_TEXT:
            case NODE_TEXTAREA:
                ((cocos2d::CCLabelTTF*)(this->m_pRenderNode))->setColor(ccc3(r, g, b));
                break;
            case NODE_TEXTFIELD:
                dynamic_cast<CTextField*>(this->m_pRenderNode)->setColor(ccc3(r, g, b));
                break;
            default:
                break;
        }
    }
    
    void CRenderNode::setFontSize(float size)
    {
        switch (this->m_nodeType) {
            case NODE_TEXT:
            case NODE_TEXTAREA:
                ((cocos2d::CCLabelTTF*)(this->m_pRenderNode))->setFontSize(size);
                break;
            case NODE_TEXTFIELD:
                dynamic_cast<CTextField*>(this->m_pRenderNode)->setFontSize(size);
                break;
            default:
                break;
        }
    }
    
    int CRenderNode::getFontSize()
    {
        switch (this->m_nodeType) {
            case NODE_TEXT:
            case NODE_TEXTAREA:
                return ((cocos2d::CCLabelTTF*)(this->m_pRenderNode))->getFontSize();
                break;
            case NODE_TEXTFIELD:
                return dynamic_cast<CTextField*>(this->m_pRenderNode)->getFontSize();
                break;
            default:
                break;
        }
        return 0;
    }
    
    void CRenderNode::setFontName(const char *name)
    {
        if (!name || strcmp(name, "")) {
            return;
        }
        switch (this->m_nodeType)
        {
            case NODE_TEXT:
            case NODE_TEXTAREA:
                ((cocos2d::CCLabelTTF *)(this->m_pRenderNode))->setFontName(name);
                break;
            
            case NODE_TEXTFIELD:
                dynamic_cast<CTextField*>(this->m_pRenderNode)->setFontName(name);
                break;
                
            default:
                break;
        }
    }
    
    const char* CRenderNode::getFontName()
    {
        switch (this->m_nodeType)
        {
            case NODE_TEXT:
            case NODE_TEXTAREA:
                return ((cocos2d::CCLabelTTF *)(this->m_pRenderNode))->getFontName();
                break;
                
            case NODE_TEXTFIELD:
                return dynamic_cast<CTextField*>(this->m_pRenderNode)->getFontName();
                break;
                
            default:
                break;
        }
        return NULL;
    }
    
    void CRenderNode::setTextAreaSize(float width, float height)
    {
        switch (this->m_nodeType) {
            case NODE_TEXTAREA:
                ((cocos2d::CCLabelTTF*)(this->m_pRenderNode))->setDimensions(CCSizeMake(width, height));
                break;
            default:
                break;
        }
    }
    
    void CRenderNode::setTextFieldSize(float width, float height)
    {
        switch (this->m_nodeType) {
            case NODE_TEXTFIELD:
                dynamic_cast<CTextField*>(this->m_pRenderNode)->setDimensions(CCSizeMake(width, height));
                dynamic_cast<CTextField*>(this->m_pRenderNode)->setHorizontalAlignment(kCCTextAlignmentCenter);
                dynamic_cast<CTextField*>(this->m_pRenderNode)->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
                break;
            default:
                break;
        }
    }
    
    void CRenderNode::setTextHorizontalAlignment(int alignment)
    {
        switch (this->m_nodeType) {
            case NODE_TEXTAREA:
                ((cocos2d::CCLabelTTF*)(this->m_pRenderNode))->setHorizontalAlignment((CCTextAlignment)alignment);
                break;
            default:
                break;
        }
    }
    
    void CRenderNode::setTextVerticalAlignment(int alignment)
    {
        switch (this->m_nodeType) {
            case NODE_TEXTAREA:
                ((cocos2d::CCLabelTTF*)(this->m_pRenderNode))->setVerticalAlignment((CCVerticalTextAlignment)alignment);
                break;
            default:
                break;
        }
    }
    
    void CRenderNode::setRect(float x,float y,float width,float height)
    {
        if (this->m_nodeType != NODE_CCSPRITE){
            return;
        }
        ((cocos2d::CCSprite*)(this->m_pRenderNode))->setTextureRect(CCRectMake(x, y, width, height));
    }
    
    void CRenderNode::openIME()
    {
        if (this->m_nodeType != NODE_TEXTFIELD){
            return;
        }
        dynamic_cast<CTextField*>(this->m_pRenderNode)->openIME();
    }
    
    void CRenderNode::closeIME()
    {
        if (this->m_nodeType != NODE_TEXTFIELD){
            return;
        }
        dynamic_cast<CTextField*>(this->m_pRenderNode)->closeIME();
    }
    
    void CRenderNode::setPlaceHolder(const char *placeHolder)
    {
        if (this->m_nodeType != NODE_TEXTFIELD){
            return;
        }
        dynamic_cast<CTextField*>(this->m_pRenderNode)->setPlaceHolder(placeHolder);
    }
    
    void CRenderNode::setCharacterLength(int length)
    {
        if (this->m_nodeType != NODE_TEXTFIELD){
            return;
        }
        dynamic_cast<CTextField*>(this->m_pRenderNode)->setCharacterLength(length);
    }
    
    void CRenderNode::setIsPassword(bool isPassword)
    {
        if (this->m_nodeType != NODE_TEXTFIELD){
            return;
        }
        dynamic_cast<CTextField*>(this->m_pRenderNode)->setIsPassword(isPassword);
    }
    
    void CRenderNode::setScale9Size(float width, float height)
    {
        if (this->m_nodeType != NODE_SCALE9SPRITE){
            return;
        }
        ((cocos2d::extension::CCScale9Sprite*)(this->m_pRenderNode))->setContentSize(CCSizeMake(width, height));
    }
    
    bool CRenderNode::hitTest(cocos2d::CCPoint &pt)
    {
        CCPoint nsp = this->m_pRenderNode->convertToNodeSpace(pt);
        CCRect bb = this->m_pRenderNode->boundingBox();
        if (nsp.x >= 0 && nsp.x <= bb.size.width && nsp.y > 0 && nsp.y <= bb.size.height) {
            return true;
        }
        return false;
    }
    
    //test
    bool CRenderNode::hitTest2(cocos2d::CCPoint &pt)
    {
        CCPoint nsp = this->m_pRenderNode->convertToNodeSpace(pt);
        CCSize bb = this->m_pRenderNode->getContentSize();
        if (nsp.x >= 0 && nsp.x <= bb.width && nsp.y > 0 && nsp.y <= bb.height) {
            return true;
        }
        return false;
    }
    
    cocos2d::CCPoint CRenderNode::convertToNodeSpace(cocos2d::CCPoint &pt)
    {
        CCPoint nsp = this->m_pRenderNode->convertToNodeSpace(pt);
        return nsp;
    }
}
