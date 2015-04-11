#pragma once

#include <vector>

#include "constants.h"

class Node {
private:
    std::vector<std::pair<int, Node*>> neighbors;

public:
    Node();

    std::vector<std::pair<int, Node*>> getNeighbors() { return this->neighbors; };

    void setNeighbors(std::vector<std::pair<int, Node*>> neighbors) { this->neighbors = neighbors; };

    bool operator< (const Node& rhs) const;
};