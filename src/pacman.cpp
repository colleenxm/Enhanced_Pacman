#include "pacman.h"

//const float Pacman::kbody_size_modifier_ = 0.05; // all objects should be the same sizes

// Adapted from OF-SNAKE MP (Snake class): https://github.com/uiuc-sp18-cs126/of-snake-ElizWang

ofVec2f& Pacman::GetMazePosition() {
    return maze_position_;
}

ofImage& Pacman::GetPacmanImage() { // gets image
    return pacman_image_;
}

Pacman::Pacman() {
    int width = ofGetWindowWidth();
    int height = ofGetWindowHeight();
    screen_dims_.set(width, height);
    
    current_direction_ = RIGHT; // starts out moving right
    maze_position_.set(3, 3); // starting point
    
    pacman_image_.load(kImagePath_);
    // pacman_image_.rotate90(1); // figure out rotations later
}

void Pacman::Update() {    
    int x = maze_position_.x;
    int y = maze_position_.y;
    
    switch (current_direction_) {
        case UP:
            if (maze_.IsLegalPosition(x, y - 1) && maze_.IsValidPacmanPosition(x, y - 1)) {
                maze_position_.set(x, y - 1);
            }
            break;
        case DOWN:
            if (maze_.IsLegalPosition(x, y + 1) && maze_.IsValidPacmanPosition(x, y + 1)) {
                maze_position_.set(x, y + 1);
            }
            break;
        case LEFT:
            if (maze_.IsLegalPosition(x - 1, y) && maze_.IsValidPacmanPosition(x - 1, y)) {
                maze_position_.set(x - 1, y);
            }
            break;
        case RIGHT:
            if (maze_.IsLegalPosition(x + 1, y) && maze_.IsValidPacmanPosition(x + 1, y)) {
                maze_position_.set(x + 1, y);
            }
            break;
    }
}

bool Pacman::IsDead() { // eaten - doesn't make sense for the pacman to be able to go off the map
    return is_eaten_;  /*|| is_offscreen();*/
}

void Pacman::GetsEaten() { // pacman is eaten
    is_eaten_ = true;
}

void Pacman::EatObject(int points_gained) { // gains points after eating food and ghost objects
    num_points_ += points_gained;
}

// Resize the pacman based on the ratio of old to new position
void Pacman::resize(int w, int h) {
    int width = ofGetWindowWidth();
    int height = ofGetWindowHeight();
    
    screen_dims_.set(width, height);
}

int Pacman::GetNumPoints() const {
    return num_points_;
}

Direction Pacman::GetDirection() const {
    return current_direction_;
}

void Pacman::setDirection(Direction newDirection) {
    current_direction_ = newDirection;
}

void Pacman::reset() { // back to original state
    current_direction_ = RIGHT; // starts out moving right
    maze_position_.set(3, 3); // starting point
    
    num_points_ = 0;
    is_eaten_ = false;
}


