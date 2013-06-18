#include "GUICCBReader.h"

#include <algorithm>

#include "GUICCNodeLoader.h"
#include "GUICCNodeLoaderLibrary.h"
#include "GUICCNodeLoaderListener.h"

//#include "CCNodeLoader.h"
//#include "CCNodeLoaderLibrary.h"
//#include "CCNodeLoaderListener.h"
#include "CCBMemberVariableAssigner.h"
#include "CCBSelectorResolver.h"
#include "CCData.h"
#include "CCBAnimationManager.h"
#include "CCBSequenceProperty.h"
#include "CCBKeyframe.h"
#include "CCBValue.h"

#include <ctype.h>

#ifdef __CC_PLATFORM_IOS
#include <UIKit/UIDevice.h>
#endif

#include "CocosGUI.h"
#include "CCControlButton.h"

using namespace std;

namespace cs
{    
    /*************************************************************************
     Implementation of GUICCBReader
     *************************************************************************/
    
    GUICCBReader::GUICCBReader(GUICCNodeLoaderLibrary * pCCNodeLoaderLibrary, CCBMemberVariableAssigner * pCCBMemberVariableAssigner, CCBSelectorResolver * pCCBSelectorResolver, GUICCNodeLoaderListener * pCCNodeLoaderListener)
    : mData(NULL)
    , mBytes(NULL)
    , mCurrentByte(-1)
    , mCurrentBit(-1)
    , mOwner(NULL)
    , mActionManager(NULL)
    , mActionManagers(NULL)
    , mAnimatedProps(NULL)
    , mOwnerOutletNodes(NULL)
    , mNodesWithAnimationManagers(NULL)
    , mAnimationManagersForNodes(NULL)
    , mOwnerCallbackNodes(NULL)
    , hasScriptingOwner(false)
    {
        this->mCCNodeLoaderLibrary = pCCNodeLoaderLibrary;
        this->mCCNodeLoaderLibrary->retain();
        this->mCCBMemberVariableAssigner = pCCBMemberVariableAssigner;
        this->mCCBSelectorResolver = pCCBSelectorResolver;
        this->mCCNodeLoaderListener = pCCNodeLoaderListener;
        init();
    }
    
    GUICCBReader::GUICCBReader(GUICCBReader * pCCBReader)
    : mData(NULL)
    , mBytes(NULL)
    , mCurrentByte(-1)
    , mCurrentBit(-1)
    , mOwner(NULL)
    , mActionManager(NULL)
    , mActionManagers(NULL)
    , mAnimatedProps(NULL)
    , mOwnerOutletNodes(NULL)
    , mNodesWithAnimationManagers(NULL)
    , mAnimationManagersForNodes(NULL)
    , mOwnerCallbackNodes(NULL)
    , hasScriptingOwner(false)
    {
        this->mLoadedSpriteSheets = pCCBReader->mLoadedSpriteSheets;
        this->mCCNodeLoaderLibrary = pCCBReader->mCCNodeLoaderLibrary;
        this->mCCNodeLoaderLibrary->retain();
        
        this->mCCBMemberVariableAssigner = pCCBReader->mCCBMemberVariableAssigner;
        this->mCCBSelectorResolver = pCCBReader->mCCBSelectorResolver;
        this->mCCNodeLoaderListener = pCCBReader->mCCNodeLoaderListener;
        
        this->mOwnerCallbackNames = pCCBReader->mOwnerCallbackNames;
        this->mOwnerCallbackNodes = pCCBReader->mOwnerCallbackNodes;
        this->mOwnerCallbackNodes->retain();
        this->mOwnerOutletNames = pCCBReader->mOwnerOutletNames;
        this->mOwnerOutletNodes = pCCBReader->mOwnerOutletNodes;
        this->mOwnerOutletNodes->retain();
        init();
    }
    
    GUICCBReader::GUICCBReader()
    : mData(NULL)
    , mBytes(NULL)
    , mCurrentByte(-1)
    , mCurrentBit(-1)
    , mOwner(NULL)
    , mActionManager(NULL)
    , mActionManagers(NULL)
    , mCCNodeLoaderLibrary(NULL)
    , mCCNodeLoaderListener(NULL)
    , mCCBMemberVariableAssigner(NULL)
    , mCCBSelectorResolver(NULL)
    , mNodesWithAnimationManagers(NULL)
    , mAnimationManagersForNodes(NULL)
    , hasScriptingOwner(false)
    {
        init();
    }
    
    GUICCBReader::~GUICCBReader() {
        CC_SAFE_RELEASE_NULL(mOwner);
        CC_SAFE_RELEASE_NULL(mData);
        
        this->mCCNodeLoaderLibrary->release();
        
        CC_SAFE_RELEASE(mOwnerOutletNodes);
        mOwnerOutletNames.clear();
        CC_SAFE_RELEASE(mOwnerCallbackNodes);
        mOwnerCallbackNames.clear();
        
        // Clear string cache.
        
        this->mStringCache.clear();
        CC_SAFE_RELEASE(mNodesWithAnimationManagers);
        CC_SAFE_RELEASE(mAnimationManagersForNodes);
        
        setAnimationManager(NULL);
    }
    
    void GUICCBReader::setCCBRootPath(const char* pCCBRootPath)
    {
        CCAssert(pCCBRootPath != NULL, "");
        mCCBRootPath = pCCBRootPath;
    }
    
    const std::string& GUICCBReader::getCCBRootPath() const
    {
        return mCCBRootPath;
    }
    
    bool GUICCBReader::init()
    {
        // Setup action manager
        CCBAnimationManager *pActionManager = new CCBAnimationManager();
        setAnimationManager(pActionManager);
        pActionManager->release();
        
        // Setup resolution scale and container size
        mActionManager->setRootContainerSize(CCDirector::sharedDirector()->getWinSize());
        
        return true;
    }
    
    CCBAnimationManager* GUICCBReader::getAnimationManager()
    {
        return mActionManager;
    }
    
    void GUICCBReader::setAnimationManager(CCBAnimationManager *pAnimationManager)
    {
        CC_SAFE_RELEASE(mActionManager);
        mActionManager = pAnimationManager;
        CC_SAFE_RETAIN(mActionManager);
    }
    
    CCDictionary* GUICCBReader::getAnimationManagers()
    {
        return mActionManagers;
    }
    
    void GUICCBReader::setAnimationManagers(CCDictionary* x)
    {
        mActionManagers = x;
    }
    
