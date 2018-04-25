#include "ofApp.h"

// Setup method
void PacmanGame::setup(){
    ofSetWindowTitle("ENHANCED PACMAN");
    
    srand(static_cast<unsigned>(time(0))); // Seed random with current time
    
    // LOADING FROM PATH
    title_font_.load(kTextPath_, 32);
    body_font_.load(kTextPath_, 16);

    background_music_.load(kIntroMusicPath_);
    crunch_.load(kPacmanEating_);
    coin_collection_.load(kCoinCollection_);
    wilhelm_scream_.load(kWilhelmScreamPath_);
    demo_movie_.load(kDemoMoviePath_);
    
    // WEBCAM SETUP
    webcam_.setup(2000, 2000);

    // HAAR CASCADER SETUP
    facial_detector_.setup(kFacialCascadePath_);
    
    // CALCULATING DIMENSIONS
    space_between_objects_ = 8; //0.0075 * ofGetWidth() + 0.0075 * ofGetHeight();
    one_d_object_size_ = 0.02 * ofGetWidth() + 0.02 * ofGetHeight(); //shouldn't be a fixed const nor should it be dependent on the number of objects there are
    coord_multiplier_x_ = ((float) ofGetWidth()) / maze_.GetWidth(); // center
    coord_multiplier_y_ = ((float) ofGetHeight()) / maze_.GetHeight();
    //vertical_shift_ = ofGetHeight() - one_d_object_size_ * maze_.GetHeight() * 1.05;
    //horizontial_shift_ = ofGetWidth() - one_d_object_size_ * maze_.GetWidth();
    float rectangular_width = maze_.GetWidth() * one_d_object_size_;
    float rectangular_height = maze_.GetHeight() * one_d_object_size_;
    float starting_x = ofGetWidth()/2 - rectangular_width/2;
    float starting_y = ofGetHeight() - rectangular_height;
    vertical_shift_ = 0; //ofGetHeight() - rectangular_height + 1.15 * one_d_object_size_;
    horizontial_shift_ = 0; //ofGetWidth()/2 - rectangular_width/2.5;  //+ 1.5 * one_d_object_size_;
    
    // SET BACKGROUND MUSIC
    background_music_.setLoop(true); // plays over and over again
    background_music_.play();
    
    SetUpButtons();
    SetUpObjects();
}

void PacmanGame::SetUpObjects() {
    // OBJECTS SETUP
    for (int current_num_ghosts = 0; current_num_ghosts < num_ghosts_; current_num_ghosts++) {
        Ghost ghost;
        ghost.SetInitialRandomPosition();
        ghosts_.push_back(ghost);
        
        // make sure ghosts aren't all at the same spot
    }
    maze_.PopulateWithFood(num_food_items);
    maze_.PopulateWithCoins(num_coins_);
}

void PacmanGame::SetUpButtons() { // for readability
    default_pacman_message_ = "DEFAULT PACMAN";
    user_image_message_ = "MY IMAGE";
    easy_level_message_ = "EASY";
    medium_level_message_ = "MEDIUM";
    hard_level_message_ = "HARD";
    
    int data_button_width = 200;
    int data_button_height = 150;
    button_width_divider_ = 3.5;
    button_height_divider_ = 8;
    data_button_y_ = ofGetHeight() - 1.75*data_button_height;
    default_pacman_button_.set(0.5*ofGetWidth()/button_width_divider_, data_button_y_, data_button_width, data_button_height);
    user_image_pacman_button_.set(1.5*ofGetWidth()/button_width_divider_, data_button_y_, data_button_width, data_button_height);
    
    level_button_y_ = ofGetHeight()/3.5;
    int level_button_width = 150; // different bc there's more of them
    int level_button_height = 100;
    easy_level_button_.set(0.5*ofGetWidth()/button_width_divider_, level_button_y_, level_button_width, level_button_height);
    medium_level_button_.set(1.25*ofGetWidth()/button_width_divider_, level_button_y_, level_button_width, level_button_height);
    hard_level_button_.set(2*ofGetWidth()/button_width_divider_, level_button_y_, level_button_width, level_button_height);
    
    is_level_button_clicked_ = false;
    is_pacman_button_clicked_ = false;
    is_user_image_button_clicked_ = false;
}

