//
//  ofxMicroInput.h
//  GranularSynth
//
//  Created by Ludovic Laffineur on 12/05/15.
//
//

#pragma once

#include "ofMain.h"
#include "ofxAudioEffect.h"

class ofxMicroInput: public ofBaseSoundOutput, public ofBaseSoundInput{
public:
    ofxMicroInput();

    void audioOut(float * output, int bufferSize, int nChannels);
    void audioIn(float * input, int bufferSize, int nChannels);
    void addEffect(ofxAudioEffect* effect);
    void play();
    void stop();

    ofSoundStream soundStream;
    std::vector<ofxAudioEffect*> mEffects;

    deque<float> bufferIntermediate;
};
