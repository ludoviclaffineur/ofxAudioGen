#include "ofxGranularSynth.h"

//--------------------------------------------------------------
ofxGranularSynth::ofxGranularSynth(string path){
    mDuration = 3000;
    mBlank    = 200;
    mPosition = 0;
    mOverlap  = 50;
    mVolume   = 0.9f;
    loadWave(path);
}

ofxGranularSynth::ofxGranularSynth(float* wav){
    mDuration = 3000;
    mBlank    = 200;
    mPosition = 0;
    mOverlap  = 50;
    mVolume   = 0.9f;
    music = wav;
}

ofxGranularSynth::ofxGranularSynth(){
    mDuration = 3000;
    mBlank    = 200;
    mPosition = 0;
    mOverlap  = 50;
    mVolume   = 0.9f;
    mInitPos  = 0;
}

//--------------------------------------------------------------
void ofxGranularSynth::audioOut(float *output, int bufferSize, int nChannels){
    for (int i=0; i<bufferSize; i++) {
        samples sample = getSample();
        
        for (int j =0; j<mEffects.size(); j++) {
            sample = mEffects[j]->process(sample);
        }
        output[i*nChannels    ] = sample.left * mVolume;
        output[i*nChannels + 1] = sample.right * mVolume;
    }

}

//--------------------------------------------------------------
samples ofxGranularSynth::getSample(){
    samples sampleResult;
    
    if(mGrains.size()==0 || mPosition++ > (mGrains[mGrains.size()-1]->mDuration + mGrains[mGrains.size()-1]->mBlank - mOverlap)){
        if(mDuration >mOverlap){
            mGrains.push_back(new Grain(music, mDuration, mBlank, mInitPos,mChannel, musicSize));
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
            sampleResult.left += retour.left;
        }
    }
    else{
        sampleResult.right = sampleResult.left = 0.0f;
    }
    return sampleResult;
}


//--------------------------------------------------------------
bool ofxGranularSynth::loadWave(string path){
    FILE *fp;
    fp = fopen(path.c_str(),"rb");
    if (fp == NULL){
        std::cout<<"path fichier faux"<<std::endl;
        throw std::logic_error( "Audio Wave not found" );
        return false;
    }
    fread(wh.riff, 4, 1, fp);
    fread(&wh.size, 4, 1, fp);
    fread(wh.wave,  4, 1, fp);
    fread(wh.fmt, 4  , 1, fp);
    fread(&wh.length, 4,1,fp);
    fread(&wh.encoding, 2,1,fp);
    fread(&wh.channels, 2,1,fp);
    fread(&wh.frequency, 4,1,fp);
    fread(&wh.byterate, 4,1,fp);
    fread(&wh.block_align, 2,1,fp);
    fread(&wh.bits_per_samples, 2,1,fp);
    fread(wh.data, 4, 1, fp);
    fread(&wh.data_size,4,1,fp);
    wh.NumSamples= ((wh.data_size*8)/wh.bits_per_samples)/wh.channels;
    
    musicSize = wh.NumSamples*wh.channels;
    music = new float[musicSize];
    mChannel = wh.channels;
    mInitPos  = musicSize/2;
    
    int count = 0;
    short int b = 0;

    while(count <musicSize){
        fread(&b,1,2,fp);
        music[count] = (b)/(float)INT16_MAX;
        if(wh.channels==2){
            fread(&b,1,2,fp);
            count++;
            music[count] = ((b)/(float)INT16_MAX);
        }
        count++;
    }
    return true;
}


//--------------------------------------------------------------
int ofxGranularSynth::getDuration(){
    return mDuration;
}

//--------------------------------------------------------------
void ofxGranularSynth::setDuration(float duration){
    if(duration>0){
        float oldDuration = mDuration;
        mDuration = duration*14000;
        setOverlap((float)mOverlap/(float)oldDuration);
    }
}

//--------------------------------------------------------------
int ofxGranularSynth::getOverlap(){
    return mOverlap;
}

//--------------------------------------------------------------
void ofxGranularSynth::setBlank(float blank){
    mBlank = blank * 14000;
}

//--------------------------------------------------------------
int ofxGranularSynth::getBlank(){
    return mBlank;
}

//--------------------------------------------------------------
void ofxGranularSynth::setOverlap(float overlap){
        mOverlap = overlap * mDuration;

}

//--------------------------------------------------------------
float ofxGranularSynth::getVolume(){
    return mVolume;
}

//--------------------------------------------------------------
void ofxGranularSynth::setVolume(float volume){
    mVolume = volume;
}

//--------------------------------------------------------------
void ofxGranularSynth::setInitPosition(int initPos){
    mInitPos = initPos;
}

//--------------------------------------------------------------
int ofxGranularSynth::getInitPosition(){
    return mInitPos;
}



// GRAINS

//--------------------------------------------------------------
Grain::Grain(float* audioFile, int duration,int blank, int initPos, int channels, int musicSize){
    mDuration = duration;
    mWindowSize = 10000;
    mCurrentPostion=0;
    mAudioFile = audioFile;
    mMusicSize = musicSize;
    mInitPostion = (initPos + rand()%mWindowSize)%(mMusicSize-mDuration-mWindowSize);
    if(mInitPostion%channels == 1){
        mInitPostion --;
    }
    mBlank = blank;
    done = false;
    mChannels = channels;

}

//--------------------------------------------------------------
samples Grain::getSample(){
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
