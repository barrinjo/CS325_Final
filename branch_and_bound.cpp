#include "branch_and_bound.hpp"

std::vector<Vertex*> vertexList;
std::vector<Node*> nodeList;

int main(int argc, char ** argv) {
    readFile(argv[1]);
    createFirstNode();
    addChildNodes(0);

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

void addChildNodes(int NodeID) {
    for(int i = 0; i < vertexList.size(); i++) {
        if(i != NodeID) {
            if(vertexList[NodeID]->getVisitedBy().size()) {
                std::vector< int > temp = vertexList[NodeID]->getVisitedBy();
                if(!std::count(temp.begin(), temp.end(), NodeID)) {
                    vertexList[NodeID]->addVisited(i);
                    nodeList.push_back(new Node(i, NodeID, nodeList[NodeID]->getTotalCost(), nodeList[NodeID]->getGraph(), &vertexList));
                }
            } else {
                vertexList[NodeID]->addVisited(i);
                nodeList.push_back(new Node(i, NodeID, nodeList[NodeID]->getTotalCost(), nodeList[NodeID]->getGraph(), &vertexList));
            }
        }
    }
}
