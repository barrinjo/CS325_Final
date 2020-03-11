#pragma once

#include <vector>
#include <math.h>

#include "vertex.hpp"

class Node {
private:
    int cost;
    int vertexID;
    std::vector< std::vector< int > > graph;
    std::vector<Vertex*> *vertexListID;

    std::vector< std::vector< int > > createGraph();
    void reduceGraph(std::vector< std::vector< int > > graph);
public:
    Node(int vertexID, std::vector<Vertex*> *vertexListID);
};