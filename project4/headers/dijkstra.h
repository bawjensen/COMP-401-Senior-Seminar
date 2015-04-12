#pragma once

#include <map>

#include "constants.h"
#include "Graph.h"
#include "Node.h"

std::map<Node*, Node*> search(Graph g, Node* source);