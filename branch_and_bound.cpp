#include "branch_and_bound.hpp"

int main(int argc, char ** argv) {
    readFile(argv[1]);
    createFirstNode();

    return 0;
}

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
    vertex temp = vertex(ID, std::make_pair(left, right));
    vertexList.push_back(temp);
}

void createFirstNode() {
    node root = node(vertexList[0]);
    nodeList.push_back(root);
}

std::vector< std::vector< int > > createGraph(int vertexID) {
    std::vector< std::vector< int > > graph;
    for(unsigned int i = 0; i < vertexList.size(); i++) {
        std::vector< int > row;
        for(unsigned int j = 0; j < vertexList.size(); j++) {
            if(i == j) {
                row.push_back(0);
            }
            else {
                int dist;
                int left = vertexList[i].location.first - vertexList[j].location.first;
                int right = vertexList[i].location.second - vertexList[j].location.second;
                dist = round(sqrt(left*left + right*right));
                row.push_back(dist);
            }
        }
        graph.push_back(row);
    }
    return graph;
}