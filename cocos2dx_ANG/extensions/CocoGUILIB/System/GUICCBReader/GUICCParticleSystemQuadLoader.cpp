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

#include "GUICCParticleSystemQuadLoader.h"



#define PROPERTY_EMITERMODE "emitterMode"
#define PROPERTY_POSVAR "posVar"
#define PROPERTY_EMISSIONRATE "emissionRate"
#define PROPERTY_DURATION "duration"
#define PROPERTY_TOTALPARTICLES "totalParticles"
#define PROPERTY_LIFE "life"
#define PROPERTY_STARTSIZE "startSize"
#define PROPERTY_ENDSIZE "endSize"
#define PROPERTY_STARTSPIN "startSpin"
#define PROPERTY_ENDSPIN "endSpin"
#define PROPERTY_ANGLE "angle"
#define PROPERTY_STARTCOLOR "startColor"
#define PROPERTY_ENDCOLOR "endColor"
#define PROPERTY_BLENDFUNC "blendFunc"
#define PROPERTY_GRAVITY "gravity"
#define PROPERTY_SPEED "speed"
#define PROPERTY_TANGENTIALACCEL "tangentialAccel"
#define PROPERTY_RADIALACCEL "radialAccel"
#define PROPERTY_TEXTURE "texture"
#define PROPERTY_STARTRADIUS "startRadius"
#define PROPERTY_ENDRADIUS "endRadius"
#define PROPERTY_ROTATEPERSECOND "rotatePerSecond"
    
NS_CC_EXT_BEGIN

void GUICCParticleSystemQuadLoader::onHandlePropTypeIntegerLabeled(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, int pIntegerLabeled, GUICCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_EMITERMODE) == 0) {
        ((CCParticleSystemQuad *)pNode)->setEmitterMode(pIntegerLabeled);
    } else {
        GUICCNodeLoader::onHandlePropTypeIntegerLabeled(pWidget, pNode, pParent, pPropertyName, pIntegerLabeled, pCCBReader);
    }
}

void GUICCParticleSystemQuadLoader::onHandlePropTypePoint(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCPoint pPoint, GUICCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_POSVAR) == 0) {
        ((CCParticleSystemQuad *)pNode)->setPosVar(pPoint);
    } else if(strcmp(pPropertyName, PROPERTY_GRAVITY) == 0) {
        ((CCParticleSystemQuad *)pNode)->setGravity(pPoint);
    } else {
        GUICCNodeLoader::onHandlePropTypePoint(pWidget, pNode, pParent, pPropertyName, pPoint, pCCBReader);
    }
}

void GUICCParticleSystemQuadLoader::onHandlePropTypeFloat(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, float pFloat, GUICCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_EMISSIONRATE) == 0) {
        ((CCParticleSystemQuad *)pNode)->setEmissionRate(pFloat);
    } else if(strcmp(pPropertyName, PROPERTY_DURATION) == 0) {
        ((CCParticleSystemQuad *)pNode)->setDuration(pFloat);
    } else {
        GUICCNodeLoader::onHandlePropTypeFloat(pWidget, pNode, pParent, pPropertyName, pFloat, pCCBReader);
    }
}

void GUICCParticleSystemQuadLoader::onHandlePropTypeInteger(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, int pInteger, GUICCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_TOTALPARTICLES) == 0) {
        ((CCParticleSystemQuad *)pNode)->setTotalParticles(pInteger);
    } else {
        GUICCNodeLoader::onHandlePropTypeInteger(pWidget, pNode, pParent, pPropertyName, pInteger, pCCBReader);
    }
}

