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

class Maze { // created so I can create an instance of maze (makes more sense than having maze just be in the game)
    // and so I have a way of checking whether a position is valid (within the maze and not at a wall), which I will do so
    // by passing in the maze object as a reference to my other classes. Also provides encapsulation for the maze because
    // giving the game the power to change the maze is dangerous
  
public:
    enum MazeObject {
        NOTHING = 0, // 0 - just an empty square, objects can be placed/move here
        WALL = 1, // 1 - objects can't be placed/move here
        FOOD = 2, // 2 - note: will just randomly generating the food here and drawing them in ofapp instead of having separate objects for each
        COIN = 3 // 3 - like food but worth more
    };

private:
    std::array<std::array<MazeObject, 33>, 37> raw_maze_;
    int num_food_items_ = 0; // num food items to randomly place inside
    int num_coins_ = 0;
    
public:
    Maze(); // constructs the maze
    void PopulateWithFood(int num_food_items); // populate the maze with food objects in random, non-wall places - swaps num_items number of 0's with that number of 2's, where 2 = food object. Note: Will end up doing this instead of having actual food objects - can get rid of the logic needed to remove the food objects, don't have to worry about if two food objects overlap, makes life easier
    void PopulateWithCoins(int num_coins);
    
    int GetElementAt(int x_pos, int y_pos); // returns the element at a specified position
    
    bool IsEmptyPosition(int x_pos, int y_pos); // true if the position is empty
    bool IsLegalPosition(int x_pos, int y_pos); // true if the position is legal - not out of bounds
    bool IsValidPacmanPosition(int x_pos, int y_pos); // true if the position is empty or has a piece of food on it
    
    void RemoveFoodAt(int x_pos, int y_pos); // removes the food item (checks if it's a food item first and swaps the 2 at that location with a 0)
    void RemoveCoinAt(int x_pos, int y_pos);
    
    int GetWidth();
    int GetHeight();
    
    void Reset(); // return to original state - remove all leftover food items and draw the pieces of food over again
};

#endif /* maze_hpp */

