#include "ofApp.h"

// LOOSELY adapted from OF-SNAKE MP: https://github.com/uiuc-sp18-cs126/of-snake-ElizWang (mostly just structural stuff)

// Setup method
void PacmanGame::setup(){
    ofSetWindowTitle("ENHANCED PACMAN");
    
    srand(static_cast<unsigned>(time(0))); // Seed random with current time
    
    string_font_.load("/Users/elizabeth/Downloads/of_v0.9.8_osx_release/examples/addons/networkTcpServerExample/bin/data/type/verdana.ttf", 32, true, false, true, 0.1);
    intro_music_.load("/Users/elizabeth/CS126-FINAL-PROJECT/final-project-ElizWang/sound_files/intro_music.mp3");


    int nbLines = 8, nbCols = 9;
    //std::vector<std::vector<int> > maze = rand_maze(nbLines,nbCols);
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
            //ofRectangle pacman_rect = game_pacman_.get_image_frame();
            //ofRectangle ghost_rect = ghost_1_.get_image_frame();

            // overlaps is logically equal to being on the same square at the same time
            //if (pacman_rect.intersects(game_food_.get_image_frame())) {
            if (game_pacman_.GetMazePosition().x == game_food_.GetMazePosition().x && game_pacman_.GetMazePosition().y == game_food_.GetMazePosition().y) { // problem - needs to ACTUALLY BE ON TOP OF THE OBJECT to eat it, change to a rectangle (should probably just create a rectangle)
                game_pacman_.eat_food_or_ghost(game_food_.kPointsWorth_); // add some sort of sound effect here
                game_food_.rebase(); //delete game_food_;
                
            //} else if (pacman_rect.intersects(ghost_rect)) {
            } else if (game_pacman_.GetMazePosition().x == ghost_1_.GetMazePosition().x && game_pacman_.GetMazePosition().y == ghost_1_.GetMazePosition().y) {
                interact_pacman_with_ghost();
            }
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
            ghost_1_.move_in_new_direction();
            ghost_1_.incr_num_steps_taken();
            
            if (game_pacman_.is_dead()) {
                current_state_ = FINISHED;
            }
        }
    }
    should_update_ = true;
}

void PacmanGame::interact_pacman_with_ghost() { // responsible for all pacman-ghost iteractions
    Direction pacman_direction = game_pacman_.get_direction(); // note: coords for 2d = 0, 0 is on the upper lhs
    Direction ghost_direction = ghost_1_.get_direction();
    
    //ofRectangle pacman_rect = game_pacman_.get_image_frame();
    //ofRectangle ghost_rect = ghost_1_.get_image_frame();
    ofVec2f pacman_pos = game_pacman_.GetMazePosition();
    ofVec2f ghost_pos = ghost_1_.GetMazePosition();
    
    if (pacman_direction == ghost_direction) { // pacman eats the ghost if both objects are pointing in the same direction and the pacman is behind the ghost
        //if (pacman_rect.getX() >= ghost_rect.getX() || pacman_rect.getY() >= ghost_rect.getY()) { // aka if pacman's x or y coord is bigger than the ghost's x y cords
        if (pacman_pos.x >= ghost_pos.x || pacman_pos.y >= ghost_pos.y) { // aka if pacman's x or y coord is bigger than the ghost's x y cords
            game_pacman_.eat_food_or_ghost(ghost_1_.kPointsWorth_);
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
        draw_food();
        draw_pacman();

    } else if(current_state_ == PAUSED) {
        draw_maze();
        draw_ghosts();
        draw_food();
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
        if (upper_key == 'W' && current_direction != DOWN && current_direction != UP) {
            game_pacman_.setDirection(UP);
            update();
            should_update_ = false;
            
            // need to rotate pacman here
        }
        
        else if (upper_key == 'A' && current_direction != RIGHT && current_direction != LEFT) {
            game_pacman_.setDirection(LEFT);
            update();
            should_update_ = false;
        }
        
        else if ((upper_key == 'S') && current_direction != UP && current_direction != DOWN) {
            game_pacman_.setDirection(DOWN);
            update();
            should_update_ = false;
        }
        else if (upper_key == 'D' && current_direction != LEFT && current_direction != RIGHT) {
            game_pacman_.setDirection(RIGHT);
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
    ghost_1_.rebase();
    current_state_ = IN_PROGRESS;
}

void PacmanGame::windowResized(int w, int h){
    ghost_1_.resize(w, h);
    game_pacman_.resize(w, h);
}

void PacmanGame::draw_maze() { // draws the maze
    const int kWidthMultiplier = 15; // don't want the blocks to overlap - will lead to misleading results
    const int kHeightMultiplier = 15;
    
    for (int i = 0; i < kMazeWidth_; i++) {
        for (int j = 0; j < kMazeHeight_; j++) {
            switch (maze_[i][j]) {
                case 0: // no wall
                    ofSetColor(100, 100, 100);
                    break;
                case 1: // wall
                    ofSetColor(225, 225, 225);
                    break;
            }
            ofDrawRectangle(i*kWidthMultiplier, j*kHeightMultiplier, kObject1DSize_, kObject1DSize_);
        }
    }
}

void PacmanGame::draw_ghosts() { // just make sizes all the same for simplicity
    //ofRectangle ghost_frame = ghost_1_.get_image_frame();
    //ghost_1_.get_food_image().draw(ghost_frame.getX(), ghost_frame.getY(), ghost_frame.getWidth(), ghost_frame.getHeight());
    ofVec2f pos = ghost_1_.GetMazePosition();
    ghost_1_.get_food_image().draw(pos.x * coordinates_multiplier_x, pos.y * coordinates_multiplier_x, ghost_1_.Get1DSize(), ghost_1_.Get1DSize());
}

void PacmanGame::draw_pacman() {
    //ofRectangle pacman_frame = game_pacman_.get_image_frame();
    //game_pacman_.get_pacman_image().draw(pacman_frame.getX(), pacman_frame.getY(), pacman_frame.getWidth(), pacman_frame.getHeight());
    ofVec2f pos = game_pacman_.GetMazePosition();
    game_pacman_.get_pacman_image().draw(pos.x * coordinates_multiplier_x, pos.y * coordinates_multiplier_y, game_pacman_.Get1DSize(), game_pacman_.Get1DSize());
}

void PacmanGame::draw_food() {
    //ofRectangle food_frame = game_food_.get_image_frame();
    //game_food_.get_food_image().draw(food_frame.getX(), food_frame.getY(), food_frame.getWidth(), food_frame.getHeight());
    ofVec2f pos = game_food_.GetMazePosition();
    game_food_.get_food_image().draw(pos.x * coordinates_multiplier_x, pos.y * coordinates_multiplier_y, game_food_.Get1DSize(), game_food_.Get1DSize());
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

bool PacmanGame::IsValidPosition(int x_pos, int y_pos) { // true if the position isn't on a part of the wall and isn't out of bounds
    return (x_pos < kMazeWidth_) && (y_pos < kMazeHeight_) && (maze_[x_pos][y_pos] == 0); // 0 = not a part of the wall wall, 1 = part of the wall
}
