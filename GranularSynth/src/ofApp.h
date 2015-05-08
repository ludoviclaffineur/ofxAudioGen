#pragma once

#include "ofMain.h"
#include "ofxAudioGen.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    void playStop(bool& check);

    void blankCallback(float& bl);
    void overlapCallback(float& bl);
    
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void grainLenth(float &gl);
        //ofxSquareSynth     SquareSynth;
        //ofxNoiseSynth      NoiseSynth;
        //ofxSawSynth        SawSynth;
        //ofxSineSynth       SineSynth;
        ofxGranularSynth   GranularSynth;
        //ofMatrixStack test;
        ofxFloatSlider mSliderGrainLength;
        ofxFloatSlider mSliderOverlap;
        ofxFloatSlider mSliderBlank;
        ofxToggle mTogglePlaySound;
    ofTrueTypeFont mytext;
    ofxPanel gui;
    int increment;
};
