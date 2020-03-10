#include "branch_and_bound.hpp"

std::vector<vertex> vertexList;

int main(int argc, char ** argv) {
    readFile(argv[1]);
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