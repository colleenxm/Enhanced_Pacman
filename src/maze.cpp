//
//  maze.cpp
//  final-project-ElizWang
//
//  Created by Elizabeth Wang on 4/20/18.
//

#include "maze.h"

void Maze::PopulateWithFood(int num_food_items) { // populate the maze with food objects in random, non-wall places
    int num_items_created = 0;
    while (num_items_created < num_food_items) {
        int x = rand() % kMazeWidth_; // random x and y coord/food item
        int y = rand() % kMazeWidth_;
        if (raw_maze_[x][y] == 0) { // can only change if it's a wall - can't change wall to food
            raw_maze_[x][y] = 2;
            num_items_created++;
        }
    }
    num_food_items_ = num_food_items; // store after - note: didn't use constructor because I didn't want to use magic numbers in ofapp
}

int Maze::GetElementAt(int x_pos, int y_pos) { // returns the element at a specified position
    return raw_maze_[x_pos][y_pos];
}

bool Maze::IsValidPosition(int x_pos, int y_pos) { // true if the position isn't on a part of the wall and isn't out of bounds
    return (x_pos < kMazeWidth_) && (y_pos < kMazeHeight_) && (raw_maze_[x_pos][y_pos] == 0); // 0 = not a part of the wall wall, 1 = part of the wall
}

void Maze::RemoveFoodAt(int x_pos, int y_pos) { // removes the food item (checks if it's a food item first and swaps the 2 at that location with a 0)
    if (raw_maze_[x_pos][y_pos] == 2) {
        raw_maze_[x_pos][y_pos] = 0;
    }
}

void Maze::Reset() { // clears all remaining food items and redraws food from the stored number of food items
    for (int x = 0; x < kMazeWidth_; x++) {
        for (int y = 0; y < kMazeHeight_; y++) {
            if (raw_maze_[x][y] == 2) {
                raw_maze_[x][y] = 0; // clear food item
            }
        }
    }
    PopulateWithFood(num_food_items_);
}
