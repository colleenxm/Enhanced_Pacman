//
//  pacman.hpp
//  final-project-ElizWang
//
//  Created by Elizabeth Wang on 4/19/18.
//

#ifndef pacman_hpp
#define pacman_hpp

#include <stdio.h>
#include <utility>

#include "ofApp.h"

class Pacman {
private:
    unsigned int score_; // number of food objects eaten
    std::pair<int, int> location_; // current location
    
    int window_width_; // keep track of the width of the window
    int window_height_; // keep track of the width of the window
    
    Pacman(); // initializes everything - need to figure out how to link other classes to open frameworks
    
public:
    // Derived from ofsnake (MP)
    typedef enum { // represents all possible directions to move in
        UP = 0,
        DOWN,
        RIGHT,
        LEFT
    } Direction;
    
    void changeLocation(Direction new_direction);
    void eatFood();
    bool isDeadOffscreen(); // can be dead if it's either eaten or goes offscreen - method handles offscreen case
    
    unsigned int getScore() {return score_; }
    std::pair<int, int> getLocation() {return location_; }
};

#endif /* pacman_hpp */

