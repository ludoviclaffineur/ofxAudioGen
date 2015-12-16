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
    void byPassFilterEffectCallback(bool& );
    void volumeCallback(float&);
    void cutoffFrequencyCallback(float&);
    void bandWidthCallback(float&);
    
    void keyPressed(int);
    void keyReleased(int);
    void mouseMoved(int, int);
    void mouseDragged(int, int, int);
    void mousePressed(int, int, int);
    void mouseReleased(int, int, int);
    void windowResized(int, int);
    void dragEvent(ofDragInfo);
    void gotMessage(ofMessage);
    
    ofxWavePlayer                   WavePlayer;
    ofxButterworthFilterEffect*     filter;
    
    ofxFloatSlider      mSliderVolume;
    ofxToggle           mTogglePlaySound;
    ofxFloatSlider      mSliderCutoffFrequency;
    ofxToggle           mToggleLP;
    ofxToggle           mToggleHP;
    ofxToggle           mToggleBP;
    ofxToggle           mToggleBR;
    ofxToggle           mToggleByPassFilterEffect;
    
    ofxPanel            gui;
    
    int                 increment;
		
};
