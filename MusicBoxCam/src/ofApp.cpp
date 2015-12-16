#include "ofApp.h"

ofImage currentFrame;
int xProfile[640];
int threshold = 128;


//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(15);
    
    ofBackground(255);
    
    camWidth 		= 80;	// try to grab at this size.
    camHeight 		= 60;
    
    currentFrame.allocate(camWidth, camHeight, OF_IMAGE_GRAYSCALE);
    
    vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(camWidth,camHeight);
    
    font.loadFont("Courier New Bold.ttf", 9);
    
    ofEnableAlphaBlending();
    
    GranularSynth.loadWave("../../../data/stereo.wav");
    GranularSynth.init();
    GranularSynth.play();

    
}


//--------------------------------------------------------------
void ofApp::update(){
    vidGrabber.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    currentFrame = vidGrabber.getPixelsRef();
    
    for(int x=0 ; x < 640 ; x++) {
        xProfile[x] = 0;
    }
    
    
    for (int x = 0; x < camWidth; x++){
        for (int y = 0; y < camHeight; y++){
            int lightness = currentFrame.getColor(x,y).getLightness();
            if (lightness>threshold) lightness = 255;
            else lightness = 0;
            if (lightness==0) xProfile[x]++;
            ofColor pixel;
            pixel.set(lightness, lightness, lightness);
            currentFrame.setColor(x, y, pixel);
            
        }
    }
    
    ofSetHexColor(0xffffff);
    currentFrame.reloadTexture();
    currentFrame.resize(640,480);
    currentFrame.draw(0,0);
    
    ofFill();
    ofSetHexColor(0x000000);
    ofSetPolyMode(OF_POLY_WINDING_ODD);
    
    ofLine(630, 400, 630, 400-255);
    ofLine(630, 400, 630+640, 400);
    
    for(int x = 0 ; x < 80 ; x++) {
        xProfile[x] = xProfile[x];
        //cout << x << " : " << histogram[x] << "\n";
        ofLine(x*4+630, 400-xProfile[x], x*4+630, 400);
    }
    
    ofSetColor(0);
    ofDrawBitmapString("xProfile : ", 670, 100);
    ofDrawBitmapString("0                                                                            640 ", 630, 415);
    ofDrawBitmapString("0", 615, 400);
    ofDrawBitmapString("?", 633, 150);
    
    GranularSynth.setInitPosition(xProfile[40]*1000);
    GranularSynth.setDuration(xProfile[0]/60.0);
    GranularSynth.setBlank(xProfile[20]/60.0);
    GranularSynth.setOverlap(xProfile[60]/60.0);
    
    
    
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
