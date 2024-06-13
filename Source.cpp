// Program Name: Minimum Spanning Tree Generator
// Programmer Name: Yuliya Wickens
// Description: Generates a Minimum Spanning Tree (MST) using Prim's algorithm from a given connected, undirected graph.
// Date Created: [6/12/2024]


#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <utility>
#include <limits>
#include <queue>

using namespace std;

class Graph {
public:
    int numberOfVertices;
    vector<list<pair<int, int>>> adjacencyList;

    Graph(int V = 0) : numberOfVertices(V) {
        adjacencyList.resize(V);
    }

    void addEdge(int u, int v, int w) {
        adjacencyList[u].push_back(make_pair(v, w));
        adjacencyList[v].push_back(make_pair(u, w));
    }

    void printGraph() {
        if (numberOfVertices == 0) {
            cout << "Empty Graph Will Be Created" << endl;
            return;
        }
        cout << "Full Graph – Adjacency List" << endl;
        for (int i = 0; i < numberOfVertices; ++i) {
            cout << "Adj[" << i << "] -> ";
            for (auto& x : adjacencyList[i]) {
                cout << "(" << x.first << ", " << x.second << ") ";
            }
            cout << endl;
        }
    }

    void primMST() {
        if (numberOfVertices == 0) {
            cout << "Empty Graph – No MST" << endl;
            return;
        }

        vector<bool> inMST(numberOfVertices, false);
        vector<int> key(numberOfVertices, numeric_limits<int>::max());
        vector<int> parent(numberOfVertices, -1);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        key[0] = 0;
        pq.push({ 0, 0 });
        vector<list<pair<int, int>>> mstAdjList(numberOfVertices);

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            inMST[u] = true;

            for (auto& edge : adjacencyList[u]) {
                int v = edge.first;
                int weight = edge.second;

                if (!inMST[v] && weight < key[v]) {
                    parent[v] = u;
                    key[v] = weight;
                    pq.push(make_pair(key[v], v));
                    mstAdjList[u].push_back({ v, weight });
                    mstAdjList[v].push_back({ u, weight }); // Since it's undirected
                }
            }
        }

        cout << "Minimum Spanning Tree" << endl;
        int totalCost = 0;
        for (int i = 1; i < numberOfVertices; ++i) {
            if (parent[i] != -1) {
                cout << "Edge: " << parent[i] << " - " << i << " weight: " << key[i] << endl;
                totalCost += key[i];
            }
        }
        cout << "Total cost of MST: " << totalCost << endl;
    
    cout << "MST Graph – Adjacency List" << endl;
    for (int i = 0; i < numberOfVertices; ++i) {
        cout << "Adj[" << i << "] -> ";
        for (auto& x : mstAdjList[i]) {
            cout << "(" << x.first << ", " << x.second << ") ";
        }
        cout << endl;
    }
    }
};

int main() {
    cout << "Welcome to the MST Test Program" << endl;
    cout << "Enter file name for graph data: ";
    string inputFileName;
    cin >> inputFileName;

    ifstream inputFile(inputFileName);
    if (!inputFile.is_open()) {
        cout << "file " << inputFileName << " cannot be opened or does not exist – program terminated" << endl;
        return 1;
    }

    int V, E;
    if (!(inputFile >> V >> E)) {
        cout << "Skipping invalid or empty line" << endl;
        return 1;
    }

    if (V < 0) {
        cout << "ERROR: number of vertices: " << V << " is less than zero" << endl;
        return 1;
    }
    else if (V == 0 || E < V - 1) {
        cout << "ERROR: Invalid or insufficient edges to form a connected graph" << endl;
        return 1;
    }

    Graph graph(V);
    int u, v, w;
    while (E-- && inputFile >> u >> v >> w) {
        if (u < 0 || u >= V || v < 0 || v >= V || w <= 0) {
            cout << "Invalid edge: " << u << ", " << v << ", " << w << " - Edge request ignored" << endl;
            continue;
        }
        graph.addEdge(u, v, w);
    }

    graph.printGraph();
    graph.primMST();

    cout << "Thank you for running the MST Test Program written by <Yuliya>!" << endl;
    return 0;
}

