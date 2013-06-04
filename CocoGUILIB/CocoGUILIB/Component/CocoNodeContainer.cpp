//
//  CocoCCContainer.cpp
//  Test
//
//  Created by cai wenzhi on 13-6-3.
//
//

#include "CocoNodeContainer.h"

namespace cs {
    
    CocoNodeContainer::CocoNodeContainer()
    {
        
    }
    
    CocoNodeContainer::~CocoNodeContainer()
    {
        
    }
    
    void CocoNodeContainer::releaseResoures()
    {
        if (this->m_pCCNode) {
            this->m_pCCNode->removeFromParentAndCleanup(true);
            this->m_pCCNode->release();
        }
    }
    
    CocoNodeContainer* CocoNodeContainer::create()
    {
        CocoNodeContainer* widget = new CocoNodeContainer();
        if (widget && widget->init()) {
            return widget;
        }
        CC_SAFE_DELETE(widget);
        return NULL;
    }
    
    void CocoNodeContainer::addCCNode(cocos2d::CCNode *node)
    {
        if (!node || this->m_pCCNode == node) {
            return;
        }
        this->m_pCCNode = node;
        this->m_pCCNode->retain();
        this->m_pCContainerNode->getRenderNode()->addChild(node);
    }
    
    void CocoNodeContainer::removeCCNode(bool cleanup)
    {
        if (!this->m_pCCNode) {
            return;
        }
        this->m_pCCNode->release();
        this->m_pCContainerNode->getRenderNode()->removeChild(m_pCCNode,cleanup);
        this->m_pCCNode = NULL;
    }
    
}