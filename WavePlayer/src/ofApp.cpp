#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(20);
    
    WavePlayer.loadWave("../../../data/stereo.wav");
    WavePlayer.init();
    WavePlayer.stop();
    delay = new ofxDelayEffect(1000, 0.9, 20000);
    filter = new ofxButterworthFilterEffect();
    WavePlayer.addEffect(delay);
    WavePlayer.addEffect(filter);
    increment = WavePlayer.musicSize / SCREENWIDTH;
    if(increment%2 == 1){
        increment++;
    }
    
    gui.setup();
    
    mTogglePlaySound.addListener(this, &ofApp::playCallback);
    mToggleByPassDelayEffect.addListener(this, &ofApp::byPassDelayEffectCallback);
    mToggleByPassFilterEffect.addListener(this, &ofApp::byPassFilterEffectCallback);
    mSliderInitPosition.addListener(this, &ofApp::initPositionCallback);
    mSliderDepth.addListener(this, &ofApp::depthCallback);
    mSliderMix.addListener(this, &ofApp::mixCallback);
    mVolume.addListener(this, &ofApp::volumeCallback);
    mSliderCutoffFrequency.addListener(this, &ofApp::cutoffFrequencyCallback);
    
    gui.add(mTogglePlaySound.setup("Play", false));
    gui.add(mSliderInitPosition.setup("Initital Position", 0, 0, 1));
    gui.add(mVolume.setup("Master Volume", 0.9, 0, 1));
    gui.add(mSliderMix.setup("Delay Amount", 0.9, 0, 1));
    gui.add(mSliderDepth.setup("Delay Depth", 20000, 0, 20000));
    gui.add(mToggleByPassDelayEffect.setup("Bypass Delay", false));
    gui.add(mSliderCutoffFrequency.setup("Cutoff Frequency", 2000, 50, 10000));
    gui.add(mToggleByPassFilterEffect.setup("Bypass Filter", false));

}

//--------------------------------------------------------------
void ofApp::cutoffFrequencyCallback(float &cutoffFrequency){
    filter->setCutoffFrequency(cutoffFrequency);
}

//--------------------------------------------------------------
void ofApp::mixCallback(float &mix){
    delay->mMix = mix;
}

//--------------------------------------------------------------
void ofApp::depthCallback(float& depth){
    delay->mDepth = depth;
}

//--------------------------------------------------------------
void ofApp::byPassDelayEffectCallback(bool &byPass){
    WavePlayer.mEffects[0]->byPass(byPass);
}

//--------------------------------------------------------------
void ofApp::byPassFilterEffectCallback(bool &byPass){
    WavePlayer.mEffects[1]->byPass(byPass);
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
void ofApp::initPositionCallback(float& initPosition){
    WavePlayer.setInitPosition(initPosition*WavePlayer.musicSize);
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
    if (y<700 && y>200) {
        WavePlayer.setInitPosition(x*increment);
    }}

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
