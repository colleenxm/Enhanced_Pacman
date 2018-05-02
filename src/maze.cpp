//
//  maze.cpp
//  final-project-ElizWang
//
//  Created by Elizabeth Wang on 4/20/18.
//

#include "maze.h"

const int Maze::kFoodPointsWorth_ = 1; // how many points a food object is worth
const int Maze::kCoinPointsWorth_ = 8; // coins are worth more point b/c there's less of them

Maze::Maze() { // intializes raw maze
    raw_maze_ = { // represents the maze
        {
            {WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL,
                WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL,
                WALL, WALL, WALL, WALL, WALL, WALL},
            {WALL, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
                NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
                NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
                NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, WALL},
            {WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL,
                WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, NOTHING,
                NOTHING, NOTHING, WALL, WALL, NOTHING, WALL},
            {WALL, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
                NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
                NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
                NOTHING, NOTHING, NOTHING, NOTHING, WALL},
            {WALL, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
                NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
                NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
                NOTHING, NOTHING, NOTHING, NOTHING, WALL},
            {WALL, NOTHING, NOTHING, WALL, WALL, WALL, WALL, WALL, WALL, NOTHING, NOTHING, WALL,
                WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, NOTHING, NOTHING, WALL,
                WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL},
            {WALL, NOTHING, NOTHING, WALL, NOTHING, NOTHING, NOTHING, NOTHING, WALL, NOTHING,
                NOTHING, WALL, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
                NOTHING, WALL, NOTHING, NOTHING, WALL, NOTHING, NOTHING, NOTHING, NOTHING,
                NOTHING, NOTHING, NOTHING, NOTHING, WALL},
            {WALL, NOTHING, NOTHING, WALL, NOTHING, WALL, WALL, NOTHING, WALL, NOTHING, NOTHING,
                WALL, NOTHING, NOTHING, WALL, WALL, WALL, WALL, NOTHING, NOTHING, WALL, NOTHING,
                NOTHING, WALL, NOTHING, NOTHING, WALL, WALL, WALL, WALL, NOTHING, NOTHING, WALL},
            {WALL, NOTHING, NOTHING, WALL, NOTHING, WALL, NOTHING, NOTHING, WALL, NOTHING, NOTHING,
                NOTHING, NOTHING, NOTHING, WALL, NOTHING, NOTHING, WALL, NOTHING, NOTHING, WALL,
                NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, WALL, NOTHING, NOTHING, WALL,
                NOTHING, NOTHING, WALL},
            {WALL, NOTHING, NOTHING, WALL, NOTHING, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL,
                WALL, WALL, NOTHING, NOTHING, WALL, NOTHING, NOTHING, WALL, WALL, WALL, WALL, WALL,
                WALL, WALL, NOTHING, NOTHING, WALL, NOTHING, NOTHING, WALL},
            {WALL, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
                NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, WALL, NOTHING,
                NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
                NOTHING, WALL, NOTHING, NOTHING, WALL},
            {WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, NOTHING,
                NOTHING, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, NOTHING,
                NOTHING, WALL, WALL, WALL, WALL, NOTHING, NOTHING, WALL},
            {WALL, NOTHING, NOTHING, NOTHING, WALL, NOTHING, NOTHING, NOTHING, NOTHING,
                NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, WALL, NOTHING, NOTHING, NOTHING,
                NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, WALL,
                NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, WALL},
            {WALL, NOTHING, NOTHING, WALL, WALL, WALL, WALL, WALL, NOTHING, NOTHING, WALL, WALL,
                WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, NOTHING, NOTHING, WALL,
                WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL},
            {WALL, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
                NOTHING, NOTHING, NOTHING, WALL, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
                NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
                NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, WALL},
            {WALL, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
                NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
                NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
                NOTHING, NOTHING, NOTHING, NOTHING, WALL},
            {WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL,
                WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, NOTHING,
                NOTHING, NOTHING, WALL, WALL, NOTHING, WALL},
            {WALL, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
                NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
                NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
                NOTHING, NOTHING, NOTHING, NOTHING, WALL},
            {WALL, NOTHING, NOTHING, WALL, WALL, WALL, WALL, WALL, WALL, NOTHING, NOTHING, WALL,
                WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, NOTHING, NOTHING, WALL, WALL,
                WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL},
            {WALL, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
                NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
                NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
                NOTHING, NOTHING, NOTHING, NOTHING, WALL},
            {WALL, NOTHING, NOTHING, WALL, NOTHING, NOTHING, NOTHING, NOTHING, WALL, NOTHING,
                NOTHING, WALL, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
                NOTHING, WALL, NOTHING, NOTHING, WALL, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
                NOTHING, NOTHING, NOTHING, WALL},
            {WALL, NOTHING, NOTHING, WALL, NOTHING, WALL, WALL, NOTHING, WALL, NOTHING, NOTHING,
                WALL, NOTHING, NOTHING, WALL, WALL, WALL, WALL, NOTHING, NOTHING, WALL, NOTHING,
                NOTHING, WALL, NOTHING, NOTHING, WALL, WALL, WALL, WALL, NOTHING, NOTHING, WALL},
            {WALL, NOTHING, NOTHING, WALL, NOTHING, WALL, NOTHING, NOTHING, WALL, NOTHING, NOTHING,
                NOTHING, NOTHING, NOTHING, WALL, NOTHING, NOTHING, WALL, NOTHING, NOTHING, WALL,
                NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, WALL, NOTHING, NOTHING, WALL, NOTHING,
                NOTHING, WALL},
            {WALL, NOTHING, NOTHING, WALL, NOTHING, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL,
                WALL, WALL, NOTHING, NOTHING, WALL, NOTHING, NOTHING, WALL, WALL, WALL, WALL, WALL,
                WALL, WALL, NOTHING, NOTHING, WALL, NOTHING, NOTHING, WALL},
            {WALL, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
                NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, WALL, NOTHING,
                NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
                NOTHING, WALL, NOTHING, NOTHING, WALL},
            {WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, NOTHING,
                NOTHING, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, NOTHING,
                NOTHING, WALL, WALL, WALL, WALL, NOTHING, NOTHING, WALL},
            {WALL, NOTHING, NOTHING, NOTHING, WALL, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
                NOTHING, NOTHING, NOTHING, NOTHING, WALL, NOTHING, NOTHING, NOTHING, NOTHING,
                NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, WALL, NOTHING,
                NOTHING, NOTHING, NOTHING, NOTHING, WALL},
            {WALL, NOTHING, NOTHING, WALL, WALL, WALL, WALL, WALL, NOTHING, NOTHING, WALL, WALL,
                WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, NOTHING, NOTHING, WALL, WALL,
                WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL},
            {WALL, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
                NOTHING, NOTHING, WALL, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
                NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
                NOTHING, NOTHING, NOTHING, NOTHING, WALL},
            {WALL, NOTHING, NOTHING, WALL, NOTHING, WALL, NOTHING, NOTHING, WALL, NOTHING, NOTHING,
                NOTHING, NOTHING, NOTHING, WALL, NOTHING, NOTHING, WALL, NOTHING, NOTHING, WALL,
                NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, WALL, NOTHING, NOTHING, WALL, NOTHING,
                NOTHING, WALL},
            {WALL, NOTHING, NOTHING, WALL, NOTHING, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL,
                WALL, WALL, NOTHING, NOTHING, WALL, NOTHING, NOTHING, WALL, WALL, WALL, WALL, WALL,
                WALL, WALL, NOTHING, NOTHING, WALL, NOTHING, NOTHING, WALL},
            {WALL, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
                NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, WALL, NOTHING,
                NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
                NOTHING, WALL, NOTHING, NOTHING, WALL},
            {WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, NOTHING,
                NOTHING, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, NOTHING,
                NOTHING, WALL, WALL, WALL, WALL, NOTHING, NOTHING, WALL},
            {WALL, NOTHING, NOTHING, NOTHING, WALL, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
                NOTHING, NOTHING, NOTHING, NOTHING, WALL, NOTHING, NOTHING, NOTHING, NOTHING,
                NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, WALL, NOTHING,
                NOTHING, NOTHING, NOTHING, NOTHING, WALL},
            {WALL, NOTHING, NOTHING, WALL, WALL, WALL, WALL, WALL, NOTHING, NOTHING, WALL, WALL,
                WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, NOTHING, NOTHING, WALL,
                WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL},
            {WALL, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
                NOTHING, NOTHING, WALL, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
                NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
                NOTHING, NOTHING, NOTHING, NOTHING, WALL},
            {WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL,
                WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL,
                WALL, WALL, WALL, WALL, WALL, WALL}
        }
    };
}

