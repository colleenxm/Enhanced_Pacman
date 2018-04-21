//
//  food.cpp
//  final-project-ElizWang
//
//  Created by Elizabeth Wang on 4/19/18.
//

#include <stdlib.h>
#include "food.h"

//const float Food::kfood_modifier_ = 0.05;

// Adapted from OF-SNAKE MP (SnakeFood class): https://github.com/uiuc-sp18-cs126/of-snake-ElizWang
Food::Food() {
    int window_width = ofGetWindowWidth();
    int window_height = ofGetWindowHeight();
    window_dims_.set(window_width, window_height);
    //one_d_size_ = kfood_modifier_ * window_width;
    
    generator_ = std::mt19937(rand());
    dist_x_ = std::uniform_int_distribution<>(0, kMazeWidth_);
    dist_y_ = std::uniform_int_distribution<>(0, kMazeHeight_);

    food_image_.load("/Users/elizabeth/CS126-FINAL-PROJECT/final-project-ElizWang/image_files/apple.png");
    rebase();
}

void Food::resize(int w, int h) { // maze matrix locations shouldn't change
    //one_d_size_ = kfood_modifier_ * w;
    
    //dist_x_ = std::uniform_int_distribution<>(0, w - one_d_size_);
    //dist_y_ = std::uniform_int_distribution<>(0, h - one_d_size_);
    //window_dims_.set(w, h);
    
    rebase();
}

void Food::rebase() {
    auto x = dist_x_(generator_);
    auto y = dist_y_(generator_);
    
    while (x < kMazeWidth_ && y < kMazeHeight_) { // don't need this in theory but something's not working because the food objects are sometimes drawn outside the maze
        x = dist_x_(generator_);
        y = dist_y_(generator_);
    }
    //image_frame_.setPosition(x, y);
    maze_position_.set(x, y);
}

ofVec2f& Food::GetMazePosition() {
    return maze_position_;
}

/*ofRectangle& Food::get_image_frame() {
    return image_frame_;
}*/

ofImage& Food::get_food_image() {
    return food_image_;
}

/*int Food::Get1DSize() {
    return one_d_size_;
}*/
