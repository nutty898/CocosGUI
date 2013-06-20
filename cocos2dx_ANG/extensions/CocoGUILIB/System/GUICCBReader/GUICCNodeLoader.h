/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __GUI_CCBI__GUICCNodeLoader__
#define __GUI_CCBI__GUICCNodeLoader__

#include "CCNodeLoader.h"
#include "GUICCBReader.h"

NS_CC_EXT_BEGIN
    
#define GUI_CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(T) virtual T * createCCNode(cocos2d::CCNode * pParent, cocos2d::extension::GUICCBReader * pCCBReader) { \
    return T::create(); \
}
    
#define GUI_CCB_PURE_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(T) virtual T * createCCNode(cocos2d::CCNode * pParent, cocos2d::extension::GUICCBReader * pCCBReader) = 0
    
    
/* Forward declaration. */
class GUICCBReader;

class GUICCNodeLoader : public CCObject
{                
public:
    GUICCNodeLoader();
    virtual ~GUICCNodeLoader();
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GUICCNodeLoader, loader);
    
    virtual CCNode * loadCCNode(CCNode *, GUICCBReader * pCCBReader);
    virtual void parseProperties(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, GUICCBReader * pCCBReader);
    /* pipu cheat */
    virtual CCDictionary* getCustomProperties();
    /**/
    
