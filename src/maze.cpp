//
//  maze.cpp
//  final-project-ElizWang
//
//  Created by Elizabeth Wang on 4/20/18.
//

#include "maze.h"

int Maze::GetElementAt(int x_pos, int y_pos) { // returns the element at a specified position
    return raw_maze_[x_pos][y_pos];
}

bool Maze::IsValidPosition(int x_pos, int y_pos) { // true if the position isn't on a part of the wall and isn't out of bounds
    return (x_pos < kMazeWidth_) && (y_pos < kMazeHeight_) && (raw_maze_[x_pos][y_pos] == 0); // 0 = not a part of the wall wall, 1 = part of the wall
}
