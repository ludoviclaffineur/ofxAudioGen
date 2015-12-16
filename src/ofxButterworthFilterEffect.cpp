#include "ofxButterworthFilterEffect.h"

//--------------------------------------------------------------
ofxButterworthFilterEffect::ofxButterworthFilterEffect(int bandWidth, int sampleRate, int cutoffFrequency, ButterworthFilterType type){
    mByPass = false;
    mSampleRate = sampleRate;
    mBandWidth = bandWidth;
    mCutoffFrequency = cutoffFrequency;
    mType = type;
    computeParameters();
}

//--------------------------------------------------------------
ofxButterworthFilterEffect::ofxButterworthFilterEffect(){
    mByPass = false;
    mSampleRate = 44100;
    mBandWidth = 1000;
    mCutoffFrequency = 2000;
    mType = LP;
    computeParameters();
}

//--------------------------------------------------------------
void ofxButterworthFilterEffect::computeParameters(){
    if (mType==LP){
        mLambda = 1.0 / tan(M_PI*mCutoffFrequency/mSampleRate);
        mA0 = 1.0/(1 + SQRT2*mLambda+ (mLambda*mLambda));
        mA1 = 2.0 * mA0;
        mA2 = mA0;
        mB1 = 2.0 * mA0 * (1.0 - (mLambda*mLambda));
        mB2 = mA0*(1.0 - SQRT2*mLambda + (mLambda*mLambda));
    }
    if (mType==HP){
        float ratio = (float)mCutoffFrequency/(float)mSampleRate;
        mLambda = tan(M_PI*mCutoffFrequency/mSampleRate);
        mA0 = 1.0/(1.0 + SQRT2*mLambda+ (mLambda*mLambda));
        mA1 = -2.0 * mA0;
        mA2 = mA0;
        mB1 = 2.0 * mA0 * ((mLambda*mLambda) - 1.0);
        mB2 = mA0*(1.0 - SQRT2*mLambda + mLambda*mLambda);
    }
    if (mType==BP){
        mLambda = 1.0 / tan(M_PI*mBandWidth/mSampleRate);
        mFi = 2.0 * cos(2.0 * M_PI * mCutoffFrequency/mSampleRate);
        mA0 = 1.0/(1.0 + mLambda);
        mA1 = 0.0;
        mA2 = - mA0;
        mB1 = - mA0 * mLambda * mFi;
        mB2 = mA0 * (mLambda - 1);
    }
    if (mType==BR){
        mLambda = tan(M_PI*mBandWidth/mSampleRate);
        mFi = 2.0 * cos(2.0 * M_PI * mCutoffFrequency/mSampleRate);
        mA0 = 1.0/(1.0 + mLambda);
        mA1 = - mA0 * mFi;
        mA2 = mA0;
        mB1 = - mA0 * mFi;
        mB2 = mA0 * (1 - mLambda);
    }
}

//--------------------------------------------------------------
void ofxButterworthFilterEffect::setCutoffFrequency(int cutoffFrequency){
    mCutoffFrequency = cutoffFrequency;
    computeParameters();
}

//--------------------------------------------------------------
samples ofxButterworthFilterEffect::process(samples sample){
    samples sampleOut;
    sampleOut.left  = sample.left;
    sampleOut.right = sample.right;
    if (!mByPass) {
        mXn_2.right = mXn_1.right;
        mXn_1.right = mXn.right;
        mXn.right = sampleOut.right;
        mYn_2.right = mYn_1.right;
        mYn_1.right = mYn.right;
        mYn.right = (mA0*mXn.right + mA1*mXn_1.right + mA2*mXn_2.right - mB1*mYn_1.right - mB2*mYn_2.right);
        mXn_2.left = mXn_1.left;
        mXn_1.left = mXn.left;
        mXn.left = sampleOut.left;
        mYn_2.left = mYn_1.left;
        mYn_1.left = mYn.left;
        mYn.left = (mA0*mXn.left + mA1*mXn_1.left + mA2*mXn_2.left - mB1*mYn_1.left - mB2*mYn_2.left);
        sampleOut.right = mYn.right;
        sampleOut.left  = mYn.left;
    }
    return sampleOut;
}

