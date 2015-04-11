#include <iostream>

#include "../headers/constants.h"
#include "../headers/dijkstra.h"
#include "../headers/Graph.h"

using namespace std;

int main() {
    Graph g;

    Node newNode;

    g.setSource(&newNode);

    vector<WeightPair> neighbors;
    Node anotherNode;

    neighbors.push_back(WeightPair(1, &anotherNode));

    g.getSource()->setNeighbors(neighbors);

    cout << g.contains(g.getAllVertices(), &anotherNode) << endl;

    // this->vertices.push_back(this->source);
    // this->vertices.push_back(new Node());

    // search(g, g.getSource());
}