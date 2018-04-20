#include "ofApp.h"

#include <algorithm>
#include <iostream>

// Setup method
void PacmanGame::setup(){
    ofSetWindowTitle("ENHANCED PACMAN");
    
    srand(static_cast<unsigned>(time(0))); // Seed random with current time
    
    string_font_.load("/Users/elizabeth/Downloads/of_v0.9.8_osx_release/examples/addons/networkTcpServerExample/bin/data/type/verdana.ttf", 32, true, false, true, 0.1);
    intro_music_.load("/Users/elizabeth/CS126-FINAL-PROJECT/final-project-ElizWang/sound_files/intro_music.mp3");
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
void PacmanGame::update() {
    if (should_update_) {
        if (current_state_ == IN_PROGRESS) {
            ofVec2f pacman_size = game_pacman_.getPacmanSize();
            ofVec2f head_pos = game_pacman_.getPosition();
            ofRectangle pacman_rect(head_pos.x, head_pos.y, pacman_size.x, pacman_size.y);
            
            ofVec2f food_size = game_food_.getBodySize();
            ofVec2f food_pos = game_food_.getPosition();
            ofRectangle food_rect(food_pos.x, food_pos.y, food_size.x, food_size.y);

            if (pacman_rect.intersects(food_rect)) {
                game_pacman_.eatFood(game_food_.getColor());
                game_food_.rebase();
            }
            game_pacman_.update();
            game_food_.update();
            
            if (game_pacman_.isDead()) {
                current_state_ = FINISHED;
            }
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
void PacmanGame::draw(){ // is called over and over again
    if (current_state_ == NOT_STARTED) {
        ofSetBackgroundColor(0, 0, 0); // set background as black

        intro_music_.setLoop(true); // plays over and over again
        intro_music_.play();
        
        string_font_.drawString("WELCOME TO PACMAN!", ofGetWidth()/1.5, ofGetHeight()/1.5);
        ofDrawBitmapString("Click anywhere to continue", ofGetWidth()/6, ofGetHeight()/6);
        
    } else if (current_state_ == IN_PROGRESS) {
        drawFood();
        drawPacman();

    } else if(current_state_ == PAUSED) {
        drawFood();
        drawPacman();
        drawGamePaused();
        
    } else if(current_state_ == FINISHED) {
        drawGameOver(); // draw another panel later
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
void PacmanGame::keyPressed(int key){
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
        Pacman::Direction current_direction = game_pacman_.getDirection(); // figure out why it's making me do this
        
        // If current direction has changed to a valid new one, force an immediate update and skip the next frame update
        if (upper_key == 'W' && current_direction != Pacman::DOWN && current_direction != Pacman::UP) {
            game_pacman_.setDirection(Pacman::UP);
            update();
            should_update_ = false;
        }
        
        else if (upper_key == 'A' && current_direction != Pacman::RIGHT && current_direction != Pacman::LEFT) {
            game_pacman_.setDirection(Pacman::LEFT);
            update();
            should_update_ = false;
        }
        
        else if ((upper_key == 'S') && current_direction != Pacman::UP && current_direction != Pacman::DOWN) {
            game_pacman_.setDirection(Pacman::DOWN);
            update();
            should_update_ = false;
        }
        else if (upper_key == 'D' && current_direction != Pacman::LEFT && current_direction != Pacman::RIGHT) {
            game_pacman_.setDirection(Pacman::RIGHT);
            update();
            should_update_ = false;
            
        } else if (upper_key == 'H') { // pauses the game and prints the highest scores
            current_state_ = PAUSED;
        }
    } else if (upper_key == 'R' && current_state_ == FINISHED) {
        //updateHighestScores(game_snake_.getFoodEaten()); // "works" if updating here, problem is that I'll be one game behind
        reset();
    }
}

void PacmanGame::mousePressed(int x, int y, int button){
    if (current_state_ == NOT_STARTED) {
        current_state_ = IN_PROGRESS;
    }
}

void PacmanGame::reset() {
    game_pacman_ = Pacman();
    game_food_.rebase();
    current_state_ = IN_PROGRESS;
}

void PacmanGame::windowResized(int w, int h){
    game_food_.resize(w, h);
    game_pacman_.resize(w, h);
}

void PacmanGame::drawFood() {
    ofVec2f food_body_size = game_food_.getBodySize();
    ofVec2f position = game_food_.getPosition();
    ofSetColor(game_food_.getColor());
    ofDrawRectangle(position.x, position.y, food_body_size.x, food_body_size.y);

    //ofSetColor(game_food_.getColor());
    //ofDrawRectangle(game_food_.getFoodRect());
}

void PacmanGame::drawPacman() {
    ofVec2f snake_body_size = game_pacman_.getPacmanSize();
    ofVec2f head_pos = game_pacman_.getPosition();
    ofSetColor(game_pacman_.getColor());
    ofDrawRectangle(head_pos.x, head_pos.y, snake_body_size.x, snake_body_size.y);
}

void PacmanGame::drawGameOver() {
    // draw another screen here
}

void PacmanGame::drawGamePaused() {
    string pause_message = "P to Unpause!";
    ofSetColor(0, 0, 0);
    ofDrawBitmapString(pause_message, ofGetWindowWidth() / 1.5, ofGetWindowHeight() / 1.5);
}


