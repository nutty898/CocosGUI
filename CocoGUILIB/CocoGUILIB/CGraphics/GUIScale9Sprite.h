//
//  GUIScale9Sprite.h
//  Test
//
//  Created by pipu on 13-5-29.
//
//

/* gui mark */
#ifndef __Test__GUIScale9Sprite__
#define __Test__GUIScale9Sprite__

#include <iostream>
#include "CCScale9Sprite.h"

namespace cs
{
    class GUIScale9Sprite : public cocos2d::extension::CCScale9Sprite
    {
    public:
        GUIScale9Sprite();
        ~GUIScale9Sprite();
        
        static GUIScale9Sprite* create();
        bool init();
        
        void setOpacityModifyRGB(bool bValue);
        void setOpacity(GLubyte opacity);
        void setColor(const cocos2d::ccColor3B& color);
        
        void updateDisplayedOpacity(GLubyte parentOpacity);
        void updateDisplayedColor(const cocos2d::ccColor3B& parentColor);
    };
}

#endif /* defined(__Test__GUIScale9Sprite__) */
/**/
