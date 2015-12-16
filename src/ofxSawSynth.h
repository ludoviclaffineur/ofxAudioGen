#pragma once

#include "ofxAudioSynth.h"

class ofxSawSynth : public ofxAudioSynth{
public:
    ofxSawSynth(){};
    void audioOut(float * output, int bufferSize, int nChannels);
private:
    float mFreq = 500;
    //todo
    //int currentSample=0;
    float mLastSample = 0.0f;
    float mIncrement = mFreq/44100.0;
};
