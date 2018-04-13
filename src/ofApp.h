#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{
private:
    void setupWebcamPanel();
    
    ofxPanel webcam_panel_; // panel for showing webcam and taking the photo
    bool show_intro_ = true; // to show the introduction once

    ofxButton photo_taking_button_; // button to press to take the photo
    void photoButtonPressed(); // listener - called when the button is pressed
        
    ofVideoGrabber webcam_; // turns on webcam and gets webcam video feed
    ofImage photo_taken_; // stores the photo taken 
    bool show_webcam_ = true; // to show the webcam 
    
    bool show_picture_ = true; // to show the picture after being taken
public:
    void setup();
    void update();
    void draw();
    void exit();
        
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
};


