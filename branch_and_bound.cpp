#include "branch_and_bound.hpp"

std::vector<Vertex*> vertexList;
std::vector<Node*> nodeList;

int main(int argc, char ** argv) {
    readFile(argv[1]);
    createFirstNode();
    addFirstNodes();
    int minValue = INT_MAX;
    int loc;
    for(unsigned int i = 0; i < nodeList.size(); i++) {
        if(nodeList[i]->getTotalCost() < minValue && !nodeList[i]->isTaken()) {
            minValue = nodeList[i]->getTotalCost();
            loc = i;
        }
    }
    addChildNodes(nodeList[loc]);

    return 0;
}

// open file from commandline and give each line to parseLine
void readFile(std::string fileName) {
    std::ifstream fileIn(fileName);
    std::string line;
    if(fileIn) {
        while(std::getline(fileIn, line)) {
            parseLine(line);
        }
    }
    fileIn.close();
}

// splits line by spaces
// first number is the vertexID
// second and third numbers are the x and y location values
// once the information is taken from the string,
// a new vertex is created and pushed onto the vertexList vector
void parseLine(std::string line) {
    std::istringstream iss(line);
    int ID, left, right;
    for(int i = 0; i < 3; i++) {
        std::string temp;
        iss >> temp;
        switch(i) {
            case 0:
                ID = stoi(temp);
                break;
            case 1:
                left = stoi(temp);
                break;
            case 2:
                right = stoi(temp);
                break;
        }
    }
    Vertex *temp = new Vertex(ID, std::make_pair(left, right));
    vertexList.push_back(temp);
}

// test function to create a node
// node construction handles graph generation automatically.
void createFirstNode() {
    Node *root = new Node(vertexList[0]->getID(), &vertexList);
    nodeList.push_back(root);
}

void addFirstNodes() {
    for(int i = 1; i < vertexList.size(); i++) {
        nodeList.push_back(new Node(i, nodeList[0], nodeList[0]->getTotalCost(), nodeList[0]->getGraph(), &vertexList));
    }
}

void addChildNodes(Node *currentNode) {
    Node *NodeID = currentNode->getParentID();
    for(unsigned int i = 0; i < nodeList.size(); i++) {
        if(!nodeList[i]->isTaken()) {
            if(nodeList[i]->getParentID() == NodeID && nodeList[i]->getvertexID() != currentNode->getvertexID()) {
                nodeList.push_back(new Node(nodeList[i]->getvertexID(), currentNode, currentNode->getTotalCost(), currentNode->getGraph(), &vertexList));
            }
        }
    }
}