#pragma once

#include "ofxAudioEffect.h"

class ofxDelayEffect: public ofxAudioEffect{
public:
    ofxDelayEffect(int delay, float mix, int depth);
    ofxDelayEffect();
    int mDelay;
    float mMix;
    int mDepth;
    samples process(samples sample);
    std::deque<samples> buffer;
};
