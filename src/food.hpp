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
    ofRectangle food_rect_; // rectangle that frames out the food object
    
    ofImage food_image_; // image that correpsonds with a food object

public:
    Food(); // Default constructor, sets up generator devices and rarndomly places food at a valid location
    void resize(int w, int h); // Called by application resize, resizes food rect to new window dimensions
    void rebase();
    
    ofRectangle& getFoodRect(); // Gets the rectangle that frames out the food object
    ofImage& getFoodImage(); // gets image
};
#endif /* food_hpp */

