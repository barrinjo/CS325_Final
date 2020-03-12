#pragma once

#include <math.h>
#include <climits>

#include "vertex.hpp"

// Node: a class that tracks information used in branch-and-bound
// each node has a vertex it is assigned to
// reduceCost: total value reduced from the graph
// travelCost: cost it takes to travel from the parent node to this node
// vertexID: number of corresponding vertex
// parentID: number of parent node
// visitedBy: tracks which nodes have visited this node
// graph: graph make to be reduced
// vertexListID is a pointer so nodes can access the vertexList
class Node {
private:
    int vertexID;
    Node * parentID;
    int parentCost;
    int totalCost;
    std::vector< std::vector< int > > graph;
    std::vector<Vertex*> *vertexListID;
    bool taken;

    void createGraph();
    int reduceGraph();
    void reviseGraph();
public:
    // Node functions
    Node(int vertexID, std::vector<Vertex*> *vertexListID);
    Node(int vertexID, Node * parentID, int parentCost, std::vector< std::vector< int > > graph, std::vector<Vertex*> *vertexListID);

    // Node Getters
    std::vector< std::vector< int > > getGraph();
    Node * getParentID();
    int getvertexID();
    int getTotalCost();
    bool isTaken();

    // Node Setters
    void makeTaken();
};