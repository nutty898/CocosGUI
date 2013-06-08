//
//  GUINodeRGBA.cpp
//  TestColorNode
//
//  Created by cai wenzhi on 13-5-9.
//
//

#include "GUINodeRGBA.h"
namespace cs {
GUINodeRGBA * GUINodeRGBA::create(void)
{
	GUINodeRGBA * pRet = new GUINodeRGBA();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
	return pRet;
}
    
    bool GUINodeRGBA::init()
    {
        if (CCNodeRGBA::init())
        {
            setCascadeOpacityEnabled(true);
            setCascadeColorEnabled(true);
            
            return true;
        }
        return false;
    }

void GUINodeRGBA::addChild(cocos2d::CCNode *child)
{
    CCNode::addChild(child);
    CCRGBAProtocol *item = dynamic_cast<CCRGBAProtocol*>(child);
    if (item)
    {
        item->setColor(this->getColor());
        item->setOpacity(this->getOpacity());
    }
}

void GUINodeRGBA::setColor(const cocos2d::ccColor3B &color3)
{
    CCNodeRGBA::setColor(color3);
    CCObject* pObj;
    CCARRAY_FOREACH(m_pChildren, pObj)
    {
        CCRGBAProtocol *item = dynamic_cast<CCRGBAProtocol*>(pObj);
        if (item)
        {
            item->setColor(color3);
        }
    }
}

void GUINodeRGBA::setOpacity(GLubyte opacity)
{
    CCNodeRGBA::setOpacity(opacity);
    CCObject* pObj;
    CCARRAY_FOREACH(m_pChildren, pObj)
    {
        CCRGBAProtocol *item = dynamic_cast<CCRGBAProtocol*>(pObj);
        if (item)
        {
            item->setOpacity(opacity);
        }
    }
}
}