void GUICCParticleSystemQuadLoader::onHandlePropTypeFloatVar(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, float * pFloatVar, GUICCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_LIFE) == 0) {
        ((CCParticleSystemQuad *)pNode)->setLife(pFloatVar[0]);
        ((CCParticleSystemQuad *)pNode)->setLifeVar(pFloatVar[1]);
    } else if(strcmp(pPropertyName, PROPERTY_STARTSIZE) == 0) {
        ((CCParticleSystemQuad *)pNode)->setStartSize(pFloatVar[0]);
        ((CCParticleSystemQuad *)pNode)->setStartSizeVar(pFloatVar[1]);
    } else if(strcmp(pPropertyName, PROPERTY_ENDSIZE) == 0) {
        ((CCParticleSystemQuad *)pNode)->setEndSize(pFloatVar[0]);
        ((CCParticleSystemQuad *)pNode)->setEndSizeVar(pFloatVar[1]);
    } else if(strcmp(pPropertyName, PROPERTY_STARTSPIN) == 0) {
        ((CCParticleSystemQuad *)pNode)->setStartSpin(pFloatVar[0]);
        ((CCParticleSystemQuad *)pNode)->setStartSpinVar(pFloatVar[1]);
    } else if(strcmp(pPropertyName, PROPERTY_ENDSPIN) == 0) {
        ((CCParticleSystemQuad *)pNode)->setEndSpin(pFloatVar[0]);
        ((CCParticleSystemQuad *)pNode)->setEndSpinVar(pFloatVar[1]);
    } else if(strcmp(pPropertyName, PROPERTY_ANGLE) == 0) {
        ((CCParticleSystemQuad *)pNode)->setAngle(pFloatVar[0]);
        ((CCParticleSystemQuad *)pNode)->setAngleVar(pFloatVar[1]);
    } else if(strcmp(pPropertyName, PROPERTY_SPEED) == 0) {
        ((CCParticleSystemQuad *)pNode)->setSpeed(pFloatVar[0]);
        ((CCParticleSystemQuad *)pNode)->setSpeedVar(pFloatVar[1]);
    } else if(strcmp(pPropertyName, PROPERTY_TANGENTIALACCEL) == 0) {
        ((CCParticleSystemQuad *)pNode)->setTangentialAccel(pFloatVar[0]);
        ((CCParticleSystemQuad *)pNode)->setTangentialAccelVar(pFloatVar[1]);
    } else if(strcmp(pPropertyName, PROPERTY_RADIALACCEL) == 0) {
        ((CCParticleSystemQuad *)pNode)->setRadialAccel(pFloatVar[0]);
        ((CCParticleSystemQuad *)pNode)->setRadialAccelVar(pFloatVar[1]);
    } else if(strcmp(pPropertyName, PROPERTY_STARTRADIUS) == 0) {
        ((CCParticleSystemQuad *)pNode)->setStartRadius(pFloatVar[0]);
        ((CCParticleSystemQuad *)pNode)->setStartRadiusVar(pFloatVar[1]);
    } else if(strcmp(pPropertyName, PROPERTY_ENDRADIUS) == 0) {
        ((CCParticleSystemQuad *)pNode)->setEndRadius(pFloatVar[0]);
        ((CCParticleSystemQuad *)pNode)->setEndRadiusVar(pFloatVar[1]);
    } else if(strcmp(pPropertyName, PROPERTY_ROTATEPERSECOND) == 0) {
        ((CCParticleSystemQuad *)pNode)->setRotatePerSecond(pFloatVar[0]);
        ((CCParticleSystemQuad *)pNode)->setRotatePerSecondVar(pFloatVar[1]);
    } else {
        GUICCNodeLoader::onHandlePropTypeFloatVar(pWidget, pNode, pParent, pPropertyName, pFloatVar, pCCBReader);
    }
}

void GUICCParticleSystemQuadLoader::onHandlePropTypeColor4FVar(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccColor4F * pCCColor4FVar, GUICCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_STARTCOLOR) == 0) {
        ((CCParticleSystemQuad *)pNode)->setStartColor(pCCColor4FVar[0]);
        ((CCParticleSystemQuad *)pNode)->setStartColorVar(pCCColor4FVar[1]);
    } else if(strcmp(pPropertyName, PROPERTY_ENDCOLOR) == 0) {
        ((CCParticleSystemQuad *)pNode)->setEndColor(pCCColor4FVar[0]);
        ((CCParticleSystemQuad *)pNode)->setEndColorVar(pCCColor4FVar[1]);
    } else {
        GUICCNodeLoader::onHandlePropTypeColor4FVar(pWidget, pNode, pParent, pPropertyName, pCCColor4FVar, pCCBReader);
    }
}

void GUICCParticleSystemQuadLoader::onHandlePropTypeBlendFunc(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccBlendFunc pCCBlendFunc, GUICCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_BLENDFUNC) == 0) {
        ((CCParticleSystemQuad *)pNode)->setBlendFunc(pCCBlendFunc);
    } else {
        GUICCNodeLoader::onHandlePropTypeBlendFunc(pWidget, pNode, pParent, pPropertyName, pCCBlendFunc, pCCBReader);
    }
}

void GUICCParticleSystemQuadLoader::onHandlePropTypeTexture(CocoWidget* pWidget, CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCTexture2D * pCCTexture2D, GUICCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_TEXTURE) == 0) {
        ((CCParticleSystemQuad *)pNode)->setTexture(pCCTexture2D);
    } else {
        GUICCNodeLoader::onHandlePropTypeTexture(pWidget, pNode, pParent, pPropertyName, pCCTexture2D, pCCBReader);
    }
}

NS_CC_EXT_END