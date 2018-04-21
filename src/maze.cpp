//
//  maze.cpp
//  final-project-ElizWang
//
//  Created by Elizabeth Wang on 4/20/18.
//

#include "maze.h"

void Maze::PopulateWithFood(int num_food_items) { // populate the maze with food objects in random, non-wall places
    std::mt19937 generator_; // pseudorandom number generation
    generator_ = std::mt19937(rand());
    std::uniform_int_distribution<> dist_x_ = std::uniform_int_distribution<>(0, raw_maze_.size() - 1);
    std::uniform_int_distribution<> dist_y_ = std::uniform_int_distribution<>(0, raw_maze_[0].size() - 1);

    int num_items_created = 0;
    while (num_items_created < num_food_items) {
        int x = dist_x_(generator_);
        int y = dist_y_(generator_);

        if (raw_maze_[x][y] == 0) { // can only change if it's a wall - can't change wall to food
            raw_maze_[x][y] = 2;
            num_items_created++;
        }
    }
    num_food_items_ = num_food_items; // store after - note: didn't use constructor because I didn't want to use magic numbers in ofapp
}

int Maze::GetElementAt(int x_pos, int y_pos) { // returns the element at a specified position
    raw_maze_.size();
    raw_maze_[0].size();
    return raw_maze_[x_pos][y_pos];
}

bool Maze::IsEmptyPosition(int x_pos, int y_pos) { // true if the position isn't on a part of the wall and isn't out of bounds
    return IsLegalPosition(x_pos, y_pos) && raw_maze_[x_pos][y_pos] == 0; // 0 = not a part of the wall, 1 = part of the wall
}

bool Maze::IsLegalPosition(int x_pos, int y_pos) { // true if the position is legal - not out of bounds
    return x_pos >= 0 && y_pos >= 0 && x_pos < raw_maze_.size() && y_pos < raw_maze_[0].size();
}

bool Maze::IsValidPacmanPosition(int x_pos, int y_pos) { // true if it's empty or has a piece of food on it, false otherwise
    return IsLegalPosition(x_pos, y_pos) && (raw_maze_[x_pos][y_pos] == 0 || raw_maze_[x_pos][y_pos] == 2); // 0 = not a part of the wall, 2 = food
}

void Maze::RemoveFoodAt(int x_pos, int y_pos) { // removes the food item (checks if it's a food item first and swaps the 2 at that location with a 0)
    if (raw_maze_[x_pos][y_pos] == 2) {
        raw_maze_[x_pos][y_pos] = 0;
    }
}

int Maze::GetWidth() {
    return raw_maze_.size();
}

int Maze::GetHeight() {
    return raw_maze_[0].size();
}

void Maze::Reset() { // clears all remaining food items and redraws food from the stored number of food items
    for (int x = 0; x < raw_maze_.size(); x++) {
        for (int y = 0; y < raw_maze_[x].size(); y++) {
            if (raw_maze_[x][y] == 2) {
                raw_maze_[x][y] = 0; // clear food item
            }
        }
    }
    PopulateWithFood(num_food_items_);
}
