#include <iostream>

#include "../headers/constants.h"
#include "../headers/dijkstra.h"
#include "../headers/Graph.h"

using namespace std;

int main() {
    Graph g;

    Node sourceNode, secondNode, thirdNode, fourthNode, fifthNode;
    vector<WeightPair> sourceNeighbors, secondNeighbors, thirdNeighbors, fourthNeighbors;

    g.setSource(&sourceNode);

    sourceNeighbors.push_back(WeightPair(1, &secondNode));
    sourceNeighbors.push_back(WeightPair(3, &thirdNode));
    sourceNode.setNeighbors(sourceNeighbors);

    secondNeighbors.push_back(WeightPair(1, &thirdNode));
    secondNeighbors.push_back(WeightPair(8, &fifthNode));
    secondNode.setNeighbors(secondNeighbors);

    thirdNeighbors.push_back(WeightPair(1, &fourthNode));
    thirdNeighbors.push_back(WeightPair(2, &fifthNode));
    thirdNode.setNeighbors(thirdNeighbors);

    fourthNeighbors.push_back(WeightPair(2, &fifthNode));
    fourthNode.setNeighbors(fourthNeighbors);

    map<Node*, Node*> pathMaps = search(g, g.getSource());

    cout << "sourceNode: " << &sourceNode << endl;
    cout << "secondNode: " << &secondNode << endl;
    cout << "thirdNode: " << &thirdNode << endl;
    cout << "fourthNode: " << &fourthNode << endl;
    cout << "fifthNode: " << &fifthNode << endl;

    Node* temp = &fifthNode;
    while (pathMaps.count( temp )) {
        temp = pathMaps[temp];
        cout << "temp: " << temp << endl;
    }
}