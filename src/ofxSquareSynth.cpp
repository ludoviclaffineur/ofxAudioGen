//
//  ofxSquareSynth.cpp
//  AudioGenTest
//
//  Created by Ludovic Laffineur on 7/05/15.
//
//

#include "ofxSquareSynth.h"




void ofxSquareSynth::audioRequested(float *output, int bufferSize, int nChannels){
    static int sampleOut = 1;
    static int  i =0;
    for (int j = 0; j < bufferSize; j++){
        if (i>halfPeriod) {
            i=0;
            if(sampleOut == -1){
                sampleOut = 1;
            }
            else{
                sampleOut = -1;
            }
        }
        i++;
        output[j*nChannels    ] = sampleOut;
        output[j*nChannels + 1] = sampleOut;
    }
}