    CCBMemberVariableAssigner * GUICCBReader::getCCBMemberVariableAssigner() {
        return this->mCCBMemberVariableAssigner;
    }
    
    CCBSelectorResolver * GUICCBReader::getCCBSelectorResolver() {
        return this->mCCBSelectorResolver;
    }
    
    set<string>* GUICCBReader::getAnimatedProperties()
    {
        return mAnimatedProps;
    }
    
    set<string>& GUICCBReader::getLoadedSpriteSheet()
    {
        return mLoadedSpriteSheets;
    }
    
    CCObject* GUICCBReader::getOwner()
    {
        return mOwner;
    }
    
    CocoWidget* GUICCBReader::widgetFromCCBFile(const char *pCCBFileName)
    {
        return widgetFromCCBFile(pCCBFileName, NULL);
    }
    
    CocoWidget* GUICCBReader::widgetFromCCBFile(const char *pCCBFileName, cocos2d::CCObject *pOwner)
    {
        return widgetFromCCBFile(pCCBFileName, pOwner, CCDirector::sharedDirector()->getWinSize());
    }
    
    CocoWidget* GUICCBReader::widgetFromCCBFile(const char *pCCBFileName, CCObject *pOwner, const CCSize &parentSize)
    {
        if (NULL == pCCBFileName || strlen(pCCBFileName) == 0)
        {
            return NULL;
        }
        
        std::string strCCBFileName(pCCBFileName);
        std::string strSuffix(".ccbi");
        // Add ccbi suffix
        if (!GUICCBReader::endsWith(strCCBFileName.c_str(), strSuffix.c_str()))
        {
            strCCBFileName += strSuffix;
        }
        
        std::string strPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(strCCBFileName.c_str());
        unsigned long size = 0;
        
        unsigned char * pBytes = CCFileUtils::sharedFileUtils()->getFileData(strPath.c_str(), "rb", &size);
        CCData *data = new CCData(pBytes, size);
        CC_SAFE_DELETE_ARRAY(pBytes);
        
        CocoWidget* widget = widgetFromData(data, pOwner, parentSize);
        
        data->release();
        
        return widget;
    }
    
    CocoWidget* GUICCBReader::widgetFromData(CCData *pData, CCObject *pOwner, const CCSize &parentSize)
    {
        mData = pData;
        CC_SAFE_RETAIN(mData);
        mBytes = mData->getBytes();
        mCurrentByte = 0;
        mCurrentBit = 0;
        mOwner = pOwner;
        CC_SAFE_RETAIN(mOwner);
        
        mActionManager->setRootContainerSize(parentSize);
        mActionManager->mOwner = mOwner;
        mOwnerOutletNodes = new CCArray();
        mOwnerCallbackNodes = new CCArray();
        
        CCDictionary* animationManagers = CCDictionary::create();
        CocoWidget* pWidgetGraph = widgetWithCleanUp(true, animationManagers);
        
        if (pWidgetGraph && mActionManager->getAutoPlaySequenceId() != -1 && !jsControlled)
        {
            // Auto play animations
            mActionManager->runAnimationsForSequenceIdTweenDuration(mActionManager->getAutoPlaySequenceId(), 0);
        }
        // Assign actionManagers to userObject
        if(jsControlled) {
            mNodesWithAnimationManagers = new CCArray();
            mAnimationManagersForNodes = new CCArray();
        }
        
        CCDictElement* pElement = NULL;
        CCDICT_FOREACH(animationManagers, pElement)
        {
            CCNode* pNode = (CCNode*)pElement->getIntKey();
            CCBAnimationManager* manager = (CCBAnimationManager*)animationManagers->objectForKey((intptr_t)pNode);
            pNode->setUserObject(manager);
            
            if (jsControlled)
            {
                mNodesWithAnimationManagers->addObject(pNode);
                mAnimationManagersForNodes->addObject(manager);
            }
        }
        
        return pWidgetGraph;
    }
    
    
    
    CCNode* GUICCBReader::readNodeGraphFromFile(const char *pCCBFileName)
    {
        return this->readNodeGraphFromFile(pCCBFileName, NULL);
    }
    
    CCNode* GUICCBReader::readNodeGraphFromFile(const char* pCCBFileName, CCObject* pOwner)
    {
        return this->readNodeGraphFromFile(pCCBFileName, pOwner, CCDirector::sharedDirector()->getWinSize());
    }
    
    CCNode* GUICCBReader::readNodeGraphFromFile(const char *pCCBFileName, CCObject *pOwner, const CCSize &parentSize)
    {
        if (NULL == pCCBFileName || strlen(pCCBFileName) == 0)
        {
            return NULL;
        }
        
        std::string strCCBFileName(pCCBFileName);
        std::string strSuffix(".ccbi");
        // Add ccbi suffix
        if (!GUICCBReader::endsWith(strCCBFileName.c_str(), strSuffix.c_str()))
        {
            strCCBFileName += strSuffix;
        }
        
        std::string strPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(strCCBFileName.c_str());
        unsigned long size = 0;
        
        unsigned char * pBytes = CCFileUtils::sharedFileUtils()->getFileData(strPath.c_str(), "rb", &size);
        CCData *data = new CCData(pBytes, size);
        CC_SAFE_DELETE_ARRAY(pBytes);
        
        CCNode *ret =  this->readNodeGraphFromData(data, pOwner, parentSize);
        
        data->release();
        
        return ret;
    }
    
    CCNode* GUICCBReader::readNodeGraphFromData(CCData *pData, CCObject *pOwner, const CCSize &parentSize)
    {
        mData = pData;
        CC_SAFE_RETAIN(mData);
        mBytes = mData->getBytes();
        mCurrentByte = 0;
        mCurrentBit = 0;
        mOwner = pOwner;
        CC_SAFE_RETAIN(mOwner);
        
        mActionManager->setRootContainerSize(parentSize);
        mActionManager->mOwner = mOwner;
        mOwnerOutletNodes = new CCArray();
        mOwnerCallbackNodes = new CCArray();
        
        CCDictionary* animationManagers = CCDictionary::create();
        CCNode *pNodeGraph = readFileWithCleanUp(true, animationManagers);
        
        if (pNodeGraph && mActionManager->getAutoPlaySequenceId() != -1 && !jsControlled)
        {
            // Auto play animations
            mActionManager->runAnimationsForSequenceIdTweenDuration(mActionManager->getAutoPlaySequenceId(), 0);
        }
        // Assign actionManagers to userObject
        if(jsControlled) {
            mNodesWithAnimationManagers = new CCArray();
            mAnimationManagersForNodes = new CCArray();
        }
        
        CCDictElement* pElement = NULL;
        CCDICT_FOREACH(animationManagers, pElement)
        {
            CCNode* pNode = (CCNode*)pElement->getIntKey();
            CCBAnimationManager* manager = (CCBAnimationManager*)animationManagers->objectForKey((intptr_t)pNode);
            pNode->setUserObject(manager);
            
            if (jsControlled)
            {
                mNodesWithAnimationManagers->addObject(pNode);
                mAnimationManagersForNodes->addObject(manager);
            }
        }
        
        return pNodeGraph;
    }
    
