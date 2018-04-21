//
//  food.hpp
//  final-project-ElizWang
//
//  Created by Elizabeth Wang on 4/19/18.
//

#ifndef food_hpp
#define food_hpp

#include <stdio.h>
#include <random>
#include "ofMain.h"

// Adapted from OF-SNAKE MP (SnakeFood class): https://github.com/uiuc-sp18-cs126/of-snake-ElizWang
class Food {
private:
    ofVec2f window_dims_; // The object must be aware of current window dimensions for resizing things appropriately
    std::mt19937 generator_; // Generator used for pseudorandom number generation for food color and position
    std::uniform_int_distribution<> dist_x_; // Generates valid x positions in current window dimension
    std::uniform_int_distribution<> dist_y_; // Generates valid y positions in current window dimension
    std::uniform_int_distribution<> dist_color_; // Generates valid rgb values
    
    static const float kfood_modifier_; // What proportion of the window width the food square should be in size
    //ofRectangle image_frame_; // rectangle that frames the food picture, provides dimensions and position
   
    ofVec2f maze_position_; // x, y position of the maze - important: this corresponds to the MAZE ELEMENT and NOT to the actual coordinates in the coordinatep lane
    
    int one_d_size_; // size per object (dimensions = kBlockSize_ * kBlockSize_), need to standardize all the object sizes to prevent the objects from overlapping with the maze walls
    const int kMazeWidth_ = 37;
    const int kMazeHeight_ = 33;

    ofImage food_image_; // image that correpsonds with a food object
    
public:
    const int kPointsWorth_ = 1; // worth less points points (b/c there's no risk of having the food turn around and eat the pacman)

    Food(); // Default constructor, sets up generator devices and rarndomly places food at a valid location
    void resize(int w, int h); // Called by application resize, resizes food rect to new window dimensions
    void rebase();
    
    ofVec2f& GetMazePosition(); // Gets the rectangle that frames out the food object
    //ofRectangle& get_image_frame(); // Gets the rectangle that frames out the food object
    ofImage& get_food_image(); // gets image
    int Get1DSize(); // for drawing the image
};
#endif /* food_hpp */