void Maze::PopulateWithFood(int num_food_items) { // Populates the maze with food objects in
    // random, non-wall places
    std::mt19937 generator_; // pseudorandom number generation
    generator_ = std::mt19937(rand());
    std::uniform_int_distribution<> dist_x_
        = std::uniform_int_distribution<>(0, raw_maze_.size() - 1);
    std::uniform_int_distribution<> dist_y_
        = std::uniform_int_distribution<>(0, raw_maze_[0].size() - 1);
    
    int num_food_items_created = 0;
    while (num_food_items_created < num_food_items) {
        int food_x = dist_x_(generator_);
        int food_y = dist_y_(generator_);
        if (raw_maze_[food_x][food_y] == NOTHING) { // can only change if it's a wall
            raw_maze_[food_x][food_y] = FOOD;
            num_food_items_created++;
        }
    }
    num_food_items_ = num_food_items; // store after
    // note: didn't use constructor because I didn't want to use magic numbers in ofapp
}

void Maze::PopulateWithCoins(int num_coins) { // populate the maze with randomly generated coins
    std::mt19937 generator_; // pseudorandom number generation
    generator_ = std::mt19937(rand());
    std::uniform_int_distribution<> dist_x_
        = std::uniform_int_distribution<>(0, raw_maze_.size() - 1);
    std::uniform_int_distribution<> dist_y_
        = std::uniform_int_distribution<>(0, raw_maze_[0].size() - 1);
    
    int num_coins_created = 0;
    while (num_coins_created < num_coins) {
        int coin_x = dist_x_(generator_);
        int coin_y = dist_y_(generator_);
        if (raw_maze_[coin_x][coin_y] == NOTHING) { // can only change if it's a wall
            raw_maze_[coin_x][coin_y] = COIN;
            num_coins_created++;
        }
    }
    num_coins_ = num_coins;
}

