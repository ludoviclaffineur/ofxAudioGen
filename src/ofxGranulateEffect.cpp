#include "ofxGranulateEffect.h"

//--------------------------------------------------------------
ofxGranulateEffect::ofxGranulateEffect(){
    mChannel = 1;
    mDuration = 3000;
    mBlank    = 0;
    mPosition = 0;
    mOverlap  = 200;
    mVolume   = 0.9f;
}

//--------------------------------------------------------------
void ofxGranulateEffect::setBuffer(float* buffer, int size){
    bufferGranulate = buffer;
    mSize = size;
}


//--------------------------------------------------------------
samples ofxGranulateEffect::process(samples sample){

    samples sampleResult;
    if(mGrains.size()==0 || mPosition++ > (mGrains[mGrains.size()-1]->mDuration + mGrains[mGrains.size()-1]->mBlank - mOverlap)){
        if(mDuration >mOverlap){
            mGrains.push_back(new GrainEffect(bufferGranulate, mDuration, mBlank, mInitPos,mChannel, mSize ));
        }
        mPosition = 0.0f;
    }
    if (mGrains.size()!=0) {
        if (mGrains[0]->isDone()){
            delete *mGrains.begin();
            mGrains.erase(mGrains.begin());
        }
        for(int i =0; i<mGrains.size();i++) {
            samples retour = mGrains[i]->getSample();
            sampleResult.right += retour.right;
            sampleResult.left  += retour.left;
        }
    }
    else{
        sampleResult.right = sampleResult.left = 0.0f;
    }
    return sampleResult;
}

//--------------------------------------------------------------
int ofxGranulateEffect::getDuration(){
    return mDuration;
}


//--------------------------------------------------------------
void ofxGranulateEffect::setDuration(float duration){
    if(duration>0){
        float oldDuration = mDuration;
        mDuration = duration*8000;
        if (mDuration>=mSize) {
            mDuration = mSize - 300;
        }
    }
}

//--------------------------------------------------------------
int ofxGranulateEffect::getOverlap(){
    return mOverlap;
}

//--------------------------------------------------------------
void ofxGranulateEffect::setBlank(float blank){
    mBlank = blank * 10000;
}

//--------------------------------------------------------------
int ofxGranulateEffect::getBlank(){
    return mBlank;
}

//--------------------------------------------------------------
void ofxGranulateEffect::setOverlap(float overlap){
    mOverlap = overlap * mDuration;
}

//--------------------------------------------------------------
float ofxGranulateEffect::getVolume(){
    return mVolume;
}

//--------------------------------------------------------------
void ofxGranulateEffect::setVolume(float volume){
    mVolume = volume;
}

//--------------------------------------------------------------
void ofxGranulateEffect::setInitPosition(int initPos){
    mInitPos = initPos;
}

//--------------------------------------------------------------
int ofxGranulateEffect::getInitPosition(){
    return mInitPos;
}


// GRAINS
//--------------------------------------------------------------
GrainEffect::GrainEffect(float* audioFile, int duration,int blank, int initPos, int channels, int size){
    mDuration = duration;
    mCurrentPostion=0;
    mWindowSize = size-mDuration;
    mInitPostion = (0 + rand()%mWindowSize);
    if(mInitPostion%channels == 1){
        mInitPostion --;
    }
    mAudioFile = new float [channels*mDuration];
    std::copy(&audioFile[mInitPostion], &audioFile[mInitPostion+mDuration*channels], mAudioFile);
    mInitPostion = 0;
    
    mBlank = blank;
    done = false;
    mChannels = channels;
}

//--------------------------------------------------------------
GrainEffect::~GrainEffect(){
    delete [] mAudioFile;
}

//--------------------------------------------------------------
samples GrainEffect::getSample(){
    samples current_sample;
    float sample = 0.0f;
    if (mCurrentPostion <mDuration) {
        float hanningCoeff = 0.5 - 0.5* cosf(2*M_PI *(float)mCurrentPostion/(float)(mDuration));
        if(mChannels == 1){
            current_sample.right = mAudioFile[mInitPostion+mCurrentPostion]*hanningCoeff;
            current_sample.left  = mAudioFile[mInitPostion+mCurrentPostion]*hanningCoeff;
        }
        else if(mChannels == 2){
            current_sample.left = mAudioFile[mInitPostion+mCurrentPostion*mChannels    ]*hanningCoeff;
            current_sample.right  = mAudioFile[mInitPostion+mCurrentPostion*mChannels + 1]*hanningCoeff;
        }

    }
    else if(mCurrentPostion< mDuration+ mBlank){
        current_sample.left = 0.0f;
        current_sample.right = 0.0f;
    }
    else{
        done = true;
    }
    mCurrentPostion++;
    return current_sample;
}