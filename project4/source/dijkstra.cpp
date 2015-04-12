#include <climits>
#include <iostream>
#include <map>

#include "../headers/constants.h"
#include "../headers/dijkstra.h"

using namespace std;

MinQueue reconstructQueue(MinQueue minQueue, Node* element, int newWeight) {
    MinQueue newMinQueue;

    while (!minQueue.empty()) {
        // Node* node = minQueue.top();
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

    // minQueue.push(pair<int, Node*>(0, source));

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

    // while (!minQueue.empty()) {
    //     pair<int, Node*> popped = minQueue.top();
    //     minQueue.pop();
    //     cout << "Popped: " << popped.first << endl;
    // }

// 3      for each vertex v in Graph:           
// 4          if v ≠ source
// 5              dist[v] ← infinity            // Unknown distance from source to v
// 6              prev[v] ← undefined           // Predecessor of v
// 7          end if
// 8          Q.add_with_priority(v, dist[v])
// 9      end for 
// 10
// 11     while Q is not empty:               // The main loop
// 12         u ← Q.extract_min()            // Remove and return best vertex
// 13         for each neighbor v of u:
// 14             alt = dist[u] + length(u, v) 
// 15             if alt < dist[v]
// 16                 dist[v] ← alt
// 17                 prev[v] ← u
// 18                 Q.decrease_priority(v, alt)
// 19             end if
// 20         end for
// 21     end while
// 21     return prev[]
}