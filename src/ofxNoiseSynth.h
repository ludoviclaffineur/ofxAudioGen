#pragma once

#include "ofxAudioSynth.h"

class ofxNoiseSynth : public ofxAudioSynth{
public:
    ofxNoiseSynth(){};
    void audioOut(float * output, int bufferSize, int nChannels);
};
