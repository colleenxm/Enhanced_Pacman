#include <stdlib.h>
#include "ghost.h"

const std::string Ghost::kImagePath_ = "image_files/pacman_ghost.png";

// Adapted and modified from OF-SNAKE MP (Food class): https://github.com/uiuc-sp18-cs126/of-snake-ElizWang
Ghost::Ghost() {
    int window_width = ofGetWindowWidth();
    int window_height = ofGetWindowHeight();
    window_dims_.set(window_width, window_height);
    generator_ = std::mt19937(rand());
    
    ghost_image_.load(kImagePath_); // loading image
}

// Method adapted and modified from OF-SNAKE MP (Food class): https://github.com/uiuc-sp18-cs126/of-snake-ElizWang
void Ghost::resize(int w, int h) {
    window_dims_.set(w, h);
}

void Ghost::SetDirection(Direction newDirection) {
    current_direction_ = newDirection;
}

ofVec2f& Ghost::GetMazePosition() {
    return maze_position_;
}

ofImage& Ghost::GetGhostImage() {
    return ghost_image_;
}

int Ghost::GetNumStepsTaken() { // gets the number of steps taken
    return num_steps_taken_;
}

void Ghost::IncrNumStepsTaken() { // increments the number of steps taken
    num_steps_taken_++;
}

Direction& Ghost::GetDirection() { // gets the current direction - needed to check whether the ghost is eating the pacman or if the pacman is eating the ghost
    return current_direction_;
}

void Ghost::FindRandomDirection() { // chooses a random direction - separated from moving because we want the ghost to move for some number of steps (specified in .h file) before changing directions again but we need to hae the loop that causes the ghost to move straight in ofapp to prevent the ghost from jumping around
    std::uniform_int_distribution<> dist_direction = std::uniform_int_distribution<>(0, kNumDirections_ - 1);
    current_direction_ = static_cast<Direction>(dist_direction(generator_) % kNumDirections_);
}


void Ghost::SetPosition(int x_pos, int y_pos) { // Sets the maze position to the corresponding x and y coords. Note that this method doesn't check if the new position is valid.
    maze_position_.x = x_pos;
    maze_position_.y = y_pos;
}
