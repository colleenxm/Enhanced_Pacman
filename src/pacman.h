#include "ofMain.h"
#include "ghost.h"
#pragma once

class Pacman {
public: // need 2 sections of public 
    typedef enum {
        UP = 0,
        DOWN,
        RIGHT,
        LEFT
    } Direction;

private:
	Direction current_direction_; // The current direction of the snake
	ofVec2f screen_dims_; // The current screen dimensions (needed to calculate values on resize()
	static const float kbody_size_modifier_; // The proportion of the screen width a body square is
    
    ofRectangle image_frame_; // stores location + dimensions of image

    //ofVec2f body_size_; // the size of a snake body piece based on kbody_size_modifier_
    //ofVec2f position_; // position of pacman
    ofColor color_;
    
    int num_points_; // corresponds to the food eaten
    
public:
    // Methods to use adapted from OF-SNAKE MP (Food class): https://github.com/uiuc-sp18-cs126/of-snake-ElizWang
    //ofVec2f getPosition() const;
    ofColor& get_color() const;
    ofRectangle& get_image_frame();

	Pacman(); // Default constructor, initializes and places length 1 snake

    //ofVec2f getPacmanSize() const; // gets the size of a body segment, used for rendering
    
	bool isDead() const; // Determines if the current state of the snake is dead
	void update(); // updates the snake one body square in the current direction
	void eatFood(); //
	void resize(int w, int h); // Resizes the snake to a new width and height
	int getNumPoints() const; // Gets the number of food items the snake has eaten
	Direction getDirection() const; // Gets the Snake's current direction
	void setDirection(Direction new_direction); // Sets the Snake's direction
    
};
