#include "ofxWavePlayer.h"


//--------------------------------------------------------------
ofxWavePlayer::ofxWavePlayer(){
    mInitPos = 0;
    mVolume   = 0.9f;
    mPosition = 0;
}

//--------------------------------------------------------------
ofxWavePlayer::ofxWavePlayer(std::string path){
    mInitPos = 0;
    mVolume   = 0.9f;
    mPosition = 0;
    loadWave(path);
}

//--------------------------------------------------------------
void ofxWavePlayer::audioOut(float *output, int bufferSize, int nChannels){
    for (int i=0; i<bufferSize; i++) {
        samples sample = getSample();
        for (int j =0; j<mEffects.size(); j++) {
            sample = mEffects[j]->process(sample);
        }
        output[i*nChannels    ] = sample.right * mVolume;
        output[i*nChannels + 1] = sample.left * mVolume;
    }
}

//--------------------------------------------------------------
samples ofxWavePlayer::getSample(){
    
    samples sampleResult;
    mPosition ++;
    sampleResult.left = music[mPosition];
    mPosition ++;
    sampleResult.right = music[mPosition];
    if (mPosition>=musicSize) mPosition = mInitPos;
    return sampleResult;
}


//--------------------------------------------------------------
bool ofxWavePlayer::loadWave(std::string path){
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
float ofxWavePlayer::getVolume(){
    return mVolume;
}

//--------------------------------------------------------------
void ofxWavePlayer::setVolume(float volume){
    mVolume = volume;
}

//--------------------------------------------------------------
void ofxWavePlayer::setInitPosition(int initPos){
    mInitPos = initPos;
}

//--------------------------------------------------------------
int ofxWavePlayer::getInitPosition(){
    return mInitPos;
}

//--------------------------------------------------------------
int ofxWavePlayer::getPosition(){
    return mPosition;
}
