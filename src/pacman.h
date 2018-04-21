#include "ofMain.h"
#include "direction.h"
#include "ghost.h"
#include "food.h"

#pragma once

class Pacman {
private:
	Direction current_direction_; // current direction
	ofVec2f screen_dims_; // The current screen dimensions (needed to calculate values on resize()
	static const float kbody_size_modifier_; // The proportion of the screen width a body square is
    
    //ofVec2f body_size_; // the size based on kbody_size_modifier_
    //ofVec2f position_; // position of pacman
    ofColor color_;
    
    int num_points_; // corresponds to the food eaten
   
    //ofRectangle image_frame_; // stores location + dimensions of image

    ofVec2f maze_position_; // x, y position of the maze - important: this corresponds to the MAZE ELEMENT and NOT to the actual coordinates in the coordinatep lane
    
    int one_d_size_; // size per object (dimensions = kBlockSize_ * kBlockSize_), need to standardize all the object sizes to prevent the objects from overlapping with the maze walls
    static const int kMazeWidth_ = 37;
    static const int kMazeHeight_ = 33;

    ofImage pacman_image_; // image that correpsonds with the pacman 
    bool is_eaten_ = false; // dies if eaten
    
    //bool is_offscreen() const; // checks if pacman is offscreen

public:
    // Methods to use adapted from OF-SNAKE MP (Food class): https://github.com/uiuc-sp18-cs126/of-snake-ElizWang
    //ofVec2f getPosition() const;
    ofColor& get_color() const;
    //ofRectangle& get_image_frame();
    ofVec2f& GetMazePosition();
    ofImage& get_pacman_image(); // gets image
    
    Direction get_direction() const; // Gets the current direction
    void setDirection(Direction new_direction); // Sets the current direction

    int Get1DSize(); // gets the 1d size of the object - needed to draw the image
    
	Pacman(); // Default constructor, initializes and places length 1 snake
    
    bool is_dead();
    void gets_eaten(); // pacman is eaten
	
    void update(); // updates the pacman in the current direction
    
	void eat_food_ghost(int points_gained); // gains points by eating objects - note that only the number of points gained is passed in rather than a reference to the object itself (so this method can work for both food and ghost objects)
    
	void resize(int w, int h); // resizes
	int getNumPoints() const; // Gets the number of points
    
};
