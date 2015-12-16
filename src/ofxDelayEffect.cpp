#include "ofxDelayEffect.h"

//--------------------------------------------------------------
ofxDelayEffect::ofxDelayEffect(int delay, float mix, int depth =10000){
    mDelay = delay;  // A quoi ça sert ??????????
    mMix = mix;
    mDepth = depth;
}

//--------------------------------------------------------------
ofxDelayEffect::ofxDelayEffect(){
    mDelay = 1000;
    mMix = 0.9;
    mDepth = 10000; 
}

//--------------------------------------------------------------
samples ofxDelayEffect::process(samples sample){
    samples sampleOut;
    sampleOut.left  = sample.left;
    sampleOut.right = sample.right;
    buffer.push_back(sample);
    if (!mByPass) {
        sampleOut.right += buffer.begin()->right*mMix;
        sampleOut.left  += buffer.begin()->left*mMix;
    }
    if (buffer.size() > mDepth) {
        buffer.erase(buffer.begin());
        if (buffer.size() > mDepth) {
            buffer.erase(buffer.begin());
        }
    }
    return sampleOut;
}

