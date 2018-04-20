//
//  wanderer.hpp
//  final-project-ElizWang
//
//  Created by Elizabeth Wang on 4/19/18.
//

#ifndef wanderer_hpp
#define wanderer_hpp

#include <random>
#include "ofMain.h"

class Wanderer { // object that randomly wanders around the game board, superclass to food and ghost
private:
    typedef enum { // represents all possible directions to move in
        UP = 0,
        DOWN,
        RIGHT,
        LEFT,
        NOT_MOVING // special case
    } Direction;

    const int kNumValidDirections = 4; // excluding the NOT_MOVING case
    
    // NEXT 10 LINES DERIVED FROM OFSNAKE MP
    ofVec2f window_dims_; // The object must be aware of current window dimensions for resizing things appropriately
    
    static const float kfood_modifier_; // What proportion of the window width the food square should be in size
    std::pair<int, int> location;
    
    Direction current_direction_ = NOT_MOVING; // default
    
    ofRectangle food_rect_; // The rectangle which represents the actual food pellet on the game board
    ofColor color_; // The color of the food rectangle
    
public:
    Wanderer();
    
    // NEXT LINE DERIVED FROM OFSNAKE MP
    void resize(int w, int h); // Called by application resize, resizes food rect to new window dimensions
    
    void update(); // moves in some random direction
    ofRectangle getFoodRect(); // Gets the rectangle that represents the food object
    ofColor getColor(); // Gets the color of the current food object
};

#endif /* wanderer_hpp */
