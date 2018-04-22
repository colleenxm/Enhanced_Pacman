#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    
    setupWebcamPanel();
    webcam_.setup(2000, 2000); // set up the webcam separately from the panel
    
    face_finder_.setup("/Users/elizabeth/CS126-FINAL-PROJECT/final-project-ElizWang/bin/data/haar_cascades/haarcascade_frontalface_alt.xml");
}

//--------------------------------------------------------------
void ofApp::setupWebcamPanel() { // sets up the intro panel - adds the button
    photo_taking_button_.addListener(this,&ofApp::photoButtonPressed);
    
    webcam_panel_.setup("webcam panel");
    webcam_panel_.add(photo_taking_button_.setup("TAKE PHOTO"));
}

//--------------------------------------------------------------
void ofApp::photoButtonPressed() { // listener - takes picture when button is pressed
    
    photo_taken_.setFromPixels(webcam_.getPixels()); // take the picture
    show_webcam_ = false; // stop displaying the webcam
    show_photo_ = true; // display the photo
}

//--------------------------------------------------------------
void ofApp::exit(){ // cleanup
    photo_taking_button_.removeListener(this, &ofApp::photoButtonPressed);
}

//--------------------------------------------------------------
void ofApp::update(){
    webcam_.update(); // updates webcam - is a moving image
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (show_intro_) { // first time the app is opened - print an introduction
        ofSetBackgroundColor(0, 0, 0);
        ofDrawBitmapString("CARTOONIFIER\n\nEnter 'c' to continue.", 100, 100);
        
    } else if (show_webcam_){ // all other times - show the webcam
        ofClear(0);
        webcam_panel_.draw();
        webcam_.draw(ofGetWidth() - ofGetWidth()/1.1, ofGetHeight() - ofGetHeight()/1.1, ofGetWidth()/1.1, ofGetHeight()/1.1);
        
    } else if (show_photo_){ // draws out the picture
        FindFaces();
        photo_taken_.draw(0, 0, photo_taken_.getWidth(), photo_taken_.getHeight());
        for(int i = 0; i < face_finder_.blobs.size(); i++) {
            ofRectangle roi = face_finder_.blobs[i].boundingRect;
            ofDrawRectangle(roi);
        }
    }
}

void ofApp::FindFaces() {
    ofxCvColorImage temp_color_img; // temp color img
    ofxCvGrayscaleImage grayscale_img_; // need to convert from regular iamge to ofxCvColorImage to ofxCvGrayscaleImage in order to use the haar cascader

    temp_color_img.setFromPixels(photo_taken_.getPixels()); // need to convert from regular iamge to ofxCvColorImage to ofxCvGrayscaleImage in order to use the haar cascader
    grayscale_img_.setFromColorImage(temp_color_img);
    
    //temp_color_img.draw(0, 0, temp_color_img.getWidth(), temp_color_img.getHeight());
    //grayscale_img_.draw(0, 0, grayscale_img_.getWidth(), grayscale_img_.getHeight());
    
    face_finder_.findHaarObjects(grayscale_img_);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'c') { // to continue past the introduction
        show_intro_ = false; // to stop showing the intro
    } else if (key == 'd') {
        //show_webcam_ = false;
        //photoButtonPressed();
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
