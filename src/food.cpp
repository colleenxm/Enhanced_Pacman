//
//  food.cpp
//  final-project-ElizWang
//
//  Created by Elizabeth Wang on 4/19/18.
//

#include <stdlib.h>
#include "food.hpp"

const float Food::kfood_modifier_ = 0.1;

// Adapted from OF-SNAKE MP (SnakeFood class): https://github.com/uiuc-sp18-cs126/of-snake-ElizWang
Food::Food() {
    int window_width = ofGetWindowWidth();
    int window_height = ofGetWindowHeight();
    window_dims_.set(window_width, window_height);
    float size_d = kfood_modifier_ * window_width;
    image_frame_.setSize(size_d, size_d);
    
    generator_ = std::mt19937(rand());
    dist_x_ = std::uniform_int_distribution<>(0, window_width - size_d);
    dist_y_ = std::uniform_int_distribution<>(0, window_height - size_d);

    auto x = dist_x_(generator_);
    auto y = dist_y_(generator_);
    image_frame_.setPosition(x, y);
    
    food_image_.load("/Users/elizabeth/CS126-FINAL-PROJECT/final-project-ElizWang/image_files/apple.png"); 
}

void Food::resize(int w, int h) {
    float size_d = kfood_modifier_ * w;
    image_frame_.setSize(size_d, size_d);
    
    float new_x = ((image_frame_.getX() / window_dims_.x) * w);
    float new_y = ((image_frame_.getY() / window_dims_.y) * h);
    image_frame_.setPosition(new_x, new_y);
    
    dist_x_ = std::uniform_int_distribution<>(0, w - size_d);
    dist_y_ = std::uniform_int_distribution<>(0, h - size_d);
    window_dims_.set(w, h);
    
    rebase();
}

void Food::rebase() {
    auto x = dist_x_(generator_);
    auto y = dist_y_(generator_);
    image_frame_.setPosition(x, y);
}

ofRectangle& Food::get_image_frame() {
    return image_frame_;
}

ofImage& Food::get_food_image() {
    return food_image_;
}


