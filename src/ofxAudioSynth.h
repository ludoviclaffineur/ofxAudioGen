//
//  ofxAudioSynth.h
//  AudioGenTest
//
//  Created by Ludovic Laffineur on 7/05/15.
//
//

#pragma once

#include "ofMain.h"

class ofxAudioSynth : public ofBaseSoundOutput{
public:
    void setup();
    virtual void audioRequested(float * output, int bufferSize, int nChannels)=0;
protected:
    vector <float> lAudio;
    vector <float> rAudio;
    ofSoundStream soundStream;
};


