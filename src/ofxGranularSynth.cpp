//
//  ofxGranularSynth.cpp
//  AudioGenTest
//
//  Created by Ludovic Laffineur on 7/05/15.
//
//

#include "ofxGranularSynth.h"

ofxGranularSynth::ofxGranularSynth(string path){
    mDuration = 3000;
    mBlank    = 200;
    mPosition = 0;
    mOverlap  = 50;
    mVolume   = 0.9f;
    music = new std::vector <float>();
    loadWave(path);
    mInitPos  = music->size()/2;
}

ofxGranularSynth::ofxGranularSynth(){
    mDuration = 3000;
    mBlank    = 200;
    mPosition = 0;
    mOverlap  = 50;
    mVolume   = 0.9f;
    music = new std::vector <float>();
    mInitPos  = 0;
}

void ofxGranularSynth::audioRequested(float *output, int bufferSize, int nChannels){
    for (int i=0; i<bufferSize; i++) {
        float sample = getSample();
        output[i*nChannels    ] = sample;
        output[i*nChannels + 1] = sample;
    }
}

float ofxGranularSynth::getSample(){
   float sampleResult = 0.0f;

   if(mGrains.size()==0 || mPosition++ > (mGrains[mGrains.size()-1]->mDuration + mGrains[mGrains.size()-1]->mBlank - mOverlap)){
       if(mDuration >mOverlap){
           mGrains.push_back(new Grain(music, mDuration, mBlank, mInitPos));
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
           sampleResult += mGrains[i]->getSample();
       }
   }
   else{
       sampleResult = 0.0f;
   }
   return sampleResult;
}

bool ofxGranularSynth::loadWave(string path){
    std::ifstream myfile(path.c_str());
    if (myfile.is_open())
    {
        int sample = 0;
        u_char ubyte;
        unsigned char lbyte;
        int  i =0;
        while ( myfile.read(reinterpret_cast<char*>(&lbyte), 1))
        {
            if (i%2 == 0) {//upper
                sample = (short) (lbyte);
            }
            else{
                sample+= (short)(lbyte<<8);
                //mAudioWave.push_back((sample));
                music->push_back((float)(sample)/(float)INT16_MAX);
            }
            i++;
        }
        myfile.close();
        mInitPos  = music->size()/2;
        return true;
    }
    else {
        std::cout << "Unable to open file";
        return false;
    }
}

// GRAINS

Grain::Grain(std::vector<float>* audioFile, int duration,int blank, int initPos){
    mDuration = duration;
    mWindowSize = 10000;
    mCurrentPostion=0;
    mAudioFile = audioFile;
    //std::cout<<initPos<<std::endl;
    mInitPostion = (initPos + rand()%mWindowSize)%(audioFile->size()-mDuration);
    mBlank = blank;
    done = false;
}

float Grain::getSample(){
    float sample = 0.0f;
    if (mCurrentPostion <mDuration) {
        float hanningCoeff = 0.5 - 0.5* cosf(2*M_PI *(float)mCurrentPostion/(float)(mDuration));
        sample = mAudioFile->at(mInitPostion+mCurrentPostion)*hanningCoeff;
    }
    else if(mCurrentPostion< mDuration+ mBlank){
        sample = 0.0f;
    }
    else{
        done = true;
    }
    mCurrentPostion++;
    return sample;
}