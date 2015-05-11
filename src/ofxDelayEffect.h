//
//  ofxDelayEffect.h
//  GranularSynth
//
//  Created by Ludovic Laffineur on 11/05/15.
//
//

#pragma once
#include "ofxAudioEffect.h"
#include <deque>

class ofxDelayEffect: public ofxAudioEffect{
public:
    ofxDelayEffect(int delay, float mix, int depth);
    int mDelay;
    float mMix;
    int mDepth;
    samples process(samples sample);

    std::deque<samples> buffer;
    
    //ofxDelayEffect(ofxDelayEffect effect);
};
