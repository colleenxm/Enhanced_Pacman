#pragma once
#include <algorithm>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <memory>
#include <utility>

#include "maze.h"
#include "ofMain.h"
#include "pacman.h"
#include "ghost.h"
#include "food.h"

// LOOSELY adapted from OF-SNAKE MP: https://github.com/uiuc-sp18-cs126/of-snake-ElizWang (mostly just structural stuff)

class PacmanGame : public ofBaseApp {
private:
    // Enum to represent the current state of the game
    enum GameState {
        NOT_STARTED = 0,
        IN_PROGRESS,
        PAUSED,
        FINISHED
    };
    
    // FOR INTRODUCTION PANEL
    ofSoundPlayer intro_music_; // plays music
    ofTrueTypeFont string_font_; // sets font, used to print strings with colors/sizes/fonts other than the default
    GameState current_state_ = NOT_STARTED; // The current state of the game, used to determine possible actions
    
    const int kNumFoodItems_ = 10; // 10 food items to put in map - can change
    const int kOneDObjectSize_ = 20; // standardized size for all the objects (to prevent the bigger ones from "leaving" the maze)
    
    // The multipliers convert coordinates on the maze matrix to coordinates on a coordinate plane
    float coord_multiplier_x_;
    float coord_multiplier_y_;
    
    Maze maze_; // object that stores the maze, created a class for this to protect the maze from being modified and to allow the other objects to access the maze (to check for valid positions)
    
    // Note: Dynamically allocationg all eatable objects (except for the pacman) so I can delete them later
    Pacman game_pacman_; // The object that represents the user controlled snake
    Ghost ghost_1_; // represents a ghost, note that ghosts can eat the pacman (which would end the game) but the pacman can also eat ghosts (which would drastically increase its num of points)

    // FOOD DATA
    const int kFoodPointsWorth_ = 1; // how many points a food object is worth
    std::string kFoodImagePath_ = "/Users/elizabeth/CS126-FINAL-PROJECT/final-project-ElizWang/bin/data/image_files/apple.png";
    
    bool should_update_ = true;     // A flag boolean used in the update() function.
    
    void InteractPredatorPreyObjects(); // contains logic for objects eating each other rename later
    void InteractPacmanWithGhost(); // interactions between the pacman and the ghost (rename method later - weird grammar)
    // Private helper methods to render various aspects of the game on screen.
    void draw_food(int x_index, int y_index);
    void draw_maze();
    void draw_ghosts();
    void draw_pacman();
    
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
    void mousePressed(int x, int y, int button);
};


