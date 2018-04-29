#pragma once
#include <random>

#include "direction.h"
#include "ofMain.h"
#include "maze.h"

class Ghost {
private:
    // FOR GENERATING RANDOM DIRECTIONS
    // Next 2 lines adapted from OF-SNAKE MP (Food class): https://github.com/uiuc-sp18-cs126/of-snake-ElizWang
    ofVec2f window_dims_;
    std::mt19937 generator_; // pseudorandom number generation
    
    // DIRECTIONS
    static const int kNumDirections_ = 4; // number of real directions, to exclude dummy direction
    Direction current_direction_ = EAST; // starts off going right
    
    // LOCATION
    int num_steps_taken_ = 0; // keeps track of the number of steps taken in the current direction
    ofVec2f maze_position_; // x, y position of the maze - important: this corresponds to the MAZE ELEMENT and NOT to the actual coordinates in the coordinatep lane.
    
    // GHOST IMAGE
    ofImage ghost_image_; // image that correpsonds with a ghost object
    static const std::string kImagePath_;
    
    Maze maze_; // keeps track of the maze - to check if position is valid, same maze as the one in the game
    
public:
    static const int kNumStepsBeforeDirectionChange_ = 20; // number of steps to take in the new  direction before changing direction. Note that this is used in ofApp so each step can be drawn out (else the ghost would jump around). No point in hiding this - will need a getter anyways
    static const int kPointsWorth_ = 10; // worth 10 points (b/c it's riskier to eat a ghost since the ghost can turn around and eat you)
    
    Ghost(); // Default constructor, sets up generator devices and rarndomly places food at a valid location
    
    // GETTERS AND SETTERS
    void SetInitialRandomPosition(); // intial random pos
    void SetDirection(Direction newDirection);
    ofVec2f GetMazePosition();
    ofImage& GetGhostImage(); // gets image
    int GetNumStepsTaken(); // gets the number of steps taken
    void IncrNumStepsTaken(); // increments the number of steps taken
    Direction& GetDirection(); // gets the current direction - needed to check whether the ghost is eating the pacman or if the pacman is eating the ghost
    
    // CALCULATING RANDOM DIRECTION AND MOVING IN IT
    void Update();
    void FindRandomDirection(); // finds new direction
    void MoveInNewDirection(); // moves in that random direction - note that this method is called more than choose_random_direction so the ghost can actually move before changing directions (will look like it's jumping around otherwise)
    void ModifyPosition(int x_incr, int y_incr); // adds x_incr to the x component of the maze position and y_incr to the y component of the maze position. Note that this method doesn't check if the new position is valid.
    
    void resize(int w, int h); // Called by application resize, resizes to new window dimensions
};

