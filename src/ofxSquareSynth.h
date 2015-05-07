//
//  ofxSquareSynth.h
//  AudioGenTest
//
//  Created by Ludovic Laffineur on 7/05/15.
//
//

#pragma once

#include "ofxAudioSynth.h"


class ofxSquareSynth : public ofxAudioSynth{
public:
    ofxSquareSynth(){};
    void audioRequested(float *output, int bufferSize, int nChannels);

private:
    float mFreq = 440.0;
    float halfPeriod = 22050.0/mFreq;
};
