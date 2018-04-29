#pragma once
#include <algorithm>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <memory>
#include <utility>

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOpenCv.h"
#include "header_addons/ofxCenteredTrueTypeFont.h" // cente ring font
#include "maze.h"
#include "pacman.h"
#include "ghost.h"
#include "food.h"

// LOOSELY adapted from OF-SNAKE MP: https://github.com/uiuc-sp18-cs126/of-snake-ElizWang (mostly just structural stuff)

class PacmanGame : public ofBaseApp {
private:
    // Enum to represent the current state of the game
    enum GameState {
        NOT_STARTED = 0,
        DISPLAYING_INSTRUCTIONS,
        SETTINGS,
        TAKING_PHOTO,
        DISPLAYING_PHOTO,
        IN_PROGRESS,
        PAUSED,
        WON_GAME,
        LOST_GAME
    };

    //NOTE: Need to have 2 enums and then set the actual level/input method after the user clicks the screen because the user can select one button and then unselect it again
    enum Level { // corresponds to the user-selected level
        EASY = 0,
        MEDIUM,
        HARD
    };

    enum DataInputMethod { // corresponds to the user-selected data input method
        DEFAULT_PACMAN = 0,
        USER_HEADSHOT,
    };

    // SOUND PATHS
    std::string kIntroMusicPath_ = "sound_files/intro_music.mp3"; // Default dir = <proj dir>/bin/data
    std::string kPacmanEating_ = "sound_files/eating_sound.mp3";
    std::string kCoinCollection_ = "sound_files/coin_collection.mp3";
    std::string kWilhelmScreamPath_ = "sound_files/wilhelmscream.mp3";
    std::string kDemoMoviePath_ = "demos/demo_purple_theme.mov";
    
    // MISC PATHS
    std::string kTextPath_ = "font_files/roboto_black.ttf";
    std::string kFoodImagePath_ = "image_files/apple.png";
    std::string kCoinImagePath_ = "image_files/coin.png";
    std::string kFacialCascadePath_ = "haar_cascades/haarcascade_frontalface_alt.xml";
    
    // ALL SOUNDS
    ofSoundPlayer background_music_; // plays music
    ofSoundPlayer wilhelm_scream_; // wilhem scream
    ofSoundPlayer crunch_; // cartoonish crunch
    ofSoundPlayer coin_collection_; // ka-ching
    
    // FOR INTRODUCTION PANEL
    ofxCenteredTrueTypeFont title_font_; // sets font, used to print centered titles
    ofxCenteredTrueTypeFont body_font_; // sets font, used to print centered text

    GameState current_state_ = NOT_STARTED; // The current state of the game, used to determine possible actions
    Level current_level_ = MEDIUM; // default
    DataInputMethod data_input_method_ = DEFAULT_PACMAN; // default - doesn't really matter because it's being set later

    ofVideoPlayer demo_movie_; // demo of what the game looks like

    // EVERYTHING TO DO WITH THE WEBCAM (taking photos and the general UI)
    ofVideoGrabber webcam_; // turns on webcam and gets webcam video feed
    ofImage photo_taken_; // stores the photo taken
    bool show_webcam_ = true; // to show the webcam
    
    // FACIAL DETECTION
    ofxCvHaarFinder facial_detector_; // finds faces
    ofxCvColorImage temp_color_img; // temp color img
    ofxCvGrayscaleImage grayscale_img_; // need to convert from regular iamge to ofxCvColorImage to ofxCvGrayscaleImage in order to use the haar cascader
    
    // BUTTONS - using ofxCenteredTrueTypeFont and the bounding rectangle
    std::string default_pacman_message_;
    ofRectangle default_pacman_button_;
    
    std::string user_image_message_;
    ofRectangle user_image_pacman_button_;
    
    std::string easy_level_message_;
    ofRectangle easy_level_button_;
    
    std::string medium_level_message_;
    ofRectangle medium_level_button_;

    std::string hard_level_message_;
    ofRectangle hard_level_button_;

    // calculated - for scaling
    int button_width_divider_;
    int button_height_divider_;
    int data_button_y_;
    int level_button_y_;
    
