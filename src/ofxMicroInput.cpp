#include "ofxMicroInput.h"

//--------------------------------------------------------------
ofxMicroInput::ofxMicroInput(){
    soundStream.setup(2, 1, SAMPLE_RATE, BUFFER_SIZE, 4);
    soundStream.setOutput(this);
    soundStream.setInput(this);
    for (int i =0; i<199680; i++) {
        bufferIntermediate[i] = 0.0f;
    }

}

//--------------------------------------------------------------
void ofxMicroInput::audioIn(float *input, int bufferSize, int nChannels){
    std::memcpy(&bufferIntermediate[currentPos], input, sizeof(float)*bufferSize*nChannels);
    currentPos += bufferSize*nChannels;
    currentPos = currentPos%199680;
}

//--------------------------------------------------------------
void ofxMicroInput::audioOut(float *output, int bufferSize, int nChannels){
    int startPositionToRead = currentPos-BUFFER_SIZE;
    if (startPositionToRead<0) startPositionToRead = 199680-BUFFER_SIZE;
    for (int i =0; i<bufferSize; i++) {
        samples s;
        s.left = bufferIntermediate[startPositionToRead+i];
        s.right = bufferIntermediate[startPositionToRead+i];
        for (int i = 0; i<mEffects.size(); i++) {
            s=mEffects[i]->process(s);
        }
        output[i*nChannels    ] = s.left;
        output[i*nChannels + 1] = s.right;
    }
}

//--------------------------------------------------------------
void ofxMicroInput::addEffect(ofxAudioEffect* effect){
    mEffects.push_back(effect);
}

//--------------------------------------------------------------
void ofxMicroInput::play(){
    soundStream.start();
}

//--------------------------------------------------------------
void ofxMicroInput::stop(){
    soundStream.stop();
}