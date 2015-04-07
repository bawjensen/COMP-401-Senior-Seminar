#pragma once

#include "Node.h"

class Graph {
private:
    Node* source;
    std::vector<Node*> vertices;

public:
    Graph();

    Node* getSource() { return this->source; };
    std::vector<Node*> getVertices() { return this->vertices; };
};