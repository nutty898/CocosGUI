//
//  CocoCCContainer.h
//  Test
//
//  Created by cai wenzhi on 13-6-3.
//
//

#ifndef __Test__CocoCCContainer__
#define __Test__CocoCCContainer__

#include "CocoWidget.h"

namespace cs {
    class CocoNodeContainer : public CocoWidget{
        
    public:
        CocoNodeContainer();
        virtual ~CocoNodeContainer();
        virtual void releaseResoures();
        static CocoNodeContainer* create();
        void addCCNode(cocos2d::CCNode* node);
        void removeCCNode(bool cleanup);
        
    protected:
        cocos2d::CCNode* m_pCCNode;
    };

}
#endif /* defined(__Test__CocoCCContainer__) */
