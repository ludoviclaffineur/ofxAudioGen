#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    gui.setup();
    mTogglePlaySound.addListener(this, &ofApp::playStop);
    mSliderGrainLength.addListener(this, &ofApp::grainLenth);
    mSliderBlank.addListener(this, &ofApp::blankCallback);
    mSliderOverlap.addListener(this, &ofApp::overlapCallback);

    gui.add(mTogglePlaySound.setup("Play", false));
    gui.add(mSliderGrainLength.setup("grain_size", 0.3,0,1));

    gui.add(mSliderBlank.setup("Blank", 0.3,0,1));

    gui.add(mSliderOverlap.setup("Overlap", 0.3,0,1));

    GranularSynth.loadWave("../../../data/sound15.wav");
    GranularSynth.init();
    GranularSynth.stop();
    increment = GranularSynth.music->size() / 1000;
    mytext.loadFont("Calibri", 20);

    ofSetFrameRate(60);
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
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    int j =0;
    for (int i =0 ; i<GranularSynth.music->size()-increment; j++ ,i+=increment) {
        ofLine(j,
               500+ GranularSynth.music->at(i)*200.0,
               j+1,
               500+ GranularSynth.music->at(i+increment)*200.0);
    }
    ofNoFill();
    ofRect(GranularSynth.getInitPosition()/(float)increment, 300, 10000/increment, 400);
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
