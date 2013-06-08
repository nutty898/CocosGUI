//
//  CocoControlButton.h
//  Test
//
//  Created by cai wenzhi on 13-6-7.
//
//

#ifndef __Test__CocoControlButton__
#define __Test__CocoControlButton__

#include "CocoWidget.h"
#include "UIScale9Sprite.h"
#include "UIText.h"

namespace cs {
    class CocoControlButton : public CocoWidget
    {
    public:
        CocoControlButton();
        virtual ~CocoControlButton();
        static CocoControlButton* create();
        virtual bool init();
        void setTexture(const char* background);
        void setTitle(const char* title);
        virtual void onPressStateChangedToNormal();
        virtual void onPressStateChangedToPressed();
        virtual void onPressStateChangedToDisabled();
        virtual CRenderNode* getValidNode();
        virtual void setAnchorPoint(const cocos2d::CCPoint &pt);
        virtual void setColor(int r,int g,int b);
        virtual void setOpacity(int opcity);
        virtual void setFlipX(bool flipX);
        virtual void setFlipY(bool flipY);
    protected:
        UIScale9Sprite* m_pBackGround;
        UIText* m_pTitle;
    };
}


#endif /* defined(__Test__CocoControlButton__) */
