#pragma once

#include <queue>

#include "Node.h"

using WeightPair = std::pair<int, Node*>;
using MinQueue = std::priority_queue<WeightPair,
                    std::vector<WeightPair>,
                    std::greater<WeightPair>>;