    CCScene* GUICCBReader::createSceneWithNodeGraphFromFile(const char *pCCBFileName)
    {
        return createSceneWithNodeGraphFromFile(pCCBFileName, NULL);
    }
    
    CCScene* GUICCBReader::createSceneWithNodeGraphFromFile(const char *pCCBFileName, CCObject *pOwner)
    {
        return createSceneWithNodeGraphFromFile(pCCBFileName, pOwner, CCDirector::sharedDirector()->getWinSize());
    }
    
    CCScene* GUICCBReader::createSceneWithNodeGraphFromFile(const char *pCCBFileName, CCObject *pOwner, const CCSize &parentSize)
    {
        CCNode *pNode = readNodeGraphFromFile(pCCBFileName, pOwner, parentSize);
        CCScene *pScene = CCScene::create();
        pScene->addChild(pNode);
        
        return pScene;
    }
    
    void GUICCBReader::cleanUpNodeGraph(CCNode *pNode)
    {
        pNode->setUserObject(NULL);
        
        CCObject *pChild = NULL;
        CCARRAY_FOREACH(pNode->getChildren(), pChild)
        {
            cleanUpNodeGraph((CCNode*)pChild);
        }
    }
    
    CocoWidget* GUICCBReader::widgetWithCleanUp(bool bCleanUp, CCDictionary *am)
    {
        if (! readHeader())
        {
            return NULL;
        }
        
        if (! readStringCache())
        {
            return NULL;
        }
        
        if (! readSequences())
        {
            return NULL;
        }
        
        setAnimationManagers(am);
        
        CocoWidget* pWidget = widget(NULL, NULL);
        
        mActionManagers->setObject(mActionManager, intptr_t(pWidget));
        
        if (bCleanUp)
        {
            cleanUpNodeGraph(pWidget->getContainerNode());
        }
        
        return pWidget;
    }
    
    CCNode* GUICCBReader::readFileWithCleanUp(bool bCleanUp, CCDictionary* am)
    {
        if (! readHeader())
        {
            return NULL;
        }
        
        if (! readStringCache())
        {
            return NULL;
        }
        
        if (! readSequences())
        {
            return NULL;
        }
        
        setAnimationManagers(am);
        
        CCNode *pNode = readNodeGraph(NULL);
        
        mActionManagers->setObject(mActionManager, intptr_t(pNode));
        
        if (bCleanUp)
        {
            cleanUpNodeGraph(pNode);
        }
        
        return pNode;
    }
    
    bool GUICCBReader::readStringCache() {
        int numStrings = this->readInt(false);
        
        for(int i = 0; i < numStrings; i++) {
            this->mStringCache.push_back(this->readUTF8());
        }
        
        return true;
    }
    
    bool GUICCBReader::readHeader()
    {
        /* If no bytes loaded, don't crash about it. */
        if(this->mBytes == NULL) {
            return false;
        }
        
        /* Read magic bytes */
        int magicBytes = *((int*)(this->mBytes + this->mCurrentByte));
        this->mCurrentByte += 4;
        
        if(CC_SWAP_INT32_LITTLE_TO_HOST(magicBytes) != 'ccbi') {
            return false;
        }
        
        /* Read version. */
        int version = this->readInt(false);
        if(version != kCCBVersion) {
            CCLog("WARNING! Incompatible ccbi file version (file: %d reader: %d)", version, kCCBVersion);
            return false;
        }
        
        // Read JS check
        jsControlled = this->readBool();
        mActionManager->jsControlled = jsControlled;
        
        return true;
    }
    
    unsigned char GUICCBReader::readByte() {
        unsigned char byte = this->mBytes[this->mCurrentByte];
        this->mCurrentByte++;
        return byte;
    }
    
    bool GUICCBReader::readBool() {
        return 0 == this->readByte() ? false : true;
    }
    
    std::string GUICCBReader::readUTF8()
    {
        std::string ret;
        
        int b0 = this->readByte();
        int b1 = this->readByte();
        
        int numBytes = b0 << 8 | b1;
        
        char* pStr = (char*)malloc(numBytes+1);
        memcpy(pStr, mBytes+mCurrentByte, numBytes);
        pStr[numBytes] = '\0';
        ret = pStr;
        free(pStr);
        
        mCurrentByte += numBytes;
        
        return ret;
    }
    
    bool GUICCBReader::getBit() {
        bool bit;
        unsigned char byte = *(this->mBytes + this->mCurrentByte);
        if(byte & (1 << this->mCurrentBit)) {
            bit = true;
        } else {
            bit = false;
        }
        
        this->mCurrentBit++;
        
        if(this->mCurrentBit >= 8) {
            this->mCurrentBit = 0;
            this->mCurrentByte++;
        }
        
        return bit;
    }
    
    void GUICCBReader::alignBits() {
        if(this->mCurrentBit) {
            this->mCurrentBit = 0;
            this->mCurrentByte++;
        }
    }
    
