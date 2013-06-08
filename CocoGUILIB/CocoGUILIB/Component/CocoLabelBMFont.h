//
//  CocoLabelBMFont.h
//  Test
//
//  Created by cai wenzhi on 13-6-7.
//
//

#ifndef __Test__CocoLabelBMFont__
#define __Test__CocoLabelBMFont__

#include "CocoWidget.h"

namespace cs {
    
    class CocoLabelBMFont : public CocoWidget
    {
    public:
        CocoLabelBMFont();
        virtual ~CocoLabelBMFont();
        static CocoLabelBMFont* create();
        virtual bool init();
        void setFntFile(const char* fileName);
        void setText(const char* value);
        const char* getStringValue();
    protected:
        cocos2d::CCLabelBMFont* m_pLabelBMFont;
    };
    
}

#endif /* defined(__Test__CocoLabelBMFont__) */
