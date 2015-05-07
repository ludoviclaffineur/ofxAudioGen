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
        if (i>1000) {
            i=0;
            sampleOut = -sampleOut;
        }
        i++;
        output[j*2    ] = sampleOut;
        output[j*2 + 1] = sampleOut;
    }
    //cout<<"ICIIII"<<endl;

}