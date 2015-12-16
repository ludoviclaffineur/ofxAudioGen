#include "ofxAudioSynth.h"

//--------------------------------------------------------------
void ofxAudioSynth::init(){
    soundStream.setup(2, 0, SAMPLE_RATE, BUFFER_SIZE, 4);
    soundStream.setOutput(this);
}

//--------------------------------------------------------------
void ofxAudioSynth::addEffect(ofxAudioEffect* effect){
    mEffects.push_back(effect);
}

//--------------------------------------------------------------
void ofxAudioSynth::stop(){
    soundStream.stop();
}

//--------------------------------------------------------------
void ofxAudioSynth::play(){
    soundStream.start();
}