#include <iostream>

#include "../headers/constants.h"
#include "../headers/Node.h"

using namespace std;

Node::Node() {
    cout << "Creating a node" << endl;
}

bool Node::operator<(const Node& rhs) const {
    return false;
}