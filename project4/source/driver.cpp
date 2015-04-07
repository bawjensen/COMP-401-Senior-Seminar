#include <iostream>

#include "../headers/Graph.h"
#include "../headers/dijkstra.h"

using namespace std;

int main() {
    Graph g;

    search(g, g.getSource());
}