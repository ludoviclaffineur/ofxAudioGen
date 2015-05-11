//
//  ofxNoiseSynth.h
//  AudioGenTest
//
//  Created by Ludovic Laffineur on 7/05/15.
//
//

#pragma once
#include "ofxAudioSynth.h"

class ofxNoiseSynth : public ofxAudioSynth{
public:
    ofxNoiseSynth(){};
    void audioOut(float * output, int bufferSize, int nChannels);
};
