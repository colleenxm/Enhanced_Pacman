#include "ofApp.h"

// LOOSELY adapted from OF-SNAKE MP: https://github.com/uiuc-sp18-cs126/of-snake-ElizWang (mostly just structural stuff)

// Setup method
void PacmanGame::setup(){
    ofSetWindowTitle("ENHANCED PACMAN");
    
    srand(static_cast<unsigned>(time(0))); // Seed random with current time
    
    string_font_.load("/Users/elizabeth/Downloads/of_v0.9.8_osx_release/examples/addons/networkTcpServerExample/bin/data/type/verdana.ttf", 32, true, false, true, 0.1);
    intro_music_.load("/Users/elizabeth/CS126-FINAL-PROJECT/final-project-ElizWang/sound_files/intro_music.mp3");
    
    // set the maze reference so the other objects can keep track of the maze as well
    //game_pacman_.SetMaze(maze_);
    //ghost_1_.SetMaze(maze_);
    ghost_1_.SetInitialRandomPosition();
    maze_.PopulateWithFood(kNumFoodItems_);
    
    //int val = maze_.GetElementAt(10, 10);
    coord_multiplier_x_ = ofGetWindowWidth() / maze_.GetWidth();
    coord_multiplier_y_ = ofGetWindowHeight() / maze_.GetHeight();
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
            InteractPredatorPreyObjects();
            game_pacman_.update(); // gets new location for the pacman and draws in the next tick
            
            // Explanation: We want the ghost to take a number of steps in its current
            // direction before changing directions so it won't look like it's just going in
            // a circle. However, we also need to make sure that each step the ghost takes
            // is clearly drawn out so it won't look like it's jumping around. So, I'm keeping
            // track of the number of steps the ghost moves in a direction before changing the
            // direction (which happens every CONST number of steps). Note that everything to
            // do with the ghost is in the ghost class for the sake of OOP (and because the
            // Pacman game has >1 ghosts ...)
            if (ghost_1_.get_num_steps_taken() % ghost_1_.kNumStepsBeforeDirectionChange_) {
                ghost_1_.choose_random_direction();
            }
            ghost_1_.MoveInNewDirection();
            ghost_1_.IncrNumStepsTaken();
            
            if (game_pacman_.is_dead()) {
                current_state_ = FINISHED;
            }
        }
    }
    should_update_ = true;
}

void PacmanGame::InteractPredatorPreyObjects() { // contains logic for having objects eat each other, should probably rename the method
    ofVec2f pacman_pos = game_pacman_.GetMazePosition();
    //ofVec2f food_pos = game_food_.GetMazePosition();
    ofVec2f ghost_pos = ghost_1_.GetMazePosition();
    
    ofRectangle pacman_rect = ofRectangle(pacman_pos.x * coord_multiplier_x_, pacman_pos.y * coord_multiplier_x_, kOneDObjectSize_, kOneDObjectSize_);
    //ofRectangle food_rect = ofRectangle(food_pos.x * coord_multiplier_x_, food_pos.y * coord_multiplier_x_, kOneDObjectSize_, kOneDObjectSize_);
    ofRectangle ghost_rect = ofRectangle(ghost_pos.x * coord_multiplier_x_, ghost_pos.y * coord_multiplier_x_, kOneDObjectSize_, kOneDObjectSize_);
    
    // Note: Creating a rectangle and using intersects() instead of just comparing indices because the latter would force the predator to be ON TOP OF the object to eat it.
    //if (pacman_rect.intersects(food_rect)) {
    if (maze_.GetElementAt(pacman_pos.x, pacman_pos.y) == 2) { // idk if this works
        maze_.RemoveFoodAt(pacman_pos.x, pacman_pos.y);
        game_pacman_.eat_food_ghost(kFoodPointsWorth_); // add some sort of sound effect here
        //game_food_.rebase(); //delete game_food_;
    }

    if (pacman_rect.intersects(ghost_rect)) {
        InteractPacmanWithGhost();
    }
}