    ofColor default_pacman_button_color_ = ofColor(100, 0, 200, 100); // to make the buttons light up - keep track of color
    ofColor user_image_pacman_button_color_ = ofColor(100, 0, 200, 100);
    ofColor easy_level_button_color_ = ofColor(100, 0, 200, 100);
    ofColor medium_level_button_color_ = ofColor(100, 0, 200, 100);
    ofColor hard_level_button_color_ = ofColor(100, 0, 200, 100);
    ofColor clicked_button_color = ofColor(230, 230, 230, 100);

    bool is_level_button_clicked_; // has at least one level button been clicked?
    bool is_data_input_button_clicked_; // has at least one data input button been clicked?
    bool is_user_image_button_clicked_;
    bool is_pacman_button_clicked_; // keeps track of the buttons that are are clicked - so that the screen only changes after all buttons are clicked  (and shows the highlighted buttons for a brief amount of time)
    bool is_screen_clicked_; // user needs to click a third time to progress to the next screen
    
    void ResetPacmanButtonColors();
    void ResetLevelButtonColors(); // resets the colors if multiple buttons are clicked and then released or if the game is reset
    // BUTTON STUFF ENDS HERE
    
    // OBJECTS
    Maze maze_; // object that stores the maze, created a class for this to protect the maze from being modified and to allow the other objects to access the maze (to check for valid positions)
    Pacman game_pacman_; // The object that represents the user controlled snake
    std::vector<Ghost> ghosts_;

    // OBJECT PROPERTIES - CONSTANTS
    int num_ghosts_;
    int num_food_items; // food items to put in map - can change
    int num_coins_; // coins to put in map - can change
    int one_d_object_size_; // standardized size for all the objects (to prevent the bigger ones from "leaving" the maze). Calculated from window dimensions in setup().
    
    // MULTIPLIERS - convert coordinates on the maze matrix to coordinates on a coordinate plane
    float coord_multiplier_x_;
    float coord_multiplier_y_;
    float space_between_objects_; // constant space between objects, just for format
    float vertical_shift_; // to shift the maze to the bottom of the screen
    float horizontial_shift_; // center horizontally
    
    bool should_update_ = true;     // A flag boolean used in the update() function.
    
    // METHODS
    // FOR INTRODUCTIONARY PARTS
    void SetUpGameObjects();
    void SetUpButtons();
    void CalculateDimensions();
    void DetectFacesInPhoto(); // use haar cascade to detect faces

    // FACIAL PROCESSING
    void SetFaceAsPacman(); // cuts the face out and uses it as pacman

    // COLLISIONS
    void ManageObjectCollisons(); // contains logic for objects eating each other rename later
    bool DoesPacmanEatGhost(Ghost& current_ghost); // interactions between the pacman and the ghost
    
    // CHECK IF THE OBJECT'S NEW POSITION IS VALID
    bool IsNewPositionValid(); // in ofapp instead of pacman/ghost to avoid having to create multiple copies of maze

    // METHODS FOR RENDERING
    void DrawIntroduction();
    void DrawInstructions();
    void DrawSettings(); // difficulty level, data input
    void DrawWebcamUI();
    void DrawFacialDetectionPhoto();
    void DrawMaze();
    void DrawFood(int x_index, int y_index);
    void DrawCoin(int x_index, int y_index);
    void DrawGhosts();
    void DrawPacman();
    void DrawScoreboard();
    void DrawGamePaused();
    void DrawGameOver();
    
    // For setting the game based on the user input
    void SetGameLevel(); // setting the finalized game level (called after the user clicks to move on)
    void SetInputMethod(); // setting the finalized input method (called after the user clicks to move on)

    void ManageUserInputtedLevel(int x, int y); // contains code for managing what the user inputs for the level - helper to mousepressed
    void ManageDataInputChoice(int x, int y); // contains code for managing what the user wants to input as data for the pacman - for settings panel, helper to mousepressed

    // Checks if pacman won - if it ate every consumable item on the board
    bool DidPacmanWin();
    
    // Resets the game objects to their original state.
    void Reset();
    
public:
    // Function used for one time setup
    void setup();
    
    // Main event loop functions called on every frame
    void update();
    void draw();
    
    // Event driven functions, called on appropriate user action
    void keyPressed(int key);
    void windowResized(int w, int h);
    void mousePressed(int x, int y, int button);
};