int Maze::GetElementAt(int x_pos, int y_pos) { // returns the element at a specified position
    raw_maze_.size();
    raw_maze_[0].size();
    return raw_maze_[x_pos][y_pos];
}

bool Maze::IsLegalPosition(int x_pos, int y_pos) { // true if the position is legal - not out of bounds
    return x_pos >= 0 && y_pos >= 0 && x_pos < raw_maze_.size() && y_pos < raw_maze_[0].size();
}

bool Maze::IsEmptyPosition(int x_pos, int y_pos) { // true if the position isn't on a part of the
    // wall and isn't out of bounds
    return IsLegalPosition(x_pos, y_pos) && raw_maze_[x_pos][y_pos] == NOTHING;
}

bool Maze::IsValidPacmanPosition(int x_pos, int y_pos) { // true if it's empty or has a piece of
    // food or a coin on it, false otherwise
    return IsLegalPosition(x_pos, y_pos) && raw_maze_[x_pos][y_pos] != WALL;
}

bool Maze::ContainsConsumableObjects() { // true if maze contains at least one coin or piece of
    // food, false otherwise - note that walls do not count as "objects"
    for (int x = 0; x < raw_maze_.size(); x++) {
        for (int y = 0; y < raw_maze_[x].size(); y++) {
            if (raw_maze_[x][y] == FOOD || raw_maze_[x][y] == COIN) { // contains food/coin
                return true;
            }
        }
    }
    return false;
}

void Maze::RemoveFoodAt(int x_pos, int y_pos) { // removes the food item (checks if it's a food
    // item first and swaps the 2 at that location with a 0)
    if (raw_maze_[x_pos][y_pos] == FOOD) {
        raw_maze_[x_pos][y_pos] = NOTHING;
    }
}

void Maze::RemoveCoinAt(int x_pos, int y_pos) { // removes the coin (checks if it's a coin first
    // and swaps the 2 at that location with a 0)
    if (raw_maze_[x_pos][y_pos] == COIN) {
        raw_maze_[x_pos][y_pos] = NOTHING;
    }
}

int Maze::GetWidth() {
    return raw_maze_.size();
}

int Maze::GetHeight() {
    return raw_maze_[0].size();
}

void Maze::Reset() { // clears all remaining items and redraws items from the stored number of
    // food items and coins
    for (int x = 0; x < raw_maze_.size(); x++) {
        for (int y = 0; y < raw_maze_[x].size(); y++) {
            if (raw_maze_[x][y] == FOOD || raw_maze_[x][y] == COIN) {
                raw_maze_[x][y] = NOTHING; // clear food item
            }
        }
    }
    PopulateWithFood(num_food_items_);
    PopulateWithCoins(num_coins_);
}

