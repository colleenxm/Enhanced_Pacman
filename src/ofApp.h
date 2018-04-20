#pragma once
#include <ctime>
#include <cstdlib>
#include <utility>

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
    
    // Note: Dynamically allocationg all eatable objects (except for the pacman) so I can delete them later
    Pacman game_pacman_; // The object that represents the user controlled snake
    Ghost ghost_1_; // represents a ghost, note that ghosts can eat the pacman (which would end the game) but the pacman can also eat ghosts (which would drastically increase its num of points)
    Food/***/ game_food_;
    
    bool should_update_ = true;     // A flag boolean used in the update() function.
    
    void interact_pacman_with_ghost(); // interactions between the pacman and the ghost (rename method later - weird grammar)
    
    // Private helper methods to render various aspects of the game on screen.
    void draw_ghosts();
    void draw_pacman();
    void draw_food();
    
    void drawGameOver();
    void drawGamePaused();
    
    // Resets the game objects to their original state.
    void reset();
        
public:
    /*PacmanGame() : game_food_ (new Food()){}
    
    ~PacmanGame() {
        delete game_food_;
    }*/
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

