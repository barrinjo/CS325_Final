#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

#include "node.hpp"

void readFile(std::string fileName);
void parseLine(std::string line);
void createFirstNode();
void addFirstNodes();
void addChildNodes(Node *currentNode);
int createTour();
bool childNodesExist(Node *node);
