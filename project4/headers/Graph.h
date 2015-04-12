#pragma once

#include <vector>

#include "constants.h"
#include "Node.h"

class Graph {
private:
    Node* source;

public:
    Graph();

    Node* getSource() { return this->source; };

    void setSource(Node* source) { this->source = source; };

    bool contains(std::vector<Node*> nodes, Node* node);

    void recursiveFindVertices(std::vector<Node*>& nodes, Node* curr);
    std::vector<Node*> getAllVertices();
};