void PacmanGame::SetFaceAsPacman() { // cuts the face out and uses it as pacman
    ofRectangle facial_frame = facial_detector_.blobs[0].boundingRect;
    ofImage cropped_face;
    cropped_face.cropFrom(photo_taken_, facial_frame.getX(), facial_frame.getY(), facial_frame.getWidth(), facial_frame.getHeight());
    
    game_pacman_.SetFacialImage(cropped_face); // need to set as pacman image
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
            for (Ghost& current_ghost : ghosts_) {
                if (current_ghost.GetNumStepsTaken() % current_ghost.kNumStepsBeforeDirectionChange_) {
                    current_ghost.FindRandomDirection();
                }
                current_ghost.MoveInNewDirection();
                current_ghost.IncrNumStepsTaken();
            }
            if (DidPacmanWin()) {
               current_state_ = WON_GAME;
            } else if (game_pacman_.IsDead()) {
                current_state_ = LOST_GAME;
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
    
    facial_detector_.findHaarObjects(grayscale_img_);
}

void PacmanGame::ManageObjectCollisons() { // contains logic for having objects eat each other, should probably rename the method
    ofVec2f pacman_pos = game_pacman_.GetMazePosition();
    ofRectangle pacman_rect = ofRectangle(pacman_pos.x * coord_multiplier_x_ + one_d_object_size_/2, pacman_pos.y * coord_multiplier_y_ + one_d_object_size_/2, one_d_object_size_, one_d_object_size_);

    if (maze_.GetElementAt(pacman_pos.x, pacman_pos.y) == Maze::FOOD) { // food
        maze_.RemoveFoodAt(pacman_pos.x, pacman_pos.y);
        crunch_.play();
        game_pacman_.EatObject(maze_.kFoodPointsWorth_); // add some sort of sound effect here
        
    } else if (maze_.GetElementAt(pacman_pos.x, pacman_pos.y) == Maze::COIN) { // coin
        maze_.RemoveCoinAt(pacman_pos.x, pacman_pos.y);
        coin_collection_.play();
        game_pacman_.EatObject(maze_.kCoinPointsWorth_); // add some sort of sound effect here
    }
    for (int ghost_ind = 0; ghost_ind < ghosts_.size(); ghost_ind++) { // ghost
        Ghost& current_ghost = ghosts_[ghost_ind];
        ofVec2f ghost_pos = current_ghost.GetMazePosition();
        
        if (pacman_pos.x == ghost_pos.x && pacman_pos.y == ghost_pos.y) {
            if (DoesPacmanEatGhost(current_ghost)) { // remove the current ghost
                ghosts_.erase(ghosts_.begin() + ghost_ind); // delete the ghost
            }
        }
    }
}

bool PacmanGame::DoesPacmanEatGhost(Ghost& current_ghost) { // responsible for all pacman-ghost iteractions, true if pacman eats the ghost, false otherwise
    if (game_pacman_.GetDirection() == current_ghost.GetDirection()) { // pacman eats the ghost if both objects are pointing in the same direction
        game_pacman_.EatObject(current_ghost.kPointsWorth_);
        crunch_.play();
        return true;
    }
    game_pacman_.GetsEaten(); // pacman dies
    wilhelm_scream_.play();
    return false;
}

bool PacmanGame::DidPacmanWin() { // true if the pacman eats everything on the board, false otherwise
    return !maze_.ContainsConsumableObjects() && (ghosts_.size() == 0); // no consumable objects and no ghosts
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
        
    } else if (current_state_ == DISPLAYING_INSTRUCTIONS) {
        DrawInstructions();
        
    } else if (current_state_ == SETTINGS) {
        DrawSettings();
        
    } else if (current_state_ == TAKING_PHOTO) {
        DrawWebcamUI(); // draw everything to do with the webcam
        
    } else if (current_state_ == DISPLAYING_PHOTO) {
        DrawFacialDetectionPhoto();
        
    } else if (current_state_ == IN_PROGRESS) {
        //DrawTitle();
        DrawMaze();
        DrawGhosts();
        DrawPacman();
        DrawScoreboard();
        
    } else if(current_state_ == PAUSED) {
        //DrawTitle();
        DrawMaze();
        DrawGhosts();
        DrawPacman();
        DrawScoreboard();
        DrawGamePaused();
       
    } else if (current_state_ == WON_GAME || current_state_ == LOST_GAME) {
        DrawGameOver();
    }
}