    int GUICCBReader::readInt(bool pSigned) {
        // Read encoded int
        int numBits = 0;
        while(!this->getBit()) {
            numBits++;
        }
        
        long long current = 0;
        for(int a = numBits - 1; a >= 0; a--) {
            if(this->getBit()) {
                current |= 1LL << a;
            }
        }
        current |= 1LL << numBits;
        
        int num;
        if(pSigned) {
            int s = current % 2;
            if(s) {
                num = (int)(current / 2);
            } else {
                num = (int)(-current / 2);
            }
        } else {
            num = current - 1;
        }
        
        this->alignBits();
        
        return num;
    }
    
    
    float GUICCBReader::readFloat() {
        unsigned char type = this->readByte();
        
        switch (type) {
            case kCCBFloat0:
                return 0;
            case kCCBFloat1:
                return 1;
            case kCCBFloatMinus1:
                return -1;
            case kCCBFloat05:
                return 0.5f;
            case kCCBFloatInteger:
                return (float)this->readInt(true);
            default:
            {
                /* using a memcpy since the compiler isn't
                 * doing the float ptr math correctly on device.
                 * TODO still applies in C++ ? */
                unsigned char* pF = (this->mBytes + this->mCurrentByte);
                float f = 0;
                
                // N.B - in order to avoid an unaligned memory access crash on 'memcpy()' the the (void*) casts of the source and
                // destination pointers are EXTREMELY important for the ARM compiler.
                //
                // Without a (void*) cast, the ARM compiler makes the assumption that the float* pointer is naturally aligned
                // according to it's type size (aligned along 4 byte boundaries) and thus tries to call a more optimized
                // version of memcpy() which makes this alignment assumption also. When reading back from a file of course our pointers
                // may not be aligned, hence we need to avoid the compiler making this assumption. The (void*) cast serves this purpose,
                // and causes the ARM compiler to choose the slower, more generalized (unaligned) version of memcpy()
                //
                // For more about this compiler behavior, see:
                // http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.faqs/ka3934.html
                memcpy((void*) &f, (const void*) pF, sizeof(float));
                
                this->mCurrentByte += sizeof(float);
                return f;
            }
        }
    }
    
    std::string GUICCBReader::readCachedString() {
        int n = this->readInt(false);
        return this->mStringCache[n];
    }
    
    CCNode * GUICCBReader::readNodeGraph(CCNode * pParent) {
        /* Read class name. */
        std::string className = this->readCachedString();
        
        std::string jsControlledName;
        
        if(jsControlled) {
            jsControlledName = this->readCachedString();
        }
        
        // Read assignment type and name
        int memberVarAssignmentType = this->readInt(false);
        std::string memberVarAssignmentName;
        if(memberVarAssignmentType != kCCBTargetTypeNone) {
            memberVarAssignmentName = this->readCachedString();
        }
        
        GUICCNodeLoader *ccNodeLoader = this->mCCNodeLoaderLibrary->getCCNodeLoader(className.c_str());
        if (! ccNodeLoader)
        {
            CCLog("no corresponding node loader for %s", className.c_str());
            return NULL;
        }
        
        CCNode *node = ccNodeLoader->loadCCNode(pParent, this);        
        
        // Set root node
        if (! mActionManager->getRootNode())
        {
            mActionManager->setRootNode(node);
        }
        
        // Assign controller
        if(jsControlled && node == mActionManager->getRootNode())
        {
            mActionManager->setDocumentControllerName(jsControlledName);
        }
        
        // Read animated properties
        CCDictionary *seqs = CCDictionary::create();
        mAnimatedProps = new set<string>();
        
        int numSequence = readInt(false);
        for (int i = 0; i < numSequence; ++i)
        {
            int seqId = readInt(false);
            CCDictionary *seqNodeProps = CCDictionary::create();
            
            int numProps = readInt(false);
            
            for (int j = 0; j < numProps; ++j)
            {
                CCBSequenceProperty *seqProp = new CCBSequenceProperty();
                seqProp->autorelease();
                
                seqProp->setName(readCachedString().c_str());
                seqProp->setType(readInt(false));
                mAnimatedProps->insert(seqProp->getName());
                
                int numKeyframes = readInt(false);
                
                for (int k = 0; k < numKeyframes; ++k)
                {
                    CCBKeyframe *keyframe = readKeyframe(seqProp->getType());
                    
                    seqProp->getKeyframes()->addObject(keyframe);
                }
                
                seqNodeProps->setObject(seqProp, seqProp->getName());
            }
            
            seqs->setObject(seqNodeProps, seqId);
        }
        
        if (seqs->count() > 0)
        {
            mActionManager->addNode(node, seqs);
        }
        
        // Read properties
        ccNodeLoader->parseProperties(NULL, node, pParent, this);
        
        bool isCCBFileNode = dynamic_cast<CCBFile*>(node);
        // Handle sub ccb files (remove middle node)
        if (isCCBFileNode)
        {
            CCBFile *ccbFileNode = (CCBFile*)node;
            
            CCNode *embeddedNode = ccbFileNode->getCCBFileNode();
            embeddedNode->setPosition(ccbFileNode->getPosition());
            embeddedNode->setRotation(ccbFileNode->getRotation());
            embeddedNode->setScaleX(ccbFileNode->getScaleX());
            embeddedNode->setScaleY(ccbFileNode->getScaleY());
            embeddedNode->setTag(ccbFileNode->getTag());
            embeddedNode->setVisible(true);
            embeddedNode->ignoreAnchorPointForPosition(ccbFileNode->isIgnoreAnchorPointForPosition());
            
            mActionManager->moveAnimationsFromNode(ccbFileNode, embeddedNode);
            
            ccbFileNode->setCCBFileNode(NULL);
            
            node = embeddedNode;
        }
        
#ifdef CCB_ENABLE_JAVASCRIPT
        /*
         if (memberVarAssignmentType && memberVarAssignmentName && ![memberVarAssignmentName isEqualToString:@""])
         {
         [[JSCocoa sharedController] setObject:node withName:memberVarAssignmentName];
         }*/
#else
        if (memberVarAssignmentType != kCCBTargetTypeNone)
        {
            if(!jsControlled)
            {
                CCObject * target = NULL;
                if(memberVarAssignmentType == kCCBTargetTypeDocumentRoot)
                {
                    target = mActionManager->getRootNode();
                }
                else if(memberVarAssignmentType == kCCBTargetTypeOwner)
                {
                    target = this->mOwner;
                }
                
                if(target != NULL)
                {
                    CCBMemberVariableAssigner * targetAsCCBMemberVariableAssigner = dynamic_cast<CCBMemberVariableAssigner *>(target);
                    
                    bool assigned = false;
                    if (memberVarAssignmentType != kCCBTargetTypeNone)
                    {
                        if(targetAsCCBMemberVariableAssigner != NULL) {
                            assigned = targetAsCCBMemberVariableAssigner->onAssignCCBMemberVariable(target, memberVarAssignmentName.c_str(), node);
                        }
                        
                        if(!assigned && this->mCCBMemberVariableAssigner != NULL) {
                            assigned = this->mCCBMemberVariableAssigner->onAssignCCBMemberVariable(target, memberVarAssignmentName.c_str(), node);
                        }
                    }
                }
            }
            else
            {
                if(memberVarAssignmentType == kCCBTargetTypeDocumentRoot) {
                    mActionManager->addDocumentOutletName(memberVarAssignmentName);
                    mActionManager->addDocumentOutletNode(node);
                } else {
                    mOwnerOutletNames.push_back(memberVarAssignmentName);
                    mOwnerOutletNodes->addObject(node);
                }
            }
        }
        
        // Assign custom properties.
        if (ccNodeLoader->getCustomProperties()->count() > 0) {
            
            bool customAssigned = false;
            
            if(!jsControlled)
            {
                CCObject * target = node;
                if(target != NULL)
                {
                    CCBMemberVariableAssigner * targetAsCCBMemberVariableAssigner = dynamic_cast<CCBMemberVariableAssigner *>(target);
                    if(targetAsCCBMemberVariableAssigner != NULL) {
                        
                        CCDictionary* pCustomPropeties = ccNodeLoader->getCustomProperties();
                        CCDictElement* pElement;
                        CCDICT_FOREACH(pCustomPropeties, pElement)
                        {
                            customAssigned = targetAsCCBMemberVariableAssigner->onAssignCCBCustomProperty(target, pElement->getStrKey(), (CCBValue*)pElement->getObject());
                            
                            if(!customAssigned && this->mCCBMemberVariableAssigner != NULL)
                            {
                                customAssigned = this->mCCBMemberVariableAssigner->onAssignCCBCustomProperty(target, pElement->getStrKey(), (CCBValue*)pElement->getObject());
                            }
                        }
                    }
                }
            }
        }
        
#endif // CCB_ENABLE_JAVASCRIPT
        
        delete mAnimatedProps;
        mAnimatedProps = NULL;
        
        /* Read and add children. */
        int numChildren = this->readInt(false);
        for(int i = 0; i < numChildren; i++) {
            CCNode * child = this->readNodeGraph(node);
            node->addChild(child);
        }
        
        // FIX ISSUE #1860: "onNodeLoaded will be called twice if ccb was added as a CCBFile".
        // If it's a sub-ccb node, skip notification to CCNodeLoaderListener since it will be
        // notified at LINE #734: CCNode * child = this->readNodeGraph(node);
        if (!isCCBFileNode) {
            // Call onNodeLoaded
            GUICCNodeLoaderListener * nodeAsCCNodeLoaderListener = dynamic_cast<GUICCNodeLoaderListener *>(node);
            if(nodeAsCCNodeLoaderListener != NULL) {
                nodeAsCCNodeLoaderListener->onNodeLoaded(node, ccNodeLoader);
            } else if(this->mCCNodeLoaderListener != NULL) {
                this->mCCNodeLoaderListener->onNodeLoaded(node, ccNodeLoader);
            }
        }
        return node;
    }
    
