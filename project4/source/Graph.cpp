#include <iostream>

#include "../headers/constants.h"
#include "../headers/Graph.h"

using namespace std;

Graph::Graph() {
    cout << "Creating a graph" << endl;
}

bool Graph::contains(vector<Node*> nodes, Node* node) {
    for (vector<Node*>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
        if (*it == node) {
            return true;
        }
    }

    return false;
}

void Graph::recursiveFindVertices(vector<Node*>& nodes, Node* curr) {
    vector<WeightPair> neighbors = curr->getNeighbors();

    for (vector<WeightPair>::iterator it = neighbors.begin(); it != neighbors.end(); ++it) {
        Node* ptr = (*it).second;

        if (!this->contains(nodes, ptr)) {
            nodes.push_back(ptr);
            this->recursiveFindVertices(nodes, ptr);
        }
    }
}

vector<Node*> Graph::getAllVertices() {
    vector<Node*> nodes;

    nodes.push_back(this->source);
    recursiveFindVertices(nodes, this->source);

    return nodes;
}