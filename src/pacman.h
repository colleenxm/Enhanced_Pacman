#include "ofMain.h"
#include "direction.h"
#include "ghost.h"
#include "food.h"
#include "maze.h"

#pragma once

class Pacman {
private:
    Direction current_direction_; // current direction
    ofVec2f screen_dims_; // The current screen dimensions (needed to calculate values on resize()
    
    int num_points_; // corresponds to the food eaten
    ofVec2f maze_position_; // x, y position of the maze - important: this corresponds to the MAZE ELEMENT and NOT to the actual coordinates in the coordinatep lane

    ofImage pacman_image_; // image that correpsonds with the pacman
    ofImage original_face_image_; // saves original face image for reset method - rotate method changes the image so we need to be able to reset it 
    std::string kImagePath_ = "/Users/elizabeth/CS126-FINAL-PROJECT/final-project-ElizWang/bin/data/image_files/pacman.png";
    
    bool is_eaten_ = false; // dies if eaten
    bool is_using_face_image_ = false; // true if using an image of a face - used to reset the pacman to the face rather than the default obj
    
    Maze maze_; // keeps track of the maze - to check if position is valid, same maze as the one in the game
    
    int num_rotations_; // keeps track of the number of rotations needed
    
public:
    Pacman(); // Default constructor, initializes and places length 1 snake
    
    // Methods to use adapted from OF-SNAKE MP (Food class): https://github.com/uiuc-sp18-cs126/of-snake-ElizWang
    ofVec2f& GetMazePosition();
    
    void SetFacialImage(ofImage facial_image); // replaces the default yellow pacman
    ofImage& GetPacmanImage(); // gets image
    
    Direction GetDirection() const; // Gets the current direction
    void SetDirection(Direction new_direction); // Sets the current direction
    
    void CalculateNumRotations(Direction new_direction); // calculates the number of 90 degree clockwise rotations needed
    void ClearNumRotations(); // sets num rotations back to 0, must be called each time an object finishes rotation
    int GetNumRotations(); // returns the number of rotations
    
    bool IsDead();
    void GetsEaten(); // pacman is eaten
    
    void Update(); // updates the pacman in the current direction
    
    void EatObject(int points_gained); // gains points by eating objects - note that only the number of points gained is passed in rather than a reference to the object itself (so this method can work for both food and ghost objects)
    
    void resize(int w, int h); // resizes
    int GetNumPoints() const; // Gets the number of points
    
    int GetIndex(Direction direction); // get index from direction - need to move this elsewhere
    void reset(); // clears everything
};

