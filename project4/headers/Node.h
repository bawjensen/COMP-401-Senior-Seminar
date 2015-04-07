#pragma once

#include <vector>

class Node {
private:
    std::vector<std::pair<int, Node*>> neighbors;

public:
    Node();

    std::vector<std::pair<int, Node*>> getNeighbors() { return this->neighbors; };

    bool operator< (const Node& rhs) const;
};