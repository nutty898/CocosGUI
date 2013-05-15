//
//  CocoImageButton.h
//  Test
//
//  Created by pipu on 13-5-14.
//
//

#ifndef __Test__CocoImageButton__
#define __Test__CocoImageButton__

#include <iostream>
#include "CocoButton.h"
#include "UISprite.h"
#include "UIScale9Sprite.h"

namespace cs
{
    class CocoImageButton : public CocoButton
    {
    public:
        CocoImageButton();
        virtual ~CocoImageButton();
        static CocoImageButton* create();
        //        static CocoImageButton* create(cocos2d::CCDictionary* options);
        //        static CocoImageButton* createWithJson(sp::SPJsonDictionary* options);
        bool init();
        //        virtual bool initWithOptions(cocos2d::CCDictionary* options);
        //        virtual bool initWithOptions_json(sp::SPJsonDictionary* options);
        void initPressState(int state);
        
        void setImageScale9Enable(bool able);
        void setImageScale9Size(float width, float height);
        void setImageTextures(const char* normal, const char* selected, const char* disabled, bool useSpriteFrame = false);
        void setImageTexturesScale9(const char* normal, const char* selected, const char* disabled,
                                    cocos2d::CCRect capInsets,
                                    bool useSpriteFrame = false);
        void setImageNormalTexture(const char* normal, bool useSpriteFrame = false);
        void setImagePressedTexture(const char* selected, bool useSpriteFrame = false);
        void setImageDisabledTexture(const char* disabled, bool useSpriteFrame = false);
        void setImageNormalTextureScale9(const char* normal, cocos2d::CCRect capInsets, bool useSpriteFrame = false);
        void setImagePressedTextureScale9(const char* selected, cocos2d::CCRect capInsets, bool useSpriteFrame = false);
        void setImageDisabledTextureScale9(const char* disabled, cocos2d::CCRect capInsets, bool useSpriteFrame = false);
        void setImageColor(GLubyte r, GLubyte g, GLubyte b);
        void setImageOpacity(GLubyte opacity);
        void setImageFlipX(bool flipX);
        void setImageFlipY(bool flipY);
        CRenderNode* getImageValidNode();
        
        // override
        void setScale9Enable(bool able);
        void setScale9Size(float buttonWidth, float buttonHeight, float imageWidth, float imageHeight);
        void setTextures(const char* buttonNormal, const char* buttonSelected, const char* buttonDisabled,
                         const char* imageNormal, const char* imageSelected, const char* imageDisabled,
                         bool useSpriteFrame = false);
        void setTexturesScale9(const char* buttonNormal, const char* buttonSelected, const char* buttonDisabled,
                               const char* imageNormal, const char* imageSelected, const char* imageDisabled,
                               cocos2d::CCRect buttonCapInsets, cocos2d::CCRect imageCapInsets,
                               bool useSpriteFrame = false);
        void setColor(GLubyte buttonR, GLubyte buttonG, GLubyte buttonB,
                      GLubyte imageR, GLubyte imageG, GLubyte imageB);
        void setOpacity(GLubyte buttonOpacity, GLubyte imageOpacity);
        void setFlipX(bool buttonFlipX, bool imageFlipX);
        void setFlipY(bool buttonFlipY, bool imageFlipY);
        
        void onPressStateChangedToNormal();
        void onPressStateChangedToPressed();
        void onPressStateChangedToDisabled();
        
    protected:
        UIElement* m_pImageNormal;
        UIElement* m_pImageClicked;
        UIElement* m_pImageDisable;
        
        bool m_bScale9Enable;
    };
}

#endif /* defined(__Test__CocoImageButton__) */