    CCBKeyframe* GUICCBReader::readKeyframe(int type)
    {
        CCBKeyframe *keyframe = new CCBKeyframe();
        keyframe->autorelease();
        
        keyframe->setTime(readFloat());
        
        int easingType = readInt(false);
        float easingOpt = 0;
        CCObject *value = NULL;
        
        if (easingType == kCCBKeyframeEasingCubicIn
            || easingType == kCCBKeyframeEasingCubicOut
            || easingType == kCCBKeyframeEasingCubicInOut
            || easingType == kCCBKeyframeEasingElasticIn
            || easingType == kCCBKeyframeEasingElasticOut
            || easingType == kCCBKeyframeEasingElasticInOut)
        {
            easingOpt = readFloat();
        }
        keyframe->setEasingType(easingType);
        keyframe->setEasingOpt(easingOpt);
        
        if (type == kCCBPropTypeCheck)
        {
            value = CCBValue::create(readBool());
        }
        else if (type == kCCBPropTypeByte)
        {
            value = CCBValue::create(readByte());
        }
        else if (type == kCCBPropTypeColor3)
        {
            int r = readByte();
            int g = readByte();
            int b = readByte();
            
            ccColor3B c = ccc3(r,g,b);
            value = ccColor3BWapper::create(c);
        }
        else if (type == kCCBPropTypeDegrees)
        {
            value = CCBValue::create(readFloat());
        }
        else if (type == kCCBPropTypeScaleLock || type == kCCBPropTypePosition
                 || type == kCCBPropTypeFloatXY)
        {
            float a = readFloat();
            float b = readFloat();
            
            value = CCArray::create(CCBValue::create(a),
                                    CCBValue::create(b),
                                    NULL);
        }
        else if (type == kCCBPropTypeSpriteFrame)
        {
            std::string spriteSheet = readCachedString();
            std::string spriteFile = readCachedString();
            
            CCSpriteFrame* spriteFrame;
            
            if (spriteSheet.length() == 0)
            {
                spriteFile = mCCBRootPath + spriteFile;
                CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(spriteFile.c_str());
                CCRect bounds = CCRectMake(0, 0, texture->getContentSize().width, texture->getContentSize().height);
                spriteFrame = CCSpriteFrame::createWithTexture(texture, bounds);
            }
            else
            {
                spriteSheet = mCCBRootPath + spriteSheet;
                CCSpriteFrameCache* frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
                
                // Load the sprite sheet only if it is not loaded
                if (mLoadedSpriteSheets.find(spriteSheet) == mLoadedSpriteSheets.end())
                {
                    frameCache->addSpriteFramesWithFile(spriteSheet.c_str());
                    mLoadedSpriteSheets.insert(spriteSheet);
                }
                
                spriteFrame = frameCache->spriteFrameByName(spriteFile.c_str());
            }
            value = spriteFrame;
        }
        
        keyframe->setValue(value);
        
        return  keyframe;
    }
    
    
    bool GUICCBReader::readCallbackKeyframesForSeq(CCBSequence* seq) {
        int numKeyframes = readInt(false);
        if(!numKeyframes) return true;
        
        CCBSequenceProperty* channel = new CCBSequenceProperty();
        channel->autorelease();
        
        for(int i = 0; i < numKeyframes; ++i) {
            
            float time = readFloat();
            std::string callbackName = readCachedString();
            
            int callbackType = readInt(false);
            
            CCArray* value = CCArray::create();
            value->addObject(CCString::create(callbackName));
            value->addObject(CCString::createWithFormat("%d", callbackType));
            
            CCBKeyframe* keyframe = new CCBKeyframe();
            keyframe->autorelease();
            
            keyframe->setTime(time);
            keyframe->setValue(value);
            
            if(jsControlled) {
                string callbackIdentifier;
                mActionManager->getKeyframeCallbacks()->addObject(CCString::createWithFormat("%d:%s",callbackType, callbackName.c_str()));
            }
            
            channel->getKeyframes()->addObject(keyframe);
        }
        
        seq->setCallbackChannel(channel);
        
        return true;
    }
    
