#include "node.hpp"

// node constructor
Node::Node(int vertexID, std::vector<Vertex*> *vertexListID):
    vertexID(vertexID),
    vertexListID(vertexListID) {
        graph = createGraph();
        graph = reduceGraph(graph);
        reduceCost = setReducedCost(graph);
    }

Node::Node(int vertexID, int parentID, std::vector< std::vector< int > > graph, std::vector<Vertex*> *vertexListID):
    vertexID(vertexID),
    parentID(parentID),
    graph(graph),
    // travelCost(setTravelCost()),
    vertexListID(vertexListID) {}

std::vector< std::vector< int > > Node::getGraph() {
    return graph;
}

void Node::setCost(int newCost) {
    reduceCost = newCost;
}

std::vector< std::vector< int > > Node::createGraph() {
    std::vector<Vertex*> vertexList = *vertexListID;
    std::vector< std::vector< int > > graph;
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
    return graph;
}

std::vector< std::vector< int > > Node::reduceGraph(std::vector< std::vector< int > > graph) {
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

    return graph;
}

int Node::setReducedCost(std::vector< std::vector< int > > graph) {
    int sum = 0;
    for(unsigned int i = 0; i < graph.size(); i++) {
        sum += graph[i][graph.size()-1];
        sum += graph[graph.size()-1][i];
    }
    return sum;
}

// int Node::setTravelCost() {
//     return graph[]
// }
