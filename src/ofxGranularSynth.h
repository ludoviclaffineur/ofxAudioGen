//
//  ofxGranularSynth.h
//  AudioGenTest
//
//  Created by Ludovic Laffineur on 7/05/15.
//
//

#pragma once

#include "ofxAudioSynth.h"

class Grain{
public:
    Grain(std::vector<float>* audioFile, int duration, int blank,int initPos);
    float getSample();
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
    std::vector<float>* mAudioFile;
    bool isDone(){
        return done;
    }
    bool done;
    int mBlank;
    int mWindowSize;
};


class ofxGranularSynth : public ofxAudioSynth{
public:
    ofxGranularSynth();
    ofxGranularSynth(string path);
    bool loadWave(string path);
    void audioRequested(float *output, int bufferSize, int nChannels);
    vector  <float>* music;

    void setInitPosition(int delay);
    int getInitPosition();

    int getDuration();
    void setDuration(int duration);

    int getOverlap();
    void setOverlap(int overlap);

    float getVolume();
    void setVolume(float volume);

    void setBlank(int blank);
    int getBlank();
    
private:
    float getSample();


    vector  <Grain*>mGrains ;
    int     mDuration;
    int     mBlank;
    int     mPosition;
    int     mOverlap;
    float   mVolume;
    int     mInitPos;
};
