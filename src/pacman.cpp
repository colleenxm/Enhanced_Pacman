#include "pacman.h"

//const float Pacman::kbody_size_modifier_ = 0.05; // all objects should be the same sizes

// Very loosely dapted from OF-SNAKE MP (Snake class): https://github.com/uiuc-sp18-cs126/of-snake-ElizWang

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

void Pacman::SetFacialImage(ofImage facial_image) { // replaces the default yellow pacman with the user's face, note: can't have a reference (must copy) because we need to save the original face iamge
    is_using_face_image_ = true;
    
    original_face_image_ = facial_image; // store original image for reset method
    pacman_image_ = facial_image;
}

ofImage& Pacman::GetPacmanImage() { // gets image
    return pacman_image_;
}

void Pacman::Update() {    
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

void Pacman::SetDirection(Direction new_direction) {
    current_direction_ = new_direction;
}

void Pacman::CalculateNumRotations(Direction new_direction) { // calculates the number of clockwise 90 degree rotations needed, note: pacman can't actually be rotated in this class - has to be rotated in the game
    
    int index_difference = GetIndex(new_direction) - GetIndex(current_direction_); // difference in indices of directions

    if (index_difference >= 0) { // then the number of clockwise 90 degree rotations = the index difference
        num_rotations_ = index_difference;
    } else { // rotating counterclockwise
        const int kNumDirections = 4;
        num_rotations_ = kNumDirections + index_difference;
        /*switch (index_difference) {
            case -1:
                num_rotations_ = 3;
            case -2: // not sure about the logic here
                return 2;
            case -3:
                return 1;
        }*/
    }
}

void Pacman::ClearNumRotations() { // sets num rotations back to 0, must be called each time an object finishes rotation
    num_rotations_ = 0;
}

int Pacman::GetNumRotations() { // returns the number of rotations
    return num_rotations_;
}

int Pacman::GetIndex(Direction direction) { // put in a method later
    switch(direction) {
        case NORTH:
            return 0;
        case EAST:
            return 1;
        case SOUTH:
            return 2;
        case WEST:
            return 3;
    }
}

void Pacman::reset() { // back to original state
    current_direction_ = EAST; 
    maze_position_.set(1, 1); // starting point
    
    num_points_ = 0;
    is_eaten_ = false;
    num_rotations_ = 0;
    
    /*if (is_using_face_image_) { // revert to original orientation
        pacman_image_ = original_face_image_;
        
    } else {*/
        pacman_image_.load(kImagePath_); // reload the original image - rotating actually CHANGES the picture and reset should set everything back to its original orientaiton
    //pacman_gif_.load(kGifPath_);
    //}
}
