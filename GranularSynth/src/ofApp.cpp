#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    gui.setup();
    mTogglePlaySound.addListener(this, &ofApp::playStop);

    mToggleByPassEffect.addListener(this, &ofApp::byPassEffects);
    mSliderGrainLength.addListener(this, &ofApp::grainLenth);
    mSliderBlank.addListener(this, &ofApp::blankCallback);
    mSliderOverlap.addListener(this, &ofApp::overlapCallback);

    mSliderDepth.addListener(this, &ofApp::depthCallback);
    mSliderMix.addListener(this, &ofApp::mixCallback);

    gui.add(mTogglePlaySound.setup("Play", false));
    gui.add(mSliderGrainLength.setup("grain_size", 0.3,0,1));

    gui.add(mSliderBlank.setup("Blank", 0.3,0,1));

    gui.add(mSliderOverlap.setup("Overlap", 0.3,0,1));



    GranularSynth.loadWave("../../../data/stereo.wav");
    delay = new ofxDelayEffect(1000,0.9, 10000);
    GranularSynth.addEffect(delay);
    GranularSynth.addEffect(new ofxDelayEffect(1000,0.9, 10000));
    GranularSynth.init();
    GranularSynth.stop();
    increment = GranularSynth.music->size() / 1000;
    if(increment%2 == 1){
        increment++;
    }

    gui.add(mSliderMix.setup("mix", 0.3,0,1));
    gui.add(mSliderDepth.setup("depth", 0,0,20000));
    gui.add(mToggleByPassEffect.setup("byPassEffect", false));
    mytext.loadFont("Calibri", 20);

    ofSetFrameRate(20);
}

void ofApp::mixCallback(float &bl){
    delay->mMix = bl;
}

void ofApp::depthCallback(float &bl){
    delay->mDepth = bl;
}

void ofApp::byPassEffects(bool &byPass){
    std::cout<<byPass<<endl;
    GranularSynth.mEffects[0]->byPass(byPass);
}

void ofApp::playStop(bool &check){
    if(check){
        GranularSynth.play();
    }
    else{
        GranularSynth.stop();
    }
}

void ofApp::grainLenth(float &gl){
    GranularSynth.setDuration(gl);
}

void ofApp::blankCallback(float &gl){
    GranularSynth.setBlank(gl);
}

void ofApp::overlapCallback(float &bl){
    GranularSynth.setOverlap(bl);
}

//--------------------------------------------------------------
void ofApp::update(){
    //delay->mDepth++;
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    int j =0;

    for (int i =0 ; i<GranularSynth.music->size()-increment; j++ ,i+=increment) {
        ofLine(j,
               300+ GranularSynth.music->at(i)*100.0,
               j+1,
               300+ GranularSynth.music->at(i+increment)*100.0);
    }
    j=0;

    for (int i =1 ; i<GranularSynth.music->size()-increment; j++ ,i+=increment) {
        ofLine(j,
                500+ GranularSynth.music->at(i)*100.0,
                j+1,
                500+ GranularSynth.music->at(i+increment)*100.0);
    }

    ofNoFill();
    ofRect(GranularSynth.getInitPosition()/(float)increment, 200, 10000/increment, 400);
    mytext.drawString("Granular synthesiser", ofGetWindowSize().x/2, 40);

    mytext.drawString("Ludovic LAFFINEUR", ofGetWindowSize().x/2, 80);
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
    if (x>0 && x<1000 && y<700 && y>300) {
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
