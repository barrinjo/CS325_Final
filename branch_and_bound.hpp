#ifndef BRANCH_AND_BOUND_CPP
#define BRANCH_AND_BOUND_CPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <string>
#include <vector>
#include <math.h>
#include <climits>

#define INF INT_MAX

void readFile(std::string fileName);
void parseLine(std::string line);
void createFirstNode();
std::vector< std::vector< int > > createGraph(int vertexID);

struct vertex {
    int ID;
    std::pair<int, int> location;

    vertex(int ID, std::pair<int, int> location): ID(ID), location(location) {}
};

struct node {
    int cost;
    std::vector< std::vector< int > > graph;
    vertex Vertex;
    node(vertex Vertex): Vertex(Vertex) {
        graph = createGraph(Vertex.ID);
    }
};

std::vector<vertex> vertexList;
std::vector<node> nodeList;

#endif