//
//  ofxAudioSynth.h
//  AudioGenTest
//
//  Created by Ludovic Laffineur on 7/05/15.
//
//

#pragma once

#include "ofMain.h"
#include "ofxAudioEffect.h"

class ofxAudioSynth : public ofBaseSoundOutput{
public:
    ofxAudioSynth():ofBaseSoundOutput(){};
    virtual void init();
    void play();
    void stop();
    virtual void audioRequested(float * output, int bufferSize, int nChannels)=0;
    virtual void addEffect(ofxAudioEffect effect);
protected:
    ofSoundStream soundStream;
    vector <ofxAudioEffect> mEffects;
};


