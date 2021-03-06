#pragma once

#include "ofxAudioSynth.h"


class ofxSquareSynth : public ofxAudioSynth{
public:
    ofxSquareSynth(){};
    void audioOut(float *output, int bufferSize, int nChannels);

private:
    float mFreq = 440.0;
    float halfPeriod = 22050.0/mFreq;
};
