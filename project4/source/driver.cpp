#include <iostream>

#include "../headers/constants.h"
#include "../headers/dijkstra.h"
#include "../headers/Graph.h"

using namespace std;

int main() {
    Graph g;

    Node sourceNode, secondNode, thirdNode/*, fourthNode, fifthNode*/;
    vector<WeightPair> sourceNeighbors, secondNeighbors/*, thirdNeighbors*/;

    g.setSource(&sourceNode);

    sourceNeighbors.push_back(WeightPair(1, &secondNode));
    sourceNeighbors.push_back(WeightPair(3, &thirdNode));

    secondNeighbors.push_back(WeightPair(1, &thirdNode));

    sourceNode.setNeighbors(sourceNeighbors);
    secondNode.setNeighbors(secondNeighbors);

    map<Node*, Node*> pathMaps = search(g, g.getSource());

    cout << "sourceNode: " << &sourceNode << endl;
    cout << "secondNode: " << &secondNode << endl;
    cout << "thirdNode: " << &thirdNode << endl;

    Node* temp = &thirdNode;
    while (pathMaps.count( temp )) {
        temp = pathMaps[temp];
        cout << "temp: " << temp << endl;
    }
}