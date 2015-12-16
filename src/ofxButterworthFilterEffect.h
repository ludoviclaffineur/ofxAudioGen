#pragma once

#include "ofxAudioEffect.h"

class ofxButterworthFilterEffect: public ofxAudioEffect{
public:
    ofxButterworthFilterEffect(int, int, int, ButterworthFilterType);
    ofxButterworthFilterEffect();
    void setCutoffFrequency(int);
    void computeParameters();
    samples process(samples);
private:
    int mSampleRate, mBandWidth, mCutoffFrequency;
    ButterworthFilterType mType;
    float mLambda, mFi, mA0, mA1, mA2, mB1, mB2, mGain;
    samples mXn, mXn_1, mXn_2;
    samples mYn, mYn_1, mYn_2;

};
