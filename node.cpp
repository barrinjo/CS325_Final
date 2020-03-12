#include "node.hpp"

// node constructor
Node::Node(int vertexID, std::vector<Vertex*> *vertexListID):
    vertexID(vertexID),
    parentID(NULL),
    parentCost(0),
    vertexListID(vertexListID),
    taken(true) {
        createGraph();
        int reduceCost = reduceGraph();
        totalCost = reduceCost;
    }

Node::Node(int vertexID, Node * parentID, int parentCost, std::vector< std::vector< int > > graph, std::vector<Vertex*> *vertexListID):
    vertexID(vertexID),
    parentID(parentID),
    parentCost(parentCost),
    graph(graph),
    vertexListID(vertexListID),
    taken(false) {
        int travelCost = graph[parentID->getvertexID()][vertexID];
        reviseGraph();
        int reduceCost = reduceGraph();
        totalCost = reduceCost + travelCost + parentCost;
    }

std::vector< std::vector< int > > Node::getGraph() {
    return graph;
}

Node * Node::getParentID() {
    return parentID;
}

int Node::getvertexID() {
    return vertexID;
}

int Node::getTotalCost() {
    return totalCost;
}

bool Node::isTaken() {
    return taken;
}

void Node::makeTaken() {
    taken = true;
}

void Node::createGraph() {
    std::vector<Vertex*> vertexList = *vertexListID;
    for(unsigned int i = 0; i < vertexList.size(); i++) {
        std::vector< int > row;
        for(unsigned int j = 0; j < vertexList.size(); j++) {
            if(i == j) {
                row.push_back(INT_MAX);
            }
            else {
                int dist;
                int left = vertexList[i]->getLocation().first - vertexList[j]->getLocation().first;
                int right = vertexList[i]->getLocation().second - vertexList[j]->getLocation().second;
                dist = round(sqrt(left*left + right*right));
                row.push_back(dist);
            }
        }
        graph.push_back(row);
    }
}

int Node::reduceGraph() {
    int sum = 0;

    for(unsigned int i = 0; i < graph[0].size(); i++) {
        int min = INT_MAX;
        for(unsigned int j = 0; j < graph[0].size(); j++) {
            if(graph[i][j] < min)
                min = graph[i][j];
        }
        // graph[i].push_back(min);
        if(min < 1000000000) {
            for(unsigned int j = 0; j < graph[0].size(); j++) {
                graph[i][j] -= min;
            }
            sum += min;   
        }
    }

    // std::vector< int > temp;
    for(unsigned int i = 0; i < graph[0].size(); i++) {
        int min = INT_MAX;
        for(unsigned int j = 0; j < graph[0].size(); j++) {
            if(graph[j][i] < min)
                min = graph[j][i];
        }
        if(min < 10000000) {
            for(unsigned int j = 0; j < graph[0].size(); j++) {
                graph[j][i] -= min;
            }
            sum += min;   
        }
    }
    
    return sum;
}

void Node::reviseGraph() {
    for(unsigned int i = 0; i < graph[0].size(); i++) {
        graph[parentID->getvertexID()][i] = INT_MAX;
        graph[i][vertexID] = INT_MAX;
    }
    graph[vertexID][parentID->getvertexID()] = INT_MAX;

    return;
}
