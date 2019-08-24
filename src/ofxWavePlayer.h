#pragma once

#include "ofxAudioSynth.h"

class ofxWavePlayer : public ofxAudioSynth{
public:
    ofxWavePlayer();
    ofxWavePlayer(std::string path);
    bool loadWave(std::string path);
    void audioOut(float *output, int bufferSize, int nChannels);
    float* music;
    int musicSize=0;;
    
    void setInitPosition(int delay);
    int getInitPosition();
    
    int getPosition();
 
    float getVolume();
    void setVolume(float volume);
    
    struct wave_header {
        char riff[4];
        uint_least32_t size;
        char wave[4];
        char fmt[4];
        uint_least32_t length;
        uint_least16_t encoding;
        uint_least16_t channels;
        uint_least32_t frequency;
        uint_least32_t byterate;
        uint_least16_t block_align;
        uint_least16_t bits_per_samples;
        char data[4];
        uint_least32_t data_size;
        int NumSamples;
        
    } wh;
    
    int mChannel;
    
    
private:
    samples getSample();
    float   mVolume;
    int     mInitPos;
    int     mPosition;
};
