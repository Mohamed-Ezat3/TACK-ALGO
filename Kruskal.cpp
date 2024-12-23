#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Edge structure to store edges
struct Edge {
    int u, v, weight;
    Edge(int u, int v, int weight) : u(u), v(v), weight(weight) {}
};

// Graph class
class Graph {
private:
    int V; // Number of vertices
    vector<Edge> edges;

    // Find function with path compression
    int findSet(vector<int>& parent, int i) {
        if (parent[i] != i)
            parent[i] = findSet(parent, parent[i]);
        return parent[i];
    }

    // Union function with union by rank
    void unionSet(vector<int>& parent, vector<int>& rank, int x, int y) {
        int rootX = findSet(parent, x);
        int rootY = findSet(parent, y);

        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }

public:
    Graph(int vertices) : V(vertices) {}

    void addEdge(int u, int v, int weight) {
        edges.emplace_back(u, v, weight);
    }

    vector<Edge> kruskal() {
        vector<Edge> mst;
        vector<int> parent(V), rank(V, 0);

        // Initialize Union-Find
        for (int i = 0; i < V; ++i)
            parent[i] = i;

        // Sort edges by weight
        sort(edges.begin(), edges.end(), [](Edge& a, Edge& b) {
            return a.weight < b.weight;
        });

        // Process edges
        for (const auto& edge : edges) {
            int rootU = findSet(parent, edge.u);
            int rootV = findSet(parent, edge.v);

            if (rootU != rootV) { // No cycle
                mst.push_back(edge);
                unionSet(parent, rank, rootU, rootV);

                if (mst.size() == V - 1)
                    break;
            }
        }

        return mst;
    }
};

int main() {
    Graph g(4);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 6);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 3, 15);
    g.addEdge(2, 3, 4);

    vector<Edge> mst = g.kruskal();
    cout << "Edges in MST:" << endl;
    for (const auto& edge : mst) {
        cout << edge.u << " -- " << edge.v << " == " << edge.weight << endl;
    }

    return 0;
}
