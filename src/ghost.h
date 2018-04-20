#pragma once
#include <random>
#include "ofMain.h"

class Ghost {
private:
    typedef enum { // all possible directions
        UP = 0,
        DOWN,
        RIGHT,
        LEFT,
        STARTING // dummy direction - to start off with
    } Direction;

    // Next 5 lines adapted from OF-SNAKE MP (Food class): https://github.com/uiuc-sp18-cs126/of-snake-ElizWang
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
    
    const int kNumRealDirections_ = 4; // number of real directions, to exclude dummy direction
    Direction current_direction_ = STARTING; // starts at a dummy direction
    
    bool is_valid_position(ofVec2f& position); // checks if new position is valid
    ofVec2f& calculate_new_position(Direction direction); // calculates the new position and returns a pair represententing the position
    
    int num_steps_taken_ = 0; // keeps track of the number of steps taken in the current direction (so that the direction can be changed once every kNumStepsBeforeDirectionChange_ steps)
    
public:
    const int kNumStepsBeforeDirectionChange_ = 20; // number of steps to take in the new  direction before changing direction. Note that this is used in ofApp so each step can be drawn out (else the ghost would jump around). No point in hiding this - will need a getter anyways

	Ghost(); // Default constructor, sets up generator devices and rarndomly places food at a valid location
	void rebase(); // Called once the snake has successfully eaten food, replaces the foods color and location
	void resize(int w, int h); // Called by application resize, resizes food rect to new window dimensions
    
    ofVec2f& get_body_size(); // get size of body
    ofVec2f& get_position(); // get current position
	//ofRectangle getFoodRect(); // Gets the rectangle that represents the food object
	ofColor& get_color(); // Gets the color of the current food object
    
    int get_num_steps_taken(); // gets the number of steps taken
    void incr_num_steps_taken(); // increments the number of steps taken
    
    void choose_random_direction(); // chooses a random direction
    void move_in_new_direction(); // moves in that random direction - note that this method is called more than choose_random_direction so the ghost can actually move before changing directions (will look like it's jumping around otherwise)
};
