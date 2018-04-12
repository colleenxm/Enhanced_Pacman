#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    
    // note: not creating a panel for the introduction b/c I don't like how labels look and because it's really simple
    setupWebcamPanel();
    webcam.setup(2000, 2000); // set up the webcam
}

//--------------------------------------------------------------
void ofApp::setupWebcamPanel() { // sets up the intro panel
    photo_taking_button_.addListener(this,&ofApp::photoButtonPressed);

    webcam_panel_.setup("webcam panel");
    webcam_panel_.add(photo_taking_button_.setup("TAKE PHOTO"));
}

//--------------------------------------------------------------
void ofApp::photoButtonPressed() { // listener for button - know that this is working
    ofxButton p;
    ofxPanel test_panel;
    test_panel.setup();
    test_panel.add(p.setup("BUTTON WAS PRESSED"));
    test_panel.draw();
}

//--------------------------------------------------------------
void ofApp::exit(){
    photo_taking_button_.removeListener(this, &ofApp::photoButtonPressed);
}

//--------------------------------------------------------------
void ofApp::update(){
    webcam.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (draw_intro_panel_) {
        ofSetBackgroundColor(0, 0, 0);
        ofDrawBitmapString("CARTOONIFIER\n\nEnter 'c' to continue.", 100, 100);
    } else {
        ofClear(0);
        webcam_panel_.draw();
        webcam.draw(ofGetWidth() - ofGetWidth()/1.1, ofGetHeight() - ofGetHeight()/1.1, ofGetWidth()/1.1, ofGetHeight()/1.1);
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