    bool GUICCBReader::readSoundKeyframesForSeq(CCBSequence* seq) {
        int numKeyframes = readInt(false);
        if(!numKeyframes) return true;
        
        CCBSequenceProperty* channel = new CCBSequenceProperty();
        channel->autorelease();
        
        for(int i = 0; i < numKeyframes; ++i) {
            
            float time = readFloat();
            std::string soundFile = readCachedString();
            float pitch = readFloat();
            float pan = readFloat();
            float gain = readFloat();
            
            CCArray* value = CCArray::create();
            
            value->addObject(CCString::create(soundFile));
            value->addObject(CCString::createWithFormat("%f", pitch));
            value->addObject(CCString::createWithFormat("%f", pan));
            value->addObject(CCString::createWithFormat("%f", gain));
            
            CCBKeyframe* keyframe = new CCBKeyframe();
            keyframe->setTime(time);
            keyframe->setValue(value);
            channel->getKeyframes()->addObject(keyframe);
            keyframe->release();
        }
        
        seq->setSoundChannel(channel);
        
        return true;
    }
    
    CocoWidget* GUICCBReader::widget()
    {
        return widget(NULL, NULL);
    }
    
    CocoWidget* GUICCBReader::widget(CocoWidget* pWidgetParent, CCNode *pParent)
    {
        /* Read class name. */
        std::string className = this->readCachedString();
        
        m_strClassName = "";
        
        /* get base class from cocos2d */
        if (strcmp(className.c_str(), "CCBFile") == 0            
            || strcmp(className.c_str(), "CCParticleSystemQuad") == 0)
        {
            m_strClassName = className;
        }
        else
        {
            CCString* classType = dynamic_cast<CCString*>(COCOUISYSTEM->getClassType(className.c_str()));
            className = classType->getCString();
        }
        /**/
        
        std::string jsControlledName;
        
        if(jsControlled) {
            jsControlledName = this->readCachedString();
        }
        
        // Read assignment type and name
        int memberVarAssignmentType = this->readInt(false);
        std::string memberVarAssignmentName;
        if(memberVarAssignmentType != kCCBTargetTypeNone) {
            memberVarAssignmentName = this->readCachedString();
        }
        
        GUICCNodeLoader *ccNodeLoader = this->mCCNodeLoaderLibrary->getCCNodeLoader(className.c_str());
        if (! ccNodeLoader)
        {
            CCLog("no corresponding node loader for %s", className.c_str());
            return NULL;
        }                
        
        /* create widget */
        CocoWidget* widget = NULL;
        if (strcmp(className.c_str(), "CCNode") == 0)
        {
            widget = CocoWidget::create();
        }
        else if (strcmp(className.c_str(), "CCLayer") == 0
                 || strcmp(className.c_str(), "CCLayerColor") == 0
                 || strcmp(className.c_str(), "CCLayerGradient") == 0
                 || strcmp(className.c_str(), "CCMenu") == 0)
        {
            widget = CocoPanel::create();
        }
        else if (strcmp(className.c_str(), "CCScrollView") == 0)
        {
            widget = CocoScrollView::create();
        }
        else if (strcmp(className.c_str(), "CCSprite") == 0)
        {
            widget = CocoImageView::create();
        }
        else if (strcmp(className.c_str(), "CCScale9Sprite") == 0)
        {
            widget = CocoImageViewScale9::create();
        }
        else if (strcmp(className.c_str(), "CCLabelTTF") == 0)
        {
            widget = CocoTextArea::create();
        }
        else if (strcmp(className.c_str(), "CCLabelBMFont") == 0)
        {
            widget = CocoLabelBMFont::create();
        }
        else if (strcmp(className.c_str(), "CCMenuItemImage") == 0)
        {
            widget = CocoButton::create();
        }
        else if (strcmp(className.c_str(), "CCControlButton") == 0)
        {
            widget = CocoControlButton::create();
        }
        else if (strcmp(className.c_str(), "CCBFile") == 0                 
                 || strcmp(className.c_str(), "CCParticleSystemQuad") == 0)
        {
            
        }        
        /**/
        
        /* create CCNode */
        CCNode *node = NULL;
        if (strcmp(className.c_str(), "CCBFile") == 0            
            || strcmp(className.c_str(), "CCParticleSystemQuad") == 0)
        {
            node = ccNodeLoader->loadCCNode(pParent, this);
        }
        else
        {
            node = widget->getContainerNode();
        }
        /**/
        
        // Set root node
        if (! mActionManager->getRootNode())
        {
            mActionManager->setRootNode(node);
        }
        
        // Assign controller
        if(jsControlled && node == mActionManager->getRootNode())
        {
            mActionManager->setDocumentControllerName(jsControlledName);
        }
        
        // Read animated properties
        CCDictionary *seqs = CCDictionary::create();
        mAnimatedProps = new set<string>();
        
        int numSequence = readInt(false);
        for (int i = 0; i < numSequence; ++i)
        {
            int seqId = readInt(false);
            CCDictionary *seqNodeProps = CCDictionary::create();
            
            int numProps = readInt(false);
            
            for (int j = 0; j < numProps; ++j)
            {
                CCBSequenceProperty *seqProp = new CCBSequenceProperty();
                seqProp->autorelease();
                
                seqProp->setName(readCachedString().c_str());
                seqProp->setType(readInt(false));
                mAnimatedProps->insert(seqProp->getName());                
                
                int numKeyframes = readInt(false);
                
                for (int k = 0; k < numKeyframes; ++k)
                {
                    CCBKeyframe *keyframe = readKeyframe(seqProp->getType());
                    
                    seqProp->getKeyframes()->addObject(keyframe);
                }
                
                seqNodeProps->setObject(seqProp, seqProp->getName());
            }
            
            seqs->setObject(seqNodeProps, seqId);
        }
        
        if (seqs->count() > 0)
        {
            mActionManager->addNode(node, seqs);
        }
        
        // Read properties
        if (strcmp(className.c_str(), "CCBFile") == 0)
        {
            ccNodeLoader->parseProperties(pWidgetParent, node, pParent, this);
        }
        else
        {
            ccNodeLoader->parseProperties(widget, node, pParent, this);
        }
        
        /* set widget property (must call behind CCNode create) */
        if (strcmp(className.c_str(), "CCLayer") == 0
            || strcmp(className.c_str(), "CCLayerColor") == 0
            || strcmp(className.c_str(), "CCLayerGradient") == 0
            || strcmp(className.c_str(), "CCMenu") == 0)
        {
            setPropsForPanelFromCCBFile(widget);
        }
        else if (strcmp(className.c_str(), "CCScrollView") == 0)
        {
            setPropsForScrollViewCCBFile(widget);
        }
        else if (strcmp(className.c_str(), "CCSprite") == 0)
        {
            setPropsForImageViewFromCCBFile(widget);
        }
        else if (strcmp(className.c_str(), "CCScale9Sprite") == 0)
        {
            setPropsForImageViewScale9FromCCBFile(widget);
        }
        else if (strcmp(className.c_str(), "CCLabelTTF") == 0)
        {
            setPropsForTextAreaFromCCBFile(widget);
        }
        else if (strcmp(className.c_str(), "CCLabelBMFont") == 0)
        {
            setPropsForLabelBMFontFromCCBFile(widget);
        }
        else if (strcmp(className.c_str(), "CCMenuItemImage") == 0)
        {
            setPropsForButtonFromCCBFile(widget);
        }
        else if (strcmp(className.c_str(), "CCControlButton") == 0)
        {
            setPropsForControlButtonFromCCBFile(widget);
        }
        /**/
        
        bool isCCBFileNode = dynamic_cast<CCBFile*>(node);
        // Handle sub ccb files (remove middle node)
        if (isCCBFileNode)
        {
            CCBFile *ccbFileNode = (CCBFile*)node;
            
            CCNode *embeddedNode = ccbFileNode->getCCBFileNode();
            embeddedNode->setPosition(ccbFileNode->getPosition());
            embeddedNode->setRotation(ccbFileNode->getRotation());
            embeddedNode->setScaleX(ccbFileNode->getScaleX());
            embeddedNode->setScaleY(ccbFileNode->getScaleY());
            embeddedNode->setTag(ccbFileNode->getTag());
            embeddedNode->setVisible(true);
            embeddedNode->ignoreAnchorPointForPosition(ccbFileNode->isIgnoreAnchorPointForPosition());
            
            mActionManager->moveAnimationsFromNode(ccbFileNode, embeddedNode);
            
            ccbFileNode->setCCBFileNode(NULL);
            
            node = embeddedNode;
        }
        
#ifdef CCB_ENABLE_JAVASCRIPT
        /*
         if (memberVarAssignmentType && memberVarAssignmentName && ![memberVarAssignmentName isEqualToString:@""])
         {
         [[JSCocoa sharedController] setObject:node withName:memberVarAssignmentName];
         }*/
#else
        if (memberVarAssignmentType != kCCBTargetTypeNone)
        {
            if(!jsControlled)
            {
                CCObject * target = NULL;
                if(memberVarAssignmentType == kCCBTargetTypeDocumentRoot)
                {
                    target = mActionManager->getRootNode();
                }
                else if(memberVarAssignmentType == kCCBTargetTypeOwner)
                {
                    target = this->mOwner;
                }
                
                if(target != NULL)
                {
                    CCBMemberVariableAssigner * targetAsCCBMemberVariableAssigner = dynamic_cast<CCBMemberVariableAssigner *>(target);
                    
                    bool assigned = false;
                    if (memberVarAssignmentType != kCCBTargetTypeNone)
                    {
                        if(targetAsCCBMemberVariableAssigner != NULL) {
                            assigned = targetAsCCBMemberVariableAssigner->onAssignCCBMemberVariable(target, memberVarAssignmentName.c_str(), node);
                        }
                        
                        if(!assigned && this->mCCBMemberVariableAssigner != NULL) {
                            assigned = this->mCCBMemberVariableAssigner->onAssignCCBMemberVariable(target, memberVarAssignmentName.c_str(), node);
                        }
                    }
                }
            }
            else
            {
                if(memberVarAssignmentType == kCCBTargetTypeDocumentRoot) {
                    mActionManager->addDocumentOutletName(memberVarAssignmentName);
                    mActionManager->addDocumentOutletNode(node);
                } else {
                    mOwnerOutletNames.push_back(memberVarAssignmentName);
                    mOwnerOutletNodes->addObject(node);
                }
            }
        }
        
        // Assign custom properties.
        if (ccNodeLoader->getCustomProperties()->count() > 0) {
            
            bool customAssigned = false;
            
            if(!jsControlled)
            {
                CCObject * target = node;
                if(target != NULL)
                {
                    CCBMemberVariableAssigner * targetAsCCBMemberVariableAssigner = dynamic_cast<CCBMemberVariableAssigner *>(target);
                    if(targetAsCCBMemberVariableAssigner != NULL) {
                        
                        CCDictionary* pCustomPropeties = ccNodeLoader->getCustomProperties();
                        CCDictElement* pElement;
                        CCDICT_FOREACH(pCustomPropeties, pElement)
                        {
                            customAssigned = targetAsCCBMemberVariableAssigner->onAssignCCBCustomProperty(target, pElement->getStrKey(), (CCBValue*)pElement->getObject());
                            
                            if(!customAssigned && this->mCCBMemberVariableAssigner != NULL)
                            {
                                customAssigned = this->mCCBMemberVariableAssigner->onAssignCCBCustomProperty(target, pElement->getStrKey(), (CCBValue*)pElement->getObject());
                            }
                        }
                    }
                }
            }
        }
        
#endif // CCB_ENABLE_JAVASCRIPT
        
        delete mAnimatedProps;
        mAnimatedProps = NULL;
        
        /* Read and add children. */
        /* Read and add widget */
        int numChildren = this->readInt(false);
        for(int i = 0; i < numChildren; i++) {
            CocoWidget* child = this->widget(widget, node);
            if (!child)
            {
                continue;
            }
            widget->addChild(child);
        }
        
        // FIX ISSUE #1860: "onNodeLoaded will be called twice if ccb was added as a CCBFile".
        // If it's a sub-ccb node, skip notification to CCNodeLoaderListener since it will be
        // notified at LINE #734: CCNode * child = this->readNodeGraph(node);
        if (!isCCBFileNode) {
            // Call onNodeLoaded
            GUICCNodeLoaderListener * nodeAsCCNodeLoaderListener = dynamic_cast<GUICCNodeLoaderListener *>(node);
            if(nodeAsCCNodeLoaderListener != NULL) {
                nodeAsCCNodeLoaderListener->onNodeLoaded(node, ccNodeLoader);
            } else if(this->mCCNodeLoaderListener != NULL) {
                this->mCCNodeLoaderListener->onNodeLoaded(node, ccNodeLoader);
            }
        }
        return widget;
    }
    
