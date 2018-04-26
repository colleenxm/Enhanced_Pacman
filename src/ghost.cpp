#include <stdlib.h>
#include "ghost.h"

const std::string Ghost::kImagePath_ = "/Users/elizabeth/CS126-FINAL-PROJECT/final-project-ElizWang/bin/data/image_files/pacman_ghost.png";

// Adapted and modified from OF-SNAKE MP (Food class): https://github.com/uiuc-sp18-cs126/of-snake-ElizWang
Ghost::Ghost() {
    int window_width = ofGetWindowWidth();
    int window_height = ofGetWindowHeight();
    window_dims_.set(window_width, window_height);
    generator_ = std::mt19937(rand());
    
    ghost_image_.load(kImagePath_); // loading image
}

void Ghost::SetInitialRandomPosition() { // intial random pos - cannot be on a wall or on top of a piece of food
    std::uniform_int_distribution<> dist_x = std::uniform_int_distribution<>(0, maze_.GetWidth() - 1);
    std::uniform_int_distribution<> dist_y = std::uniform_int_distribution<>(0, maze_.GetHeight() - 1);
    
    int x = dist_x(generator_);
    int y = dist_y(generator_);
    
    while (!maze_.IsEmptyPosition(x, y)) { // can only start off on a blank square
        x = dist_x(generator_);
        y = dist_y(generator_);
    }
    maze_position_.set(x, y);
}

// Method adapted and modified from OF-SNAKE MP (Food class): https://github.com/uiuc-sp18-cs126/of-snake-ElizWang
void Ghost::resize(int w, int h) {
    window_dims_.set(w, h);
}

void Ghost::SetDirection(Direction newDirection) {
    current_direction_ = newDirection;
}

ofVec2f Ghost::GetMazePosition() {
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

void Ghost::MoveInNewDirection() { // moves in that direction - jumps over food items, cannot go through walls
    int x = maze_position_.x;
    int y = maze_position_.y;
    
    switch (current_direction_) {
        case NORTH:
            if (maze_.IsLegalPosition(x, y - 1) && maze_.IsValidPacmanPosition(x, y - 1)) {
                maze_position_.set(x, y - 1);
            }
            break;
        case SOUTH:
            if (maze_.IsLegalPosition(x, y + 1) && maze_.IsValidPacmanPosition(x, y + 1)) {
                maze_position_.set(x, y + 1);
            }
            break;
        case WEST:
            if (maze_.IsLegalPosition(x - 1, y) && maze_.IsValidPacmanPosition(x - 1, y)) {
                maze_position_.set(x - 1, y);
            }
            break;
        case EAST:
            if (maze_.IsLegalPosition(x + 1, y) && maze_.IsValidPacmanPosition(x + 1, y)) {
                maze_position_.set(x + 1, y);
            }
            break;
    }
}
