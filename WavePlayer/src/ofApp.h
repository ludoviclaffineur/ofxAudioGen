#pragma once

#include "ofMain.h"
#include "ofxAudioGen.h"
#include "ofxGui.h"

#define SCREENWIDTH       1024
#define SCREENHEIGHT      800


class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void playCallback(bool&);
    void depthCallback(float&);
    void mixCallback(float&);
    void byPassDelayEffectCallback(bool&);
    void byPassFilterEffectCallback(bool& );
    void initPositionCallback(float&);
    void volumeCallback(float&);
    void cutoffFrequencyCallback(float&);
    
    void keyPressed(int);
    void keyReleased(int);
    void mouseMoved(int, int);
    void mouseDragged(int, int, int);
    void mousePressed(int, int, int);
    void mouseReleased(int, int, int);
    void windowResized(int, int);
    void dragEvent(ofDragInfo);
    void gotMessage(ofMessage);
    
    ofxWavePlayer       WavePlayer;
    ofxDelayEffect*     delay;
    ofxButterworthFilterEffect*     filter;
    
    ofxFloatSlider      mSliderInitPosition;
    ofxFloatSlider      mSliderDepth;
    ofxFloatSlider      mSliderMix;
    ofxFloatSlider      mVolume;
    ofxToggle           mTogglePlaySound;
    ofxFloatSlider      mSliderCutoffFrequency;
    ofxToggle           mToggleByPassDelayEffect;
    ofxToggle           mToggleByPassFilterEffect;
    ofxPanel            gui;
    
    int                 increment;
		
};
