#include <climits>
#include <iostream>
#include <map>

#include "../headers/constants.h"
#include "../headers/dijkstra.h"

using namespace std;

MinQueue reconstructQueue(MinQueue minQueue, Node* element, int newWeight) {
    MinQueue newMinQueue;

    while (!minQueue.empty()) {
        WeightPair elem = minQueue.top();
        minQueue.pop();

        if (elem.second == element) {
            elem.first = newWeight;
        }

        newMinQueue.push(elem);
    }

    return newMinQueue;
}

map<Node*, Node*> search(Graph g, Node* source) {
    MinQueue minQueue;

    map<Node*, int> distMap;
    map<Node*, Node*> prevMap;

    vector<Node*> vertices = g.getAllVertices();
    for (int i = 0, l = vertices.size(); i < l; ++i) {
        Node* v = vertices[i];

        if (v != source) {
            distMap[v] = INT_MAX;
            prevMap[v] = NULL;
        }

        minQueue.push(pair<int, Node*>(distMap[v], v));
    }

    while (!minQueue.empty()) {
        Node* u = minQueue.top().second;    // Grab the next node from the top
        minQueue.pop();                     // Remove it from the queue

        vector<pair<int, Node*>> neighbors = u->getNeighbors();
        for (int i = 0, l = neighbors.size(); i < l; ++i) {
            int w = neighbors[i].first;
            Node* v = neighbors[i].second;

            int alt = distMap[u] + w;

            if (alt < distMap[v]) {
                distMap[v] = alt;
                prevMap[v] = u;
                minQueue = reconstructQueue(minQueue, v, alt);
            }
        }
    }

    return prevMap;
}