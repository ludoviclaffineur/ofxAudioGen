//
//  ofxMicroInput.cpp
//  GranularSynth
//
//  Created by Ludovic Laffineur on 12/05/15.
//
//

#include "ofxMicroInput.h"

#include "ofxAudioGenConstants.h"


ofxMicroInput::ofxMicroInput(){
    soundStream.setup(2, 1, SAMPLE_RATE, BUFFER_SIZE, 4);
    
    soundStream.setOutput(this);
    soundStream.setInput(this);

}

void ofxMicroInput::audioIn(float *input, int bufferSize, int nChannels){
    //cout<< "INPUT " <<endl;
    for (int i=0; i<bufferSize; i++) {
        bufferIntermediate.push_back(input[i]);
    }



}

void ofxMicroInput::audioOut(float *output, int bufferSize, int nChannels){
    for (int i =0; i<bufferSize; i++) {
        samples s;
        s.left = s.right = bufferIntermediate.front();;
        for (int i = 0; i<mEffects.size(); i++) {
            s=mEffects[i]->process(s);
        }

        output[i*nChannels    ] = s.left;
        output[i*nChannels + 1] = s.right;



        bufferIntermediate.erase(bufferIntermediate.begin());
    }
}

void ofxMicroInput::addEffect(ofxAudioEffect* effect){
    mEffects.push_back(effect);
}

void ofxMicroInput::play(){
    soundStream.start();
}

void ofxMicroInput::stop(){
    soundStream.stop();
    
}