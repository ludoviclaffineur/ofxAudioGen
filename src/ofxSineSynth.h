#pragma once

#include "ofxAudioSynth.h"

class ofxSineSynth : public ofxAudioSynth{
public:
    ofxSineSynth();
    void audioOut(float * output, int bufferSize, int nChannels);

private:
    const float TABLE_SIZE = 1470.0f;
    int mCurrentSamplePosition;
    float mTime;
    float mRate;
    float mPhaseOffset;
    unsigned int mIndex;
    float mAlpha;
    float mFreq = 440.0;
    vector<float> table;
    float mIncrement = (TABLE_SIZE * mFreq)/ 44100.0;
};


