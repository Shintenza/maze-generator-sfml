#pragma once
#include <iostream>

struct Cell {
    bool isVisited = false; 
    bool hasNorthNeighbour = false;
    bool hasEastNeighbour = false;
    bool hasSouthNeighbour = false;
    bool hasWestNeighbour = false;
};
