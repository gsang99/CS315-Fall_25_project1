//
// Created by Gemma on 9/6/2025.
//
#pragma once
#ifndef CS315_PROJECT1_CS315_MAZE_H
#define CS315_PROJECT1_CS315_MAZE_H
#include <stack>
#include <vector>
#include <iostream>
#include <string>

class Vector2D {
public:

    //helper function to call to make sure to check if the matrix is empty
    bool isItEmpty();

    //function to load information into the 2D vector
    bool loadFromFile(const std::string &filename);

    //default vector to grab
    Vector2D() = default;

    // Constructor
    Vector2D(size_t rows, size_t cols);

    // Destructor
    ~Vector2D();

    //finds the entrance & exit target cells
    void findEdges(
            const std::vector<std::vector<int>>& grid,
            std::vector<std::pair<int,int>>& coords4entrance,
            std::vector<std::pair<int,int>>& coords4target
    );

    //is the path valid
    bool isValid(int row, int col, int boundsOfMaze, std::vector<std::vector<int>> &grid);

    //finding the path inside the maze
    int findPath(int row, int col); //inside actual maze


    //print function for original maze
    void printMaze() const;

    //get coordinates in order to pass it to the getter
    const std::vector<std::pair<int, int>> &getCoords4Entrance() const;


    //print function for the solved maze
    void printSolvedMaze() const;


private:
    // 2D vector
    std::vector<std::vector<int>> grid;

    //making sizes for the rows and columns to see how many there are in order to traverse
    int rowSize = 0;
    int colSize = 0;

    //this stores the coordinates of the entrance & target cell
    std::vector<std::pair<int,int>> coords4entrance;
    std::vector<std::pair<int,int>> coords4target;

    //stores coordinates for when inside the maze
    using pos = std::pair<int,int>;

    //storing the path inside of the stack
    std::stack<pos>mazePath;

    //direction variable
    int dirRow[4] = {1,-1,0, 0};
    int dirCols[4] =  {0,0,1,-1};

    //makes a copy of the coordinates and uses it to check the row & col that was originally saved in each.
    std::pair<int,int> entrance;
    std::pair<int,int> target;
};

#endif //CS315_PROJECT1_CS315_MAZE_H