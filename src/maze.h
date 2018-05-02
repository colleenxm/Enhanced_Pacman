//
//  maze.hpp
//  final-project-ElizWang
//
//  Created by Elizabeth Wang on 4/20/18.
//

#ifndef maze_hpp
#define maze_hpp

#include <array>
#include <random>
#include <stdio.h>

class Maze { // provides encapsulation for the maze because giving the game the power to change
    // the maze is dangerous
  
public:
    enum MazeObject {
        NOTHING = 0, // 0 - just an empty square, objects can be placed/move here
        WALL = 1, // 1 - objects can't be placed/move here
        FOOD = 2, // 2 - note: will just randomly generating the food here and drawing them in
            // ofapp instead of having separate objects for each
        COIN = 3 // 3 - like food but worth more
    };

private:
    std::array<std::array<MazeObject, 33>, 37> raw_maze_;
    int num_food_items_ = 0; // num food items to randomly place inside
    int num_coins_ = 0;
    
public:
    Maze(); // constructs the maze
    
    // DATA - belongs to the maze bc the consumable objects belong to the maze
    static const int kFoodPointsWorth_; // how many points a food object is worth
    static const int kCoinPointsWorth_; // coins are worth more point b/c there's less of them

    void PopulateWithFood(int num_food_items); // populate the maze with food objects in random,
        // non-wall places - swaps num_items number of 0's with that number of 2's, where 2 = food object.
    void PopulateWithCoins(int num_coins);
    
    int GetElementAt(int x_pos, int y_pos); // returns the element at a specified position
    
    bool IsEmptyPosition(int x_pos, int y_pos); // true if the position is empty
    bool IsLegalPosition(int x_pos, int y_pos); // true if the position is legal - not out of bounds
    bool IsValidPacmanPosition(int x_pos, int y_pos); // true if the position contains food/empty
    bool ContainsConsumableObjects(); // true if maze contains at least one coin or piece of food,
        // false otherwise - note that walls do not count as "objects"

    void RemoveFoodAt(int x_pos, int y_pos); // removes the food item (checks if it's a food item first and swaps the 2 at that location with a 0)
    void RemoveCoinAt(int x_pos, int y_pos);
    
    int GetWidth();
    int GetHeight();
    
    void Reset(); // return to original state - remove all leftover items and regenerates items
};

#endif /* maze_hpp */