    void GUICCBReader::setPropsForWidgetFromCCBFile(CocoWidget *widget)
    {
        CCNode* node = widget->getContainerNode();
        
        widget->setName("default");        
        widget->setUseMergedTexture(false);
        widget->setWidgetZOrder(node->getZOrder());
    }                    

    void GUICCBReader::setPropsForContainerWidgetFromCCBFile(CocoWidget *widget)
    {
        setPropsForWidgetFromCCBFile(widget);
        
        CocoContainerWidget* containerWidget = dynamic_cast<CocoContainerWidget*>(widget);        
        containerWidget->setClipAble(true);                
    }
    
    void GUICCBReader::setPropsForPanelFromCCBFile(CocoWidget *widget)
    {
        setPropsForContainerWidgetFromCCBFile(widget);
        
        CocoPanel* panel = dynamic_cast<CocoPanel*>(widget);        
                
        float w = widget->getRect().size.width;
        float h = widget->getRect().size.height;
        panel->setSize(w, h);
        
        panel->setBackGroundColorEnable(true);
    }
    
    void GUICCBReader::setPropsForScrollViewCCBFile(CocoWidget *widget)
    {
        setPropsForPanelFromCCBFile(widget);
    }
    
    void GUICCBReader::setPropsForImageViewFromCCBFile(CocoWidget *widget)
    {
        setPropsForWidgetFromCCBFile(widget);        
    }
    
