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

#include "CocoNodeContainer.h"

NS_CC_EXT_BEGIN
    
CocoNodeContainer::CocoNodeContainer()
{
    
}

CocoNodeContainer::~CocoNodeContainer()
{
    
}

void CocoNodeContainer::releaseResoures()
{
    CocoWidget::releaseResoures();
    if (this->m_pCCNode)
    {
        this->m_pCCNode->removeFromParentAndCleanup(true);
        this->m_pCCNode->release();
    }
}

CocoNodeContainer* CocoNodeContainer::create()
{
    CocoNodeContainer* widget = new CocoNodeContainer();
    if (widget && widget->init())
    {
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

void CocoNodeContainer::addCCNode(cocos2d::CCNode *node)
{
    if (!node || this->m_pCCNode == node)
    {
        return;
    }
    this->m_pCCNode = node;
    this->m_pCCNode->retain();
    this->m_pCCRenderNode->addChild(node);
}

void CocoNodeContainer::removeCCNode(bool cleanup)
{
    if (!this->m_pCCNode)
    {
        return;
    }
    this->m_pCCNode->release();
    this->m_pCCRenderNode->removeChild(m_pCCNode,cleanup);
    this->m_pCCNode = NULL;
}

NS_CC_EXT_END