//
//  CClipAbleLayerGradient.h
//  Test
//
//  Created by cai wenzhi on 13-6-18.
//
//

#ifndef __Test__CClipAbleLayerGradient__
#define __Test__CClipAbleLayerGradient__

#include "cocos2d.h"

namespace cs {
    class CClipAbleLayerGradient : public cocos2d::CCLayerGradient {
    public:
        CClipAbleLayerGradient():m_bClipAble(false),m_fScissorX(0.0),m_fScissorY(0.0),m_fScissorWidth(0.0),m_fScissorHeight(0.0),m_bEnableCustomArea(false),m_bColorEnable(false){};
        virtual ~CClipAbleLayerGradient(){};
        static CClipAbleLayerGradient* create(const cocos2d::ccColor4B &colorStart,const cocos2d::ccColor4B &colorEnd);
        static CClipAbleLayerGradient* create();
        virtual void visit();
        void setClipAble(bool able);
        void setColorEnable(bool enable);
        bool getColorEnable();
        void setClipRect(const cocos2d::CCRect &rect);
        void setClipSize(float width,float height);
        virtual void draw();
    protected:
        bool m_bClipAble;
        float m_fScissorX;
        float m_fScissorY;
        float m_fScissorWidth;
        float m_fScissorHeight;
        bool m_bEnableCustomArea;
        bool m_bColorEnable;
    };
}

#endif /* defined(__Test__CClipAbleLayerGradient__) */
