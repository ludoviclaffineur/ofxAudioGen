//
//  ofxSawSynth.cpp
//  AudioGenTest
//
//  Created by Ludovic Laffineur on 7/05/15.
//
//

#include "ofxSawSynth.h"


void ofxSawSynth::audioOut(float *output, int bufferSize, int nChannels){
    
    for (int i = 0; i < bufferSize; i++){
        mLastSample += mIncrement;
        if (mLastSample>1) {
            mLastSample = -1;
        }
        output[i*nChannels    ] = mLastSample;
        output[i*nChannels + 1] = mLastSample;
    }
}