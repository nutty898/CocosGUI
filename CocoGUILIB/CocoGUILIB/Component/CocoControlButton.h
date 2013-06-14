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
#include "cocos2d.h"
#include "CCScale9Sprite.h"

namespace cs {
    class CocoControlButton : public CocoWidget
    {
    public:
        CocoControlButton();
        virtual ~CocoControlButton();
        static CocoControlButton* create();
        virtual void initNodes();
        void setTexture(const char* background);
        void setTitle(const char* title);
        virtual void onPressStateChangedToNormal();
        virtual void onPressStateChangedToPressed();
        virtual void onPressStateChangedToDisabled();
        virtual cocos2d::CCNode* getValidNode();
        virtual void setAnchorPoint(const cocos2d::CCPoint &pt);
        virtual void setFlipX(bool flipX);
        virtual void setFlipY(bool flipY);
    protected:
        cocos2d::extension::CCScale9Sprite* m_pBackGround;
        cocos2d::CCLabelTTF* m_pTitle;
    };
}


#endif /* defined(__Test__CocoControlButton__) */
