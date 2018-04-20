#include <stdlib.h>
#include "ghost.h"

const float Ghost::kFoodModifier = 0.1; // same size as pacman

// Adapted and modified from OF-SNAKE MP (Food class): https://github.com/uiuc-sp18-cs126/of-snake-ElizWang
Ghost::Ghost() {
    int window_width = ofGetWindowWidth();
    int window_height = ofGetWindowHeight();
    window_dims_.set(window_width, window_height);
    float size_d = kFoodModifier * window_width;
    //body_size_.set(size_d, size_d);
    image_frame_.setSize(size_d, size_d);
    
    generator_ = std::mt19937(rand());
    dist_x_ = std::uniform_int_distribution<>(0, window_width - size_d);
    dist_y_ = std::uniform_int_distribution<>(0, window_height - size_d);
    dist_color_ = std::uniform_int_distribution<>(0, 255);
    
    ghost_image_.load("/Users/elizabeth/CS126-FINAL-PROJECT/final-project-ElizWang/image_files/ghost.png"); // loading image
    rebase();
}

// Method adapted and modified from OF-SNAKE MP (Food class): https://github.com/uiuc-sp18-cs126/of-snake-ElizWang
void Ghost::resize(int w, int h) {
    float size_d = kFoodModifier * w;
    image_frame_.setSize(size_d, size_d);
    //body_size_.set(size_d, size_d);
    
    //float new_x = ((body_size_.x / window_dims_.x) * w);
    //float new_y = ((body_size_.y / window_dims_.y) * h);
    float new_x = ((image_frame_.getWidth() / window_dims_.x) * w);
    float new_y = ((image_frame_.getHeight() / window_dims_.y) * h);
    
    //position_.set(new_x, new_y);
    image_frame_.setPosition(new_x, new_y);
    
    dist_x_ = std::uniform_int_distribution<>(0, w - size_d);
    dist_y_ = std::uniform_int_distribution<>(0, h - size_d);
    window_dims_.set(w, h);
}

// Method adapted and modified from OF-SNAKE MP (Food class): https://github.com/uiuc-sp18-cs126/of-snake-ElizWang
void Ghost::rebase() {
    auto x = dist_x_(generator_);
    auto y = dist_y_(generator_);
    
    //position_.set(x, y);
    image_frame_.setPosition(x, y);
    
    color_.r = dist_color_(generator_);
    color_.g = dist_color_(generator_);
    color_.b = dist_color_(generator_);
}

ofColor& Ghost::get_color() {
    return color_;
}

ofRectangle& Ghost::get_image_frame() {
    return image_frame_;
}

ofImage& Ghost::get_food_image() {
    return ghost_image_;
}

/*ofVec2f& Ghost::get_body_size() { // size of the wanderer
    return body_size_;
}

ofVec2f& Ghost::get_position() {
    return position_;
}*/

int Ghost::get_num_steps_taken() { // gets the number of steps taken
    return num_steps_taken_;
}

void Ghost::incr_num_steps_taken() { // increments the number of steps taken
    num_steps_taken_++;
}

bool Ghost::is_valid_position(ofVec2f& position) {// checks if new position is valid
    return (position.x >= 0 && position.y >= 0 && position.x <= window_dims_.x && position.y <= window_dims_.y);
}

ofVec2f& Ghost::calculate_new_position(Direction direction) { // calculates the new position and returns a pair represententing the position
    ofVec2f new_position;
    
    switch (direction) {
        case UP:
            //new_position.x =  image_.x;
            //new_position.y = position_.y - body_size_.y;
            new_position.x =  image_frame_.getX();
            new_position.y = image_frame_.getY() - image_frame_.getHeight();
            break;
            
        case DOWN:
            //new_position.x = position_.x;
            //new_position.y = position_.y + body_size_.y;
            new_position.x =  image_frame_.getX();
            new_position.y = image_frame_.getY() + image_frame_.getHeight();
            break;
            
        case LEFT:
            //new_position.x = position_.x - body_size_.x;
            //new_position.y = position_.y;
            new_position.x = image_frame_.getX() - image_frame_.getWidth();
            new_position.y = image_frame_.getY();
            break;
            
        case RIGHT:
            //new_position.x = position_.x + body_size_.x;
            //new_position.y = position_.y;
            new_position.x = image_frame_.getX() + image_frame_.getWidth();
            new_position.y = image_frame_.getY();
            break;
    }
    return new_position;
}

void Ghost::choose_random_direction() { // valid position - can take at least 1 step in that direction
    
    Direction random_direction;
    ofVec2f new_location;
    new_location.set(-1, -1);
    
    while (!is_valid_position(new_location)) { // while position isn't valid
        random_direction = static_cast<Direction>(rand() % kNumRealDirections_); // 1 of the 4 real direction
        new_location = calculate_new_position(random_direction);
    }
    current_direction_ = random_direction;
}

void Ghost::move_in_new_direction() { // need to figure out what to do if the ghost becomes stuck
    ofVec2f new_position = calculate_new_position(current_direction_);
    
    if (is_valid_position(new_position)) {
        //position_.set(new_position.x, new_position.y);
        image_frame_.setPosition(new_position.x, new_position.y);
    }
}
