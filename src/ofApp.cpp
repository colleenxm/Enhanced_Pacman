#include "ofApp.h"

#include <algorithm>
#include <iostream>

// Setup method
void EnhancedPacman::setup(){
    ofSetWindowTitle("ENHANCED PACMAN");
    
    string_font_.load("/Users/elizabeth/Downloads/of_v0.9.8_osx_release/examples/addons/networkTcpServerExample/bin/data/type/verdana.ttf", 32, true, false, true, 0.1);
    
    intro_music_.load("/Users/elizabeth/CS126-FINAL-PROJECT/final-project-ElizWang/sound_files/intro_music.mp3"); // fix this later?
    
    if (current_state_ == NOT_STARTED) { // only plays the intro music when the intro is being shown
        intro_music_.setLoop(true); // plays over and over again
        intro_music_.play();
    }
     
    srand(static_cast<unsigned>(time(0))); // Seed random with current time
}

/*
 Update function called before every draw
 If the function should update when it is called it will:
 1. Check to see if the game is in progress, if it is paused or over it should not update.
 2. Check to see if the current head of the snake intersects the food pellet. If so:
 * The snake should grow by length 1 in its current direction
 * The food should be moved to a new random location
 3. Update the snake in the current direction it is moving
 4. Check to see if the snakes new position has resulted in its death and the end of the game
 */
void EnhancedPacman::update() {
    if (should_update_) {
        if (current_state_ == IN_PROGRESS) {
            
        }
    }
    should_update_ = true;
}

/*
 Draws the current state of the game with the following logic
 1. If the game is paused draw the pause screen
 2. If the game is finished draw the game over screen and final score
 3. Draw the current position of the food and of the snake
 */
void EnhancedPacman::draw(){ // is called over and over again
    if (current_state_ == NOT_STARTED) {
        ofSetBackgroundColor(0, 0, 0); // black
        ofSetColor(0, 90, 60); // dark green
        ofFill();
        
        ofDrawBitmapString("Click anywhere to continue. ", ofGetWidth()/6, ofGetHeight()/6);
        string_font_.drawString("WELCOME TO THE PACMAN GAME", ofGetWidth()/6, ofGetWidth()/6);
  
    } else if (current_state_ == IN_PROGRESS){
        drawFood();
        
    } else if(current_state_ == PAUSED) {
        drawGamePaused();
    } else if(current_state_ == FINISHED) {
        drawGameOver();
    }
}

/*
 Function that handles actions based on user key presses
 1. if key == F12, toggle fullscreen
 2. if key == p and game is not over, toggle pause
 3. if game is in progress handle WASD action
 4. if key == r and game is over reset it
 
 WASD logic:
 Let dir be the direction that corresponds to a key
 if current direction is not dir (Prevents key spamming to rapidly update the snake)
 and current_direction is not opposite of dir (Prevents the snake turning and eating itself)
 Update direction of snake and force a game update (see ofApp.h for why)
 */
void EnhancedPacman::keyPressed(int key){
    if (key == OF_KEY_F12) {
        ofToggleFullscreen();
        return;
    }
    
    int upper_key = toupper(key); // Standardize on upper case
    
    if (upper_key == 'P' && current_state_ != FINISHED) {
        // Pause or unpause
        current_state_ = (current_state_ == IN_PROGRESS) ? PAUSED : IN_PROGRESS;
    }
    else if (current_state_ == IN_PROGRESS)
    {
    } else if (upper_key == 'R' && current_state_ == FINISHED) {
        reset();
    }
}

void EnhancedPacman::reset() {
    // create more food objects (??)
    current_state_ = IN_PROGRESS;
}

void EnhancedPacman::windowResized(int w, int h){
    game_food_.resize(w, h);
}

void EnhancedPacman::drawFood() {
    ofSetColor(game_food_.getColor());
    ofDrawRectangle(game_food_.getFoodRect());
}

void EnhancedPacman::drawGameOver() {
}

void EnhancedPacman::drawGamePaused() {
    string pause_message = "P to Unpause!";
    ofSetColor(0, 0, 0);
    ofDrawBitmapString(pause_message, ofGetWindowWidth() / 1.5, ofGetWindowHeight() / 1.5);
}

//--------------------------------------------------------------
void EnhancedPacman::keyReleased(int key){
    
}

//--------------------------------------------------------------
void EnhancedPacman::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void EnhancedPacman::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void EnhancedPacman::mousePressed(int x, int y, int button){
    if (current_state_ == NOT_STARTED) { // stop showing intro after the mouse is clicked
        current_state_ = IN_PROGRESS; // start the game
    }
}

//--------------------------------------------------------------
void EnhancedPacman::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void EnhancedPacman::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void EnhancedPacman::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void EnhancedPacman::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void EnhancedPacman::dragEvent(ofDragInfo dragInfo){
    
}