protected:
    GUI_CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCNode);
    
    virtual CCPoint parsePropTypePosition(CCNode * pNode, CCNode * pParent, GUICCBReader * pCCBReader, const char *pPropertyName);
    virtual CCPoint parsePropTypePoint(CCNode * pNode, CCNode * pParent, GUICCBReader * pCCBReader);
    virtual CCPoint parsePropTypePointLock(CCNode * pNode, CCNode * pParent, GUICCBReader * pCCBReader);
    virtual CCSize parsePropTypeSize(CCNode * pNode, CCNode * pParent, GUICCBReader * pCCBReader);
    virtual float * parsePropTypeScaleLock(CCNode * pNode, CCNode * pParent, GUICCBReader * pCCBReader, const char *pPropertyName);
    virtual float parsePropTypeFloat(CCNode * pNode, CCNode * pParent, GUICCBReader * pCCBReader);
    virtual float parsePropTypeDegrees(CCNode * pNode, CCNode * pParent, GUICCBReader * pCCBReader, const char *pPropertyName);
    virtual float parsePropTypeFloatScale(CCNode * pNode, CCNode * pParent, GUICCBReader * pCCBReader);
    virtual int parsePropTypeInteger(CCNode * pNode, CCNode * pParent, GUICCBReader * pCCBReader);
    virtual int parsePropTypeIntegerLabeled(CCNode * pNode, CCNode * pParent, GUICCBReader * pCCBReader);
    virtual float * parsePropTypeFloatVar(CCNode * pNode, CCNode * pParent, GUICCBReader * pCCBReader);
    virtual bool parsePropTypeCheck(CCNode * pNode, CCNode * pParent, GUICCBReader * pCCBReader, const char *pPropertyName);
    virtual CCSpriteFrame * parsePropTypeSpriteFrame(CCNode * pNode, CCNode * pParent, GUICCBReader * pCCBReader, const char *pPropertyName);
    virtual CCAnimation * parsePropTypeAnimation(CCNode * pNode, CCNode * pParent, GUICCBReader * pCCBReader);
    virtual CCTexture2D * parsePropTypeTexture(CCNode * pNode, CCNode * pParent, GUICCBReader * pCCBReader);
    virtual unsigned char parsePropTypeByte(CCNode * pNode, CCNode * pParent, GUICCBReader * pCCBReader, const char *pPropertyName);
    virtual ccColor3B parsePropTypeColor3(CCNode * pNode, CCNode * pParent, GUICCBReader * pCCBReader, const char *pPropertyName);
    virtual ccColor4F * parsePropTypeColor4FVar(CCNode * pNode, CCNode * pParent, GUICCBReader * pCCBReader);
    virtual bool * parsePropTypeFlip(CCNode * pNode, CCNode * pParent, GUICCBReader * pCCBReader);
    virtual ccBlendFunc parsePropTypeBlendFunc(CCNode * pNode, CCNode * pParent, GUICCBReader * pCCBReader);
    virtual std::string parsePropTypeFntFile(CCNode * pNode, CCNode * pParent, GUICCBReader * pCCBReader);
    virtual std::string parsePropTypeString(CCNode * pNode, CCNode * pParent, GUICCBReader * pCCBReader);
    virtual std::string parsePropTypeText(CCNode * pNode, CCNode * pParent, GUICCBReader * pCCBReader);
    virtual std::string parsePropTypeFontTTF(CCNode * pNode, CCNode * pParent, GUICCBReader * pCCBReader);
    virtual BlockData * parsePropTypeBlock(CCNode * pNode, CCNode * pParent, GUICCBReader * pCCBReader);
    virtual BlockCCControlData * parsePropTypeBlockCCControl(CCNode * pNode, CCNode * pParent, GUICCBReader * pCCBReader);
    virtual CCNode * parsePropTypeCCBFile(CCNode * pNode, CCNode * pParent, GUICCBReader * pCCBReader);
    virtual float * parsePropTypeFloatXY(CCNode * pNode, CCNode * pParent, GUICCBReader * pCCBReader);
    virtual CocoWidget* parsePropTypeCCBFile(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, GUICCBReader * pCCBReader);
    
    
    virtual void onHandlePropTypePosition(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char* pPropertyName, CCPoint pPosition, GUICCBReader * pCCBReader);
    virtual void onHandlePropTypePoint(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char* pPropertyName, CCPoint pPoint, GUICCBReader * pCCBReader);
    virtual void onHandlePropTypePointLock(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char* pPropertyName, CCPoint pPointLock, GUICCBReader * pCCBReader);
    virtual void onHandlePropTypeSize(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char* pPropertyName, CCSize pSize, GUICCBReader * pCCBReader);
    virtual void onHandlePropTypeScaleLock(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char* pPropertyName, float * pScaleLock, GUICCBReader * pCCBReader);
    virtual void onHandlePropTypeFloat(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, GUICCBReader * pCCBReader);
    virtual void onHandlePropTypeDegrees(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pDegrees, GUICCBReader * pCCBReader);
    virtual void onHandlePropTypeFloatScale(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloatScale, GUICCBReader * pCCBReader);
    virtual void onHandlePropTypeInteger(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char* pPropertyName, int pInteger, GUICCBReader * pCCBReader);
    virtual void onHandlePropTypeIntegerLabeled(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char* pPropertyName, int pIntegerLabeled, GUICCBReader * pCCBReader);
    virtual void onHandlePropTypeFloatVar(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char* pPropertyName, float * pFoatVar, GUICCBReader * pCCBReader);
    virtual void onHandlePropTypeFloatXY(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char* pPropertyName, float * pFoatVar, GUICCBReader * pCCBReader);
    
    virtual void onHandlePropTypeCheck(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char* pPropertyName, bool pCheck, GUICCBReader * pCCBReader);
    virtual void onHandlePropTypeSpriteFrame(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char* pPropertyName, CCSpriteFrame * pCCSpriteFrame, GUICCBReader * pCCBReader);
    virtual void onHandlePropTypeAnimation(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char* pPropertyName, CCAnimation * pCCAnimation, GUICCBReader * pCCBReader);
    virtual void onHandlePropTypeTexture(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char* pPropertyName, CCTexture2D * pCCTexture2D, GUICCBReader * pCCBReader);
    virtual void onHandlePropTypeByte(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char* pPropertyName, unsigned char pByte, GUICCBReader * pCCBReader);
    virtual void onHandlePropTypeColor3(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char* pPropertyName, ccColor3B pCCColor3B, GUICCBReader * pCCBReader);
    virtual void onHandlePropTypeColor4FVar(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char* pPropertyName, ccColor4F * pCCColor4FVar, GUICCBReader * pCCBReader);
    virtual void onHandlePropTypeFlip(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char* pPropertyName, bool * pFlip, GUICCBReader * pCCBReader);
    virtual void onHandlePropTypeBlendFunc(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char* pPropertyName, ccBlendFunc pCCBlendFunc, GUICCBReader * pCCBReader);
    virtual void onHandlePropTypeFntFile(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char* pPropertyName, const char * pFntFile, GUICCBReader * pCCBReader);
    virtual void onHandlePropTypeString(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char* pPropertyName, const char * pString, GUICCBReader * pCCBReader);
    virtual void onHandlePropTypeText(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char* pPropertyName, const char * pText, GUICCBReader * pCCBReader);
    virtual void onHandlePropTypeFontTTF(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char* pPropertyName, const char * pFontTTF, GUICCBReader * pCCBReader);
    virtual void onHandlePropTypeBlock(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char* pPropertyName, BlockData * pBlockData, GUICCBReader * pCCBReader);
    virtual void onHandlePropTypeBlockCCControl(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char* pPropertyName, BlockCCControlData * pBlockCCControlData, GUICCBReader * pCCBReader);
    virtual void onHandlePropTypeCCBFile(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char* pPropertyName, CCNode * pCCBFileNode, GUICCBReader * pCCBReader);
    virtual void onHandlePropTypeCCBFile(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char* pPropertyName, CCNode * pCCBFileNode, CocoWidget* pCCBFileWidget,  GUICCBReader * pCCBReader);
    
protected:
    CCDictionary* m_pCustomProperties;
};

NS_CC_EXT_END

#endif /* defined(__GUI_CCBI__GUICCNodeLoader__) */
