#include "ofMain.h"
#include "direction.h"
#include "ghost.h"
#include "food.h"
#include "maze.h"

#pragma once

class Pacman {
private:
    // KEEPS TRACK OF DIMENSIONS AND POSITION
    Direction current_direction_; // current direction
    ofVec2f screen_dims_; // The current screen dimensions (needed to calculate values on resize()
    int num_points_; // corresponds to the food eaten
    
    // important: this corresponds to the MAZE ELEMENT and NOT to the actual coordinates in the coordinate plane
    ofVec2f maze_position_; // x, y position of the maze

    // HAS TO DO WITH DISPLAYING THE PACMAN IMAGE
    ofImage pacman_image_; // image that correpsonds with the pacman
    ofImage original_face_image_; // saves original face image for reset method - rotate method
        // changes the image so we need to be able to reset it
    static const std::string kImagePath_;
    int num_rotations_; // keeps track of the number of rotations needed

    // FLAGS
    bool is_eaten_ = false; // dies if eaten
    bool is_using_face_image_ = false; // true if using an image of a face
        
public:
    Pacman(); // Default constructor, initializes and places length 1 snake
    
    // Adapted from OF-SNAKE MP (Food class): https://github.com/uiuc-sp18-cs126/of-snake-ElizWang
    // GETTERS AND SETTERS
    ofVec2f& GetMazePosition();
    void SetFacialImage(ofImage facial_image); // replaces the default yellow pacman
    ofImage& GetPacmanImage(); // gets image
    Direction GetDirection() const; // Gets the current direction
    void SetDirection(Direction new_direction); // Sets the current direction
    int GetNumPoints() const; // Gets the number of points

    // DEALS WITH ROTATIONS
    void CalculateNumRotations(Direction new_direction); // calculates the number of 90 degree clockwise rotations needed
    void ClearNumRotations(); // sets num rotations back to 0, must be called each time an object finishes rotation
    int GetNumRotations(); // returns the number of rotations
    
    // MODIFIER METHODS
    bool IsDead();
    void GetsEaten(); // pacman is eaten
    void SetPosition(int x_pos, int y_pos); // Sets the maze position to the corresponding x and y
        // coords. Note that this method doesn't check if the new position is valid.
    void EatObject(int points_gained); // gains points by eating objects - note that only the
        // number of points gained is passed in rather than a reference to the object itself
        // (so this method can work for both food and ghost objects)
    
    void reset(); // clears everything
    void resize(int w, int h); // resizes the pacman
};

