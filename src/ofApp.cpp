#include "ofApp.h"

// Setup method
void PacmanGame::setup(){
    ofSetWindowTitle("ENHANCED PACMAN");
    
    srand(static_cast<unsigned>(time(0))); // Seed random with current time
    
    // LOADING FROM PATH
    string_font_.load(kTextPath_, 32, true, false, true, 0.1);
    intro_music_.load(kIntroMusicPath_);
    pacman_eating_sound_.load(kPacmanEating_);
    pacman_death_sound_.load(kDeathSoundPath_);
    demo_movie_.load(kDemoMoviePath_);
    
    // WEBCAM SETUP
    photo_taking_button_.addListener(this, &PacmanGame::PhotoButtonPressed);
    photo_taking_button_.setup("TAKE PHOTO");
    webcam_.setup(2000, 2000); // set up the webcam separately from the pane

    // HAAR CASCADER SETUP
    facial_detector_.setup(kFacialCascadePath_);

    // OBJECTS SETUP
    for (int current_num_ghosts = 0; current_num_ghosts < kNumGhosts_; current_num_ghosts++) {
        Ghost ghost;
        ghost.SetInitialRandomPosition();
        all_ghosts_.push_back(ghost);
                
        // make sure ghosts aren't all at the same spot
    }

    maze_.PopulateWithFood(kNumFoodItems_);
    
    coord_multiplier_x_ = ((float) ofGetWindowWidth()) / maze_.GetWidth(); // bug here - doesn't take into account the size of the object - causes ovelap
    coord_multiplier_y_ = ((float) ofGetWindowHeight()) / maze_.GetHeight();
}

void PacmanGame::PhotoButtonPressed() { // listener - takes picture when button is pressed
    photo_taken_.setFromPixels(webcam_.getPixels()); // take the picture
    current_state_ = DISPLAYING_PHOTO;
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
        if (current_state_ == NOT_STARTED) { // play demo
            demo_movie_.update();
            
        } else if (current_state_ == TAKING_PHOTO) {
            webcam_.update(); // updates webcam - is a moving image
            
        } else if (current_state_ == DISPLAYING_PHOTO) {
            DetectFacesInPhoto();
            
        } else if (current_state_ == IN_PROGRESS) {
            ManageObjectCollisons();
            game_pacman_.Update(); // gets new location for the pacman and draws in the next tick
            
            // Explanation: We want the ghost to take a number of steps in its current
            // direction before changing directions so it won't look like it's just going in
            // a circle. However, we also need to make sure that each step the ghost takes
            // is clearly drawn out so it won't look like it's jumping around. So, I'm keeping
            // track of the number of steps the ghost moves in a direction before changing the
            // direction (which happens every CONST number of steps). Note that everything to
            // do with the ghost is in the ghost class for the sake of OOP (and because the
            // Pacman game has >1 ghosts ...)
            for (Ghost& current_ghost : all_ghosts_) {
                if (current_ghost.GetNumStepsTaken() % current_ghost.kNumStepsBeforeDirectionChange_) { // clean up later
                    current_ghost.FindRandomDirection();
                }
                current_ghost.MoveInNewDirection();
                current_ghost.IncrNumStepsTaken();
            }
            if (game_pacman_.IsDead()) {
               current_state_ = FINISHED;
            }
        }
    }
    should_update_ = true;
}

// DERIVED FROM EXAMPLE http://openframeworks.cc/documentation/ofxOpenCv/ofxCvHaarFinder/
void PacmanGame::DetectFacesInPhoto() { // using haar cascader (opencv) to detect faces
    ofxCvColorImage temp_color_img; // temp color img
    ofxCvGrayscaleImage grayscale_img_; // need to convert from regular iamge to ofxCvColorImage to ofxCvGrayscaleImage in order to use the haar cascader
    
    temp_color_img.setFromPixels(photo_taken_.getPixels()); // need to convert from regular iamge to ofxCvColorImage to ofxCvGrayscaleImage in order to use the haar cascader
    grayscale_img_.setFromColorImage(temp_color_img);
    
    //temp_color_img.draw(0, 0, temp_color_img.getWidth(), temp_color_img.getHeight());
    //grayscale_img_.draw(0, 0, grayscale_img_.getWidth(), grayscale_img_.getHeight());
    
    facial_detector_.findHaarObjects(grayscale_img_);
}

