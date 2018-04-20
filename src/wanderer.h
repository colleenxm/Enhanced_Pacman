#pragma once
#include <random>
#include "ofMain.h"

class Wanderer {
private:
    typedef enum { // all possible directions
        UP = 0,
        DOWN,
        RIGHT,
        LEFT,
        STARTING // dummy direction - to start off with
    } Direction;

	ofVec2f window_dims_; // The object must be aware of current window dimensions for resizing things appropriately
	std::mt19937 generator_; // Generator used for pseudorandom number generation for food color and position
	std::uniform_int_distribution<> dist_x_; // Generates valid x positions in current window dimension
	std::uniform_int_distribution<> dist_y_; // Generates valid y positions in current window dimension
	std::uniform_int_distribution<> dist_color_; // Generates valid rgb values

	static const float kFoodModifier; // What proportion of the window width the food square should be in size
	//ofRectangle food_rect_; // The rectangle which represents the actual food pellet on the game board
	ofColor color_; // The color of the food rectangle
    
    ofVec2f body_size_; // size of wanderer - replaces rectangle
    ofVec2f position_; // position of wanderer
    
    const int kNumRealDirections = 4; // number of real directions, to exclude dummy direction
    Direction current_direction_ = STARTING; // starts at a dummy direction
    
    void choose_random_direction(); // chooses a random direction - called in update
    void move_in_new_direction(); // moves in that random direction - called in update
    bool is_valid_position(ofVec2f& position); // checks if new position is valid
    ofVec2f& calculate_new_position(Direction direction); // calculates the new position and returns a pair represententing the position
    
public:
	Wanderer(); // Default constructor, sets up generator devices and rarndomly places food at a valid location
	void rebase(); // Called once the snake has successfully eaten food, replaces the foods color and location
	void resize(int w, int h); // Called by application resize, resizes food rect to new window dimensions
    
    ofVec2f getBodySize(); // get size of body
    ofVec2f getPosition(); // get current position
	//ofRectangle getFoodRect(); // Gets the rectangle that represents the food object
	ofColor getColor(); // Gets the color of the current food object
    
    void update(); // moves in a random direction for 4 units
};
