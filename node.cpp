#include "node.hpp"

// node constructor
Node::Node(int vertexID, std::vector<Vertex*> *vertexListID):
    vertexID(vertexID),
    vertexListID(vertexListID) {
        createGraph();
        reduceGraph();
        reduceCost = setReducedCost();
    }

Node::Node(int vertexID, int parentID, std::vector< std::vector< int > > graph, std::vector<Vertex*> *vertexListID):
    vertexID(vertexID),
    parentID(parentID),
    graph(graph),
    vertexListID(vertexListID) {
        travelCost = graph[vertexID][parentID];
        reviseGraph();
        reduceCost = setReducedCost();
    }

std::vector< std::vector< int > > Node::getGraph() {
    return graph;
}

int Node::getReduceCost() {
    return reduceCost;
}

void Node::setCost(int newCost) {
    reduceCost = newCost;
}

void Node::setTotalCost(int newTotal) {
    totalCost = newTotal;
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

void Node::reduceGraph() {
    for(unsigned int i = 0; i < graph.size(); i++) {
        int min = INT_MAX;
        for(unsigned int j = 0; j < graph.size(); j++) {
            if(graph[i][j] < min)
                min = graph[i][j];
        }
        for(unsigned int j = 0; j < graph.size(); j++) {
            graph[i][j] -= min;
        }
        graph[i].push_back(min);
    }

    std::vector< int > temp;
    for(unsigned int i = 0; i < graph.size(); i++) {
        int min = INT_MAX;
        for(unsigned int j = 0; j < graph.size(); j++) {
            if(graph[j][i] < min)
                min = graph[j][i];
        }
        for(unsigned int j = 0; j < graph.size(); j++) {
            graph[j][i] -= min;
        }
        
        temp.push_back(min);
    }
    graph.push_back(temp);
}

void Node::reviseGraph() {
}


int Node::setReducedCost() {
    int sum = 0;
    for(unsigned int i = 0; i < graph.size(); i++) {
        sum += graph[i][graph.size()-1];
        sum += graph[graph.size()-1][i];
    }
    return sum;
}
