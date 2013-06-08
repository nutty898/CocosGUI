//
//  GUISprite.h
//  Test
//
//  Created by pipu on 13-6-5.
//
//

/* gui mark */

#ifndef __Test__GUISprite__
#define __Test__GUISprite__

#include "cocos2d.h"

namespace cs
{
    class GUISprite : public cocos2d::CCSprite
    {
    public:
        GUISprite();
        ~GUISprite();
        
        static GUISprite* createWithSpriteFrameName(const char *pszSpriteFrameName);
    };
}

#endif /* defined(__Test__GUISprite__) */
/**/
