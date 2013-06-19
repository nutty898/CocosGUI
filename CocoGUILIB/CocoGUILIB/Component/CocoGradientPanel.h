//
//  CocoGradientPanel.h
//  Test
//
//  Created by cai wenzhi on 13-6-18.
//
//

#ifndef __Test__CocoGradientPanel__
#define __Test__CocoGradientPanel__

#include "CocoPanel.h"

namespace cs {

    class CocoGradientPanel : public CocoPanel
    {
    public:
        CocoGradientPanel();
        virtual ~CocoGradientPanel();
        static CocoGradientPanel* create();
        virtual void initNodes();
        virtual void setBackGroundColorEnable(bool able);
        void setStartColor(const cocos2d::ccColor3B &color);
        void setEndColor(const cocos2d::ccColor3B &color);
        void setStartOpacity(int opacity);
        void setEndOpacity(int opacity);
    protected:
    };
}

#endif /* defined(__Test__CocoGradientPanel__) */
