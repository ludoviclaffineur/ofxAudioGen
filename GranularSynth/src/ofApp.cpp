#include "ofApp.h"
#include "ofMath.h"
//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(20);
    
    GranularSynth.loadWave("../../../data/sound15.wav");
    delay = new ofxDelayEffect(1000, 0.9, 10000);
    GranularSynth.addEffect(delay);
    GranularSynth.init();
    GranularSynth.stop();
    increment = GranularSynth.musicSize / SCREENWIDTH;
    if(increment%2 == 1){
        increment++;
    }
    
    gui.setup();
    
    mTogglePlaySound.addListener(this, &ofApp::playCallback);
    mToggleByPassEffect.addListener(this, &ofApp::byPassEffectsCallback);
    mSliderGrainLength.addListener(this, &ofApp::grainLengthCallback);
    mSliderBlank.addListener(this, &ofApp::blankCallback);
    mSliderOverlap.addListener(this, &ofApp::overlapCallback);
    mSliderDepth.addListener(this, &ofApp::depthCallback);
    mSliderMix.addListener(this, &ofApp::mixCallback);
    mVolume.addListener(this, &ofApp::volumeCallback);
    
    gui.add(mTogglePlaySound.setup("Play", false));
    gui.add(mSliderGrainLength.setup("Grain Size", 0.3,0,1));
    gui.add(mSliderBlank.setup("Blank", 0.3,0,1));
    gui.add(mSliderOverlap.setup("Overlap", 0.3,0,1));
    gui.add(mVolume.setup("Volume", 0.9,0,1));
    gui.add(mSliderMix.setup("Mix", 0.3,0,1));
    gui.add(mSliderDepth.setup("Depth", 0,0,20000));
    gui.add(mToggleByPassEffect.setup("Bypass Effect", false));
    
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
void ofApp::byPassEffectsCallback(bool &byPass){
    GranularSynth.mEffects[0]->byPass(byPass);
}

//--------------------------------------------------------------
void ofApp::playCallback(bool &play){
    if(play){
        GranularSynth.play();
    }
    else{
        GranularSynth.stop();
    }
}

//--------------------------------------------------------------
void ofApp::grainLengthCallback(float& grainLength){
    GranularSynth.setDuration(grainLength);
}

//--------------------------------------------------------------
void ofApp::volumeCallback(float& volume){
    GranularSynth.setVolume(volume);
}

//--------------------------------------------------------------
void ofApp::blankCallback(float& blank){
    GranularSynth.setBlank(blank);
}

//--------------------------------------------------------------
void ofApp::overlapCallback(float& overlap){
    GranularSynth.setOverlap(overlap);
}

//--------------------------------------------------------------
void ofApp::update(){
    // remove this line if you want to select grains in a specific region
    GranularSynth.setInitPosition(ofRandom(10,1000)*increment);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    int j =0;
    for (int i =0 ; i<GranularSynth.musicSize-increment; j++ ,i+=increment) {
        ofLine(j,
               300+ GranularSynth.music[i]*100.0,
               j+1,
               300+ GranularSynth.music[i+increment]*100.0);
    }
    j=0;
    for (int i =1 ; i<GranularSynth.musicSize-increment; j++ ,i+=increment) {
        ofLine(j,
               500+ GranularSynth.music[i]*100.0,
               j+1,
               500+ GranularSynth.music[i+increment]*100.0);
    }
    ofNoFill();
    ofRect(GranularSynth.getInitPosition()/(float)increment, 200, GranularSynth.getDuration()/increment, 400);
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
        GranularSynth.setInitPosition(x*increment);
    }
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
