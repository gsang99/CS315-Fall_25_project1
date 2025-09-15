#include <iostream>
#include "CS315_maze.h"
#include <vector>
#include <fstream>
#include <string>
#include <filesystem>
#include <stack>


int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <maze_file.txt>\n";
        return 1; // <-- exit early!
    }

    std::string filename = argv[1];

    // Optional but nice:
    if (!std::filesystem::exists(filename)) {
        std::cerr << "Error: file not found: " << filename << "\n";
        return 1;
    }

    Vector2D maze;
    if (!maze.loadFromFile(filename)) return 1;

    maze.printMaze();

    const auto& entrances = maze.getCoords4Entrance();
    if (entrances.empty()) {
        std::cerr << "No entrance found on the boundary.\n";
        return 1;
    }

    std::pair<int,int> start = entrances.front();
    maze.findPath(start.first, start.second);
    maze.printSolvedMaze();

    return 0;


}