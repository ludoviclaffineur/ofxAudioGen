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
    
    void playCallback(bool& play);
    void blankCallback(float& blank);
    void overlapCallback(float& overlap);
    void depthCallback(float& depth);
    void mixCallback(float& mix);
    void byPassEffectsCallback(bool& byPass);
    void grainLengthCallback(float& grainLength);
    void volumeCallback(float& volume);
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    
    //ofxSquareSynth     SquareSynth;
    //ofxNoiseSynth      NoiseSynth;
    //ofxSawSynth        SawSynth;
    //ofxSineSynth       SineSynth;
    ofxGranularSynth    GranularSynth;
    ofxDelayEffect*     delay;
    
    ofxFloatSlider      mSliderGrainLength;
    ofxFloatSlider      mSliderDepth;
    ofxFloatSlider      mSliderMix;
    ofxFloatSlider      mSliderOverlap;
    ofxFloatSlider      mSliderBlank;
    ofxFloatSlider      mVolume;
    ofxToggle           mTogglePlaySound;
    ofxToggle           mToggleByPassEffect;
    ofxPanel            gui;
    
    int                 increment;
};
