//
//  ofxSineSynth.cpp
//  AudioGenTest
//
//  Created by Ludovic Laffineur on 7/05/15.
//
//

#include "ofxSineSynth.h"

ofxSineSynth::ofxSineSynth(): mTime(0.0), mRate(1.0), mPhaseOffset(0.0),mCurrentSamplePosition(0){
    float temp = 1.0/TABLE_SIZE;
    for (int i =0; i<=TABLE_SIZE; i++) {
        table.push_back(sin( (TWO_PI * i)/TABLE_SIZE));
    }
    //std::cout << table[0] << "  " << table[table.size()-1] <<endl;
}

void ofxSineSynth::audioOut(float *output, int bufferSize, int nChannels){
    for (int i=0; i<bufferSize; i++) {
        if (mCurrentSamplePosition > TABLE_SIZE) {
            mCurrentSamplePosition = mCurrentSamplePosition - TABLE_SIZE - 1;
        }
        output[i*nChannels    ] = table[mCurrentSamplePosition];
        output[i*nChannels + 1] = table[mCurrentSamplePosition];

        mCurrentSamplePosition += mIncrement;
    }
}