void PacmanGame::ManageObjectCollisons() { // contains logic for having objects eat each other, should probably rename the method
    ofVec2f pacman_pos = game_pacman_.GetMazePosition();
    ofRectangle pacman_rect = ofRectangle(pacman_pos.x * coord_multiplier_x_ + kOneDObjectSize_/2, pacman_pos.y * coord_multiplier_y_ + kOneDObjectSize_/2, kOneDObjectSize_, kOneDObjectSize_);

    if (maze_.GetElementAt(pacman_pos.x, pacman_pos.y) == Maze::FOOD) { // food
        maze_.RemoveFoodAt(pacman_pos.x, pacman_pos.y);
        pacman_eating_sound_.play();
        game_pacman_.EatObject(kFoodPointsWorth_); // add some sort of sound effect here
    }
    
    for (Ghost& current_ghost : all_ghosts_) { // ghost
        ofVec2f ghost_pos = current_ghost.GetMazePosition();
        ofRectangle ghost_rect = ofRectangle(ghost_pos.x * coord_multiplier_x_ + kOneDObjectSize_/2, ghost_pos.y * coord_multiplier_y_ + kOneDObjectSize_/2, kOneDObjectSize_, kOneDObjectSize_);
        
        if (pacman_rect.intersects(ghost_rect)) {
            ManagePacmanGhostCollisions(current_ghost);
        }
    }
}

void PacmanGame::ManagePacmanGhostCollisions(Ghost& current_ghost) { // responsible for all pacman-ghost iteractions
    Direction pacman_direction = game_pacman_.GetDirection(); // note: coords for 2d = 0, 0 is on the upper lhs
    Direction ghost_direction = current_ghost.GetDirection();
    
    ofVec2f pacman_pos = game_pacman_.GetMazePosition(); // considering changing the logic here as well
    ofVec2f ghost_pos = current_ghost.GetMazePosition();
    
    if (pacman_direction == ghost_direction) { // pacman eats the ghost if both objects are pointing in the same direction and the pacman is behind the ghost
        if (pacman_pos.x >= ghost_pos.x || pacman_pos.y >= ghost_pos.y) { // aka if pacman's x or y coord is bigger than the ghost's x y cords
            game_pacman_.EatObject(current_ghost.kPointsWorth_);
            
            for (int ghost_ind = 0; ghost_ind < all_ghosts_.size(); ghost_ind++) { // remove the ghost
                if (current_ghost.GetMazePosition() == all_ghosts_[ghost_ind].GetMazePosition()) {
                    all_ghosts_.erase(all_ghosts_.begin() + ghost_ind); // delete the ghost
                }
            }
            
        } else { // ghost eats the pacman if both objects are pointing in the same direction and the ghost is behind the pacman
            game_pacman_.GetsEaten(); // pacman dies
            pacman_death_sound_.play();
        }
    } else { // ghost eats the pacman if the objects are pointing in different directions
        if ((pacman_direction == NORTH && ghost_direction == SOUTH) || (pacman_direction == SOUTH && ghost_direction == NORTH)
            || (pacman_direction == WEST && ghost_direction == EAST) || (pacman_direction == EAST && ghost_direction == WEST)) {
            game_pacman_.GetsEaten(); // pacman dies
            pacman_death_sound_.play();
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
        DrawIntroduction();
    }
    else if (current_state_ == TAKING_PHOTO) {
        DrawWebcamUI(); // draw everything to do with the webcam
        
    } else if (current_state_ == DISPLAYING_PHOTO) {
        DrawFacialDetectionPhoto();
    }
    /*if (current_state_ == NOT_STARTED) {
        ofSetBackgroundColor(0, 0, 0); // set background as black
        
        intro_music_.setLoop(true); // plays over and over again
        intro_music_.play();
        
        ofSetColor(0, 200, 0); // green
        string_font_.drawString("WELCOME TO PACMAN!", ofGetWidth()/8, ofGetHeight()/8);

        ofSetColor(255, 255, 255); // white
        demo_movie_.draw(ofGetWidth()/4, ofGetHeight()/5, 400, 200); // play movie
        
        ofDrawBitmapString("Click anywhere to continue", ofGetWidth()/6, ofGetHeight()/6);
        
    } else if (current_state_ == PHOTO_TAKING) {
        DrawWebcamUI(); // draw everything to do with the webcam
        current_state_ = IN_PROGRESS;
        
    } else if (current_state_ == IN_PROGRESS) {
        DrawMaze();
        DrawGhosts();
        DrawPacman();
        DrawScoreboard();
        
    } else if(current_state_ == PAUSED) {
        DrawMaze();
        DrawGhosts();
        DrawPacman();
        DrawGamePaused();
        
    } else if(current_state_ == FINISHED) {
        DrawGameOver(); // draw another panel later
    }*/
}

// Adapted from OF-SNAKE MP: https://github.com/uiuc-sp18-cs126/of-snake-ElizWang (mostly just structural stuff)
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
        
    } else if (current_state_ == IN_PROGRESS) {
        Direction current_direction = game_pacman_.GetDirection();
        if (upper_key == 'W') { // change up order - makes logical sense
            // need to rotate pacman here
            game_pacman_.CalculateNumRotations(NORTH);
            game_pacman_.SetDirection(NORTH);
            update();
            should_update_ = false;
            
        } else if (upper_key == 'A') {
            game_pacman_.CalculateNumRotations(WEST);
            game_pacman_.SetDirection(WEST);
            update();
            should_update_ = false;
            
        } else if (upper_key == 'S') {
            game_pacman_.CalculateNumRotations(SOUTH);
            game_pacman_.SetDirection(SOUTH);
            update();
            should_update_ = false;
            
        } else if (upper_key == 'D') {
            game_pacman_.CalculateNumRotations(EAST);
            game_pacman_.SetDirection(EAST);
            update();
            should_update_ = false;
        }
        
    } else if (upper_key == 'R' && current_state_ == FINISHED) {
        Reset();
    }
}

