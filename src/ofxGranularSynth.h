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
    Grain(std::vector<float>* audioFile, int duration, int blank,int initPos, int channels);
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
    std::vector<float>* mAudioFile;
    bool isDone(){
        return done;
    }
    bool done;
    int mBlank;
    int mWindowSize;
    int mChannels;
};


class ofxGranularSynth : public ofxAudioSynth{
public:
    ofxGranularSynth();
    ofxGranularSynth(string path);
    bool loadWave(string path);
    void audioOut(float *output, int bufferSize, int nChannels);
    vector  <float>* music;

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


    struct wave_header {
        char riff[4];
        uint_least32_t size;
        char wave[4];
        char fmt[4];
        uint_least32_t length;
        uint_least16_t encoding;
        uint_least16_t channels;
        uint_least32_t frequency;
        uint_least32_t byterate;
        uint_least16_t block_align;
        uint_least16_t bits_per_samples;
        char data[4];
        uint_least32_t data_size;
        int NumSamples;

    } wh;

    int mChannel;
private:
    samples getSample();


    vector  <Grain*>mGrains ;
    int     mDuration;
    int     mBlank;
    int     mPosition;
    int     mOverlap;
    float   mVolume;
    int     mInitPos;
};
