#pragma once

#include "ofxAudioSynth.h"


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

    float bufferIntermediate[199680]; // Mais pourquoi donc ce chiffre ?
    int currentPos=0;

};
