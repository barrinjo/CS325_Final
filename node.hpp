#pragma once

#include <vector>
#include <math.h>
#include <climits>

#include "vertex.hpp"

// Node is a class that tracks information used in branch-and-bound
// each node has a vertex it is assigned to
// cost is the total value reduced from the graph
// graph is the graph make to be reduced
// vertexListID is a pointer so nodes can access the vertexList
class Node {
private:
    int cost;
    int vertexID;
    std::vector< std::vector< int > > graph;
    std::vector<Vertex*> *vertexListID;

    std::vector< std::vector< int > > createGraph();
    std::vector< std::vector< int > > reduceGraph(std::vector< std::vector< int > > graph);
public:
    Node(int vertexID, std::vector<Vertex*> *vertexListID);
    int reducedCost(std::vector< std::vector< int > > graph);
    std::vector< std::vector< int > > getGraph();
    void setCost(int cost);
};