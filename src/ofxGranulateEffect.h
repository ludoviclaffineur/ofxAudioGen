//
//  ofxGranulateEffect.h
//  MicroInput
//
//  Created by Ludovic Laffineur on 12/05/15.
//
//

#pragma once
#include "ofxAudioEffect.h"

#include "ofMain.h"

#include <deque>
#include <math.h>
#include <iostream>
class GrainEffect{
public:
    GrainEffect(float* audioFile, int duration, int blank,int initPos, int channels, int size);
    ~GrainEffect();
    samples getSample();
    enum ENVELOPE{
        ATTACK=0,
        DELAY,
        RELEASE,
        STOP,
    };
    int mEnvelope;
    int mDuration;
    int mCurrentPostion;
    int mInitPostion;
    const int nbrSamplesFade = 20;
    float* mAudioFile;
    bool isDone(){
        return done;
    }
    bool done;
    int mBlank;
    int mWindowSize;
    int mChannels;


};


class ofxGranulateEffect : public ofxAudioEffect{
public:
    ofxGranulateEffect();
    samples process(samples sample);

    void setInitPosition(int delay);
    int getInitPosition();

    int getDuration();
    void setDuration(float duration);

    int getOverlap();
    void setOverlap(float overlap);

    float getVolume();
    void setVolume(float volume);

    void setBlank(float blank);
    int getBlank();

    float* bufferGranulate;

    void setBuffer(float* buffer, int size);

private:
    std::deque <GrainEffect*> mGrains ;
    int     mDuration;
    int     mBlank;
    int     mPosition;
    int     mOverlap;
    float   mVolume;
    int     mInitPos;
    int     mChannel;
    int mSize;
};