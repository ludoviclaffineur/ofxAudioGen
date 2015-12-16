#pragma once

#include "ofxAudioEffect.h"

class ofxAudioSynth : public ofBaseSoundOutput{
public:
    ofxAudioSynth():ofBaseSoundOutput(){};
    virtual void init();
    void play();
    void stop();
    virtual void audioOut(float * output, int bufferSize, int nChannels)=0;
    virtual void addEffect(ofxAudioEffect* effect);
    vector <ofxAudioEffect*> mEffects;
protected:
    ofSoundStream soundStream;

};


