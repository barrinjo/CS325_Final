#include "node.hpp"

struct comp {
    bool operator()(Node* left, Node* right) const
    {
        return left->getTotalCost() > right->getTotalCost();
    }
};

// node constructor
Node::Node(int vertexID, std::vector<Vertex*> *vertexListID, std::vector<Node*> *nodeListID, std::string fileName):
    vertexID(vertexID),
    parentID(NULL),
    parentCost(0),
    vertexListID(vertexListID),
    depth(0) {
        createGraph();
        int reduceCost = reduceGraph();
        totalCost = reduceCost;
        std::priority_queue<Node*, std::vector<Node*>, comp> queue;

        for(unsigned int i = 1; i < vertexListID->size(); i++) {
            Node *node = new Node(i, this, totalCost, graph, vertexListID, 1, fileName);
            // printf("add v: %i, cost: %i, depth: %i\n", node->getvertexID(), node->getTotalCost(), node->getDepth());
            queue.push(node);
        }
        int maxDepth = 0;
        while(true) {
            Node *parentNode = queue.top();
            queue.pop();
            if(parentNode->getDepth() > maxDepth) {
                maxDepth = parentNode->getDepth();
                // printf("%i\n", maxDepth);
            }
            // printf("step v: %i, cost: %i, depth: %i\n", parentNode->getvertexID(), parentNode->getTotalCost(), parentNode->getDepth());
            int loc = parentNode->getvertexID();
            for(unsigned int i = 0; i < vertexListID->size(); i++) {
                std::vector< std::vector< int > > currentGraph = parentNode->getGraph();
                if(currentGraph[loc][i] < 1000000 && currentGraph[loc][i] >= 0) {
                    // printf("loc: %i, i: %i, currentGraph: %i\n", loc, i, currentGraph[loc][i]);
                    Node *node = new Node(i,
                                          parentNode,
                                          parentNode->getTotalCost(),
                                          parentNode->getGraph(),
                                          vertexListID,
                                          parentNode->getDepth()+1,
                                          fileName);
                    // printf("new v: %i, cost: %i, depth: %i\n", node->getvertexID(), node->getTotalCost(), node->getDepth());
                    queue.push(node);
                }
            }
        }
    }

Node::Node(int vertexID,
           Node * parentID,
           int parentCost,
           std::vector< std::vector< int > > graph,
           std::vector<Vertex*> *vertexListID,
           unsigned int depth,
           std::string fileName):
    vertexID(vertexID),
    parentID(parentID),
    parentCost(parentCost),
    graph(graph),
    vertexListID(vertexListID),
    depth(depth) {
        int travelCost = graph[parentID->getvertexID()][vertexID];
        reviseGraph();
        int reduceCost = reduceGraph();
        // printf("r: %i, t: %i, p: %i\n", reduceCost, travelCost, parentCost);
        totalCost = reduceCost + travelCost + parentCost;

        std::vector<int> tempArray;
        if(depth == vertexListID->size()-1) {
            tempArray.push_back(totalCost);
            tempArray.push_back(vertexID);
            // printf("total cost: %i\n", totalCost);
            // printf("%i, ", vertexID);
            while(parentID) {
                // printf("%i, ", parentID->getvertexID());
                tempArray.push_back(parentID->getvertexID());
                parentID = parentID->getParentID();
            }
            // std::cout << std::endl;
            std::ofstream file (fileName + ".tour");

            for(unsigned int i = 0; i < tempArray.size(); i++) {
                file << tempArray[i] << std::endl;
            }
            exit(0);
        }
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

int Node::getDepth() {
    return depth;
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
        graph[i][parentID->getvertexID()] = INT_MAX;
    }

    return;
}
