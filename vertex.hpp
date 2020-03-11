#pragma once

#include <utility>

class Vertex {
private:
    int ID;
    std::pair<int, int> location;
public:
    Vertex(int ID, std::pair<int, int> location);

    int getID();
    std::pair<int, int> getLocation();
};