void PacmanGame::DrawIntroduction() { // everything to do with the intro
    ofSetBackgroundColor(0, 0, 0); // set background as black
    
    background_music_.setLoop(true); // plays over and over again
    background_music_.play();
    
    ofSetColor(100, 0, 200); // green
    std::string introduction_title = "WELCOME TO PACMAN!";
    title_font_.drawStringCentered(introduction_title, ofGetWidth()/2, ofGetHeight()/8);
    
    ofSetColor(255, 255, 255); // white
    body_font_.drawStringCentered("Click anywhere to continue.", ofGetWidth()/2, ofGetHeight()/5);
    
    const int kDivider = 2; // keep track of to center the demo, inversely proportional to size of the movie
    demo_movie_.draw(ofGetWidth()/2 - ofGetWidth()/(2 * kDivider), ofGetHeight()/2 - ofGetHeight()/(2 * kDivider), ofGetWidth()/kDivider, ofGetHeight()/kDivider); // play movie
    demo_movie_.play();
}

void PacmanGame::DrawInstructions() {
    ofSetBackgroundColor(0, 0, 0); // set background as black
    
    ofSetColor(100, 0, 200); // purple
    title_font_.drawString("INSTRUCTIONS", ofGetWidth()/6, ofGetHeight()/10);

    ofSetColor(255, 255, 255); // white
    
    std::string instructions = "This game is an enhanced version of Pacman.\n1.You (the pacman) can navigate through the maze using WASD logic \n\t\t\tW = north \n\t\t\tD = east \n\t\t\tS = south \n\t\t\tA = west.\n2.You can also press 'p' to pause and 'r' to reset the game after it ends.\n3.Your goal is to consume apples (1 point)\n and gold coins (8 points).\n4.You may attempt to eat ghosts (10 points), which can also eat you.\n5. You win if you eat all the pieces on the board.\n6. You lose if you're eaten by a ghost.\n\n\n\t\t\tClick anywhere to continue.";
    body_font_.drawString(instructions, ofGetWidth()/15, ofGetHeight()/3);
}

void PacmanGame::DrawSettings() { // difficulty level
    ofSetBackgroundColor(0, 0, 0); // set background as black
    // difficulty level - slider
    
    ofSetColor(100, 0, 200); // purple
    title_font_.drawStringCentered("SETTINGS", ofGetWidth()/2, ofGetHeight()/12);

    ofSetColor(255, 255, 255); // white
    std::string instructions = "Choose your difficulty level and image input method. Afterwards, click anywhere to continue.\n";
    body_font_.drawStringCentered(instructions, ofGetWidth()/2, ofGetHeight()/7);
    
    ofxCenteredTrueTypeFont subtitle_font_; // sets font, used to print centered text
    subtitle_font_.load(kTextPath_, 25);
    ofSetColor(100, 0, 200); // purple
    subtitle_font_.drawStringCentered("DIFFICULTY LEVEL", ofGetWidth()/2, ofGetHeight()/4);
    
    ofSetColor(easy_level_button_color_); // buttons light up once you choose them
    ofDrawRectRounded(easy_level_button_, 20);
    ofSetColor(medium_level_button_color_);
    ofDrawRectRounded(medium_level_button_, 20);
    ofSetColor(hard_level_button_color_);
    ofDrawRectRounded(hard_level_button_, 20);

    ofSetColor(255, 255, 255); // white
    body_font_.drawString(easy_level_message_, 0.55*ofGetWidth()/button_width_divider_, level_button_y_*1.15);
    body_font_.drawString(medium_level_message_, 1.30*ofGetWidth()/button_width_divider_, level_button_y_*1.15);
    body_font_.drawString(hard_level_message_, 2.05*ofGetWidth()/button_width_divider_, level_button_y_*1.15);

    ofSetColor(100, 0, 200); // purple
    subtitle_font_.drawStringCentered("IMAGE INPUT METHOD", ofGetWidth()/2, ofGetHeight()/2);
    
    ofSetColor(default_pacman_button_color_);
    ofDrawRectRounded(default_pacman_button_, 20);
    ofSetColor(user_image_pacman_button_color_);
    ofDrawRectRounded(user_image_pacman_button_, 20);

    ofSetColor(255, 255, 255); // white
    body_font_.drawStringCentered(default_pacman_message_, 0.95*ofGetWidth()/button_width_divider_, data_button_y_*1.15);
    body_font_.drawStringCentered(user_image_message_, 0.95*2*ofGetWidth()/button_width_divider_, data_button_y_*1.15);
}

void PacmanGame::DrawWebcamUI() { // everything to do with the webcam
    ofClear(0);
    
    ofSetColor(255, 255, 255); // white
    body_font_.drawStringCentered("Click anywhere to take a picture\nor click the button to use the default pacman.\nMake sure your face is clearly visible.\n", ofGetWidth()/2, ofGetHeight()/9);
    webcam_.draw(ofGetWidth()/2 - ofGetWidth()/5, ofGetHeight()/2 - ofGetHeight()/5, ofGetWidth()/2.5, ofGetHeight()/2.5);
}