    void GUICCBReader::setPropsForImageViewScale9FromCCBFile(CocoWidget *widget)
    {
        setPropsForWidgetFromCCBFile(widget);
    }
    
    void GUICCBReader::setPropsForTextAreaFromCCBFile(CocoWidget *widget)
    {
        setPropsForWidgetFromCCBFile(widget);
    }
    
    void GUICCBReader::setPropsForLabelBMFontFromCCBFile(CocoWidget *widget)
    {
        setPropsForWidgetFromCCBFile(widget);
    }
    
    void GUICCBReader::setPropsForButtonFromCCBFile(CocoWidget *widget)
    {
        setPropsForWidgetFromCCBFile(widget);
    }
    
    void GUICCBReader::setPropsForControlButtonFromCCBFile(CocoWidget *widget)
    {
        setPropsForWidgetFromCCBFile(widget);                
    }
    
    CCNode * GUICCBReader::readNodeGraph() {
        return this->readNodeGraph(NULL);
    }
    
    bool GUICCBReader::readSequences()
    {
        CCArray *sequences = mActionManager->getSequences();
        
        int numSeqs = readInt(false);
        
        for (int i = 0; i < numSeqs; i++)
        {
            CCBSequence *seq = new CCBSequence();
            seq->autorelease();
            
            seq->setDuration(readFloat());
            seq->setName(readCachedString().c_str());
            seq->setSequenceId(readInt(false));
            seq->setChainedSequenceId(readInt(true));
            
            if(!readCallbackKeyframesForSeq(seq)) return false;
            if(!readSoundKeyframesForSeq(seq)) return false;
            
            sequences->addObject(seq);
        }
        
        mActionManager->setAutoPlaySequenceId(readInt(true));
        return true;
    }
    
    std::string GUICCBReader::lastPathComponent(const char* pPath) {
        std::string path(pPath);
        size_t slashPos = path.find_last_of("/");
        if(slashPos != std::string::npos) {
            return path.substr(slashPos + 1, path.length() - slashPos);
        }
        return path;
    }
    
    std::string GUICCBReader::deletePathExtension(const char* pPath) {
        std::string path(pPath);
        size_t dotPos = path.find_last_of(".");
        if(dotPos != std::string::npos) {
            return path.substr(0, dotPos);
        }
        return path;
    }
    
    std::string GUICCBReader::toLowerCase(const char* pString) {
        std::string copy(pString);
        std::transform(copy.begin(), copy.end(), copy.begin(), ::tolower);
        return copy;
    }
    
    bool GUICCBReader::endsWith(const char* pString, const char* pEnding) {
        std::string string(pString);
        std::string ending(pEnding);
        if(string.length() >= ending.length()) {
            return (string.compare(string.length() - ending.length(), ending.length(), ending) == 0);
        } else {
            return false;
        }
    }
    
    bool GUICCBReader::isJSControlled() {
        return jsControlled;
    }
    
    void GUICCBReader::addOwnerCallbackName(std::string name) {
        mOwnerCallbackNames.push_back(name);
    }
    
    void GUICCBReader::addOwnerCallbackNode(CCNode *node) {
        mOwnerCallbackNodes->addObject(node);
    }
    
    
    void GUICCBReader::addDocumentCallbackName(std::string name) {
        mActionManager->addDocumentCallbackName(name);
    }
    
    void GUICCBReader::addDocumentCallbackNode(CCNode *node) {
        mActionManager->addDocumentCallbackNode(node);
    }
    
    
    CCArray* GUICCBReader::getOwnerCallbackNames() {
        CCArray* pRet = CCArray::createWithCapacity(mOwnerCallbackNames.size());
        std::vector<std::string>::iterator it = mOwnerCallbackNames.begin();
        for (; it != mOwnerCallbackNames.end(); ++it)
        {
            pRet->addObject(CCString::create(*it));
        }
        
        return pRet;
    }
    
    CCArray* GUICCBReader::getOwnerCallbackNodes() {
        return mOwnerCallbackNodes;
    }
    
    CCArray* GUICCBReader::getOwnerOutletNames() {
        CCArray* pRet = CCArray::createWithCapacity(mOwnerOutletNames.size());
        std::vector<std::string>::iterator it = mOwnerOutletNames.begin();
        for (; it != mOwnerOutletNames.end(); ++it)
        {
            pRet->addObject(CCString::create(*it));
        }
        return pRet;
    }
    
    CCArray* GUICCBReader::getOwnerOutletNodes() {
        return mOwnerOutletNodes;
    }
    
    CCArray* GUICCBReader::getNodesWithAnimationManagers() {
        return mNodesWithAnimationManagers;
    }
    
    CCArray* GUICCBReader::getAnimationManagersForNodes() {
        return mAnimationManagersForNodes;
    }
    
    /************************************************************************
     Static functions
     ************************************************************************/
    
    static float __ccbResolutionScale = 1.0f;
    
    float GUICCBReader::getResolutionScale()
    {
        return __ccbResolutionScale;
    }
    
    void GUICCBReader::setResolutionScale(float scale)
    {
        __ccbResolutionScale = scale;
    }
}