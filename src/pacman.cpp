#include "pacman.h"

// Adapted from OF-SNAKE MP (Snake class): https://github.com/uiuc-sp18-cs126/of-snake-ElizWang

const std::string Pacman::kImagePath_ = "image_files/pacman.png";

Pacman::Pacman() {
    int width = ofGetWindowWidth();
    int height = ofGetWindowHeight();
    screen_dims_.set(width, height);
    
    current_direction_ = EAST; // starts out moving right
    maze_position_.set(1, 1); // starting point
    
    pacman_image_.load(kImagePath_);
    num_rotations_ = 0; // initialize
}

ofVec2f& Pacman::GetMazePosition() {
    return maze_position_;
}

void Pacman::SetFacialImage(ofImage facial_image) { // replaces the default yellow pacman with the
    // user's face, note: can't have a reference (must copy) because we need to save the original face iamge
    is_using_face_image_ = true;
    
    original_face_image_ = facial_image; // store original image for reset method
    pacman_image_ = facial_image;
}

ofImage& Pacman::GetPacmanImage() { // gets image
    return pacman_image_;
}

void Pacman::SetPosition(int x_pos, int y_pos) { // Sets the maze position to the corresponding x
    // and y coords. Note that this method doesn't check if the new position is valid.
    maze_position_.x = x_pos;
    maze_position_.y = y_pos;
}

bool Pacman::IsDead() { // eaten - doesn't make sense for the pacman to be able to go off the map
    return is_eaten_;
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

void Pacman::SetDirection(Direction new_direction) {
    current_direction_ = new_direction;
}

void Pacman::CalculateNumRotations(Direction new_direction) { // calculates the number of clockwise
    // 90 degree rotations needed, note: pacman can't actually be rotated in this class - has to
    // be rotated in the game
    
    int index_difference = (int)new_direction - (int)current_direction_;
    if (index_difference >= 0) { // then the number of clockwise 90 degree rotations = the index difference
        num_rotations_ = index_difference;
    } else { // rotating counterclockwise
        const int kNumDirections = 4;
        num_rotations_ = kNumDirections + index_difference;
    }
}

void Pacman::ClearNumRotations() { // sets num rotations back to 0, must be called each time an
    // object finishes rotation
    num_rotations_ = 0;
}

int Pacman::GetNumRotations() { // returns the number of rotations
    return num_rotations_;
}

void Pacman::reset() { // back to original state
    current_direction_ = EAST; 
    maze_position_.set(1, 1); // starting point
    
    num_points_ = 0;
    is_eaten_ = false;
    num_rotations_ = 0;
    
    pacman_image_.load(kImagePath_); // reload the original image
}