void PacmanGame::DrawFacialDetectionPhoto() {
    // DERIVED FROM http://openframeworks.cc/documentation/ofxOpenCv/ofxCvHaarFinder/#show_findHaarObjects
    if (facial_detector_.blobs.size() > 0) { // takes the first face found - change later?
        ofSetColor(255, 255, 255); // white
        body_font_.drawString("Click anywhere to proceed to the game or press 'r' to retake the photo", ofGetWidth()/15, ofGetHeight()/15);

        ofRectangle facial_frame = facial_detector_.blobs[0].boundingRect;
        photo_taken_.drawSubsection(ofGetWidth()/2 - facial_frame.getWidth()/2, ofGetHeight()/2 - facial_frame.getHeight()/2, facial_frame.getWidth(), facial_frame.getHeight(), facial_frame.getX(), facial_frame.getY()); // draws out the part of the photo corresponding to the face the haar cascade detected
    } else {
        body_font_.drawString("ERROR - face not found", ofGetWidth()/2, ofGetHeight()/2); // loop back
        current_state_ = TAKING_PHOTO;
    }
}

void PacmanGame::DrawMaze() { // draws the maze
    std::vector<std::pair<int, int> > food_indices; // use to store the indices of the food elements - so I can just directly iterate through this vector and draw the food items rathe than having to go through the maze again
    std::vector<std::pair<int, int> > coin_indices;
    
    float x_coord;
    float y_coord; // debug
    
    for (int x_index = 0; x_index < maze_.GetWidth(); x_index++) { // draw the maze first and THEN draw apples over the maze to prevent the apples from being covered by maze blocks (which would make them look squished)
        x_coord = x_index * coord_multiplier_x_;
        for (int y_index = 0; y_index < maze_.GetHeight(); y_index++) {
            y_coord = y_index * coord_multiplier_y_;
            
            auto maze_element = maze_.GetElementAt(x_index, y_index);
            if (maze_element == Maze::NOTHING || maze_element == Maze::FOOD || maze_element == Maze::COIN) { // want to draw a gray square if it's not a wall
                ofSetColor(100, 0, 100); // purple
                ofDrawRectangle(x_coord + one_d_object_size_/2 + horizontial_shift_, y_coord + one_d_object_size_/2 + vertical_shift_, one_d_object_size_, one_d_object_size_);
                if (maze_element == Maze::FOOD) {
                    food_indices.push_back(std::make_pair(x_index, y_index));
                } else if (maze_element == Maze::COIN) {
                    coin_indices.push_back(std::make_pair(x_index, y_index));
                }
            } else if (maze_element == Maze::WALL) {
                ofSetColor(100, 100, 100); // gray
                ofDrawRectangle(x_coord + one_d_object_size_/2 + horizontial_shift_, y_coord + one_d_object_size_/2 + vertical_shift_, one_d_object_size_, one_d_object_size_);
            }
        }
    }
    ofSetColor(255, 255, 255); // white
    for (auto food_index : food_indices) { // then draw food/coin items on top
        DrawFood(food_index.first, food_index.second);
    }
    for (auto coin_index : coin_indices) {
        DrawCoin(coin_index.first, coin_index.second);
    }
}

void PacmanGame::DrawFood(int x_index, int y_index) {
    ofImage food_image_; // image that correpsonds with a food object
    food_image_.load(kFoodImagePath_);
    food_image_.draw(x_index * coord_multiplier_x_ + one_d_object_size_/2 + horizontial_shift_, y_index * coord_multiplier_y_ + one_d_object_size_/2 + + vertical_shift_, one_d_object_size_, one_d_object_size_);
}

void PacmanGame::DrawCoin(int x_index, int y_index) {
    ofImage coin_image; // image that correpsonds with a food object
    coin_image.load(kCoinImagePath_);
    coin_image.draw(x_index * coord_multiplier_x_ + one_d_object_size_/2 + horizontial_shift_, y_index * coord_multiplier_y_ + one_d_object_size_/2 + + vertical_shift_, one_d_object_size_, one_d_object_size_);
}

