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
    virtual void setup();
    void play();
    void stop();
    virtual void audioRequested(float * output, int bufferSize, int nChannels)=0;
    virtual void addEffect(ofxAudioEffect* effect);
protected:
    vector <float> lAudio;
    vector <float> rAudio;
    ofSoundStream soundStream;
    vector <ofxAudioEffect*> mEffects;
};


