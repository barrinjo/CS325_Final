#pragma once

#include <utility>

// Vertex Stores information for each location on the graph
// ID is a unique identifier assigned from the text file
// location is a coordinate that tracks the x and y location
class Vertex {
private:
    int ID;
    std::pair<int, int> location;
public:
    Vertex(int ID, std::pair<int, int> location);

    int getID();
    std::pair<int, int> getLocation();
};