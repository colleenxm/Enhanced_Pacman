#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    
    // note: not creating a panel for the introduction b/c I don't like how labels look and because it's really simple
    setupWebcamPanel();
}
//--------------------------------------------------------------

void ofApp::setupWebcamPanel() { // sets up the intro panel
    photo_taking_button_.addListener(this,&ofApp::photoButtonPressed);

    webcam_panel_.setup("webcam panel");
    webcam_panel_.add(photo_taking_button_.setup("TAKE PHOTO"));
}
//--------------------------------------------------------------

void ofApp::photoButtonPressed() {
    ofxLabel p;
    webcam_panel_.add(p.setup("button pressed", "")); // is working
}
//--------------------------------------------------------------

void ofApp::exit(){
    photo_taking_button_.removeListener(this, &ofApp::photoButtonPressed);
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (draw_intro_panel_) {
        ofSetBackgroundColor(0, 0, 0);
        ofDrawBitmapString("CARTOONIFIER\n\nEnter 'c' to continue.", 100, 100);
    } else {
        ofClear(0);
        webcam_panel_.draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'c') {
        draw_intro_panel_ = false;
    } else if (key == 'd') {
    }
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
    photoButtonPressed();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
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


