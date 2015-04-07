#include <iostream>

#include "../headers/Graph.h"

using namespace std;

Graph::Graph() {
    cout << "Creating a graph" << endl;

    this->source = new Node();

    this->vertices.push_back(this->source);
    this->vertices.push_back(new Node());
}