void PacmanGame::DrawGhosts() { // just make sizes all the same for simplicity
    for (Ghost& current_ghost : ghosts_) {
        ofVec2f pos = current_ghost.GetMazePosition();
        current_ghost.GetGhostImage().draw(pos.x * coord_multiplier_x_ + one_d_object_size_/2 + horizontial_shift_, pos.y * coord_multiplier_y_ + one_d_object_size_/2 + + vertical_shift_, one_d_object_size_, one_d_object_size_);
    }
}

void PacmanGame::DrawPacman() {
    ofVec2f& pos = game_pacman_.GetMazePosition();
    game_pacman_.GetPacmanImage().rotate90(game_pacman_.GetNumRotations());
    
    game_pacman_.GetPacmanImage().draw(pos.x * coord_multiplier_x_ + one_d_object_size_/2 + horizontial_shift_, pos.y * coord_multiplier_y_ + one_d_object_size_/2 + vertical_shift_, one_d_object_size_, one_d_object_size_);
    game_pacman_.ClearNumRotations(); // set back to 0 to prevent the pacman from spinning into oblivion
}

void PacmanGame::DrawScoreboard() {
    std::string current_score = "Current score: " + std::to_string(game_pacman_.GetNumPoints());
    
    ofSetColor(0, 0, 0); // translucent
    title_font_.drawCenteredBoundingBox(current_score, ofGetWidth()/1.3, ofGetHeight()/60);
    ofSetColor(255, 255, 255);
    title_font_.drawStringCentered(current_score, ofGetWidth()/1.3, ofGetHeight()/60);
}

void PacmanGame::DrawGamePaused() {
    ofSetColor(0, 0, 0, 75);
    std::string pause_message = "Press 'p' to unpause.";
    title_font_.drawCenteredBoundingBox(pause_message, ofGetWidth()/2, ofGetHeight()/2);
    ofSetColor(0, 200, 0);
    title_font_.drawStringCentered(pause_message, ofGetWidth()/2, ofGetHeight()/2);
}

void PacmanGame::DrawGameOver() {
    ofSetBackgroundColor(0, 0, 0); // set background as black
    ofSetColor(100, 0, 200);
    
    std::string game_over_message;
    if (current_state_ == WON_GAME) {
        game_over_message = "YOU WON!";
    } else if (current_state_ == LOST_GAME) {
        game_over_message = "YOU LOST!";
    }
    title_font_.drawStringCentered(game_over_message, ofGetWidth()/2, ofGetHeight()/3);
    ofSetColor(255, 255, 255);
    body_font_.drawStringCentered("Your final score was: " +std::to_string(game_pacman_.GetNumPoints()), ofGetWidth()/2, ofGetHeight()/2.5);
    body_font_.drawStringCentered("Press 'r' to restart.", ofGetWidth()/2, ofGetHeight()/1.5);
}

// Adapted from OF-SNAKE MP: https://github.com/uiuc-sp18-cs126/of-snake-ElizWang (mostly just structural stuff)
/*
 Function that handles actions based on user key presses
 1. if key == p and game is not over, toggle pause
 2. if game is in progress handle WASD action
 3. if key == r and game is over reset it
 
 WASD logic:
 Let dir be the direction that corresponds to a key
 if current direction is not dir (Prevents key spamming to rapidly update the snake)
 and current_direction is not opposite of dir (Prevents the snake turning and eating itself)
 Update direction of snake and force a game update (see ofApp.h for why)
 */
void PacmanGame::keyPressed(int key){
    int upper_key = toupper(key); // Standardize on upper case
    
    if (upper_key == 'P' && (current_state_ == IN_PROGRESS || current_state_ == PAUSED)) {
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
        
    } else if (upper_key == 'R') {
        if (current_state_ == DISPLAYING_PHOTO) { // go back to taking the photo
            current_state_ = TAKING_PHOTO;
            
        } else if (current_state_ == LOST_GAME || current_state_ == WON_GAME) { // restart
            Reset();
        }
    }
}

void GetUserLevel() {
    
}

void GetUserImage() {
    
}

void PacmanGame::LightenColor(ofColor& color) { // helper method to mouse pressed to lighten the color of the button that's pressed
    int color_adjustment = 50;
    int color_max = 255;
    
    if (color.r + color_adjustment <= color_max) {
        color.r += color_adjustment;
    }
    if (color.g + color_adjustment <= color_max) {
        color.g += color_adjustment;
    }
    if (color.b + color_adjustment <= color_max) {
        color.b += color_adjustment;
    }
}

