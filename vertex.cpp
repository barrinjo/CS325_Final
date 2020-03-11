#include "vertex.hpp"

Vertex::Vertex(int ID, std::pair<int, int> location): ID(ID), location(location) {}

int Vertex::getID() {
    return ID;
}

std::pair<int, int> Vertex::getLocation() {
    return location;
}