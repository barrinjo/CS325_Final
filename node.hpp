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
    int reduceCost;
    int travelCost;
    int vertexID;
    int parentID;
    std::vector< std::vector< int > > graph;
    std::vector<Vertex*> *vertexListID;

    std::vector< std::vector< int > > createGraph();
    std::vector< std::vector< int > > reduceGraph(std::vector< std::vector< int > > graph);
    int setReducedCost(std::vector< std::vector< int > > graph);
    int setTravelCost();
public:
    Node(int vertexID, std::vector<Vertex*> *vertexListID);
    Node(int vertexID, int parentID, std::vector< std::vector< int > > graph, std::vector<Vertex*> *vertexListID);
    std::vector< std::vector< int > > getGraph();
    void setCost(int reduceCost);
};