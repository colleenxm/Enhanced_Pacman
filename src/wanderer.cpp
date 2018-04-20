#include <stdlib.h>
#include "wanderer.h"

const float Wanderer::kFoodModifier = 0.02; // slightly smaller than pacman

Wanderer::Wanderer() {
    int window_width = ofGetWindowWidth();
    int window_height = ofGetWindowHeight();
    window_dims_.set(window_width, window_height);
    float size_d = kFoodModifier * window_width;
    body_size_.set(size_d, size_d);
    
    generator_ = std::mt19937(rand());
    dist_x_ = std::uniform_int_distribution<>(0, window_width - size_d);
    dist_y_ = std::uniform_int_distribution<>(0, window_height - size_d);
    dist_color_ = std::uniform_int_distribution<>(0, 255);
    rebase();
}

void Wanderer::resize(int w, int h) {
    float size_d = kFoodModifier * w;
    body_size_.set(size_d, size_d);
    
    float new_x = ((body_size_.x / window_dims_.x) * w);
    float new_y = ((body_size_.y / window_dims_.y) * h);
    position_.set(new_x, new_y);
    
    dist_x_ = std::uniform_int_distribution<>(0, w - size_d);
    dist_y_ = std::uniform_int_distribution<>(0, h - size_d);
    window_dims_.set(w, h);
}

void Wanderer::rebase() {
    auto x = dist_x_(generator_);
    auto y = dist_y_(generator_);
    
    position_.set(x, y);
    position_.set(position_.x, position_.y);
    
    color_.r = dist_color_(generator_);
    color_.g = dist_color_(generator_);
    color_.b = dist_color_(generator_);
}

/*ofRectangle Wanderer::getFoodRect() {
    return food_rect_;
}*/

ofColor Wanderer::getColor() {
    return color_;
}

ofVec2f Wanderer::getBodySize() { // size of the wanderer
    return body_size_;
}

ofVec2f Wanderer::getPosition() {
    return position_;
}

void Wanderer::update() { // moves in a random direction
    bool is_valid_direction = false;
    
    int new_x_pos = -1; // new x position
    int new_y_pos = -1; // new y position - either the x or the y position will equal the original position because it's only moving in 1 direction at a time

    while (!is_valid_direction) {
        Direction random_direction = static_cast<Direction>(rand() % kNumRealDirections); // 1 of the 4 real directions
        
        switch (random_direction) {
            case UP:
                new_x_pos = position_.x;
                new_y_pos = position_.y - body_size_.y;
                break;
                
            case DOWN:
                new_x_pos = position_.x;
                new_y_pos = position_.y + body_size_.y;
                break;
                
            case LEFT:
                new_x_pos = position_.x - body_size_.x;
                new_y_pos = position_.y;
                break;
                
            case RIGHT:
                new_x_pos = position_.x + body_size_.x;
                new_y_pos = position_.y;
                break;
                
            default:
                break;
        }
        if (new_x_pos >= 0 && new_y_pos >= 0 && new_x_pos <= window_dims_.x && new_y_pos <= window_dims_.y) {
            is_valid_direction = true;
        }
    }
    position_.set(new_x_pos, new_y_pos); // valid direction
}
