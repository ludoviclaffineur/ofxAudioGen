//
//  ofxAudioSynth.cpp
//  AudioGenTest
//
//  Created by Ludovic Laffineur on 7/05/15.
//
//

#include "ofxAudioSynth.h"
#include "ofxAudioGenConstants.h"

void ofxAudioSynth::setup(){

    soundStream.setup(2, 0, SAMPLE_RATE, BUFFER_SIZE, 4);
    soundStream.setOutput(this);
    //soundStream.
    cout<<"SOUNDSTREAM SETUP"<<endl;

}

