#pragma once

#include <vector>
#include <utility>

// Vertex Stores information for each location on the graph
// ID is a unique identifier assigned from the text file
// location is a coordinate that tracks the x and y location
class Vertex {
private:
    int ID;
    std::pair<int, int> location;
    std::vector< int > visitedBy;
public:
    Vertex(int ID, std::pair<int, int> location);

    int getID();
    std::vector< int > getVisitedBy();
    std::pair<int, int> getLocation();

    void addVisited(int i);
};