void PacmanGame::InteractPacmanWithGhost() { // responsible for all pacman-ghost iteractions
    Direction pacman_direction = game_pacman_.get_direction(); // note: coords for 2d = 0, 0 is on the upper lhs
    Direction ghost_direction = ghost_1_.get_direction();
    
    ofVec2f pacman_pos = game_pacman_.GetMazePosition(); // considering changing the logic here as well
    ofVec2f ghost_pos = ghost_1_.GetMazePosition();
    
    if (pacman_direction == ghost_direction) { // pacman eats the ghost if both objects are pointing in the same direction and the pacman is behind the ghost
        if (pacman_pos.x >= ghost_pos.x || pacman_pos.y >= ghost_pos.y) { // aka if pacman's x or y coord is bigger than the ghost's x y cords
            game_pacman_.eat_food_ghost(ghost_1_.kPointsWorth_);
            // need to do something about the ghost
        } else { // ghost eats the pacman if both objects are pointing in the same direction and the ghost is behind the pacman
            game_pacman_.gets_eaten(); // game over - pacman needs to die
            current_state_ = FINISHED;
        }
    } else { // ghost eats the pacman if the objects are pointing in different directions
        if ((pacman_direction == UP && ghost_direction == DOWN) || (pacman_direction == DOWN && ghost_direction == UP)
            || (pacman_direction == LEFT && ghost_direction == RIGHT) || (pacman_direction == RIGHT && ghost_direction == LEFT)) {
            game_pacman_.gets_eaten(); // game over - pacman needs to die
            current_state_ = FINISHED;
        }
    }
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
        draw_maze();
        draw_ghosts();
        draw_pacman();

    } else if(current_state_ == PAUSED) {
        draw_maze();
        draw_ghosts();
        draw_pacman();
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
        Direction current_direction = game_pacman_.get_direction();
        
        // If current direction has changed to a valid new one, force an immediate update and skip the next frame update
        if (upper_key == 'W') {
            game_pacman_.setDirection(UP);
            update();
            should_update_ = false;
            
            // need to rotate pacman here
        }
        
        else if (upper_key == 'A') {
            game_pacman_.setDirection(LEFT);
            update();
            should_update_ = false;
        }
        
        else if (upper_key == 'S') {
            game_pacman_.setDirection(DOWN);
            update();
            should_update_ = false;
        }
        else if (upper_key == 'D') {
            game_pacman_.setDirection(RIGHT);
            update();
            should_update_ = false;
            
        } else if (upper_key == 'H') { // pauses the game and prints the highest scores
            current_state_ = PAUSED;
        }
    } else if (upper_key == 'R' && current_state_ == FINISHED) {
        reset();
    }
}

void PacmanGame::mousePressed(int x, int y, int button){
    if (current_state_ == NOT_STARTED) {
        current_state_ = IN_PROGRESS;
    }
}

void PacmanGame::reset() { // resets everything
    game_pacman_.reset();
    ghost_1_.SetInitialRandomPosition();
    current_state_ = IN_PROGRESS;
    
    maze_.Reset(); // clears all leftover food items and redraws food items
}

void PacmanGame::windowResized(int w, int h){
    ghost_1_.resize(w, h);
    game_pacman_.resize(w, h);
}

void PacmanGame::draw_maze() { // draws the maze
    for (int x_index = 0; x_index < maze_.GetWidth(); x_index++) {
        for (int y_index = 0; y_index < maze_.GetHeight(); y_index++) {
            switch (maze_.GetElementAt(x_index, y_index)) {
                case 0: // no wall
                    ofSetColor(100, 100, 100);
                    ofDrawRectangle(x_index * coord_multiplier_x_, y_index * coord_multiplier_y_, 20, 20); //kObject1DSize_, kObject1DSize_);
                    break;
                case 1: // wall
                    ofSetColor(225, 225, 225);
                    ofDrawRectangle(x_index * coord_multiplier_x_, y_index * coord_multiplier_y_, 20, 20); //kObject1DSize_, kObject1DSize_);
                    break;
                case 2: // food
                    ofImage food_image_; // image that correpsonds with a food object
                    food_image_.load("/Users/elizabeth/CS126-FINAL-PROJECT/final-project-ElizWang/image_files/apple.png");
                    food_image_.draw(x_index * coord_multiplier_x_, y_index * coord_multiplier_y_, kOneDObjectSize_, kOneDObjectSize_);
                    break;
            }
        }
    }
}

void PacmanGame::draw_ghosts() { // just make sizes all the same for simplicity
    ofVec2f pos = ghost_1_.GetMazePosition();
    ghost_1_.get_ghost_image().draw(pos.x * coord_multiplier_x_, pos.y * coord_multiplier_x_, kOneDObjectSize_, kOneDObjectSize_);
}

void PacmanGame::draw_pacman() {
    ofVec2f pos = game_pacman_.GetMazePosition();
    game_pacman_.get_pacman_image().draw(pos.x * coord_multiplier_x_, pos.y * coord_multiplier_y_, kOneDObjectSize_, kOneDObjectSize_);
}

void PacmanGame::drawGameOver() {
    ofSetBackgroundColor(0, 0, 0); // set background as black
    
    string_font_.drawString("YOU LOST!", ofGetWidth()/6, ofGetHeight()/6);
}

void PacmanGame::drawGamePaused() {
    string pause_message = "P to Unpause!";
    ofSetColor(0, 0, 0);
    ofDrawBitmapString(pause_message, ofGetWindowWidth() / 1.5, ofGetWindowHeight() / 1.5);
}
