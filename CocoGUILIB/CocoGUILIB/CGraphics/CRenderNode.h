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

#ifndef SPII_CRenderNode_h
#define SPII_CRenderNode_h
#include "cocos2d.h"
#include <vector>

namespace cs {
    
    typedef enum{
        NODE_NONE,//0
        NODE_CCNODE,//1
        NODE_CCSPRITE,//2
        NODE_CCLAYER,//3
        NODE_CCCOLORLAYER,//4
        NODE_TEXT,//5
        //Special
        NODE_TEXTFIELD,//6
        NODE_CLIPSPRITE,//7
        NODE_CLIPLAYERCOLOR,//8
        NODE_LABELATLAS,//9
        NODE_SCALE9SPRITE,//10
        NODE_TEXTAREA,//11
        NODE_EDITBOX//12
    } NodeType;
    
    class CRenderNode{
        public:
        CRenderNode();
       // CRenderNode(DEFINE_JS obj);
        virtual ~CRenderNode();
        
        bool addRenderNode(CRenderNode* node);
        bool removeRenderNodeAndCleanUp(CRenderNode* node,bool cleanUp);
        bool removeAllRenderNodeAndCleanUp(bool cleanUp);
        bool removeFromParentAndCleanUp(bool cleanUp);
        void setVisible(bool visible);
        bool getVisible();
        //cocos property

        void setOpacity(int opacity);
        int getOpacity();
        void setScale(float scale);
        float getScale();
        void setScaleX(float scaleX);
        float getScaleX();
        void setScaleY(float scaleY);
        float getScaleY();
        void setFlipX(bool flipX);
        bool isFlipX();
        void setFlipY(bool filipY);
        bool isFlipY();
        void setRotation(float rotation);
        float getRotation();
        void setPosition(const cocos2d::CCPoint &pos);
        void setPositionXY(float x,float y);
        cocos2d::CCPoint getPosition();
        void setAnchorPoint(const cocos2d::CCPoint &pt);
        void setAnchorPointXY(float x,float y);
        cocos2d::CCPoint getAnchorPoint();
        void setColor(int r,int g,int b);
        cocos2d::ccColor3B getColor();
        
        void setZOrder(int z);
        int getZOrder();
        void setNodeType(int type);
        int getNodeType();
        cocos2d::CCSize getContentSize();
        float getContentSizeWidth();
        float getContentSizeHeight();
        
        void initNode(int nodeType);
        
        bool hitTest(cocos2d::CCPoint &pt);
        
        //test
        bool hitTest2(cocos2d::CCPoint &pt);
        
        
        //ccsprite
        void setTextureWithFile(const char* fileName,bool useSpriteFrame);
        void setRect(float x,float y,float width,float height);
        //cclabel
        void setStringValue(const char* value);
        const char* getStringValue();
        void setTextColor(int r,int g,int b);
        void setFontSize(float size);
        int getFontSize();
        void setFontName(const char *name);
        const char* getFontName();
        //cctextfield
        void openIME();
        void closeIME();
        void setPlaceHolder(const char* placeHolder);
        void setTextFieldSize(float width,float height);
        //clipsprite
        void setClipAble(bool able);
        void setClipRect(float x,float y,float width,float height);
        void setClipSize(float width,float height);
        //cliplayercolor
        void setColorAndSize(int r,int g,int b,int o,float width,float height);
                void setSize(float width,float height);
        cocos2d::CCPoint convertToWorldSpace();
        cocos2d::CCPoint convertToNodeSpace(cocos2d::CCPoint& pt);
        //cclabelatlas
        void setLabelAtlasProperty(const char *string, const char *charMapFile,  int itemWidth,  int itemHeight,  const char* startCharMap,bool useSpriteFrame);
        //scale9sprite
        void setScale9Size(float width,float height);
        void setScale9FileAndCapInsets(const char* fileName,float x,float y,float width,float height,bool useSpriteFrame);
        //textarea
        void setTextAreaSize(float width,float height);
        void setTextHorizontalAlignment(int alignment);
        void setTextVerticalAlignment(int alignment);
        
        cocos2d::CCNode* getRenderNode();
        void setParent(CRenderNode* parent);
        CRenderNode* getParent();
        protected:
        cocos2d::CCNode* m_pRenderNode;
        CRenderNode* m_pParent;
        std::vector<CRenderNode*> m_children;
        NodeType m_nodeType;
        
        //ccsprite
        std::string m_strTextureName;
        //cclabel
        std::string m_strTextValue;
        
        
        //cocos property
        bool m_bVisible;
//        int m_nOpacity;
//        float m_fScaleX;
//        float m_fScaleY;
//        float m_fScale;
//        bool m_bFlipX;
//        bool m_bFlipY;
//        float m_fRotation;
//        
//        cocos2d::CCPoint m_position;
//        cocos2d::CCPoint m_anchorPoint;
     
        cocos2d::CCPoint m_contentSize;
     
        cocos2d::CCPoint m_worldPosition;
     
        
        int m_nZOrder;
    };
    
}

#endif
