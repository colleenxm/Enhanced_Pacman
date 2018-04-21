#pragma once
#include <random>

#include "direction.h"
#include "ofMain.h"

class Ghost {
private:
    // Next 5 lines adapted from OF-SNAKE MP (Food class): https://github.com/uiuc-sp18-cs126/of-snake-ElizWang
	ofVec2f window_dims_;
	std::mt19937 generator_; // pseudorandom number generation
	std::uniform_int_distribution<> dist_x_;
	std::uniform_int_distribution<> dist_y_;
	std::uniform_int_distribution<> dist_color_;

	static const float kFoodModifier; // proportions
	ofColor color_; // The color of the food rectangle
    
    const int kNumRealDirections_ = 4; // number of real directions, to exclude dummy direction
    Direction current_direction_ = RIGHT; // starts off going right
    
    bool is_valid_position(ofVec2f& position); // checks if new position is valid
    ofVec2f& calculate_new_position(Direction direction); // calculates the new position and returns a pair represententing the position
    
    int num_steps_taken_ = 0; // keeps track of the number of steps taken in the current direction (so that the direction can be changed once every kNumStepsBeforeDirectionChange_ steps)
    
    // Explanation: Using a rectangle to keep track of the width/height/x/y corods of the actual image, which is that of a ghost. Image will be drawn with the image frame's dimensions and coords.
    //ofRectangle image_frame_; // frames the still iamge
    ofVec2f maze_position_; // x, y position of the maze - important: this corresponds to the MAZE ELEMENT and NOT to the actual coordinates in the coordinatep lane
    ofImage ghost_image_; // image that correpsonds with a ghost object
    
    int one_d_size_; // size per object (dimensions = kBlockSize_ * kBlockSize_), need to standardize all the object sizes to prevent the objects from overlapping with the maze walls
    const int kMazeWidth_ = 37;
    const int kMazeHeight_ = 33;

public:
    const int kNumStepsBeforeDirectionChange_ = 20; // number of steps to take in the new  direction before changing direction. Note that this is used in ofApp so each step can be drawn out (else the ghost would jump around). No point in hiding this - will need a getter anyways

    const int kPointsWorth_ = 10; // worth 10 points (b/c it's riskier to eat a ghost since the ghost can turn around and eat you)

	Ghost(); // Default constructor, sets up generator devices and rarndomly places food at a valid location
	void rebase(); // Called once the snake has successfully eaten food, replaces the foods color and location
	void resize(int w, int h); // Called by application resize, resizes food rect to new window dimensions
        
	//ofRectangle& get_image_frame(); // Gets the rectangle that represents the food object
    ofVec2f GetMazePosition();
    ofColor& get_color(); // Gets the color of the current food object
    ofImage& get_food_image(); // gets image

    int Get1DSize(); // gets the 1d size of the object - needed to draw the image

    int get_num_steps_taken(); // gets the number of steps taken
    void incr_num_steps_taken(); // increments the number of steps taken
    
    Direction& get_direction(); // gets the current direction - needed to check whether the ghost is eating the pacman or if the pacman is eating the ghost
    void choose_random_direction(); // chooses a random direction
    void move_in_new_direction(); // moves in that random direction - note that this method is called more than choose_random_direction so the ghost can actually move before changing directions (will look like it's jumping around otherwise)
};
