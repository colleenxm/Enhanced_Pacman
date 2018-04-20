#include <stdlib.h>
#include "wanderer.hpp"

const float Wanderer::kfood_modifier_ = 0.02;
//const float SnakeFood::kfood_modifier_ = 0.05;

Wanderer::Wanderer() {
    int window_width = ofGetWindowWidth();
    int window_height = ofGetWindowHeight();
    window_dims_.set(window_width, window_height);
    float size_d = kfood_modifier_ * window_width;
    food_rect_.setSize(size_d, size_d);
    
    location.first = rand() % window_width;
    location.second = rand() % window_height;
}

void Wanderer::resize(int w, int h) { // to resize the food along with the window. Derived from ofsnake MP.
    float size_d = kfood_modifier_ * w;
    food_rect_.setSize(size_d, size_d);
    
    float new_x = ((food_rect_.getX() / window_dims_.x) * w);
    float new_y = ((food_rect_.getY() / window_dims_.y) * h);
    food_rect_.setPosition(new_x, new_y);
    
    window_dims_.set(w, h);
}

void Wanderer::update() { // chooses one random direction to go in and goes in that direction
    // chooses one random direction to go in - must be valid
    bool is_valid_dir = false;
    int rand_direction_index;
    
    while (!is_valid_dir) {
        rand_direction_index = rand() % kNumValidDirections; // 4 random indices
    }
    
    // check if it can go in that direction
    current_direction_ = (Direction) rand_direction_index; // set direction
}

ofRectangle Wanderer::getFoodRect() {
    return food_rect_;
}

ofColor Wanderer::getColor() {
    return color_;
}

