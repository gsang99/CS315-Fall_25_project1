//
// Created by Gemma on 9/6/2025.
//

#include "CS315_maze.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <stack>


bool Vector2D::isItEmpty()
{
    // if its
    if (grid.empty() || grid.at(0).empty())
    {
        std:: cout << "The maze is empty\n ";
        std::exit(EXIT_FAILURE);
    }

    return false;

}

//loading information from text into the 2D vector
bool Vector2D::loadFromFile(const std::string &filename) {

    std::ifstream maze(filename);
    //if its not open
    if (!maze.is_open()) {
        std::cout << "Error opening file" << std::endl;
        return false;
    }
    //clear previous info
    grid.clear();
    coords4entrance.clear();
    coords4target.clear();
    //variable to store each character from file into the 2D vector we made
    std::string readInMaze;


    while (std::getline(maze, readInMaze))
    {
        //make a vector of characters
        std::vector<int> row;

        for (char &c: readInMaze)
        {
            if (c == '0' || c == '1')
            {
                row.push_back(c - '0');
            }
        }
        grid.push_back(row);

    }

    // set sizes
    rowSize = static_cast<int>(grid.size());
    colSize = grid.empty() ? 0 : static_cast<int>(grid.at(0).size());

    //checking if its empty, and if it's not, then find edges will fill accordingdly
    isItEmpty();
    findEdges(grid, coords4entrance, coords4target);

    return true;
}


void Vector2D::findEdges(const std::vector<std::vector<int>> &grid, std::vector<std::pair<int, int>> &coords4entrance,
                         std::vector<std::pair<int, int>> &coords4target)
                         {
    if (grid.empty() || grid.at(0).empty()) return;

    // sync to the matrix
    rowSize = static_cast<int>(grid.size());
    colSize = static_cast<int>(grid.at(0).size());


    //we are looking for the entrance and the exit, look at edges in clock wise motion
    //trav. left to right
    for (  int j = 0; j < colSize; j++)
    {
        // if the position in the matrix contains a zero we will store it
        if ( grid.at(0).at(j) == 0)
        {
            //we store these entrances
            coords4entrance.push_back({0,j});

        }
    }

    //this is now moving from the last column and to the second row
    for (int i = 1; i < rowSize; i++)
    {
        //if the position in the matrix contains a zero we will store it
        if ( grid.at(i).at(colSize - 1) == 0)
        {
            coords4target.push_back({i, colSize - 1});
        }
    }

    //this is now moving to the bottom row, starting from the second to last column
    for (int j = colSize - 2; j >= 0; j--)
    {
        //if the position in the matrix contains a zero we will store it
        if ( grid.at(rowSize - 1).at(j) == 0)
        {
            coords4target.push_back({rowSize - 1, j});
        }
    }

    // Traverse the first column from bottom to up, starting from second last row and
    //  ending at second row.
    for (int r = rowSize - 2 ; r > 0; r--)
    {
        //if the position in the matrix contains a zero we will store it
        if ( grid.at(r).at(0) == 0)
        {
            coords4entrance.push_back({r, 0});
        }
    }

    if (!coords4entrance.empty()) entrance = coords4entrance[0];
    //pushing the coordinates for the entrance to the stack
    mazePath.push(entrance);


}


// optional Constructor definition
Vector2D::Vector2D(size_t rows, size_t cols)
{
    grid.resize(rows, std::vector<int>(cols, 0));
    rowSize = static_cast<int>(rows);
    colSize = static_cast<int>(cols);

}

// this checks if the following coordinates is able to be used and it makes sure we are sticking within the size of the maze
bool Vector2D::isValid(int row, int col, int boundsOfMaze, std::vector<std::vector<int>> &grid) {
    return row >= 0 && col>=0 && row < boundsOfMaze && col < boundsOfMaze && grid[row][col] ;
}


// Get value at (row, col)
int Vector2D::findPath(int row, int col ) {
    //check if its empty
    isItEmpty();

    //checking if we have met our base case
    if (!coords4target.empty())
    {
        std::pair<int,int> target = coords4target[0];
        if (row == target.first && col == target.second)
        {
            grid.at(row).at(col) = 2;
            mazePath.push(target);
            std::cout<< "yes we found it!!\n";
            return -1;
        }
    }



    //mark current cell as blocked
    grid.at(row).at(col) = 2;
    mazePath.push({row,col});

    auto in_bounds = [&](int r, int c){
        return r >= 0 && c >= 0 && r < rowSize && c < colSize;
    };

    //we are going to check all pathways for an open cell
    for (int i = 0; i < 4; i++)
    {

        //creates a new coordinate to check
        int newRowCoord = row + dirRow[i];
        int newColCoord = col + dirCols[i];



        if (in_bounds( newRowCoord, newColCoord) && grid.at(newRowCoord).at(newColCoord) == 0)
        {
            //mazePath.push({newRowCoord,newColCoord});
            int res = findPath(newRowCoord, newColCoord);

            if (res == -1)
            {
                return -1;
            }
        }

    }

    mazePath.pop();
    grid.at(row).at(col) = 0;
    return 0;

}


//prints the maze and anything else
void Vector2D::printMaze() const {
    for (size_t i = 0; i < grid.size(); i++ )
    {
        for (size_t j = 0; j < grid.at(i).size(); j++)
        {
            std::cout<< grid.at(i).at(j);
        }
        std::cout<<'\n';

    }
    std::cout << "Entrances (row,col)=value\n";
    for (const auto& rc : coords4entrance) {
        int r = rc.first, c = rc.second;
        if (r >= 0 && r < static_cast<int>(grid.size()) &&
            c >= 0 && !grid.empty() && c < static_cast<int>(grid.at(0).size())) {
            std::cout << "(" << r << "," << c << ")=" << grid.at(r).at(c) << '\n';
        } else {
            std::cout << "(" << r << "," << c << ")=<out of bounds>\n";
        }
    }

    std::cout << "Targets (row,col)=value\n";
    for (const auto& rc : coords4target) {
        int r = rc.first, c = rc.second;
        if (r >= 0 && r < static_cast<int>(grid.size()) &&
            !grid.empty() && c >= 0 && c < static_cast<int>(grid.at(0).size())) {
            std::cout << "(" << r << "," << c << ")=" << grid.at(r).at(c) << '\n'; // <-- at/at
        } else {
            std::cout << "(" << r << "," << c << ")=<out of bounds>\n";
        }
    }


}

const std::vector<std::pair<int, int>> &Vector2D::getCoords4Entrance() const {
    return coords4entrance;
}


void Vector2D::printSolvedMaze() const
{
    for (size_t i = 0; i < grid.size(); i++)
    {
        for (size_t j = 0; j < grid.at(i).size(); j++)
        {
            if (grid.at(i).at(j) == 1) {
                std::cout << "1";        // wall
            } else if (grid.at(i).at(j) == 0) {
                    std::cout << "0";        // empty path
            } else if (grid.at(i).at(j) == 2) {
                std::cout <<  " ";
            }
        }
        std::cout << "\n";
    }
}


// Destructor definition
Vector2D::~Vector2D() {
    //FIX ME LATER
    std::cout << "Vector2D destroyed" << std::endl;
}








