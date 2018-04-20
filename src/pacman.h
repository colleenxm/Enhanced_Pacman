#include "ofMain.h"
#include "direction.h"
#include "ghost.h"
#include "food.h"

#pragma once

class Pacman {
private:
	RawDirection current_direction_; // current direction
	ofVec2f screen_dims_; // The current screen dimensions (needed to calculate values on resize()
	static const float kbody_size_modifier_; // The proportion of the screen width a body square is
    
    ofRectangle image_frame_; // stores location + dimensions of image

    //ofVec2f body_size_; // the size based on kbody_size_modifier_
    //ofVec2f position_; // position of pacman
    ofColor color_;
    
    int num_points_; // corresponds to the food eaten
   
    ofImage pacman_image_; // image that correpsonds with the pacman 
    
public:
    // Methods to use adapted from OF-SNAKE MP (Food class): https://github.com/uiuc-sp18-cs126/of-snake-ElizWang
    //ofVec2f getPosition() const;
    ofColor& get_color() const;
    ofRectangle& get_image_frame();
    ofImage& get_pacman_image(); // gets image
    RawDirection get_direction() const; // Gets the current direction
    void setDirection(RawDirection new_direction); // Sets the current direction

	Pacman(); // Default constructor, initializes and places length 1 snake
    
	bool isDead() const; // if the pacman is dead
	void update(); // updates the pacman in the current direction
    
	void eat_food_or_ghost(int points_gained); // gains points by eating objects - note that only the number of points gained is passed in rather than a reference to the object itself (so this method can work for both food and ghost objects)
    
	void resize(int w, int h); // resizes
	int getNumPoints() const; // Gets the number of points
    
};
