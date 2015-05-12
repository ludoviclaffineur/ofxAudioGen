//
//  ofxGranulateEffect.cpp
//  MicroInput
//
//  Created by Ludovic Laffineur on 12/05/15.
//
//

#include "ofxGranulateEffect.h"

ofxGranulateEffect::ofxGranulateEffect():bufferGranulate(200000,0.0f){
    mChannel = 2;
    mDuration = 1500;
    mBlank    = 0;
    mPosition = 0;
    mOverlap  = 200;
    mVolume   = 0.9f;
}

samples ofxGranulateEffect::process(samples sample){
    bufferGranulate.push_back(sample.left);
    bufferGranulate.push_back(sample.right);

    samples sampleResult;
    if(mGrains.size()==0 || mPosition++ > (mGrains[mGrains.size()-1]->mDuration + mGrains[mGrains.size()-1]->mBlank - mOverlap)){
        if(mDuration >mOverlap){
            mGrains.push_back(new GrainEffect(bufferGranulate, mDuration, mBlank, mInitPos,mChannel));
        }
        mPosition = 0.0f;
    }
    if (mGrains.size()!=0) {
        if (mGrains[0]->isDone()){
            //std::cout<<"DELETE"<<std::endl;
            delete *mGrains.begin();
            mGrains.erase(mGrains.begin());
        }
        for(int i =0; i<mGrains.size();i++) {
            samples retour = mGrains[i]->getSample();
            sampleResult.right += retour.right;
            sampleResult.left += retour.left;
        }
    }
    else{
        sampleResult.right = sampleResult.left = 0.0f;
    }
    bufferGranulate.pop_front();
    bufferGranulate.pop_front();
    return sampleResult;
}

int ofxGranulateEffect::getDuration(){
    return mDuration;
}




void ofxGranulateEffect::setDuration(float duration){
    if(duration>0){
        float oldDuration = mDuration;
        mDuration = duration*14000;
        setOverlap((float)mOverlap/(float)oldDuration);
    }
}

int ofxGranulateEffect::getOverlap(){
    return mOverlap;
}

void ofxGranulateEffect::setBlank(float blank){
    mBlank = blank * bufferGranulate.size();
}

int ofxGranulateEffect::getBlank(){
    return mBlank;
}

void ofxGranulateEffect::setOverlap(float overlap){
    mOverlap = overlap * mDuration;

}

float ofxGranulateEffect::getVolume(){
    return mVolume;
}

void ofxGranulateEffect::setVolume(float volume){
    mVolume = volume;
}

void ofxGranulateEffect::setInitPosition(int initPos){
    //std::cout<<initPos<<std::endl;
    mInitPos = initPos;
}
int ofxGranulateEffect::getInitPosition(){
    return mInitPos;
}





//GRAIN EFFECT



// GRAINS

GrainEffect::GrainEffect(std::deque<float> audioFile, int duration,int blank, int initPos, int channels){
    mDuration = duration;
    mWindowSize = audioFile.size()-6000;
    mCurrentPostion=0;
    mAudioFile.assign(audioFile.begin(), audioFile.end());
    //std::cout<<initPos<<std::endl;
    mInitPostion = (0 + rand()%mWindowSize)%(audioFile.size()-mDuration);
    if(mInitPostion%channels == 1){
        mInitPostion --;
    }
    mBlank = blank;
    done = false;
    mChannels = channels;
}

samples GrainEffect::getSample(){
    samples current_sample;
    float sample = 0.0f;
    if (mCurrentPostion <mDuration) {
        float hanningCoeff = 0.5 - 0.5* cosf(2*M_PI *(float)mCurrentPostion/(float)(mDuration));
        if(mChannels == 1){
            current_sample.right = mAudioFile.at(mInitPostion+mCurrentPostion)*hanningCoeff;
            current_sample.left  = mAudioFile.at(mInitPostion+mCurrentPostion)*hanningCoeff;
        }
        else if(mChannels == 2){
            current_sample.left = mAudioFile.at(mInitPostion+mCurrentPostion*mChannels    )*hanningCoeff;
            current_sample.right  = mAudioFile.at(mInitPostion+mCurrentPostion*mChannels + 1)*hanningCoeff;
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