#include "node.hpp"
// #include "global.hpp"

Node::Node(int vertexID, std::vector<Vertex*> *vertexListID): vertexID(vertexID), vertexListID(vertexListID) {
    graph = createGraph();
    reduceGraph(graph);
}

std::vector< std::vector< int > > Node::createGraph() {
    std::vector<Vertex*> vertexList = *vertexListID;
    std::vector< std::vector< int > > graph;
    for(unsigned int i = 0; i < vertexList.size(); i++) {
        std::vector< int > row;
        for(unsigned int j = 0; j < vertexList.size(); j++) {
            if(i == j) {
                row.push_back(0);
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

void Node::reduceGraph(std::vector< std::vector< int > > graph) {
}