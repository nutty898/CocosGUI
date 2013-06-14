//
//  CocoLabelBMFont.cpp
//  Test
//
//  Created by cai wenzhi on 13-6-7.
//
//

#include "CocoLabelBMFont.h"

namespace cs {
    
    CocoLabelBMFont::CocoLabelBMFont()
    {
        
    }
    
    CocoLabelBMFont::~CocoLabelBMFont()
    {
        
    }
    
    CocoLabelBMFont* CocoLabelBMFont::create()
    {
        CocoLabelBMFont* widget = new CocoLabelBMFont();
        if (widget && widget->init()) {
            return widget;
        }
        CC_SAFE_DELETE(widget);
        return NULL;
    }
    
    bool CocoLabelBMFont::init()
    {
        if (CocoWidget::init()) {
            this->m_pLabelBMFont = cocos2d::CCLabelBMFont::create();
            this->m_pCCRenderNode->addChild(this->m_pLabelBMFont);
            return true;
        }
        return false;
    }
    
    void CocoLabelBMFont::setFntFile(const char *fileName)
    {
        this->m_pLabelBMFont->initWithString("", fileName);
    }
    
    void CocoLabelBMFont::setText(const char* value)
    {
        this->m_pLabelBMFont->setString(value);
    }
    
    const char* CocoLabelBMFont::getStringValue()
    {
        return this->m_pLabelBMFont->getString();
    }
}