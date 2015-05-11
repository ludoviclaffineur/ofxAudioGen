//
//  ofxDelayEffect.cpp
//  GranularSynth
//
//  Created by Ludovic Laffineur on 11/05/15.
//
//

#include "ofxDelayEffect.h"
#include <iostream>

ofxDelayEffect::ofxDelayEffect(int delay, float mix, int depth =10000){
    mDelay = delay;
    mMix = mix;
    mDepth = depth;
}

samples ofxDelayEffect::process(samples sample){
    samples sampleOut;
    sampleOut.left  = sample.left;
    sampleOut.right = sample.right;
    buffer.push_back(sample);
    if (!mByPass) {
        //std::cout << "ON FAIT LE DELAY" <<std::endl;
        sampleOut.right += buffer.begin()->right*mMix;
        sampleOut.left  += buffer.begin()->left*mMix;

    }
    if (buffer.size() > mDepth) {


        buffer.erase(buffer.begin());
        if (buffer.size()>mDepth) {
            buffer.erase(buffer.begin());
        }
    }
    return sampleOut;
}

