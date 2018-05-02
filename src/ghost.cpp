#include <stdlib.h>
#include "ghost.h"

const std::string Ghost::kImagePath_ = "image_files/pacman_ghost.png";

// Adapted from OF-SNAKE MP (Food class): https://github.com/uiuc-sp18-cs126/of-snake-ElizWang
Ghost::Ghost() {
    int window_width = ofGetWindowWidth();
    int window_height = ofGetWindowHeight();
    window_dims_.set(window_width, window_height);
    generator_ = std::mt19937(rand());
    
    ghost_image_.load(kImagePath_); // loading image
    
    num_rotations_ = 0;
}

// Method adapted from OF-SNAKE MP (Food class)
// https://github.com/uiuc-sp18-cs126/of-snake-ElizWang
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

void Ghost::CalculateNumRotations(Direction new_direction) { // calculates the number of clockwise
    // 90 degree rotations needed
    
    int index_difference = (int)new_direction - (int)current_direction_;
    if (index_difference >= 0) { // then the number of clockwise 90 degree rotations = the
        // index difference
        num_rotations_ = index_difference;
    } else { // rotating counterclockwise
        const int kNumDirections = 4;
        num_rotations_ = kNumDirections + index_difference;
    }
}

void Ghost::ClearNumRotations() { // sets num rotations back to 0, must be called each time an
    // object finishes rotation
    num_rotations_ = 0;
}

int Ghost::GetNumRotations() { // returns the number of rotations
    return num_rotations_;
}

Direction Ghost::GetDirection() { // gets the current direction - needed to check whether the
    // ghost is eating the pacman or if the pacman is eating the ghost
    return current_direction_;
}

Direction Ghost::FindRandomDirection() { // chooses a random direction - separated from moving
    // because we want the ghost to move for some number of steps (specified in .h file) before
    // changing directions again but we need to hae the loop that causes the ghost to move straight
    // in ofapp to prevent the ghost from jumping around
    std::uniform_int_distribution<> dist_direction = std::uniform_int_distribution<>(0, kNumDirections_ - 1);
    return static_cast<Direction>(dist_direction(generator_) % kNumDirections_);
}


void Ghost::SetPosition(int x_pos, int y_pos) { // Sets the maze position to the corresponding x
    // and y coords. Note that this method doesn't check if the new position is valid.
    maze_position_.x = x_pos;
    maze_position_.y = y_pos;
}
