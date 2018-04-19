#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    string_font_.load("/Users/elizabeth/Downloads/of_v0.9.8_osx_release/examples/addons/networkTcpServerExample/bin/data/type/verdana.ttf", 32, true, false, true, 0.1);
    
    intro_music_.load("/Users/elizabeth/CS126-FINAL-PROJECT/final-project-ElizWang/intro_music.mp3");
    
    /*if (show_intro_) { // only plays the intro music when the intro is being shown
        intro_music_.setLoop(true); // plays over and over again
        intro_music_.play();
    }*/
}

//--------------------------------------------------------------
void ofApp::exit(){
    
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (show_intro_) {
        intro_music_.play();
        
        ofSetBackgroundColor(0, 0, 0); // black
        ofSetColor(0, 90, 60); // dark green
        ofFill();
    
        ofDrawBitmapString("Click anywhere to continue. ", ofGetWidth()/6, ofGetHeight()/6);
        string_font_.drawString("WELCOME TO THE PACMAN GAME", ofGetWidth()/6, ofGetWidth()/6);
    }
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
    if (show_intro_) { // stop showing intro after the mouse is clicked
        show_intro_ = false;
    }
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
