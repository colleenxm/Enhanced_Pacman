#pragma once
#include <ctime>
#include <cstdlib>
#include <utility>

#include "ofMain.h"
#include "wanderer.hpp"

// Enum to represent the current state of the game
enum GameState {
    NOT_STARTED = 0, // introduction
    IN_PROGRESS,
    PAUSED,
    FINISHED
};

class EnhancedPacman : public ofBaseApp {
private:
    // FOR INTRODUCTION PANEL
    ofSoundPlayer intro_music_; // plays music
    ofTrueTypeFont string_font_; // sets font, used to print strings with colors/sizes/fonts other than the default

    
    GameState current_state_ = NOT_STARTED; // should start at the introduction

    Wanderer game_food_; // The object that represents the food pellet the user is attempting to eat with the snake
    
    bool should_update_ = true;     // A flag boolean used in the update() function. Due to the frame dependent animation we've
    // written, and the relatively low framerate, a bug exists where users can prefire direction
    // changes faster than a frame update. Our solution is to force a call to update on direction
    // changes and then not update on the next frame to prevent the snake from skipping across the screen.
    
    // Private helper methods to render various aspects of the game on screen.
    void drawFood();
    void drawGameOver();
    void drawGamePaused();
    
    // Resets the game objects to their original state.
    void reset();
    
public:
    // Function used for one time setup
    void setup();
    
    // Main event loop functions called on every frame
    void update();
    void draw();
    
    // Event driven functions, called on appropriate user action
    void keyPressed(int key);
    void windowResized(int w, int h);
    
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
};

