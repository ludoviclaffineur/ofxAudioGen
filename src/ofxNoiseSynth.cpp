//
//  ofxNoiseSynth.cpp
//  AudioGenTest
//
//  Created by Ludovic Laffineur on 7/05/15.
//
//

#include "ofxNoiseSynth.h"

void ofxNoiseSynth::audioOut(float *output, int bufferSize, int nChannels){
    for (int i = 0; i < bufferSize; i++){
        output[i*nChannels    ] = ofRandom(-1, 1);
        output[i*nChannels + 1] = ofRandom(-1, 1);
    }
}