//
//  CClipAbleLayerGradient.cpp
//  Test
//
//  Created by cai wenzhi on 13-6-18.
//
//

#include "CClipAbleLayerGradient.h"

using namespace cocos2d;

namespace cs {
    
    CClipAbleLayerGradient* CClipAbleLayerGradient::create(const cocos2d::ccColor4B &colorStart,const cocos2d::ccColor4B &colorEnd){
        CClipAbleLayerGradient * pLayer = new CClipAbleLayerGradient();
        if( pLayer && pLayer->initWithColor(colorStart,colorEnd))
        {
            pLayer->autorelease();
            return pLayer;
        }
        CC_SAFE_DELETE(pLayer);
        return NULL;
    }
    
    CClipAbleLayerGradient* CClipAbleLayerGradient::create(){
        CClipAbleLayerGradient * pLayer = new CClipAbleLayerGradient();
        if( pLayer && pLayer->init())
        {
            pLayer->autorelease();
            return pLayer;
        }
        CC_SAFE_DELETE(pLayer);
        return NULL;
    }
    
    void CClipAbleLayerGradient::visit(){
        if (this->m_bClipAble) {
            glEnable(GL_SCISSOR_TEST);
            CCPoint local = this->convertToWorldSpace(CCPointZero);
            
            if (this->m_bEnableCustomArea) {
                CCEGLView::sharedOpenGLView()->setScissorInPoints(local.x, local.y, this->m_fScissorWidth, this->m_fScissorHeight);
            }else{
                CCSize s = this->boundingBox().size;
                CCEGLView::sharedOpenGLView()->setScissorInPoints(local.x, local.y, s.width, s.height);
            }
            
            CCLayerColor::visit();
            glDisable(GL_SCISSOR_TEST);
        }else {
            CCLayerColor::visit();
        }
    }
    
    void CClipAbleLayerGradient::setClipAble(bool able)
    {
        this->m_bClipAble = able;
    }
    
    void CClipAbleLayerGradient::setColorEnable(bool enable)
    {
        this->m_bColorEnable = enable;
    }
    
    bool CClipAbleLayerGradient::getColorEnable()
    {
        return this->m_bColorEnable;
    }
    
    void CClipAbleLayerGradient::setClipRect(const cocos2d::CCRect &rect)
    {
        
    }
    
    void CClipAbleLayerGradient::setClipSize(float width, float height)
    {
        this->m_bEnableCustomArea = true;
        this->m_fScissorWidth = width;
        this->m_fScissorHeight = height;
    }
    
    void CClipAbleLayerGradient::draw()
    {
        //        to head off the draw call
        if (this->m_bColorEnable) {
            CCLayerColor::draw();
        }
    }
}
