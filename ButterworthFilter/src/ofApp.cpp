#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(20);
    
    WavePlayer.loadWave("../../../data/stereo.wav");
    WavePlayer.init();
    WavePlayer.stop();
    filter = new ofxButterworthFilterEffect(100, 44100, 2000, LP);
    WavePlayer.addEffect(filter);
    increment = WavePlayer.musicSize / SCREENWIDTH;
    if(increment%2 == 1){
        increment++;
    }

    gui.setup();
    
    gui.add(mTogglePlaySound.setup("Play", false));
    gui.add(mSliderVolume.setup("Master Volume", 0.9, 0, 1));
    gui.add(mSliderCutoffFrequency.setup("Frequency", 2000, 50, 10000));
    gui.add(mToggleLP.setup("LP", true));
    gui.add(mToggleHP.setup("HP", false));
    gui.add(mToggleBP.setup("BP", false));
    gui.add(mToggleBR.setup("BR", false));
    gui.add(mToggleByPassFilterEffect.setup("Bypass Filter", false));
    
    mTogglePlaySound.addListener(this, &ofApp::playCallback);
    mToggleByPassFilterEffect.addListener(this, &ofApp::byPassFilterEffectCallback);
    mSliderVolume.addListener(this, &ofApp::volumeCallback);
    mSliderCutoffFrequency.addListener(this, &ofApp::cutoffFrequencyCallback);
 
}

//--------------------------------------------------------------
void ofApp::cutoffFrequencyCallback(float &cutoffFrequency){
    filter->setCutoffFrequency(cutoffFrequency);
}


//--------------------------------------------------------------
void ofApp::byPassFilterEffectCallback(bool &byPass){
    WavePlayer.mEffects[0]->byPass(byPass);
}

//--------------------------------------------------------------
void ofApp::playCallback(bool &play){
    if(play){
        WavePlayer.play();
    }
    else{
        WavePlayer.stop();
    }
}

//--------------------------------------------------------------
void ofApp::volumeCallback(float& volume){
    WavePlayer.setVolume(volume);
}



//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    int j =0;
    for (int i =0 ; i<WavePlayer.musicSize-increment; j++ ,i+=increment) {
        ofLine(j,
               300+ WavePlayer.music[i]*100.0,
               j+1,
               300+ WavePlayer.music[i+increment]*100.0);
    }
    j=0;
    for (int i =1 ; i<WavePlayer.musicSize-increment; j++ ,i+=increment) {
        ofLine(j,
               500+ WavePlayer.music[i]*100.0,
               j+1,
               500+ WavePlayer.music[i+increment]*100.0);
    }
    ofNoFill();
    ofRect(WavePlayer.getInitPosition()/(float)increment, 200, 2, 400);
    ofRect(WavePlayer.getPosition()/(float)increment, 200, 2, 400);
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}


//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
