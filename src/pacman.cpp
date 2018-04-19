//
//  pacman.cpp
//  final-project-ElizWang
//
//  Created by Elizabeth Wang on 4/19/18.
//

#include "pacman.hpp"

Pacman::Pacman(): score_(0), location_(std::make_pair(-1, -1)), window_width_(ofGetWindowWidth()), window_height_(ofGetWindowHeight()) {
}

bool Pacman::isDeadOffscreen() { // is dead if it's offscreen
    return (location_.first < 0 || location_.second < 0 || location_.first > window_width_ || location_.second > window_height_);
}

void changeLocation(Pacman::Direction new_direction);
void eatFood();
bool isDeadOffscreen(); // can be dead if it's either eaten or goes offscreen - method handles offscreen case

