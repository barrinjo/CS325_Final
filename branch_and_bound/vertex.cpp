#include "vertex.hpp"

Vertex::Vertex(int ID, std::pair<int, int> location): ID(ID), location(location) {}

int Vertex::getID() {
    return ID;
}

// std::vector< int > Vertex::getVisitedBy() {
//     return visitedBy;
// }

std::pair<int, int> Vertex::getLocation() {
    return location;
}

// void Vertex::addVisited(int i) {
//     visitedBy.push_back(i);
// }