#include <stdlib.h>
#include "ghost.h"

//const float Ghost::kFoodModifier = 0.05; // same size as pacman

// Adapted and modified from OF-SNAKE MP (Food class): https://github.com/uiuc-sp18-cs126/of-snake-ElizWang
Ghost::Ghost() {
    int window_width = ofGetWindowWidth();
    int window_height = ofGetWindowHeight();
    window_dims_.set(window_width, window_height);
    generator_ = std::mt19937(rand());
    
    ghost_image_.load(kImagePath_); // loading image
}

void Ghost::SetInitialRandomPosition() { // intial random pos - cannot be on a wall or on top of a piece of food
    std::uniform_int_distribution<> dist_x_ = std::uniform_int_distribution<>(0, maze_.GetWidth() - 1);
    std::uniform_int_distribution<> dist_y_ = std::uniform_int_distribution<>(0, maze_.GetHeight() - 1);
    
    int x = dist_x_(generator_);
    int y = dist_y_(generator_);
    
    while (!maze_.IsEmptyPosition(x, y)) { // can only start off on a blank square
        x = dist_x_(generator_);
        y = dist_y_(generator_);
    }
    maze_position_.set(x, y);
}

// Method adapted and modified from OF-SNAKE MP (Food class): https://github.com/uiuc-sp18-cs126/of-snake-ElizWang
void Ghost::resize(int w, int h) {
    window_dims_.set(w, h);
}

ofVec2f Ghost::GetMazePosition() {
    return maze_position_;
}

ofImage& Ghost::get_ghost_image() {
    return ghost_image_;
}

int Ghost::get_num_steps_taken() { // gets the number of steps taken
    return num_steps_taken_;
}

void Ghost::IncrNumStepsTaken() { // increments the number of steps taken
    num_steps_taken_++;
}

Direction& Ghost::get_direction() { // gets the current direction - needed to check whether the ghost is eating the pacman or if the pacman is eating the ghost
    return current_direction_;
}

void Ghost::CalculateNewPosition() { // calculates the new position
    current_direction_ = static_cast<Direction>(rand() % kNumDirections_);
    
    int x = maze_position_.x;
    int y = maze_position_.y;
    
    switch (current_direction_) {
        case UP:
            if (maze_.IsLegalPosition(x, y - 1) && maze_.IsEmptyPosition(x, y - 1)) {
                maze_position_.set(x, y - 1);
            }
            break;
        case DOWN:
            if (maze_.IsLegalPosition(x, y + 1) && maze_.IsEmptyPosition(x, y + 1)) {
                maze_position_.set(x, y + 1);
            }
            break;
        case LEFT:
            if (maze_.IsLegalPosition(x - 1, y) && maze_.IsEmptyPosition(x - 1, y)) {
                maze_position_.set(x - 1, y);
            }
            break;
        case RIGHT:
            if (maze_.IsLegalPosition(x + 1, y) && maze_.IsEmptyPosition(x + 1, y)) {
                maze_position_.set(x + 1, y);
            }
            break;
    }
}