void PacmanGame::mousePressed(int x, int y, int button){
    if (current_state_ == NOT_STARTED) {
        current_state_ = TAKING_PHOTO;
    }
}

void PacmanGame::Reset() { // resets everything
    //game_pacman_.reset();
    game_pacman_ = Pacman();
    
    for (Ghost& current_ghost : all_ghosts_) {
        current_ghost.SetInitialRandomPosition();
    }
    current_state_ = IN_PROGRESS;    
    maze_.Reset(); // clears all leftover food items and redraws food items    
}

void PacmanGame::windowResized(int w, int h){
    for (Ghost& current_ghost : all_ghosts_) {
        current_ghost.resize(w, h);
    }
    game_pacman_.resize(w, h);
}

void PacmanGame::DrawIntroduction() { // everything to do with the intro
    ofSetBackgroundColor(0, 0, 0); // set background as black
    
    intro_music_.setLoop(true); // plays over and over again
    intro_music_.play();
    
    ofSetColor(0, 200, 0); // green
    string_font_.drawString("WELCOME TO PACMAN!", ofGetWidth()/8, ofGetHeight()/8);
    
    ofSetColor(255, 255, 255); // white
    demo_movie_.draw(ofGetWidth()/4, ofGetHeight()/5, 400, 200); // play movie
    
    ofDrawBitmapString("Click anywhere to continue", ofGetWidth()/6, ofGetHeight()/6);
}

void PacmanGame::DrawWebcamUI() { // everything to do with the webcam
    ofClear(0);
    photo_taking_button_.draw();
    webcam_.draw(ofGetWidth() - ofGetWidth()/1.1, ofGetHeight() - ofGetHeight()/1.1, ofGetWidth()/1.1, ofGetHeight()/1.1);
}

void PacmanGame::DrawFacialDetectionPhoto() {
    // DERIVED FROM http://openframeworks.cc/documentation/ofxOpenCv/ofxCvHaarFinder/#show_findHaarObjects
    //photo_taken_.draw(0, 0, photo_taken_.getWidth(), photo_taken_.getHeight());
    for(int i = 0; i < facial_detector_.blobs.size(); i++) {
        ofRectangle facial_frame = facial_detector_.blobs[i].boundingRect;
        //ofDrawRectangle(rect);
        photo_taken_.drawSubsection(0, 0, facial_frame.getWidth(), facial_frame.getHeight(), facial_frame.getX(), facial_frame.getY()); // draws out the part of the photo corresponding to the face the haar cascade detected
    }
}

