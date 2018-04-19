#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{
private:
    // FOR INTRODUCTION PANEL
    ofxPanel intro_panel_; // introductionary panel
    bool show_intro_ = true; // to show the introduction once
    ofSoundPlayer intro_music_; // plays music
    
    ofTrueTypeFont string_font_; // sets font, used to print strings with colors/sizes/fonts other than the default

    
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