void PacmanGame::mousePressed(int x, int y, int button){
    if (current_state_ == NOT_STARTED) {
        current_state_ = DISPLAYING_INSTRUCTIONS;
        
    } else if (current_state_ == DISPLAYING_INSTRUCTIONS) {
        current_state_ = SETTINGS;
        
    } else if (current_state_ == SETTINGS) { // make sure both are clicked
        // 3 level buttons - can only choose 1
        if (easy_level_button_.inside(x, y)) {
            is_level_button_clicked_ = true;
            ResetLevelButtonColors(); // need to reset all colors in case the user selects a button and then changes his/her mind
            num_ghosts_ = 5; // level's being set but it doesn't stay???
            num_food_items = 5;
            num_coins_ = 5;
            LightenColor(easy_level_button_color_);
            
        } else if (medium_level_button_.inside(x, y)) {
            is_level_button_clicked_ = true;
            ResetLevelButtonColors();
            num_ghosts_ = 10;
            num_food_items = 15;
            num_coins_ = 5;
            LightenColor(medium_level_button_color_);

        } else if (hard_level_button_.inside(x, y)) {
            is_level_button_clicked_ = true;
            ResetLevelButtonColors();
            num_ghosts_ = 25;
            num_food_items = 15;
            num_coins_ = 15;
            LightenColor(hard_level_button_color_);
        }
        
        SetUpObjects(); // initialize everything here
        
        if (user_image_pacman_button_.inside(x, y)) {
            is_user_image_button_clicked_ = true;
            ResetPacmanButtonColors();
            LightenColor(user_image_pacman_button_color_);
            
        } else if (default_pacman_button_.inside(x, y)) { // covers all other options
            is_pacman_button_clicked_ = true;
            ResetPacmanButtonColors();
            LightenColor(default_pacman_button_color_);
        }
        
        if (is_user_image_button_clicked_ && is_level_button_clicked_) { // make sure all the buttons are actually selected
            current_state_ = TAKING_PHOTO;
        }
        
        if (is_pacman_button_clicked_ && is_level_button_clicked_) {
            current_state_ = IN_PROGRESS;
        }
        
    } else if (current_state_ == TAKING_PHOTO) {
        photo_taken_.setFromPixels(webcam_.getPixels()); // take the picture
        current_state_ = DISPLAYING_PHOTO;
        
    } else if (current_state_ == DISPLAYING_PHOTO) {
        SetFaceAsPacman();
        current_state_ = IN_PROGRESS;
    }
}

void PacmanGame::ResetPacmanButtonColors()  {
    // reset the button colors
    default_pacman_button_color_ = ofColor(100, 0, 200, 100); // to make the buttons light up - keep track of color
    user_image_pacman_button_color_ = ofColor(100, 0, 200, 100);
}

void PacmanGame::ResetLevelButtonColors()  {
    easy_level_button_color_ = ofColor(100, 0, 200, 100);
    medium_level_button_color_ = ofColor(100, 0, 200, 100);
    hard_level_button_color_ = ofColor(100, 0, 200, 100);
}

void PacmanGame::ClearGhosts() { // clear ghosts from the vector
    
}

void PacmanGame::Reset() { // resets everything
    game_pacman_.reset();
    
    for (Ghost& current_ghost : ghosts_) {
        current_ghost.SetInitialRandomPosition();
    }
    current_state_ = DISPLAYING_INSTRUCTIONS;
    maze_.Reset(); // clears all leftover food items and redraws food items
    
    ResetPacmanButtonColors();
    ResetLevelButtonColors();
    
    is_level_button_clicked_ = false; // unclicked
    is_pacman_button_clicked_ = false;
    is_user_image_button_clicked_ = false;
    
    num_ghosts_ = 0;
    num_food_items = 0;
    num_coins_ = 0;
    
    ghosts_ = std::vector<Ghost>(); // clear the ghosts!!!
}

void PacmanGame::windowResized(int w, int h){
    for (Ghost& current_ghost : ghosts_) {
        current_ghost.resize(w, h);
    }
    game_pacman_.resize(w, h);
    
    one_d_object_size_ = 0.02 * w + 0.02 * w; // shouldn't be a fixed const nor should it be dependent on the number of objects there are

    //space_between_objects_ = 0.01 * w + 0.01 * h;
    coord_multiplier_x_ = ((float) w) / maze_.GetWidth(); // center
    coord_multiplier_y_ = ((float) h) / maze_.GetHeight();
    vertical_shift_ = 0; //h - one_d_object_size_ * maze_.GetHeight() * 1.05;
    horizontial_shift_ = 0; //w - one_d_object_size_ * maze_.GetWidth();
}