void PacmanGame::DrawMaze() { // draws the maze
    std::vector<std::pair<int, int> > food_indices; // use to store the indices of the food elements - so I can just directly iterate through this vector and draw the food items rathe than having to go through the maze again
    
    float x_coord;
    float y_coord; // debug
    for (int x_index = 0; x_index < maze_.GetWidth(); x_index++) { // draw the maze first and THEN draw apples over the maze to prevent the apples from being covered by maze blocks (which would make them look squished)
        x_coord = x_index * coord_multiplier_x_;
        for (int y_index = 0; y_index < maze_.GetHeight(); y_index++) {
            y_coord = y_index * coord_multiplier_y_;
            switch (maze_.GetElementAt(x_index, y_index)) {
                case Maze::NOTHING: // no wall
                    ofSetColor(100, 100, 100);
                    ofDrawRectangle(x_coord + kOneDObjectSize_/2, y_coord + kOneDObjectSize_/2, kOneDObjectSize_, kOneDObjectSize_);
                    break;
                case Maze::WALL: // wall
                    ofSetColor(225, 225, 225);
                    ofDrawRectangle(x_coord + kOneDObjectSize_/2, y_coord + kOneDObjectSize_/2, kOneDObjectSize_, kOneDObjectSize_);
                    break;
                case Maze::FOOD: // store indices of food elements
                    food_indices.push_back(std::make_pair(x_index, y_index));
            }
        }
    }
    
    for (int i = 0; i < food_indices.size(); i++) { // draw food AFTER drawing the maze to prevent overlap
        std::pair<int, int>& indices = food_indices[i];
        DrawFood(indices.first, indices.second);
    }
}

void PacmanGame::DrawFood(int x_index, int y_index) {
    ofImage food_image_; // image that correpsonds with a food object
    food_image_.load(kFoodImagePath_);
    food_image_.draw(x_index * coord_multiplier_x_ + kOneDObjectSize_/2, y_index * coord_multiplier_y_ + kOneDObjectSize_/2, kOneDObjectSize_, kOneDObjectSize_);

}

void PacmanGame::DrawGhosts() { // just make sizes all the same for simplicity
    for (Ghost& current_ghost : all_ghosts_) {
        ofVec2f pos = current_ghost.GetMazePosition();
        current_ghost.GetGhostImage().draw(pos.x * coord_multiplier_x_ + kOneDObjectSize_/2, pos.y * coord_multiplier_y_ + kOneDObjectSize_/2, kOneDObjectSize_, kOneDObjectSize_);
    }
}

void PacmanGame::DrawPacman() {
    ofVec2f& pos = game_pacman_.GetMazePosition();
    game_pacman_.GetPacmanImage().rotate90(game_pacman_.GetNumRotations());
    
    game_pacman_.GetPacmanImage().draw(pos.x * coord_multiplier_x_ + kOneDObjectSize_/2, pos.y * coord_multiplier_y_ + kOneDObjectSize_/2, kOneDObjectSize_, kOneDObjectSize_);
    game_pacman_.ClearNumRotations(); // set back to 0 to prevent the pacman from spinning into oblivion
}

void PacmanGame::DrawScoreboard() {
    std::string current_score = "Current score: " + std::to_string(game_pacman_.GetNumPoints());
    
    ofSetColor(200, 200, 200);
    ofDrawBitmapString(current_score, ofGetWidth() - 200, ofGetHeight() - 200);
    //string_font_.drawString(current_score, ofGetWidth() - 200, ofGetHeight() - 200);
}

void PacmanGame::DrawGameOver() {
    ofSetBackgroundColor(0, 0, 0); // set background as black
    string_font_.drawString("YOU LOST!", ofGetWidth()/1.5, ofGetHeight()/1.5);
}

void PacmanGame::DrawGamePaused() {
    std::string pause_message = "P to Unpause!";
    ofSetColor(0, 0, 0);
    ofDrawBitmapString(pause_message, ofGetWindowWidth() / 1.5, ofGetWindowHeight() / 1.5);
}

