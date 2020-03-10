#ifndef BRANCH_AND_BOUND_CPP
#define BRANCH_AND_BOUND_CPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <string>
#include <vector>

void readFile(std::string fileName);
void parseLine(std::string line);

struct vertex {
    int ID;
    std::pair<int, int> location;

    vertex(int ID, std::pair<int, int> location): ID(ID), location(location) {}
};

struct node {
    int cost;
    int reducedMatrix[0][0];
    vertex Vertex;
};

#endif